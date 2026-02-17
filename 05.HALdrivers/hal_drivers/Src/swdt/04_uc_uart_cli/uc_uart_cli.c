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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "uc_uart_cli.h"

#include "rcc.h"
#include "gpio.h"
#include "usart.h"
#include "mport.h"
#include "system.h"
#include "seif_tsl2561.h"
#include "fw_debug.h"

#include "cast.h"

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

/** \name Command tokens configuration. */
/**@{*/
#define  UC_UART_CLI_CMD_LENGTH_MAX        (128u)
#define  UC_UART_CLI_CMD_TOKEN_MAX         (16u)
#define  UC_UART_CLI_CMD_TOKEN_DELIMITER   (" ")
#define  UC_UART_CLI_CMD_TOKEN_DIGIT       (10)
#define  UC_UART_CLI_LED_NUM			   (3u)
#define  UC_UART_CLI_LED_MASK			   (((uint32_t)1u << UC_UART_CLI_LED_NUM) - 1u)
/**@{*/

/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef struct {
	char cmd_str[UC_UART_CLI_CMD_LENGTH_MAX];
	uint8_t cmd_num_of_args;
	int32_t cmd_arg[UC_UART_CLI_CMD_TOKEN_MAX];
} t_cmd_token;

typedef enum {
	e_cmd_id_help = 0u,
	e_cmd_id_sled = 1u,
	e_cmd_id_gled = 2u,
	e_cmd_id_lux  = 3u,
	e_cmd_id_max  = 4u
} t_cmd_id;

typedef t_error_code t_cmd_exe (int32_t * const p_params, uint8_t * const p_param_len);

typedef struct {
    const char * const p_prompt;
    t_cmd_exe * const cmd_run;
} t_cmd_registry;


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
static t_error_code uc_uart_cli_usart_init(void);

static void uc_uart_cli_init(void);

static void uc_uart_cli_sensor_init(void);

static t_error_code uc_uart_cli_cmd_help(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len);

static t_error_code uc_uart_cli_cmd_set_led(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len);

static t_error_code uc_uart_cli_cmd_get_led(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len);

static t_error_code uc_uart_cli_cmd_get_lux(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len);

static void uc_uart_cli_cmd_hlr(const uint8_t p_msg_req[UC_UART_CLI_CMD_LENGTH_MAX], uint8_t p_msg_resp[UC_UART_CLI_CMD_LENGTH_MAX]);

static uint32_t uc_uart_cli_get_tokens(const uint8_t p_cmd[ UC_UART_CLI_CMD_LENGTH_MAX], const uint8_t * p_argv[ UC_UART_CLI_CMD_TOKEN_MAX]);

static uint32_t uc_uart_cli_tokens_to_nums(const uint32_t num_of_tokens, const uint8_t * const p_token[UC_UART_CLI_CMD_TOKEN_MAX], int32_t p_nums[ UC_UART_CLI_CMD_TOKEN_MAX]);



/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */


