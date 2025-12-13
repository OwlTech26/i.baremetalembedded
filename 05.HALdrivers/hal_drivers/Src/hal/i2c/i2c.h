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

#endif /* I2C_H_ */
/*** EOF ***/
