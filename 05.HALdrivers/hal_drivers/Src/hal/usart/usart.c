/**
 * Copyright (c) 2025 OwlTech
 *
 * \file usart.c
 * \brief
 * \author OwlTech
 * \date Feb 10, 2026
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "usart.h"

#include "rcc.h"
#include "cast.h"
#include "hal_reg.h"
#include "usart_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/


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
t_error_code USART_peri_enable(const t_usart_port usart_sel, const uint8_t port_en, const uint8_t lpwrm_en)
{
	/** \paramrange{usart_sel,e_usart_1,e_usart_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (usart_sel < e_usart_max) {
		// Enable the peripheral clock for SPI peripheral
		const uint8_t peri_sel[e_usart_max] = {e_peri_usart1, e_peri_usart2, e_peri_usart3, e_peri_usart4, e_peri_usart5, e_peri_usart6};
		const t_clock_peri peri_clk_sel = ((usart_sel == e_usart_1) || (usart_sel == e_usart_6)) ? e_peri_apb2 : e_peri_apb1;
		RCC_enable_peri(peri_clk_sel, peri_sel[usart_sel], port_en, lpwrm_en);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_error_code USART_peri_reset(const t_usart_port usart_sel)
{
	t_error_code ret_stat = e_ec_invalid_param;

	return ret_stat;
}

t_USART_RegDef * const USART_get_peri_base(const t_usart_port usart_sel)
{
	const uint32_t usart_base[e_usart_max] = {USART1_BASE, USART2_BASE, USART3_BASE, UART4_BASE, UART5_BASE, USART6_BASE};

	t_USART_RegDef * const ret_base = (usart_sel < e_usart_max) ? CAST_TO(t_USART_RegDef * const, usart_base[usart_sel]) : NULL;

	return ret_base;
}

t_error_code USART_config(const t_usart_handle * const p_usart_handle)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((p_usart_handle->mode < e_usart_mode_max) &&
		(p_usart_handle->baud < e_usart_baud_max) &&
		(p_usart_handle->stop_bits < e_usart_stop_bit_max) &&
		(p_usart_handle->parity_ctrl < e_usart_parity_max) &&
		(p_usart_handle->hwflow_ctrl < e_usart_hwflow_max)) {


		// Configure USART CR1 register
		const uint32_t usart_mode_set[e_usart_mode_max] = {USART_CR1_TE_MASK, USART_CR1_RE_MASK, USART_CR1_TE_MASK | USART_CR1_RE_MASK};
		const uint32_t parity_ctrl_set = (p_usart_handle->parity_ctrl == e_usart_parity_none) ? 0u :
				((uint32_t)p_usart_handle->parity_ctrl | USART_CR1_PCE_MASK);
		p_usart_handle->p_usart_reg->USARTx_CR1 =
			usart_mode_set[p_usart_handle->mode] | 							// Configure modes
			parity_ctrl_set 					 | 							// Set parity
			(b_to_uint32(p_usart_handle->word_9bit_en) << USART_CR1_M_POS); // Set Word length

		// Configure USART CR2 register
		p_usart_handle->p_usart_reg->USARTx_CR2 = ((uint32_t)p_usart_handle->stop_bits) << USART_CR2_STOP_POS;

		// Configure USART CR3 register
		const uint32_t hwflow_ctrl_set =
			(p_usart_handle->hwflow_ctrl == e_usart_hwflow_rtscts) ? (USART_CR3_RTSE_MASK | USART_CR3_CTSE_MASK) :
			(p_usart_handle->hwflow_ctrl == e_usart_hwflow_rts) ? USART_CR3_RTSE_MASK :
			(p_usart_handle->hwflow_ctrl == e_usart_hwflow_cts) ? USART_CR3_CTSE_MASK : 0u;
		p_usart_handle->p_usart_reg->USARTx_CR3 = hwflow_ctrl_set;

		// ToDo: Configure baud rate
		p_usart_handle->p_usart_reg->USARTx_BRR;
		p_usart_handle->baud;

	}

	return ret_stat;
}

void USART_peri_ctrl(t_USART_RegDef * const p_i2c, const t_bool usart_en)
{
	// Enable/disable the USART by setting UE in CR1
}

/*** EOF ***/
