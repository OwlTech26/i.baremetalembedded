/**
 * Copyright (c) 2025 OwlTech
 *
 * \file hal_reg.h
 * \brief
 * \author OwlTech
 * \date Nov 04, 2025
 */

#ifndef HAL_REG_H_
#define HAL_REG_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include <stdint.h>

#include "cast.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define HAL_BIT_CREATE_MASK(bit_pos, width) 	    ((((uint32_t)1u << width) - 1u) << bit_pos)
#define HAL_BIT_CREATE_NMASK(bit_pos, width) 	    (~HAL_BIT_CREATE_MASK(bit_pos, width))
#define HAL_BIT_VAL(bit_pos, width, value)          (((value) << bit_pos) &  HAL_BIT_CREATE_MASK(bit_pos, width))
#define HAL_BIT_GET(reg_val, bit_pos, width)        (((reg_val)&HAL_BIT_CREATE_MASK(bit_pos, width)) >> bit_pos)
#define HAL_BIT_SET(reg_val, bit_pos, width, value) (reg_val) = ((reg_val)&HAL_BIT_CREATE_NMASK(bit_pos, width)) | HAL_BIT_VAL(bit_pos, width, value)

/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief Full word read register.
 *  \param[in] read_addr Address to read from.
 *  \return Read value.
 */
static inline uint32_t HAL_REG_READ(const uint32_t read_addr);

/** \brief Full word write register.
 *  \param[in] write_addr Address to write to.
 *  \param[in] write_data Data to be written to register.
 */
static inline void HAL_REG_WRITE(const uint32_t write_addr, const uint32_t write_data);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
static inline uint32_t HAL_REG_READ(const uint32_t read_addr)
{
	volatile uint32_t const * const p_reg_val = CAST_TO(volatile uint32_t const * const, read_addr);

	return *p_reg_val;
}

static inline void HAL_REG_WRITE(const uint32_t write_addr, const uint32_t write_data)
{
	volatile uint32_t * const p_reg_val = CAST_TO(volatile uint32_t * const, write_addr);

	*p_reg_val = write_data;
}


/******************************************************************************/
/*---------------------------API Function Prototypes--------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */

#endif /* HAL_REG_H_ */
/*** EOF ***/
