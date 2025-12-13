/**
 * Copyright (c) 2025 OwlTech
 *
 * \file uc_led_blink.c
 * \brief
 * \author OwlTech
 * \date Nov 3, 2025
 */
#if defined(USE_CASE_RUN_IDX_1)
/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "uc_traffic_light.h"

#include "system.h"
#include "rcc.h"
#include "gpio.h"
#include "cortex_m4.h"
#include "fw_debug.h"
#include "traffic_light_state.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HSE_RCC_TIMEOUT	100u

/** \name Traffic Light Parameters. */
/**@{*/
#define TL_LED_NUM			(4u)
#define TL_IRQ_PRIO_CTRL 	(15u)
/**@{*/

/** \name Traffic Light Timing Parameters. Granularity: 10 ms. */
/**@{*/
#define TL_TIME_STAT_BLINK	(30u)
#define TL_TIME_IDLE_BLINK	(50u)
#define TL_TIME_STOP		(200u)
#define TL_TIME_PREP_GO		(100u)
#define TL_TIME_GO			(300u)
#define TL_TIME_PREP_STOP	(100u)
/**@{*/

/** \name SysTick timer settings. */
/**@{*/
#define TL_SYSTICK_10MS_RELOAD_VAL	(160000u-1u) //!< Calculated based on 16 MHz clock
/**@}*/

/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef void t_task (void);

static uint32_t g_tl_main_trg_10ms;
static uint32_t g_tl_stat_trg_10ms;

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static void uc_traffic_light_init(t_GPIO_RegDef * const p_led_port, t_GPIO_RegDef * const p_btn_port);

static void tl_task_reset(void);
static void tl_task_idle(void);
static void tl_task_stop(void);
static void tl_task_prep_go(void);
static void tl_task_go(void);
static void tl_task_prep_stop(void);
static const uint8_t decode_state_order(const t_tl_state tl_state);
static void uc_traffic_light_routine(void);
static void uc_traffic_light_work_callback(void);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
static void uc_traffic_light_init(t_GPIO_RegDef * const p_led_port, t_GPIO_RegDef * const p_btn_port)
{
	t_error_code init_stat = e_ec_timeout;

	DEBUG_PRINT("=========================\n");
	DEBUG_PRINT("| Traffic Light Use Case |\n");
	DEBUG_PRINT("=========================\n\n");

	DEBUG_PRINT("Initialization...\n");

	// 1. Enable the HSE clock using HSEON bit (RCC_CR)
	// 2. Enable the HSE bypass bit (bypass the oscillator with an ext clock)
	const t_clock_source clk_src = e_clk_hse;
	RCC_enable_source(clk_src, TRUE);

	// 3. Wait until HSE clock enabled
	uint32_t timeout = HSE_RCC_TIMEOUT;
	while ((RCC_get_source_stat(clk_src) == FALSE) && (timeout > 0u)) {
		timeout--;
	}

	// 4. Switch the system clock to HSE
	if (timeout > 0u) {
		DEBUG_PRINT("  - HSE clock enable SUCCESS\n");

		const t_clock_cfgr clk_cfg = {
			.clk_sw = e_clk_sys_hsi,
			.clk_hpre = e_clk_hpre_0
		};
		init_stat = RCC_set_config(&clk_cfg);
		DEBUG_PRINT((init_stat == e_ec_no_error) ? "  - HSE Clock switch SUCCESS\n" : "  - HSE Clock switch FAIL\n");
		DEBUG_PRINT("  - AHB1 peripheral clock frequency: %lu MHz\n", RCC_get_peri_clock_freq(e_peri_ahb1) / RCC_CLOCK_FREQ_TO_MHZ);
	} else {
		DEBUG_PRINT("  - HSE clock enable FAIL.\n");
	}

	// 5. Enable GPIO ports in normal mode
	const t_error_code led_en_stat = GPIO_port_enable(SYS_GPIO_LED_PORT, ENABLE, DISABLE);
	const t_error_code ctrl_en_stat = GPIO_port_enable(SYS_GPIO_BTN_PORT, ENABLE, DISABLE);
	DEBUG_PRINT(((led_en_stat == e_ec_no_error) && (ctrl_en_stat == e_ec_no_error)) ? "  - GPIO Enable SUCCESS\n" : "  - GPIO Enable FAIL\n");


	// 6. Configure GPIO for LED driver
	uint8_t succ_cnt = 0u;
	const uint8_t gpio_leds[TL_LED_NUM] = {SYS_PIN_STAT_LED, SYS_PIN_RED_LED, SYS_PIN_YEL_LED, SYS_PIN_GRN_LED};
	for (uint8_t led_sel= 0u; led_sel < TL_LED_NUM; led_sel++) {
		const t_gpio_handle gpio_led_cfg = {
			.p_gpio_reg = p_led_port,
			.mode_sel = e_gpio_mode_output,
			.open_drain_en = FALSE,
			.speed = e_gpio_speed_low,
			.pupd = e_gpio_pupd_no,
			.alt_func_sel = 0u
		};
		succ_cnt += (e_ec_no_error == GPIO_port_config(&gpio_led_cfg, gpio_leds[led_sel])) ? 1u : 0u;
	}
	DEBUG_PRINT((succ_cnt == TL_LED_NUM) ? "  - GPIO LED Configure SUCCESS\n" : "  - GPIO LED Configure FAIL\n");

	// 7. Configure GPIO for BUTTON driver
	const t_gpio_handle gpio_btn_cfg = {
		.p_gpio_reg = p_btn_port,
		.mode_sel = e_gpio_mode_it_ft,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_fast,
		.pupd = e_gpio_pupd_no,
		.alt_func_sel = 0u
	};
	const t_error_code ctrl_cfg_stat = GPIO_port_config(&gpio_btn_cfg, SYS_PIN_ONBOARD_BTN);
	const t_error_code ctrl_it_cfg_stat = GPIO_interrupt_config(SYS_GPIO_BTN_PORT, SYS_PIN_ONBOARD_BTN, TL_IRQ_PRIO_CTRL);
	DEBUG_PRINT(((ctrl_cfg_stat == e_ec_no_error) && (ctrl_it_cfg_stat == e_ec_no_error)) ? "  - GPIO IT BUTTON Configure SUCCESS\n" :
		"  - GPIO IT BUTTON Configure FAIL\n");

	// 8. Enable SysTick timer
	CORTEX_M4_systick_configure(TRUE, TRUE);
	CORTEX_M4_systick_set_preload(TL_SYSTICK_10MS_RELOAD_VAL);
	CORTEX_M4_systick_enable(TRUE);

	// 10. Initialize global variables
	g_tl_main_trg_10ms = 0u;
	g_tl_stat_trg_10ms = 0u;

	DEBUG_PRINT("...Done!\n");
}

