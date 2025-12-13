/**
 * Copyright (c) 2025 OwlTech
 *
 * \file uc_bmp280_spi.c
 * \brief
 * \author OwlTech
 * \date Nov 21, 2025
 */
#if defined(USE_CASE_RUN_IDX_2)
/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "uc_bmp280_spi.h"

#include <stdlib.h>
#include "common_def.h"
#include "system.h"
#include "rcc.h"
#include "mport.h"
#include "seif_bmp280.h"
#include "rtc.h"
#include "cortex_m4.h"
#include "fw_debug.h"
#include "cast.h"

/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HSE_RCC_TIMEOUT			100u

/** \name Timestamp settings. */
/**@{*/
//!< 12.05.2025 Friday
#define TSTP_YEAR_BCD		(((uint8_t)2u << RTC_BCD_BIT_NUM) | (uint8_t)5u)
#define TSTP_MONTH_BCD		(((uint8_t)1u << RTC_BCD_BIT_NUM) | (uint8_t)2u)
#define TSTP_DAY_BCD		(((uint8_t)0u << RTC_BCD_BIT_NUM) | (uint8_t)5u)
#define TSTP_WEEK_DAY		(e_rtc_wd_friday)
//!< 16:11:45
#define TSTP_HOUR_BCD		(((uint8_t)1u << RTC_BCD_BIT_NUM) | (uint8_t)6u)
#define TSTP_MIN_BCD		(((uint8_t)1u << RTC_BCD_BIT_NUM) | (uint8_t)1u)
#define TSTP_SEC_BCD		(((uint8_t)4u << RTC_BCD_BIT_NUM) | (uint8_t)5u)
#define TSTP_24HRS_FORMAT	(TRUE)
/**@}*/

/** \name SysTick timer settings. */
/**@{*/
#define SENS_SYSTICK_10MS_RELOAD_VAL	(40000u-1) //!< Calculated based on 4 MHz clock
#define SENS_SYS_TICK_WAIT				(500u) 	   //!< Sensor data refresh rate: 5 sec
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

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static void uc_bmp280_init(void);

static void uc_bmp280_real_time_clock_init(void);

static void uc_bmp280_systick_init(void);

static void uc_bmp280_provide_data(const t_bmp280_comp_params * const p_comp_params);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static void uc_bmp280_init(void)
{
	t_error_code init_stat = e_ec_timeout;

	DEBUG_PRINT("=====================================\n");
	DEBUG_PRINT("| BMP280 Barometric Sensor Use Case |\n");
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
		DEBUG_PRINT("  - HSE clock enable SUCCESS\n");

		const t_clock_cfgr clk_cfg = {
			.clk_sw = e_clk_sys_hse,
			.clk_hpre = e_clk_hpre_2,
			.clk_ppre2 = e_clk_ppre_2
		};
		init_stat = RCC_set_config(&clk_cfg);
		DEBUG_PRINT((init_stat == e_ec_no_error) ? "  - HSE Clock switch SUCCESS\n" : "  - HSE Clock switch FAIL\n");
		DEBUG_PRINT("  - APB2 peripheral clock frequency: %lu MHz\n", RCC_get_peri_clock_freq(e_peri_apb2) / RCC_CLOCK_FREQ_TO_MHZ);
	} else {
		DEBUG_PRINT("  - HSE clock enable FAIL.\n");
	}

	// 5. Initialize Sensor Interface
	const t_error_code mport_stat = MPORT_spi_init();
	DEBUG_PRINT((mport_stat == e_ec_no_error) ? "  - MPORT init SUCCESS\n" : "  - MPORT init FAIL\n");

	// 6. Initialize real-time clock unit
	uc_bmp280_real_time_clock_init();
}

static void uc_bmp280_real_time_clock_init(void)
{
	RTC_enable(TRUE, FALSE);

	const t_rtc_date date_init = {
		.year = TSTP_YEAR_BCD,
		.month = TSTP_MONTH_BCD,
		.day = TSTP_DAY_BCD,
		.week_day = TSTP_WEEK_DAY
	};
	const t_rtc_time time_init = {
		.hours = TSTP_HOUR_BCD,
		.mins = TSTP_MIN_BCD,
		.secs = TSTP_SEC_BCD,
		.time_f_12h = TSTP_24HRS_FORMAT
	};
	const t_error_code rtc_init_stat = RTC_init(&date_init, &time_init);
	DEBUG_PRINT((rtc_init_stat == e_ec_no_error) ? "  - RTC init SUCCESS\n" : "  - RTC init FAIL\n");
}