/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static t_error_code uc_uart_cli_usart_init(void)
{
	t_error_code ret_stat = e_ec_invalid_param;
	uint32_t err_stat = ERR_STAT_NO_ERROR;

	// 1. Enable GPIO port for UART
	const t_error_code usart_gpio_en_stat = GPIO_port_enable(SYS_USART_GPIO_PORT, ENABLE, DISABLE);
	err_stat |= (usart_gpio_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : UC_UART_CLI_ERR_STAT_GPIO_EN;

	// 2. Configure GPIO pins for UART
	t_gpio_handle gpio_usart_cfg = {
		.p_gpio_reg = GPIO_get_port_base(SYS_USART_GPIO_PORT),
		.mode_sel = e_gpio_mode_alt_func,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_fast,
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
	t_usart_handle usart_handle = {
		.p_usart_reg = USART_get_peri_base(SYS_USART_PERI),
		.mode = e_usart_mode_txrx,
		.baud = e_usart_baud_9600,
		.stop_bits = e_usart_stop_bit_1,
		.word_9bit_en = FALSE,
		.parity_ctrl = e_usart_parity_none,
		.hwflow_ctrl = e_usart_hwflow_none,
		.over8_en = FALSE
	};
	const t_error_code usart_cfg_stat = USART_config(&usart_handle);
	err_stat |= (usart_cfg_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : UC_UART_CLI_ERR_STAT_USART_CFG;

	// 5. Enable USART
	USART_peri_ctrl(usart_handle.p_usart_reg, TRUE);

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
			.clk_sw = e_clk_sys_hsi,
			.clk_hpre = e_clk_hpre_0,
			.clk_ppre1 = e_clk_ppre_0
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


	// 6. Initialize Sensor Interface
	const t_error_code mport_stat = MPORT_i2c_init();
	DEBUG_PRINT((mport_stat == e_ec_no_error) ? "  - MPORT init SUCCESS\n" : "  - MPORT init FAIL\n");

	// 7. Enable GPIO ports in normal mode
	GPIO_port_enable(SYS_GPIO_LED_PORT, ENABLE, DISABLE);

	// 8. Configure GPIO for LEDs
	uint8_t succ_cnt = 0u;
	const uint8_t gpio_leds[UC_UART_CLI_LED_NUM] = {SYS_PIN_RED_LED, SYS_PIN_YEL_LED, SYS_PIN_GRN_LED};
	for (uint8_t led_sel= 0u; led_sel < UC_UART_CLI_LED_NUM; led_sel++) {
		const t_gpio_handle gpio_led_cfg = {
			.p_gpio_reg = GPIO_get_port_base(SYS_GPIO_LED_PORT),
			.mode_sel = e_gpio_mode_output,
			.open_drain_en = FALSE,
			.speed = e_gpio_speed_low,
			.pupd = e_gpio_pupd_no,
			.alt_func_sel = 0u
		};
		succ_cnt += (e_ec_no_error == GPIO_port_config(&gpio_led_cfg, gpio_leds[led_sel])) ? 1u : 0u;
		GPIO_set_pin(GPIO_get_port_base(SYS_GPIO_LED_PORT), gpio_leds[led_sel], DISABLE);
	}
	DEBUG_PRINT((succ_cnt == UC_UART_CLI_LED_NUM) ? "  - GPIO LED Configure SUCCESS\n" : "  - GPIO LED Configure FAIL\n");
}

static void uc_uart_cli_sensor_init(void)
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
}

static t_error_code uc_uart_cli_cmd_help(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len)
{
    // NOP

    return e_ec_no_error;
}

static t_error_code uc_uart_cli_cmd_set_led(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len)
{
    t_error_code ret_stat = e_ec_invalid_param;

    uint32_t led_sel_mask = (uint32_t)p_cmd_param[0u];
    if ((led_sel_mask <= UC_UART_CLI_LED_MASK) && (*p_cmd_param_len == 2u)) {
    	const t_bool led_val = (p_cmd_param[1u] == 0) ? FALSE : TRUE;
		const uint8_t gpio_leds[UC_UART_CLI_LED_NUM] = {SYS_PIN_RED_LED, SYS_PIN_YEL_LED, SYS_PIN_GRN_LED};

		for (uint32_t i=0u; i<UC_UART_CLI_LED_NUM; i++) {
    		if ((led_sel_mask & 0x1u) != 0u) {
    			GPIO_set_pin(GPIO_get_port_base(SYS_GPIO_LED_PORT), gpio_leds[i], led_val);
    		}

    		led_sel_mask >>= 1u;
    	}

    	ret_stat = e_ec_no_error;
    }

    return ret_stat;
}

static t_error_code uc_uart_cli_cmd_get_led(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len)
{
    t_error_code ret_stat = e_ec_invalid_param;

	if (*p_cmd_param_len == 0u) {
		const uint8_t gpio_leds[UC_UART_CLI_LED_NUM] = {SYS_PIN_RED_LED, SYS_PIN_YEL_LED, SYS_PIN_GRN_LED};

		for (uint32_t i=0u; i<UC_UART_CLI_LED_NUM; i++) {
			p_cmd_param[i] = (int32_t)GPIO_get_pin(GPIO_get_port_base(SYS_GPIO_LED_PORT), gpio_leds[i]);
		}
		*p_cmd_param_len = UC_UART_CLI_LED_NUM;

		ret_stat = e_ec_no_error;
	}

    return ret_stat;
}

static t_error_code uc_uart_cli_cmd_get_lux(int32_t * const p_cmd_param, uint8_t * const p_cmd_param_len)
{
    t_error_code ret_stat = e_ec_invalid_param;

    if (0u == *p_cmd_param_len) {
        const uint16_t tsl_visible_ir = SEIF_TSL2561_read_visible_ir();
    	const uint16_t tsl_ir_only = SEIF_TSL2561_read_ir_only();
    	p_cmd_param[0u] = (int32_t)tsl_visible_ir;
    	p_cmd_param[1u] = (int32_t)tsl_ir_only;
    	*p_cmd_param_len = 2u;

    	ret_stat = e_ec_no_error;
    }

    return ret_stat;
}

static void uc_uart_cli_cmd_hlr(const uint8_t p_msg_req[UC_UART_CLI_CMD_LENGTH_MAX], uint8_t p_msg_resp[UC_UART_CLI_CMD_LENGTH_MAX])
{
	t_cmd_token cmd_token = {0};

	// Handle request
	const uint8_t * argv[UC_UART_CLI_CMD_TOKEN_MAX] = {NULL};
	const uint32_t argc = uc_uart_cli_get_tokens(p_msg_req, argv);

	// Lower case command
	for(char *p=CAST_TO(char *, argv[0u]); *p; p++) *p=tolower(*p);
	strcpy(cmd_token.cmd_str, CAST_TO(const char *, argv[0u]));
	cmd_token.cmd_num_of_args = (uint8_t)uc_uart_cli_tokens_to_nums(argc, argv, cmd_token. cmd_arg);

	// Execute command
	const t_cmd_registry cmd_registry[e_cmd_id_max] = {
		[e_cmd_id_help].p_prompt = "help",   [e_cmd_id_help].cmd_run = &uc_uart_cli_cmd_help,
		[e_cmd_id_sled].p_prompt = "setled", [e_cmd_id_sled].cmd_run = &uc_uart_cli_cmd_set_led,
		[e_cmd_id_gled].p_prompt = "getled", [e_cmd_id_gled].cmd_run = &uc_uart_cli_cmd_get_led,
		[e_cmd_id_lux].p_prompt  = "getlux", [e_cmd_id_lux].cmd_run  = &uc_uart_cli_cmd_get_lux
	};

	uint32_t cmd_idx = 0u;
	while ((strcmp(cmd_token.cmd_str, cmd_registry[cmd_idx].p_prompt) != 0) && ((uint32_t)e_cmd_id_max)>cmd_idx++);

	t_error_code cmd_resp = e_ec_invalid_param;
	if (cmd_idx < (uint32_t)e_cmd_id_max) {
		int32_t * const p_params = CAST_TO(int32_t * const, &cmd_token.cmd_arg[0u]);
		uint8_t * const p_param_len = CAST_TO(uint8_t * const, &cmd_token.cmd_num_of_args);
		cmd_resp = cmd_registry[cmd_idx].cmd_run(p_params, p_param_len);
	} else {
		printf("Invalid command: %lu\n", cmd_idx);
	}

	// Create response
	char * p_cmd_resp = CAST_TO(char *, p_msg_resp);
	if (cmd_resp == e_ec_no_error) {
		switch (cmd_idx) {
			case (uint32_t)e_cmd_id_help:
				const uint32_t req_params[e_cmd_id_max] = {0u, 2u, 0u, 0u};
				char cmd_help[UC_UART_CLI_CMD_LENGTH_MAX / (sizeof(cmd_registry) / sizeof(cmd_registry[0u]))] = {""};
				for (uint32_t i=1u; i<(uint32_t)e_cmd_id_max; i++) {
					snprintf(cmd_help, UC_UART_CLI_CMD_LENGTH_MAX,
						"cmd: %s, params: %lu\r\n",
						cmd_registry[i].p_prompt, req_params[i]);
					strcat(p_cmd_resp, cmd_help);
				}
				break;
			case (uint32_t)e_cmd_id_sled:
				strcpy(p_cmd_resp, ">> SUCCESS - LED(s) set\r\n");
				break;
			case (uint32_t)e_cmd_id_gled:
				snprintf(p_cmd_resp, UC_UART_CLI_CMD_LENGTH_MAX,
					">> SUCCESS - RLED: %ld, YLED: %ld, GRED: %ld\r\n",
					cmd_token.cmd_arg[0u], cmd_token.cmd_arg[1u], cmd_token.cmd_arg[2u]);
				break;
			case (uint32_t)e_cmd_id_lux:
				snprintf(p_cmd_resp, UC_UART_CLI_CMD_LENGTH_MAX,
					">> SUCCESS - LUX: %ld, IRED: %ld\r\n",
					cmd_token.cmd_arg[0u], cmd_token.cmd_arg[1u]);
				break;
			default:
				strcpy(CAST_TO(char *, p_msg_resp), ">> INVALID\r\n");
				break;
		}
	} else {
		strcpy(p_cmd_resp, ">> INVALID\r\n");
	}
}

static uint32_t uc_uart_cli_get_tokens(const uint8_t p_cmd[ UC_UART_CLI_CMD_LENGTH_MAX], const uint8_t * p_argv[ UC_UART_CLI_CMD_TOKEN_MAX])
{
    uint32_t ret_argc = 0u;

    p_argv[ret_argc] = CAST_TO(const uint8_t *, strtok(CAST_TO(char *, &p_cmd[ret_argc]),  UC_UART_CLI_CMD_TOKEN_DELIMITER));
    while ((ret_argc <  UC_UART_CLI_CMD_TOKEN_MAX) && (p_argv[ret_argc] != NULL)) {
        p_argv[++ret_argc] = CAST_TO(const uint8_t *, strtok(NULL,  UC_UART_CLI_CMD_TOKEN_DELIMITER));
    }

    return ret_argc;
}

static uint32_t uc_uart_cli_tokens_to_nums(const uint32_t num_of_tokens, const uint8_t * const p_token[UC_UART_CLI_CMD_TOKEN_MAX], int32_t p_nums[ UC_UART_CLI_CMD_TOKEN_MAX])
{
    uint32_t ret_idx = 0u;

    for (uint32_t i=0u; i<num_of_tokens; i++) {
        char * p_token_endptr = NULL;
        const int32_t curr_num = (int32_t)strtol(CAST_TO(const char *, p_token[i]), &p_token_endptr, UC_UART_CLI_CMD_TOKEN_DIGIT);
        if ((p_token_endptr != CAST_TO(char *, p_token[i])) &&
        	((*p_token_endptr == '\0') || (*p_token_endptr == '\r'))) {
            p_nums[ret_idx++] = curr_num;
        }
    }

    return ret_idx;
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void UC_UART_CLI_run(void)
{
	uc_uart_cli_init();
	uc_uart_cli_sensor_init();

	t_USART_RegDef * const p_uart = USART_get_peri_base(SYS_USART_PERI);

	uint8_t rx_buff[UC_UART_CLI_CMD_LENGTH_MAX] = {0u};
	uint8_t tx_buff[UC_UART_CLI_CMD_LENGTH_MAX] = {0u};

	while (1) {
		const uint32_t rx_data_len = USART_read_byte(p_uart, rx_buff, UC_UART_CLI_CMD_LENGTH_MAX);
		if (rx_data_len > 0u) {
			rx_buff[rx_data_len-1] = '\0';

			uc_uart_cli_cmd_hlr(rx_buff, tx_buff);

			USART_write_byte(p_uart, CAST_TO(const uint8_t * const, tx_buff), strlen(CAST_TO(char *, tx_buff)));
		}

		for (uint32_t i=0u; i<1000000u; ++i);
	}
}

/*** EOF ***/