static void tl_task_reset(void)
{
	t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

	GPIO_set_pin(p_tl_led_port, SYS_PIN_STAT_LED, DISABLE);
	GPIO_set_pin(p_tl_led_port, SYS_PIN_RED_LED, DISABLE);
	GPIO_set_pin(p_tl_led_port, SYS_PIN_YEL_LED, DISABLE);
	GPIO_set_pin(p_tl_led_port, SYS_PIN_GRN_LED, DISABLE);
}

static void tl_task_idle(void)
{
	if (TRAFFIC_LIGHT_STATE_changed() != FALSE) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_set_pin(p_tl_led_port, SYS_PIN_RED_LED, DISABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_YEL_LED, ENABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_GRN_LED, DISABLE);
	}

	if (g_tl_main_trg_10ms == 0u) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_toggle_pin(p_tl_led_port, SYS_PIN_YEL_LED);
		g_tl_main_trg_10ms = TL_TIME_IDLE_BLINK;
	}
}

static void tl_task_stop(void)
{
	if (TRAFFIC_LIGHT_STATE_changed() != FALSE) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_set_pin(p_tl_led_port, SYS_PIN_RED_LED, ENABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_YEL_LED, DISABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_GRN_LED, DISABLE);
	}

	if (g_tl_main_trg_10ms == 0u) {
		g_tl_main_trg_10ms = TL_TIME_PREP_GO;
		TRAFFIC_LIGHT_STATE_setter(e_tl_st_prep_go);
	}
}

