/**
 * Copyright (c) 2025 OwlTech
 *
 * \file rtc.c
 * \brief
 * \author OwlTech
 * \date Dec 4, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "rtc.h"

#include "rcc.h"
#include "hal_reg.h"
#include "cast.h"
#include "rtc_register.h"
#include "pwr_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define RTC_INIT_WR_PROT_DISABLE_KEY_1		((uint8_t)0xCAu)
#define RTC_INIT_WR_PROT_DISABLE_KEY_2		((uint8_t)0x53u)
#define RTC_INIT_WR_PROT_ENABLE_KEY			((uint8_t)0xFFu)
#define RTC_INIT_ENABLE_ISR_MASK			(RTC_ISR_RSF_MASK | RTC_ISR_INIT_MASK | RTC_ISR_ALRAF_MASK | RTC_ISR_ALRBF_MASK | RTC_ISR_WUTF_MASK | RTC_ISR_TSF_MASK | RTC_ISR_TSOVF_MASK | RTC_ISR_TAMP1F_MASK | RTC_ISR_TAMP2F_MASK)
#define RTC_PRESCALE_ASYNCH_VAL				(0x7Fu)
#define RTC_PRESCALE_SYNCH_VAL				(0x00F9u)


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef struct {
	volatile uint32_t RTC_TR;			//!< RTC calendar time shadow register.
	volatile uint32_t RTC_DR;			//!< RTC calendar date shadow register.
	volatile uint32_t RTC_CR;			//!< RTC control register register.
	volatile uint32_t RTC_ISR;			//!< RTC initialization and status register.
	volatile uint32_t RTC_PRER;			//!< RTC prescaler register.
	volatile uint32_t RTC_WUTR;			//!< RTC wakeup timer register.
	volatile uint32_t RTC_CALIBR;		//!< RTC calibration register.
	volatile uint32_t RTC_ALRMAR;		//!< RTC alarm A register.
	volatile uint32_t RTC_ALRMBR;		//!< RTC alarm B register.
	volatile uint32_t RTC_WPR;			//!< RTC write protection register.
	volatile uint32_t const RTC_SSR;	//!< RTC sub second register.
	volatile uint32_t RTC_SHIFTR;		//!< RTC shift control register.
	volatile uint32_t const RTC_TSTR;	//!< RTC time stamp time register.
	volatile uint32_t const RTC_TSDR;	//!< RTC time stamp date register.
	volatile uint32_t const RTC_TSSSR;	//!< RTC timestamp sub second register.
	volatile uint32_t RTC_CALR;			//!< RTC calibration register.
	volatile uint32_t RTC_TAFCR;		//!< RTC tamper and alternate function configuration register.
	volatile uint32_t RTC_ALRMASSR;		//!< RTC alarm A sub second register.
	volatile uint32_t RTC_ALRMBSSR;		//!< RTC alarm B sub second register.
} t_RTC_RegDef;

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static inline t_RTC_RegDef * const rtc_get_base(void);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static void rtc_init_mode_set(const t_bool rtc_init_mode_en);

/** \brief Sets date in BCD format. */
static t_error_code rtc_init_date(const t_rtc_date * const p_rtc_date);

