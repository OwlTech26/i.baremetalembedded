/**
 * Copyright (c) 2025 OwlTech
 *
 * \file uc_light_det_i2c.c
 * \brief
 * \author OwlTech
 * \date Dec 8, 2025
 */

#if defined(USE_CASE_RUN_IDX_3)
/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "uc_light_det_i2c.h"

#include "rcc.h"
#include "mport.h"
#include "gpio.h"
#include "cortex_m4.h"
#include "fw_debug.h"
#include "system.h"
#include "seif_tsl2561.h"
#include "seif_veml6040.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HSE_RCC_TIMEOUT			100u

#define SENS_IRQ_PRIO_BTN 			(15u)
#define SENS_IT_EDGE_TRG_BTN 		(e_gpio_it_trg_sel_ft)
#define SENS_IRQ_PRIO_LUX_INT 		(14u)
#define SENS_IT_EDGE_TRG_LUX_INT 	(e_gpio_it_trg_sel_ft)

#define VEML6040_CHIP_ID_WORD		(0xCAFEu)

/** \name SysTick timer settings. */
/**@{*/
#define SENS_SYSTICK_10MS_RELOAD_VAL	(40000u-1) //!< Calculated based on 4 MHz clock
#define SENS_SYS_TICK_WAIT				(300u) 	   //!< Sensor data refresh rate: 3 sec
/**@}*/



/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
static uint32_t SENS_SYS_TICK;

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static inline void uc_light_det_i2c_set_alert(void);

static inline void uc_light_det_i2c_clear_alert(void);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static void uc_light_det_i2c_init(void);

static void uc_light_det_i2c_systick_init(void);

static void uc_light_det_i2c_sensor_init(void);

static void uc_light_det_i2c_enable_lux_intr(void);

static void uc_light_det_i2c_provide_data(void);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline void uc_light_det_i2c_set_alert(void)
{
	GPIO_set_pin(GPIO_get_port_base(SYS_GPIO_LED_PORT), SYS_PIN_RED_LED, ENABLE);
}

static inline void uc_light_det_i2c_clear_alert(void)
{
	GPIO_set_pin(GPIO_get_port_base(SYS_GPIO_LED_PORT), SYS_PIN_RED_LED, DISABLE);
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static void uc_light_det_i2c_init(void)
{
	t_error_code init_stat = e_ec_timeout;

	DEBUG_PRINT("==================================================\n");
	DEBUG_PRINT("| TSL2561-M and VEML6040-M Light Sensor Use Case |\n");
	DEBUG_PRINT("==================================================\n\n");

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
		DEBUG_PRINT("  - HSE Clock enable SUCCESS\n");

		const t_clock_cfgr clk_cfg = {
			.clk_sw = e_clk_sys_hse,
			.clk_hpre = e_clk_hpre_2,
			.clk_ppre1 = e_clk_ppre_2
		};
		init_stat = RCC_set_config(&clk_cfg);
		DEBUG_PRINT((init_stat == e_ec_no_error) ? "  - HSE Clock switch SUCCESS\n" : "  - HSE Clock switch FAIL\n");
		DEBUG_PRINT("  - APB1 peripheral clock frequency: %lu MHz\n", RCC_get_peri_clock_freq(e_peri_apb1) / RCC_CLOCK_FREQ_TO_MHZ);
	} else {
		DEBUG_PRINT("  - HSE clock enable FAIL.\n");
	}

	// 5. Initialize Sensor Interface
	const t_error_code mport_stat = MPORT_i2c_init();
	DEBUG_PRINT((mport_stat == e_ec_no_error) ? "  - MPORT init SUCCESS\n" : "  - MPORT init FAIL\n");

	// 6. Enable GPIO ports in normal mode
	GPIO_port_enable(SYS_GPIO_LED_PORT, ENABLE, DISABLE);
	GPIO_port_enable(SYS_GPIO_BTN_PORT, ENABLE, DISABLE);

	// 7. Configure GPIO for LED system threshold alert
	const t_gpio_handle gpio_led_cfg = {
		.p_gpio_reg = GPIO_get_port_base(SYS_GPIO_LED_PORT),
		.mode_sel = e_gpio_mode_output,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_low,
		.pupd = e_gpio_pupd_no,
		.alt_func_sel = 0u
	};
	const t_error_code led_cfg_stat = GPIO_port_config(&gpio_led_cfg, SYS_PIN_RED_LED);
	DEBUG_PRINT((led_cfg_stat == e_ec_no_error) ? "  - GPIO LED Configure SUCCESS\n" : "  - GPIO LED Configure FAIL\n");

	// 8. Configure GPIO for BUTTON driver
	const t_gpio_handle gpio_btn_cfg = {
		.p_gpio_reg = GPIO_get_port_base(SYS_GPIO_BTN_PORT),
		.mode_sel = e_gpio_mode_input,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_fast,
		.pupd = e_gpio_pupd_pu,
		.alt_func_sel = 0u
	};
	const t_error_code ctrl_cfg_stat = GPIO_port_config(&gpio_btn_cfg, SYS_PIN_ONBOARD_BTN);
	const t_error_code ctrl_it_cfg_stat = GPIO_interrupt_config(SYS_GPIO_BTN_PORT, SYS_PIN_ONBOARD_BTN, SENS_IRQ_PRIO_BTN, SENS_IT_EDGE_TRG_BTN);
	DEBUG_PRINT(((ctrl_cfg_stat == e_ec_no_error) && (ctrl_it_cfg_stat == e_ec_no_error)) ? "  - GPIO IT BUTTON Configure SUCCESS\n" :
		"  - GPIO IT BUTTON Configure FAIL\n");

	// 9. Initialize alert LED
	GPIO_set_pin(GPIO_get_port_base(SYS_GPIO_LED_PORT), SYS_PIN_RED_LED, DISABLE);
}

