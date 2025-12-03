/**
 * Copyright (c) 2025 OwlTech
 *
 * \file uc_us_sensor.c
 * \brief
 * \author OwlTech
 * \date Nov 21, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "../06_uc_us_sensor/uc_us_sensor.h"

#include "common_def.h"
#include "clock_reset.h"
#include "fw_debug.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HSE_CLOCK_RESET_TIMEOUT	100u


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
void uc_us_sensor_init(void);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
void uc_us_sensor_init(void)
{
	t_error_code init_stat = e_ec_timeout;

	DEBUG_PRINT("=============================\n");
	DEBUG_PRINT("| Ultrasonic Sensor Use Case |\n");
	DEBUG_PRINT("=============================\n\n");

	DEBUG_PRINT("Initialization...\n");

	// 1. Enable the HSE clock using HSEON bit (RCC_CR)
	// 2. Enable the HSE bypass bit (bypass the oscillator with an ext clock)
	const t_clock_source clk_src = e_clk_hse;
	CLOCK_RESET_enable_source(clk_src, TRUE);

	// 3. Wait until HSE clock enabled
	uint32_t timeout = HSE_CLOCK_RESET_TIMEOUT;
	while ((CLOCK_RESET_get_source_stat(clk_src) == FALSE) && (timeout > 0u)) {
		timeout--;
	}

	// 4. Switch the system clock to HSE
	if (timeout > 0u) {
		DEBUG_PRINT("  - HSE clock enable SUCCESS\n");

		const t_clock_cfgr clk_cfg = {
			.clk_sw = e_clk_sys_hse,
			.clk_mco1 = e_clk_mco_hse,
			.clk_mco1_pre = e_clk_mco_pre_4
		};
		init_stat = CLOCK_RESET_set_config(&clk_cfg);
		DEBUG_PRINT((init_stat == e_ec_no_error) ? "  - HSE Clock switch SUCCESS\n" : "  - HSE Clock switch FAIL\n");
	} else {
		DEBUG_PRINT("  - HSE clock enable FAIL.\n");
	}
}


/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void UC_US_SENSOR_run(void)
{
	uc_us_sensor_init();

	while(1);
}

/*** EOF ***/
