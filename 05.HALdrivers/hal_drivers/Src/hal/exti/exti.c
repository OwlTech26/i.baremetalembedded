/**
 * Copyright (c) 2025 OwlTech
 *
 * \file exti.c
 * \brief
 * \author OwlTech
 * \date Nov 20, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "exti.h"

#include "hal_reg.h"
#include "exti_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} t_EXTI_RegDef;

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

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
t_error_code EXTI_interrupt_enable(const uint32_t exti_line, const t_exti_it_mode it_mode_sel)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if (exti_line < (uint32_t)e_exti_max) {
		ret_stat = e_ec_no_error;

		t_EXTI_RegDef * const p_exti_reg = CAST_TO(t_EXTI_RegDef * const, EXTI_BASE);

		// Umask designated EXTI
		p_exti_reg->IMR |= EXTI_IMR_MASK(exti_line);

		// Interrupt EXTI edge detection enable
		switch (it_mode_sel) {
			case e_exti_it_ft: // Falling edge trigger detection
				p_exti_reg->FTSR |= EXTI_FTSR_MASK(exti_line);
				p_exti_reg->RTSR &= EXTI_RTSR_NMASK(exti_line);
				break;
			case e_exti_it_rt: // Rising edge trigger detection
				p_exti_reg->RTSR |= EXTI_RTSR_MASK(exti_line);
				p_exti_reg->FTSR &= EXTI_FTSR_NMASK(exti_line);
				break;
			case e_exti_it_rft: // Both Rising and Falling edge trigger detection
				p_exti_reg->RTSR |= EXTI_FTSR_MASK(exti_line);
				p_exti_reg->FTSR |= EXTI_RTSR_MASK(exti_line);
				break;
			default:
				ret_stat = e_ec_invalid_param;
				break;
		}
	}

	return ret_stat;
}

void EXTI_irq_handle(const uint32_t exti_line)
{
	// Clear EXTI PR register
	t_EXTI_RegDef * const p_exti_reg = CAST_TO(t_EXTI_RegDef * const, EXTI_BASE);

	if ((p_exti_reg->PR & EXTI_PR_MASK(exti_line)) != 0u) {
		p_exti_reg->PR |= EXTI_PR_MASK(exti_line);
	}
}

/*** EOF ***/
