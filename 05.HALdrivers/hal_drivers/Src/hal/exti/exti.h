/**
 * Copyright (c) 2025 OwlTech
 *
 * \file exti.h
 * \brief
 * \author OwlTech
 * \date Nov 20, 2025
 */

#ifndef EXTI_H_
#define EXTI_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "common_def.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef enum {
	e_exti_gpio_pin_0 	= 0u,
	e_exti_gpio_pin_1 	= 1u,
	e_exti_gpio_pin_2 	= 2u,
	e_exti_gpio_pin_3 	= 3u,
	e_exti_gpio_pin_4 	= 4u,
	e_exti_gpio_pin_5 	= 5u,
	e_exti_gpio_pin_6 	= 6u,
	e_exti_gpio_pin_7 	= 7u,
	e_exti_gpio_pin_8 	= 8u,
	e_exti_gpio_pin_9 	= 9u,
	e_exti_gpio_pin_10 	= 10u,
	e_exti_gpio_pin_11 	= 11u,
	e_exti_gpio_pin_12	= 12u,
	e_exti_gpio_pin_13 	= 13u,
	e_exti_gpio_pin_14 	= 14u,
	e_exti_gpio_pin_15 	= 15u,
	e_exti_pvd_out 		= 16u,
	e_exti_rtc_alarm 	= 17u,
	e_exti_usb_otg_fs 	= 18u,
	e_exti_usb_otg_hs 	= 20u,
	e_exti_rtc_event 	= 21u,
	e_exti_rtc_wakeup 	= 22u,
	e_exti_max 			= 23u
} t_exti_line;

typedef enum {
	e_exti_it_ft 	= 0u,
	e_exti_it_rt 	= 1u,
	e_exti_it_rft 	= 2u
} t_exti_it_mode;

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
t_error_code EXTI_interrupt_enable(const uint32_t exti_line, const t_exti_it_mode it_mode_sel);

void EXTI_irq_handle(const uint32_t exti_line);

#endif /* EXTI_H_ */
/*** EOF ***/
