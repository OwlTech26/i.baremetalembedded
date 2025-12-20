/**
 * Copyright (c) 2025 OwlTech
 *
 * \file i2c.h
 * \brief
 * \author OwlTech
 * \date Dec 8, 2025
 */

#ifndef I2C_H_
#define I2C_H_

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
	volatile uint32_t I2Cx_CR1;
	volatile uint32_t I2Cx_CR2;
	volatile uint32_t I2Cx_OAR1;
	volatile uint32_t I2Cx_OAR2;
	volatile uint32_t I2Cx_DR;
	volatile uint32_t I2Cx_SR1;
	volatile const uint32_t I2Cx_SR2;
	volatile uint32_t I2Cx_CCR;
	volatile uint32_t I2Cx_TRISE;
	volatile uint32_t I2Cx_FLTR;
} t_I2C_RegDef;

typedef enum {
	e_i2c_1 		= 0u,
	e_i2c_2 		= 1u,
	e_i2c_3 		= 2u,
	e_i2c_max	 	= 3u
} t_i2c_port;

typedef enum {
	e_i2c_spd_sm	= 0u, //!< Standard mode 100 kHz SCL speed.
	e_i2c_spd_fm2k	= 1u, //!< Fast mode 200 kHz SCL speed.
	e_i2c_spd_fm4k	= 2u, //!< Fast mode 400 kHz SCL speed.
	e_i2c_spd_max	= 3u
} t_i2c_speed;

typedef struct {
	t_I2C_RegDef * const p_i2c_reg;
	t_bool addr_mode_10bit_en;	//!< 10-bit slave addressing mode enable.
								//!< \value{FALSE,7-bit slave addressing}
								//!< \value{TRUE,10-bit slave addressing}
	uint16_t own_addr1; 		//!< Device address.
	uint8_t own_addr2; 			//!< Device address 2. Used only in dual addressing mode.
	t_i2c_speed speed;			//!< SCL speed.
	t_bool fmode_duty_16_9_en;  //!< Fm mode duty cycle.
    							//!< \value{FALSE,Fm mode t_low/t_high duty cycle = 2}
								//!< \value{TRUE,Fm mode t_low/t_high duty cycle = 16/9}
	uint8_t scl_trise; 			//!< SCL rise time value.
} t_i2c_handle;

typedef enum {
	e_i2c_it_st_ready	= 0u,
	e_i2c_it_st_tx_busy	= 1u,
	e_i2c_it_st_rx_busy	= 2u
} t_i2c_it_stat;

typedef struct {
	t_I2C_RegDef *  p_i2c_reg;
	uint8_t * 		p_tx_buffer;
	uint8_t * 		p_rx_buffer;
	uint8_t 		slave_addr;
	uint32_t 		tx_len;
	uint32_t 		rx_len;
	t_bool			start_rep;
	t_i2c_it_stat	i2c_it_stat;
} t_i2c_it_handle;

typedef enum {
	e_i2c_event_rx_done		= 0u,
	e_i2c_event_tx_done		= 1u,
	e_i2c_event_stop		= 2u,
	e_i2c_event_ovr_error	= 3u,
	e_i2c_event_max			= 4u
} t_i2c_event;

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
t_error_code I2C_peri_enable(const t_i2c_port i2c_sel, const uint8_t port_en, const uint8_t lpwrm_en);

t_error_code I2C_peri_reset(const t_i2c_port i2c_sel);

t_I2C_RegDef * const I2C_get_peri_base(const t_i2c_port i2c_sel);

t_error_code I2C_config(const t_i2c_handle * const p_i2c_handle);

void I2C_peri_ctrl(t_I2C_RegDef * const p_i2c, const t_bool i2c_en);

void I2C_read_byte(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr, uint8_t * const p_data);

void I2C_read_byte_burst(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr, uint8_t * const p_data, const uint32_t data_len);

void I2C_write_byte_burst(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr, const uint8_t * const p_data, const uint32_t data_len);



t_i2c_it_stat I2C_read_byte_it(t_i2c_it_handle * const p_i2c_handle, const uint8_t slave_addr, uint8_t * const p_data, const uint32_t data_len, const t_bool start_rep);

t_i2c_it_stat I2C_write_byte_it(t_i2c_it_handle * const p_i2c_handle, const uint8_t slave_addr, const uint8_t * const p_data, const uint32_t data_len, const t_bool start_rep);

void I2C_api_event_cb(const t_i2c_it_handle * const p_i2c_handle, const t_i2c_event i2c_event);

/** \brief Interrupt handling for both master and slave mode of a device
 *  \param p_i2c_handle[in,out] I2C handler parameters
 */
void I2C_ev_irq_handling(t_i2c_it_handle * const p_i2c_handle);

#endif /* I2C_H_ */
/*** EOF ***/