static void uc_light_det_i2c_systick_init(void)
{
	// Enable SysTick timer
	CORTEX_M4_systick_configure(TRUE, TRUE);
	CORTEX_M4_systick_set_preload(SENS_SYSTICK_10MS_RELOAD_VAL);
	CORTEX_M4_systick_enable(TRUE);
	SENS_SYS_TICK = 0u;
}

static void uc_light_det_i2c_sensor_init(void)
{
	// Initialize TSL2561 sensor
	const uint8_t tsl2561_id = SEIF_TSL2561_get_id();
	if (tsl2561_id == SYS_TSL2561_CHIP_ID) {
		INTENTIONALLY_UNUSED(SEIF_TSL2561_set_config(SYS_TSL2561_CFG_INTEG_INIT, SYS_TSL2561_CFG_GAIN_INIT));
		const uint8_t cfg_data_act = SEIF_TSL2561_get_config();
		const uint8_t cfg_data_exp = (b_to_uint32(SYS_TSL2561_CFG_GAIN_INIT) << 4u) | (uint8_t)SYS_TSL2561_CFG_INTEG_INIT;
		SEIF_TSL2561_clear_it();
		SEIF_TSL2561_set_pwr(TRUE);

		SEIF_TSL2561_set_it_threshold(SYS_TSL2561_CFG_IT_THRES_LOW, SYS_TSL2561_CFG_IT_THRES_HIGH);
		INTENTIONALLY_UNUSED(SEIF_TSL2561_set_it_ctrl(SYS_TSL2561_CFG_IT_TYPE, SYS_TSL2561_CFG_IT_PERS));

		DEBUG_PRINT((cfg_data_act == cfg_data_exp) ? "  - TSL2561 initialization SUCCESS.\n" : "  - TSL2561 initialization FAIL.\n");
	} else {
		DEBUG_PRINT("  - TSL2561 initialization: ChipID FAIL.\n");
	}

	// Initialize VEML6040 sensor
	SEIF_VEML6040_set_id(VEML6040_CHIP_ID_WORD);
	const uint16_t veml6040_id = SEIF_VEML6040_get_id();
	if (veml6040_id == VEML6040_CHIP_ID_WORD) {
		INTENTIONALLY_UNUSED(SEIF_VEML6040_set_config(SYS_VEML6040_CFG_INTEG_INIT, SYS_VEML60401_CFG_AF_INIT, TRUE));
		const uint8_t cfg_data_act = SEIF_VEML6040_get_config();
		const uint8_t cfg_data_exp = (3u << 4u) | ((uint8_t)SYS_VEML60401_CFG_AF_INIT << 1u);
		DEBUG_PRINT((cfg_data_act == cfg_data_exp) ? "  - VEML6040 initialization SUCCESS.\n" : "  - VEML6040 initialization FAIL.\n");
	} else {
		DEBUG_PRINT("  - VEML6040 initialization: ChipID FAIL.\n");
	}
}

