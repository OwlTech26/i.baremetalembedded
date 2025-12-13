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
#include "fw_debug.h"
#include "system.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HSE_RCC_TIMEOUT			100u


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
static void uc_light_det_i2c_init(void);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

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
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void UC_LIGHT_DET_I2C_run(void)
{
	uc_light_det_i2c_init();


	while(1) {
		uint8_t rx_buffer[16u] = {0};
		MPORT_i2c_byte_read_reg(0x39u, 0xAu, rx_buffer);
		DEBUG_PRINT("TSL2561: %u\n", rx_buffer[0]);
		MPORT_i2c_byte_read_reg_burst(0x10u, 0x00u, rx_buffer, 2u);
		DEBUG_PRINT("VEML6040: %u\n", rx_buffer[0]);
	}
}
#endif /* USE_CASE_RUN_IDX_3 */

/*** EOF ***/