static void tl_task_prep_go(void)
{
	if (TRAFFIC_LIGHT_STATE_changed() != FALSE) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_set_pin(p_tl_led_port, SYS_PIN_RED_LED, ENABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_YEL_LED, ENABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_GRN_LED, DISABLE);
	}

	if (g_tl_main_trg_10ms == 0u) {
		g_tl_main_trg_10ms = TL_TIME_GO;
		TRAFFIC_LIGHT_STATE_setter(e_tl_st_go);
	}
}

static void tl_task_go(void)
{
	if (TRAFFIC_LIGHT_STATE_changed() != FALSE) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_set_pin(p_tl_led_port, SYS_PIN_RED_LED, DISABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_YEL_LED, DISABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_GRN_LED, ENABLE);
	}

	if (g_tl_main_trg_10ms == 0u) {
		g_tl_main_trg_10ms = TL_TIME_PREP_STOP;
		TRAFFIC_LIGHT_STATE_setter(e_tl_st_prep_stop);
	}
}

static void tl_task_prep_stop(void)
{
	if (TRAFFIC_LIGHT_STATE_changed() != FALSE) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_set_pin(p_tl_led_port, SYS_PIN_RED_LED, DISABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_YEL_LED, ENABLE);
		GPIO_set_pin(p_tl_led_port, SYS_PIN_GRN_LED, DISABLE);
	}

	if (g_tl_main_trg_10ms == 0u) {
		g_tl_main_trg_10ms = TL_TIME_STOP;
		TRAFFIC_LIGHT_STATE_setter(e_tl_st_stop);
	}
}

static const uint8_t decode_state_order(const t_tl_state tl_state)
{
	uint8_t ret_val = 0u;

	switch (tl_state) {
		case e_tl_st_stop:
			ret_val = 1u;
			break;
		case e_tl_st_prep_go:
			ret_val = 2u;
			break;
		case e_tl_st_go:
			ret_val = 3u;
			break;
		case e_tl_st_prep_stop:
			ret_val = 4u;
			break;
		case e_tl_st_idle:
		default:
			break;
	}

	return ret_val;
}

static void uc_traffic_light_routine(void)
{
	// Blink status LED
	if (g_tl_stat_trg_10ms == 0u) {
		t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);

		GPIO_toggle_pin(p_tl_led_port, SYS_PIN_STAT_LED);
		g_tl_stat_trg_10ms = TL_TIME_STAT_BLINK;
	}

	t_task * const p_task_register[] = {
		&tl_task_idle,
		&tl_task_stop,
		&tl_task_prep_go,
		&tl_task_go,
		&tl_task_prep_stop,
	};

	const uint8_t task_sel = decode_state_order(TRAFFIC_LIGHT_STATE_getter());

	p_task_register[task_sel]();

	g_tl_main_trg_10ms--;
	g_tl_stat_trg_10ms--;
}

static void uc_traffic_light_work_callback(void)
{
	static t_bool tl_idle = FALSE;

	tl_idle ^= TRUE;

	if (tl_idle == FALSE) {
		g_tl_main_trg_10ms = TL_TIME_PREP_STOP;
		TRAFFIC_LIGHT_STATE_setter(e_tl_st_stop);
		DEBUG_PRINT("-> Traffic light started.\n");
	} else {
		g_tl_main_trg_10ms = TL_TIME_IDLE_BLINK;
		TRAFFIC_LIGHT_STATE_setter(e_tl_st_idle);
		DEBUG_PRINT("-> Traffic light out of order.\n");
	}
}


/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	GPIO_irq_handle(SYS_PIN_ONBOARD_BTN);
	uc_traffic_light_work_callback();
}

void SysTick_Handler(void)
{
	uc_traffic_light_routine();
}

void UC_TRAFFIC_LIGHT_run(void)
{
	t_GPIO_RegDef * const p_tl_led_port = GPIO_get_port_base(SYS_GPIO_LED_PORT);
	t_GPIO_RegDef * const p_tl_ctrl_port = GPIO_get_port_base(SYS_GPIO_BTN_PORT);

	if ((p_tl_led_port != NULL) && (p_tl_ctrl_port != NULL)) {
		uc_traffic_light_init(p_tl_led_port, p_tl_ctrl_port);
		tl_task_reset();
		TRAFFIC_LIGHT_STATE_init();
	} else {
		DEBUG_PRINT("Invalid GPIO PORT reference.");
	}

	while(1);
}
#endif /* USE_CASE_RUN_IDX */
/*** EOF ***/
