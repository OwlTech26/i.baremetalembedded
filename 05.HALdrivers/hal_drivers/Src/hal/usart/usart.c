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
/** \name UART Baud Rate Parameters. */
/**@{*/
#define USART_BAUD_RATE_1200 	(1200u)
#define USART_BAUD_RATE_2400 	(2400u)
#define USART_BAUD_RATE_9600 	(9600u)
#define USART_BAUD_RATE_19K200  (19200u)
#define USART_BAUD_RATE_38K400	(38400u)
#define USART_BAUD_RATE_57K600	(57600u)
#define USART_BAUD_RATE_115K2	(115200llu)
#define USART_BAUD_RATE_230K4 	(230400llu)
#define USART_BAUD_RATE_460K8 	(460800llu)
#define USART_BAUD_RATE_921K6 	(921600llu)
#define USART_BRR_DIV_FACTOR	(2u)
#define USART_BRR_FRACT_MASK	(0x0000000Fu)
#define USART_BRR_INT_MASK	    (~USART_BRR_FRACT_MASK)
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
static uint32_t usart_compute_brr(const uint32_t peri_clk, const t_usart_baud baud_rate, const t_bool over8);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */


/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static uint32_t usart_compute_brr(const uint32_t peri_clk, const t_usart_baud baud_rate, const t_bool over8)
{
	const uint32_t baud_rates[e_usart_baud_max] = {USART_BAUD_RATE_1200, USART_BAUD_RATE_2400, USART_BAUD_RATE_9600, USART_BAUD_RATE_19K200, USART_BAUD_RATE_38K400, USART_BAUD_RATE_57K600, USART_BAUD_RATE_115K2,
		USART_BAUD_RATE_230K4, USART_BAUD_RATE_460K8, USART_BAUD_RATE_921K6};
	const uint32_t baud_rate_sel = baud_rates[baud_rate];

    /** Baud = fck / (8 * (2 - OVER8) * USARTDIV), format: Q12.4
     *  Note: When OVER8=0, the fractional part is coded on 4 bits and programmed by the
     *    DIV_fraction[3:0] bits in the USART_BRR register
     *  Note: When OVER8=1, the fractional part is coded on 3 bits and programmed by the
     *    DIV_fraction[2:0] bits in the USART_BRR register, and bit DIV_fraction[3] must be kept cleared.
     */
	uint32_t ret_brr_uq12_4 = (peri_clk + (baud_rate_sel / USART_BRR_DIV_FACTOR)) / baud_rate_sel;
	if (over8 != FALSE) {
	    ret_brr_uq12_4 *= USART_BRR_DIV_FACTOR;
	    ret_brr_uq12_4 = (ret_brr_uq12_4 & USART_BRR_INT_MASK) | ((ret_brr_uq12_4 & USART_BRR_FRACT_MASK) >> 1u);
	}

	return ret_brr_uq12_4;
}

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

		// Configure baud rate
		const t_clock_peri peri_clk_sel = (((uint32_t)p_usart_handle->p_usart_reg == USART1_BASE) || ((uint32_t)p_usart_handle->p_usart_reg == USART6_BASE)) ? e_peri_apb2 : e_peri_apb1;
		const uint32_t peri_clk = RCC_get_peri_clock_freq(peri_clk_sel);
		p_usart_handle->p_usart_reg->USARTx_BRR = usart_compute_brr(peri_clk, p_usart_handle->baud, p_usart_handle->over8_en);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

void USART_peri_ctrl(t_USART_RegDef * const p_usart, const t_bool usart_en)
{
	// Enable/disable the USART by setting UE in CR1
	if (usart_en != FALSE) { 	// Enable USART periphery
		p_usart->USARTx_CR1 |= USART_CR1_UE_MASK;
	} else { 				// Disable USART periphery
		p_usart->USARTx_CR1 &= USART_CR1_UE_NMASK;
	}
}

uint32_t USART_read_byte(t_USART_RegDef * const p_usart, uint8_t * const p_buf, const uint32_t buf_len)
{
	uint32_t ret_length = 0u;

	while ((ret_length < buf_len) && (p_buf[ret_length-1u] != '\r')) {
		// Wait until receive data register is not empty
		while((p_usart->USARTx_SR & USART_SR_RXNE_MASK) == 0u);
		p_buf[ret_length++] = p_usart->USARTx_DR;
	}

	return ret_length;
}

void USART_write_byte(t_USART_RegDef * const p_usart, const uint8_t * const p_data, const uint32_t data_len)
{
	for (uint32_t i=0u; i<data_len; ++i) {
		// Wait until transmit data register is empty
		while((p_usart->USARTx_SR & USART_SR_TXE_MASK) == 0u);

		p_usart->USARTx_DR = p_data[i];
	}
}

/*** EOF ***/
