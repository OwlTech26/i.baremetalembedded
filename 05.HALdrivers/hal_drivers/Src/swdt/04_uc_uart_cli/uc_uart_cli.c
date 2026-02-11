/**
 * Copyright (c) 2025 OwlTech
 *
 * \file uc_usart_cli.c
 * \brief
 * \author OwlTech
 * \date Feb 10, 2026
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "uc_uart_cli.h"

#include "rcc.h"
#include "gpio.h"
#include "usart.h"
#include "system.h"
#include "fw_debug.h"

/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HSE_RCC_TIMEOUT			100u

/** \name UART configuration Parameters. */
/**@{*/
#define UC_UART_CLI_PIN_NUM_ALT_MODE	(2u)
#define UC_UART_CLI_ERR_STAT_GPIO_EN	(1u << 0u)
#define UC_UART_CLI_ERR_STAT_GPIO_CFG	(1u << 1u)
#define UC_UART_CLI_ERR_STAT_USART_EN	(1u << 2u)
#define UC_UART_CLI_ERR_STAT_USART_CFG	(1u << 3u)
/**@{*/


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.

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
t_error_code uc_uart_cli_usart_init(void);

static void uc_uart_cli_init(void);



/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
t_error_code uc_uart_cli_usart_init(void)
{
	t_error_code ret_stat = e_ec_invalid_param;
	uint32_t err_stat = ERR_STAT_NO_ERROR;

	// 1. Enable GPIO port for USART
	const t_error_code usart_gpio_en_stat = GPIO_port_enable(SYS_USART_GPIO_PORT, ENABLE, DISABLE);
	err_stat |= (usart_gpio_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : UC_UART_CLI_ERR_STAT_GPIO_EN;

	// 2. Configure GPIO pins for UART
	t_GPIO_RegDef * const p_gpio_usart = GPIO_get_port_base(SYS_USART_GPIO_PORT);
	t_gpio_handle gpio_usart_cfg = {
		.p_gpio_reg = p_gpio_usart,
		.mode_sel = e_gpio_mode_alt_func,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_medium,
		.pupd = e_gpio_pupd_no,
		.alt_func_sel = SYS_USART_ALT_FUNC
	};
	uint8_t succ_cnt = 0u;
	const uint8_t usart_pins[UC_UART_CLI_PIN_NUM_ALT_MODE] = {SYS_USART_RX, SYS_USART_TX};
	for (uint8_t pin_sel= 0u; pin_sel < UC_UART_CLI_PIN_NUM_ALT_MODE; pin_sel++) {
		succ_cnt += (e_ec_no_error == GPIO_port_config(&gpio_usart_cfg, usart_pins[pin_sel])) ? 1u : 0u;
	}
	err_stat |= (succ_cnt == UC_UART_CLI_PIN_NUM_ALT_MODE) ? ERR_STAT_NO_ERROR : UC_UART_CLI_ERR_STAT_GPIO_CFG;

	// 3. Enable UART port
	const t_error_code usart_en_stat = USART_peri_enable(SYS_USART_PERI, ENABLE, DISABLE);
	err_stat |= (usart_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : UC_UART_CLI_ERR_STAT_USART_EN;


	// 4. Configure USART port
	t_USART_RegDef * const p_usart_reg = USART_get_peri_base(SYS_USART_PERI);
	t_usart_handle usart_handle = {
		.p_usart_reg = p_usart_reg,
		.mode = e_usart_mode_rx_only,
		.baud = e_usart_baud_9600,
		.stop_bits = e_usart_stop_bit_1,
		.word_9bit_en = FALSE,
		.parity_ctrl = e_usart_parity_none,
		.hwflow_ctrl = e_usart_hwflow_none
	};
	const t_error_code usart_cfg_stat = USART_config(&usart_handle);
	err_stat |= (usart_cfg_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : UC_UART_CLI_ERR_STAT_USART_CFG;


	if (ERR_STAT_NO_ERROR == err_stat) {
		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}


static void uc_uart_cli_init(void)
{
	t_error_code init_stat = e_ec_timeout;

	DEBUG_PRINT("=====================================\n");
	DEBUG_PRINT("| UART Based Command Line Interface |\n");
	DEBUG_PRINT("=====================================\n\n");

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

	// 5. Initialize USART
	const t_error_code usart_stat = uc_uart_cli_usart_init();
	DEBUG_PRINT((usart_stat == e_ec_no_error) ? "  - USART init SUCCESS\n" : "  - USART init FAIL\n");

#if 0
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
#endif
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void UC_UART_CLI_run(void)
{
	uc_uart_cli_init();
#if 0
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
#endif
	while (1);
}

/*** EOF ***/
