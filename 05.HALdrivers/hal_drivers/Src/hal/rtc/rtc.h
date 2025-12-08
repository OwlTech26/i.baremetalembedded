/**
 * Copyright (c) 2025 OwlTech
 *
 * \file rtc.h
 * \brief
 * \author OwlTech
 * \date Dec 4, 2025
 */

#ifndef RTC_H_
#define RTC_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "common_def.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define RTC_BCD_TENS_MASK					(0xF0u)
#define RTC_BCD_UNITS_MASK					(0x0Fu)
#define RTC_BCD_BIT_NUM						(4u)
#define RTC_BCD_DIGIT_MAX					(9u)
#define RTC_BCD_MONTH_TENS_DIGIT_MAX		(1u)
#define RTC_BCD_DAY_TENS_DIGIT_MAX			(3u)
#define RTC_BCD_HRS_TENS_DIGIT_MAX			(2u)
#define RTC_BCD_MINS_SECS_TENS_DIGIT_MAX	(6u)


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
typedef enum {
	e_rtc_wd_forbidden 	= 0u,
	e_rtc_wd_monday 	= 1u,
	e_rtc_wd_tuesday 	= 2u,
	e_rtc_wd_wednesday 	= 3u,
	e_rtc_wd_thursday 	= 4u,
	e_rtc_wd_friday 	= 5u,
	e_rtc_wd_saturday 	= 6u,
	e_rtc_wd_sunday 	= 7u,
	e_rtc_wd_max 		= 8u
} t_rtc_week_day;

typedef struct {
	t_rtc_week_day week_day; //!< Day of the week.
	uint8_t day;			 //!< Day of the month.
	uint8_t month;			 //!< Month of the year.
	uint8_t year;			 //!< Year
} t_rtc_date;

typedef struct {
	t_bool time_f_12h;	//!< 12h time format
	uint8_t hours;
	uint8_t mins;
	uint8_t secs;
} t_rtc_time;

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */


/******************************************************************************/
/*---------------------------API Function Prototypes--------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
void RTC_enable(const t_bool rtc_en, const uint8_t lpwrm_en);

t_error_code RTC_init(const t_rtc_date * const p_rtc_date, const t_rtc_time * const p_rtc_time);

void RTC_get_date(t_rtc_date * const p_rtc_date);

void RTC_get_time(t_rtc_time * const p_rtc_time);

#endif /* RTC_H_ */
/*** EOF ***/
