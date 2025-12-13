/**
 * Copyright (c) 2025 OwlTech
 *
 * \file spi.h
 * \brief
 * \author OwlTech
 * \date Nov 21, 2025
 */

#ifndef SPI_H_
#define SPI_H_

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
	volatile uint32_t SPIx_CR1;
	volatile uint32_t SPIx_CR2;
	volatile const uint32_t SPIx_SR;
	volatile uint32_t SPIx_DR;
	volatile uint32_t SPIx_CRCPR;
	volatile const uint32_t SPIx_RXCRCR;
	volatile const uint32_t SPIx_TXCRCR;
	volatile uint32_t SPIx_I2SCFGR;
	volatile uint32_t SPIx_I2SPR;
} t_SPI_RegDef;

typedef enum {
	e_spi_1 		= 0u,
	e_spi_2 		= 1u,
	e_spi_3 		= 2u,
	e_spi_4 		= 3u,
	e_spi_max	 	= 4u
} t_spi_port;

typedef enum {
	e_spi_full_duplex 		= 0u,
	e_spi_half_duplex 		= 1u,
	e_spi_simplex_txonly	= 2u,
	e_spi_simplex_rxonly	= 3u,
	e_spi_bus_cfg_max		= 4u
} t_spi_bus_cfg;

typedef enum {
	e_spi_br_2 		= 0u,
	e_spi_br_4 		= 1u,
	e_spi_br_8 		= 2u,
	e_spi_br_16		= 3u,
	e_spi_br_32		= 4u,
	e_spi_br_64		= 5u,
	e_spi_br_128	= 6u,
	e_spi_br_256	= 7u,
	e_spi_br_max	= 8u
} t_spi_speed;

typedef struct {
	t_SPI_RegDef * const p_spi_reg;
	t_bool 		  	  	 master_en;
	t_spi_bus_cfg 	  	 bus_cfg;
	t_spi_speed 	  	 speed;
	t_bool	 	  	  	 dff_16bit_en;
	t_bool		 	  	 cpol_en;
	t_bool		 	  	 cpha_en;
	t_bool		 	  	 ssm_en;
} t_spi_handle;

typedef enum {
	e_spi_event_rx_done		= 0u,
	e_spi_event_tx_done		= 1u,
	e_spi_event_ovr_error	= 2u,
	e_spi_event_max			= 3u
} t_spi_event;

typedef struct {
	t_SPI_RegDef *  p_spi_reg;
	uint8_t * 		p_tx_buffer;
	uint8_t * 		p_rx_buffer;
	uint32_t 		tx_len;
	uint32_t 		rx_len;
	t_bool			spi_tx_bsy;
	t_bool			spi_rx_bsy;
} t_spi_it_handle;

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
t_error_code SPI_peri_enable(const t_spi_port spi_sel, const uint8_t port_en, const uint8_t lpwrm_en);

t_error_code SPI_peri_reset(const t_spi_port spi_sel);

t_SPI_RegDef * const SPI_get_peri_base(const t_spi_port spi_sel);

t_error_code SPI_config(const t_spi_handle * const p_spi_handle);

void SPI_peri_ctrl(t_SPI_RegDef * const p_spi, const t_bool spi_en);

void SPI_tx_data(t_SPI_RegDef * const p_spi, const uint8_t * const p_data, const uint32_t data_len);

void SPI_rx_data(t_SPI_RegDef * const p_spi, uint8_t * const p_data, const uint32_t data_len);

t_bool SPI_tx_data_it(t_spi_it_handle * const p_spi_handle, const uint8_t * const p_data, const uint32_t data_len);

t_bool SPI_rx_data_it(t_spi_it_handle * const p_spi_handle, uint8_t * const p_data, const uint32_t data_len);

t_error_code SPI_interrupt_config(const t_spi_port spi_sel, uint32_t spi_irq_prio);

void SPI_init_it_handle(t_spi_it_handle * const p_spi_handle, t_SPI_RegDef * const p_spi);

void SPI_irq_handle(t_spi_it_handle * const p_spi_handle);

void SPI_tx_it_close(t_spi_it_handle * const p_spi_handle);

void SPI_rx_it_close(t_spi_it_handle * const p_spi_handle);

void SPI_api_event_cb(const t_spi_it_handle * const p_spi_handle, const t_spi_event spi_event);

#endif /* SPI_H_ */
/*** EOF ***/