/** \brief Sets time in BCD format. */
static t_error_code rtc_init_time(const t_rtc_time * const p_rtc_time);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline t_RTC_RegDef * const rtc_get_base(void)
{
	t_RTC_RegDef * const ret_base = CAST_TO(t_RTC_RegDef * const, RTC_BASE);

	return ret_base;
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static void rtc_init_mode_set(const t_bool rtc_init_mode_en)
{
	t_RTC_RegDef * const p_rtc = rtc_get_base();
	if (rtc_init_mode_en != FALSE) {
		// Start init mode
		p_rtc->RTC_ISR = RTC_INIT_ENABLE_ISR_MASK;

		// Wait till completion
		while ((p_rtc->RTC_ISR & RTC_ISR_INITF_MASK) == 0u);
	} else {
		// Stop init mode
		p_rtc->RTC_ISR = 0u;
		// Clear RSF
		p_rtc->RTC_ISR &= RTC_ISR_RSF_NMASK;

		// Wait till completion
		while ((p_rtc->RTC_ISR & RTC_ISR_RSF_MASK) == 0u);
	}
}


static t_error_code rtc_init_date(const t_rtc_date * const p_rtc_date)
{
	t_error_code ret_stat = e_ec_invalid_param;

	const uint32_t year	 		  = p_rtc_date->year;
	const uint32_t month 		  = p_rtc_date->month;
	const uint32_t day   		  = p_rtc_date->day;
	const t_rtc_week_day week_day = p_rtc_date->week_day;

	if (((year >> RTC_BCD_BIT_NUM) <= RTC_BCD_DIGIT_MAX) 			 && ((year & RTC_BCD_UNITS_MASK) <= RTC_BCD_DIGIT_MAX) &&
		((month >> RTC_BCD_BIT_NUM) <= RTC_BCD_MONTH_TENS_DIGIT_MAX) && ((month & RTC_BCD_UNITS_MASK) <= RTC_BCD_DIGIT_MAX) &&
		((day >> RTC_BCD_BIT_NUM) <= RTC_BCD_DAY_TENS_DIGIT_MAX) 	 && ((day & RTC_BCD_UNITS_MASK) <= RTC_BCD_DIGIT_MAX) &&
		((week_day != e_rtc_wd_forbidden) 				 			 && (week_day < e_rtc_wd_max)))
	{
		const uint32_t rtc_data_reg =
			((year & RTC_BCD_TENS_MASK) << (RTC_DR_YT_POS - RTC_BCD_BIT_NUM))  | // Year tens in BCD
			((year & RTC_BCD_UNITS_MASK) << RTC_DR_YU_POS) 					   | // Year units in BCD
			((uint32_t)week_day << RTC_DR_WDU_POS) 				   			   | // Week day units
			((month & RTC_BCD_TENS_MASK) << (RTC_DR_MT_POS - RTC_BCD_BIT_NUM)) | // Month tens in BCD
			((month & RTC_BCD_UNITS_MASK) << RTC_DR_MU_POS) 				   | // Month units in BCD
			((day & RTC_BCD_TENS_MASK) << (RTC_DR_DT_POS - RTC_BCD_BIT_NUM)) | 	 // Date tens in BCD
			((day & RTC_BCD_UNITS_MASK) << RTC_DR_DU_POS); 						 // Date units in BCD

		t_RTC_RegDef * const p_rtc = rtc_get_base();
		p_rtc->RTC_DR = rtc_data_reg;

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

static t_error_code rtc_init_time(const t_rtc_time * const p_rtc_time)
{
	t_error_code ret_stat = e_ec_invalid_param;

	const uint32_t hours = p_rtc_time->hours;
	const uint32_t mins  = p_rtc_time->mins;
	const uint32_t secs  = p_rtc_time->secs;
	const t_bool time_pm_format = p_rtc_time->time_f_12h;

	const uint32_t hour_tens_max = (time_pm_format == FALSE) ? RTC_BCD_HRS_TENS_DIGIT_MAX : RTC_BCD_HRS_TENS_DIGIT_MAX - 1u;

	if (((hours >> RTC_BCD_BIT_NUM) <= hour_tens_max)	 			 	 && ((hours & RTC_BCD_UNITS_MASK) <= RTC_BCD_DIGIT_MAX) &&
		((mins >> RTC_BCD_BIT_NUM) <= RTC_BCD_MINS_SECS_TENS_DIGIT_MAX)  && ((mins & RTC_BCD_UNITS_MASK) <= RTC_BCD_DIGIT_MAX) &&
		((secs >> RTC_BCD_BIT_NUM) <= RTC_BCD_MINS_SECS_TENS_DIGIT_MAX)  && ((secs & RTC_BCD_UNITS_MASK) <= RTC_BCD_DIGIT_MAX))
	{
		const uint32_t rtc_time_reg =
			(b_to_uint32(time_pm_format) << RTC_TR_PM_POS) 				   	   | // AM/PM time format
			((hours & RTC_BCD_TENS_MASK) << (RTC_TR_HT_POS - RTC_BCD_BIT_NUM)) | // hours tens in BCD
			((hours & RTC_BCD_UNITS_MASK) << RTC_TR_HU_POS) 				   | // hours units in BCD
			((mins & RTC_BCD_TENS_MASK) << (RTC_TR_MNT_POS - RTC_BCD_BIT_NUM)) | // Mins tens in BCD
			((mins & RTC_BCD_UNITS_MASK) << RTC_TR_MNU_POS) 				   | // Mins units in BCD
			((secs & RTC_BCD_TENS_MASK) << (RTC_TR_ST_POS - RTC_BCD_BIT_NUM))  | // Secs tens in BCD
			((secs & RTC_BCD_UNITS_MASK) << RTC_TR_SU_POS); 					 // Secs units in BCD

		t_RTC_RegDef * const p_rtc = rtc_get_base();
		p_rtc->RTC_TR = rtc_time_reg;

		ret_stat = e_ec_no_error;
	}

	return ret_stat;

}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void RTC_enable(const t_bool rtc_en, const uint8_t lpwrm_en)
{
	// Enable/disable clock access to PWR
	RCC_enable_peri(e_peri_apb1, e_peri_pwr, rtc_en, lpwrm_en);

	uint32_t pwr_cr_reg = PWR_CR_GET();
	if (rtc_en != FALSE) {
		pwr_cr_reg |= PWR_CR_DBP_MASK; // Enable Backup access to configure RTC
		PWR_CR_SET(pwr_cr_reg);
	} else {
		pwr_cr_reg &= PWR_CR_DBP_NMASK; // Disable Backup access to configure RTC
		PWR_CR_SET(pwr_cr_reg);
	}

	// Enable/disable Low Speed Internal Oscillator
	RCC_lsion_enable(rtc_en);

	if (rtc_en != FALSE) {
		// Reset backup domain
		RCC_backup_domain_reset();

		// Set RTC clock source to LSI
		RCC_rtc_clock_sel(e_clk_rtc_lsi);
	}

	// Enable/disable RTC
	RCC_rtc_enable(rtc_en);
}

t_error_code RTC_init(const t_rtc_date * const p_rtc_date, const t_rtc_time * const p_rtc_time)
{
	// Disable RTC registers write protection
	t_RTC_RegDef * const p_rtc = rtc_get_base();
	p_rtc->RTC_WPR = RTC_INIT_WR_PROT_DISABLE_KEY_1;
	p_rtc->RTC_WPR = RTC_INIT_WR_PROT_DISABLE_KEY_2;

	// Enter initialization mode
	rtc_init_mode_set(TRUE);

	// Set date
	const t_error_code date_init_stat = rtc_init_date(p_rtc_date);

	// Set time
	const t_error_code time_init_stat = rtc_init_time(p_rtc_time);

	// Set Asynchronous and Synchronous pre-scaler
	p_rtc->RTC_PRER = ((uint32_t)RTC_PRESCALE_ASYNCH_VAL << RTC_PRER_PREDIV_A_POS) |
					   ((uint32_t)RTC_PRESCALE_SYNCH_VAL << RTC_PRER_PREDIV_S_POS);

	// Exit initialization mode
	rtc_init_mode_set(FALSE);

	// Enable RTC registers write protection
	p_rtc->RTC_WPR = RTC_INIT_WR_PROT_ENABLE_KEY;

	const t_error_code ret_stat = ((date_init_stat == e_ec_no_error) && (time_init_stat == e_ec_no_error)) ? e_ec_no_error : e_ec_invalid_param;

	return ret_stat;
}

void RTC_get_date(t_rtc_date * const p_rtc_date)
{
	const t_RTC_RegDef * const p_rtc = rtc_get_base();
	const uint32_t date_reg = p_rtc->RTC_DR;

	p_rtc_date->year = (uint8_t)((date_reg & (RTC_DR_YT_MASK | RTC_DR_YU_MASK)) >> RTC_DR_YU_POS);
	p_rtc_date->month = (uint8_t)((date_reg & (RTC_DR_MT_MASK | RTC_DR_MU_MASK)) >> RTC_DR_MU_POS);
	p_rtc_date->day = (uint8_t)((date_reg & (RTC_DR_DT_MASK | RTC_DR_DU_MASK)) >> RTC_DR_DU_POS);
	const t_rtc_week_day week_days[e_rtc_wd_max] = {e_rtc_wd_forbidden, e_rtc_wd_monday, e_rtc_wd_tuesday, e_rtc_wd_wednesday, e_rtc_wd_thursday,
		e_rtc_wd_friday, e_rtc_wd_saturday, e_rtc_wd_sunday};
	const uint32_t rtc_wdu_idx = (date_reg & RTC_DR_WDU_MASK) >> RTC_DR_WDU_POS;
	p_rtc_date->week_day = (rtc_wdu_idx < (uint32_t)e_rtc_wd_max) ? week_days [rtc_wdu_idx] : e_rtc_wd_forbidden;
}

void RTC_get_time(t_rtc_time * const p_rtc_time)
{
	const t_RTC_RegDef * const p_rtc = rtc_get_base();
	const uint32_t time_reg = p_rtc->RTC_TR;

	p_rtc_time->hours = (uint8_t)((time_reg & (RTC_TR_HT_MASK | RTC_TR_HU_MASK)) >> RTC_TR_HU_POS);
	p_rtc_time->mins = (uint8_t)((time_reg & (RTC_TR_MNT_MASK | RTC_TR_MNU_MASK)) >> RTC_TR_MNU_POS);
	p_rtc_time->secs = (uint8_t)((time_reg & (RTC_TR_ST_MASK | RTC_TR_SU_MASK)) >> RTC_TR_SU_POS);
	p_rtc_time->time_f_12h = ((time_reg & RTC_TR_PM_MASK) != 0u) ? TRUE : FALSE;
}

/*** EOF ***/