static void uc_light_det_i2c_enable_lux_intr(void)
{
	// Enable GPIO for TSL2561 chip interrupt
	GPIO_port_enable(SYS_LUX_INT_GPIO_PORT, ENABLE, DISABLE);

	// Configure GPIO for LUX input IT
	const t_gpio_handle gpio_luxint_cfg = {
		.p_gpio_reg = GPIO_get_port_base(SYS_LUX_INT_GPIO_PORT),
		.mode_sel = e_gpio_mode_input,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_fast,
		.pupd = e_gpio_pupd_pu,
		.alt_func_sel = 0u
	};
	const t_error_code luxint_cfg_stat = GPIO_port_config(&gpio_luxint_cfg, SYS_LUX_INT_IN);
	const t_error_code luxint_it_cfg_stat = GPIO_interrupt_config(SYS_LUX_INT_GPIO_PORT, SYS_LUX_INT_IN, SENS_IRQ_PRIO_LUX_INT, SENS_IT_EDGE_TRG_LUX_INT);
	DEBUG_PRINT(((luxint_cfg_stat == e_ec_no_error) && (luxint_it_cfg_stat == e_ec_no_error)) ? "  - GPIO LUX IT Configure SUCCESS\n" :
		"  - GPIO GPIO LUX IT FAIL\n");
}

static void uc_light_det_i2c_provide_data(void)
{
	const uint16_t tsl_visible_ir = SEIF_TSL2561_read_visible_ir();
	const uint16_t tsl_ir_only = SEIF_TSL2561_read_ir_only();

	t_veml6040_data veml_data = {0};
	SEIF_VEML6040_read_light_data(&veml_data);

	DEBUG_PRINT("----------------------------------------------------------------\n");
	DEBUG_PRINT("| Light  | IRED  |  RED  | GREEN | BLUE  | White |   Valid     |\n");
	DEBUG_PRINT("| %5u  | %5u | %5u | %5u | %5u | %5u | %5u-%5u |\n",
		tsl_visible_ir, tsl_ir_only, veml_data.red, veml_data.green, veml_data.blue, veml_data.white,
		SYS_TSL2561_CFG_IT_THRES_LOW, SYS_TSL2561_CFG_IT_THRES_HIGH);
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void UC_LIGHT_DET_I2C_run(void)
{
	uc_light_det_i2c_init();

	// Initialize system sensors
	uc_light_det_i2c_sensor_init();

	// Initialize system tick for data sampling
	uc_light_det_i2c_systick_init();

	// Enable TSL2561 chip lux interrupt
	uc_light_det_i2c_enable_lux_intr();

	while(1) {
		if (SENS_SYS_TICK_WAIT == SENS_SYS_TICK) {
			// Read sensor data
			uc_light_det_i2c_provide_data();

			SENS_SYS_TICK = 0u;
		}
	}
}

void SysTick_Handler(void)
{
	SENS_SYS_TICK++;
}

// Lux interrupt
void EXTI9_5_IRQHandler(void)
{
	GPIO_irq_handle(SYS_LUX_INT_IN);
	uc_light_det_i2c_set_alert();
}

// BTN interrupt
void EXTI15_10_IRQHandler(void)
{
	GPIO_irq_handle(SYS_PIN_ONBOARD_BTN);
	uc_light_det_i2c_clear_alert();
	SEIF_TSL2561_clear_it();
}

#endif /* USE_CASE_RUN_IDX_3 */

/*** EOF ***/
