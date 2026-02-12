/**
 * Copyright (c) 2025 OwlTech
 *
 * \file usart.h
 * \brief
 * \author OwlTech
 * \date Feb 10, 2026
 */

#ifndef USART_H_
#define USART_H_

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
typedef struct {
	volatile uint32_t USARTx_SR;
	volatile uint32_t USARTx_DR;
	volatile uint32_t USARTx_BRR;
	volatile uint32_t USARTx_CR1;
	volatile uint32_t USARTx_CR2;
	volatile uint32_t USARTx_CR3;
	volatile uint32_t USARTx_GTPR;
} t_USART_RegDef;

typedef enum {
	e_usart_1 		= 0u,
	e_usart_2 		= 1u,
	e_usart_3 		= 2u,
	e_usart_4 		= 3u,
	e_usart_5 		= 4u,
	e_usart_6 		= 5u,
	e_usart_max	 	= 6u
} t_usart_port;

typedef enum {
	e_usart_mode_tx_only 	= 0u,
	e_usart_mode_rx_only 	= 1u,
	e_usart_mode_txrx 		= 2u,
	e_usart_mode_max 		= 3u
} t_usart_mode;

typedef enum {
	e_usart_baud_1200 	= 0u,
	e_usart_baud_2400 	= 1u,
	e_usart_baud_9600 	= 2u,
	e_usart_baud_19k200 = 3u,
	e_usart_baud_38k400 = 4u,
	e_usart_baud_57k600 = 5u,
	e_usart_baud_115k2 	= 6u,
	e_usart_baud_230k4 	= 7u,
	e_usart_baud_460k8 	= 8u,
	e_usart_baud_921k6 	= 8u,
	e_usart_baud_max	= 10u
} t_usart_baud;

typedef enum {
	e_usart_stop_bit_1 		= 0u,
	e_usart_stop_bit_0p5 	= 1u,
	e_usart_stop_bit_2 		= 2u,
	e_usart_stop_bit_1p5 	= 3u,
	e_usart_stop_bit_max	= 4u
} t_usart_stop_bit;

typedef enum {
	e_usart_parity_even = 0u,
	e_usart_parity_odd 	= 1u,
	e_usart_parity_none = 2u,
	e_usart_parity_max	= 3u
} t_usart_parity;

typedef enum {
	e_usart_hwflow_none 	= 0u,
	e_usart_hwflow_rts 		= 1u,
	e_usart_hwflow_cts 		= 2u,
	e_usart_hwflow_rtscts	= 3u,
	e_usart_hwflow_max		= 4u
} t_usart_hwflow;

typedef struct {
	t_USART_RegDef * const p_usart_reg;
	t_usart_mode mode;
	t_usart_baud baud;
	t_usart_stop_bit stop_bits;
	t_bool word_9bit_en;			//!< 9-bit word length mode enable.
									//!< \value{FALSE,8-bit word length}
									//!< \value{TRUE,9-bit word length}
	t_usart_parity parity_ctrl;
	t_usart_hwflow hwflow_ctrl;
	t_bool over8_en;				//!< Oversampling by 8 mode enabled.
									//!< \value{FALSE,oversampling by 16}
									//!< \value{TRUE,oversampling by 8}
} t_usart_handle;

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
t_error_code USART_peri_enable(const t_usart_port usart_sel, const uint8_t port_en, const uint8_t lpwrm_en);

t_error_code USART_peri_reset(const t_usart_port usart_sel);

t_USART_RegDef * const USART_get_peri_base(const t_usart_port usart_sel);

t_error_code USART_config(const t_usart_handle * const p_usart_handle);

void USART_peri_ctrl(t_USART_RegDef * const p_usart, const t_bool usart_en);

uint32_t USART_read_byte(t_USART_RegDef * const p_usart, uint8_t * const p_buf, const uint32_t buf_len);

void USART_write_byte(t_USART_RegDef * const p_usart, const uint8_t * const p_data, const uint32_t data_len);

#endif /* USART_H_ */
/*** EOF ***/
