/**
 * Copyright (c) 2025 OwlTech
 *
 * \file bmp280_regmap.h
 * \brief
 * \author OwlTech
 * \date Dec 1, 2025
 */

#ifndef BMP280_REGMAP_H_
#define BMP280_REGMAP_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
/** \name BMP80 Registers Address. */
/**@{*/
#define BMP280_REG_CALIB						(0x88u)
	#define BMP280_REG_CALIB_IDX_MIN			(0u)
	#define BMP280_REG_CALIB_IDX_MAX			(25u)
	#define BMP280_REG_CALIB_XX(idx)			(BMP280_REG_CALIB + idx)
#define BMP280_REG_ID							(0xD0u)
	#define BMP280_REG_ID_LEN					(1u)
#define BMP280_RESET							(0xE0u)
#define BMP280_STAT								(0xF3u)
#define BMP280_CTRL_MEAS						(0xF4u)
	#define BMP280_CTRL_MEAS_LEN				(1u)
		#define BMP280_CTRL_MEAS_MODE_WIDTH		(2u)
		#define BMP280_CTRL_MEAS_MODE_POS		(0u)
		#define BMP280_CTRL_MEAS_MODE_MASK		(HAL_BIT_CREATE_MASK(BMP280_CTRL_MEAS_MODE_POS, BMP280_CTRL_MEAS_MODE_WIDTH))
		#define BMP280_CTRL_MEAS_MODE_NMASK 	(~(BMP280_CTRL_MEAS_MODE_MASK))
		#define BMP280_CTRL_MEAS_OSRS_P_WIDTH	(3u)
		#define BMP280_CTRL_MEAS_OSRS_P_POS		(2u)
		#define BMP280_CTRL_MEAS_OSRS_P_MASK	(HAL_BIT_CREATE_MASK(BMP280_CTRL_MEAS_OSRS_P_POS, BMP280_CTRL_MEAS_OSRS_P_WIDTH))
		#define BMP280_CTRL_MEAS_OSRS_P_NMASK 	(~(BMP280_CTRL_MEAS_OSRS_P_MASK))
		#define BMP280_CTRL_MEAS_OSRS_T_WIDTH	(3u)
		#define BMP280_CTRL_MEAS_OSRS_T_POS		(5u)
		#define BMP280_CTRL_MEAS_OSRS_T_MASK	(HAL_BIT_CREATE_MASK(BMP280_CTRL_MEAS_OSRS_T_POS, BMP280_CTRL_MEAS_OSRS_T_WIDTH))
		#define BMP280_CTRL_MEAS_OSRS_T_NMASK 	(~(BMP280_CTRL_MEAS_OSRS_T_MASK))
#define BMP280_CONFIG					(0xF5u)
#define BMP280_PRESS_MSB				(0xF7u)
#define BMP280_PRESS_LSB				(0xF8u)
#define BMP280_PRESS_XLSB				(0xF9u)
#define BMP280_TEMP_MSB					(0xFAu)
#define BMP280_TEMP_LSB					(0xFBu)
#define BMP280_TEMP_XLSB				(0xFCu)
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

#endif /* BMP280_REGMAP_H_ */
/*** EOF ***/