static void uc_bmp280_systick_init(void)
{
	// Enable SysTick timer
	CORTEX_M4_systick_configure(TRUE, TRUE);
	CORTEX_M4_systick_set_preload(SENS_SYSTICK_10MS_RELOAD_VAL);
	CORTEX_M4_systick_enable(TRUE);
	SENS_SYS_TICK = 0u;
}

static void uc_bmp280_provide_data(const t_bmp280_comp_params * const p_comp_params)
{
	// Get timestamp
	t_rtc_time tstp_data = {0};
	RTC_get_time(&tstp_data);

	uint32_t temp_raw = 0u;
	const int32_t temp_degc = SEIF_BMP280_get_temp_degc(p_comp_params, &temp_raw);
	const uint32_t press_pa_q23_8 = SEIF_BMP280_get_press_pa(p_comp_params, temp_raw);

	// Display timestamp and sensor data
	DEBUG_PRINT("  %u%u:%u%u.%u%u ", tstp_data.hours >> RTC_BCD_BIT_NUM, tstp_data.hours & RTC_BCD_UNITS_MASK,
					tstp_data.mins >> RTC_BCD_BIT_NUM, tstp_data.mins & RTC_BCD_UNITS_MASK,
					tstp_data.secs >> RTC_BCD_BIT_NUM, tstp_data.secs & RTC_BCD_UNITS_MASK);
	DEBUG_PRINT("   %2ld.%2d °C | %4.3f hPa\n", temp_degc / 100, abs((int)temp_degc) % 100, (float)press_pa_q23_8 / 25600.0);
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void UC_BMP280_SPI_run(void)
{
	uc_bmp280_init();

	// Read ID
	DEBUG_PRINT("BMP280 ID %#X\n", SEIF_BMP280_get_id());

	// Set Measurement mode and read back
	const t_bmp280_ctrl_meas bmp280_mode = {
		.mode = e_bmp280_mode_normal,
		.press_ovs = e_bmp280_osrs_1x,
		.temp_ovs = e_bmp280_osrs_1x
	};
	const t_error_code bmp280_mode_stat = SEIF_BMP280_set_meas_mode(&bmp280_mode);
	const uint8_t bmp280_curr_mode = SEIF_BMP280_get_meas_mode();
	DEBUG_PRINT((bmp280_mode_stat == e_ec_no_error) ? "BMP280 mode setting PASS\n" : "BMP280 mode setting FAIL\n");
	DEBUG_PRINT("ctrl_meas= %#X\n", bmp280_curr_mode);

	// Read compensation parameters
	t_bmp280_comp_params comp_params = {0};
	SEIF_BMP280_get_comp_params(&comp_params);

	t_rtc_date datum = {0};
	RTC_get_date(&datum);

	const char * const p_weekdays[e_rtc_wd_max] = {"N/A", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

	// Initialize system tick for data sampling
	uc_bmp280_systick_init();

	DEBUG_PRINT("\n>> Log started at: %u%u.%u%u 20%u%u, %s\n", datum.month >> RTC_BCD_BIT_NUM, datum.month & RTC_BCD_UNITS_MASK,
			datum.day >> RTC_BCD_BIT_NUM, datum.day & RTC_BCD_UNITS_MASK,
			datum.year >> RTC_BCD_BIT_NUM, datum.year & RTC_BCD_UNITS_MASK,
			p_weekdays[datum.week_day]);
	DEBUG_PRINT("-------------------------------------\n");
	DEBUG_PRINT("| Timestamp | Temp[°C] | Press[hPa] |\n");
	DEBUG_PRINT("-------------------------------------\n");

	uc_bmp280_provide_data(&comp_params);

	while(1) {
		if (SENS_SYS_TICK_WAIT == SENS_SYS_TICK) {
			// Read temperature and pressure data
			uc_bmp280_provide_data(&comp_params);

			SENS_SYS_TICK = 0u;
		}
	}
}

void SysTick_Handler(void)
{
	SENS_SYS_TICK++;
}
#endif /* USE_CASE_RUN_IDX_2 */
/*** EOF ***/
