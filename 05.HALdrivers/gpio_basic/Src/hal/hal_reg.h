/**
 * Copyright (c) 2025 OwlTech
 *
 * \file hal_reg.h
 * \brief
 * \author OwlTech
 * \date Jun 11, 2025
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
/** \brief Returns new Register-bitfield value - lowlevel macro
 * 	\param[in] bf Specifies the bitfield to be set.
 * 	\param[in] value Specifies the value to be set to the bitfield.
 * 	\return Value shifted to correct bitfield bit-offset
 */
#define HAL_BF_VAL(bf, value) (((value) << bf##_POS) & bf##_MASK)

/** \brief Updates Register-bitfield to new value - lowlevel macro
 *	\param[in] reg_val Specifies the Register-value where the bitfield should be updated.
 * 	\param[in] bf Specifies the bitfield to be set.
 * 	\param[in] value Specifies the value to be set to the bitfield.
 * 	\return None
 */
#define HAL_BF_SET(reg_val, bf, value) (reg_val) = ((reg_val)&bf##_NMASK) | HAL_BF_VAL(bf, value)

/** \brief Returns current Register-bitfield value - lowlevel macro
 * 	\param[in] reg_val Specifies the Register-value where the bitfield should be extracted.
 * 	\param[in] bf Specifies the bitfield to be read.
 * 	return Extracted bitfield value
 */
#define HAL_BF_GET(reg_val, bf) (((reg_val)&bf##_MASK) >> bf##_POS)

/** \brief Creates a mask for a specified field based on its width and position.
 * 	\param[in] field Specifies the bitfield to be masked.
 * 	\return Mask of bitfield.
 */
#define HAL_BF_CREATE_MASK(field) ((((uint32_t)1u << field##_WIDTH) - 1u) << field##_POS)

/** \brief Creates a port mask for a specified field based on its width and position.
 * 	\param[in] field Specifies the bitfield to be masked.
 * 	\param[in] port Specifies the port bitfield to be masked.
 * 	\return Mask of bitfield.
 */
#define HAL_BF_CREATE_PORT_MASK(field, port) ((((uint32_t)1u << field##_WIDTH) - 1u) << field##port##_POS)

/** \brief Returns new Register-bitfield value - highlevel macro
 * 	\param[in] field Specifies the bitfield to be set.
 * 	\param[in] value Specifies the value to be set to the bitfield.
 * 	\return Value shifted to correct bitfield bit-offset
 */
#define HAL_FIELD_VAL(field, value) HAL_BF_VAL(field, (uint32_t)(value))

/** \brief Updates Register-bitfield to new value - highlevel macro
 * 	\param[in] reg_val Specifies the Register-value where the bitfield should be updated.
 * 	\param[in] field Specifies the bitfield to be set.
 * 	\param[in] value Specifies the value to be set to the bitfield.
 * 	\return None
 */
#define HAL_FIELD_SET(reg_val, field, value) HAL_BF_SET(reg_val, field, (uint32_t)(value))

/** \brief Returns current Register-bitfield value - highlevel macro
 * 	\param[in] reg_val Specifies the Register-value where the bitfield should be extracted.
 * 	\param[in] field Specifies the bitfield to be read.
 * 	return Extracted bitfield value
 */
#define HAL_FIELD_GET(reg_val, field) HAL_BF_GET(reg_val, field)

/** \brief Creates a mask for a specified field based on its width and position.
 * 	\param[in] field Specifies the bitfield to be masked.
 * 	\return Mask of bitfield.
 */
#define HAL_FIELD_CREATE_MASK(field) (HAL_BF_CREATE_MASK(field))

/** \brief Creates a port mask for a specified field based on its width and position.
 * 	\param[in] field Specifies the bitfield to be masked.
 * 	\param[in] port Specifies the port bitfield to be masked.
 * 	\return Mask of bitfield.
 */
#define HAL_FIELD_CREATE_PORT_MASK(field, port) (HAL_BF_CREATE_PORT_MASK(field, port))

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
