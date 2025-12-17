/**
 * Copyright (c) 2025 OwlTech
 *
 * \file veml6040_regmap.h
 * \brief
 * \author OwlTech
 * \date Dec 15, 2025
 */

#ifndef VEML6040_REGMAP_H_
#define VEML6040_REGMAP_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define VEML6040_ADDR							(0x10u)

#define VEML6040_CONF							(0x00u)
	#define VEML6040_CONF_LEN					(1u)
		//!< Chip shutdown setting.
		#define VEML6040_CONF_SD_WIDTH			(1u)
		#define VEML6040_CONF_SD_POS			(0u)
		#define VEML6040_CONF_SD_MASK			(HAL_BIT_CREATE_MASK(VEML6040_CONF_SD_POS, VEML6040_CONF_SD_WIDTH))
		#define VEML6040_CONF_SD_NMASK 			(~(VEML6040_CONF_SD_MASK))
		//!< Auto / manual force mode.
		#define VEML6040_CONF_AF_WIDTH			(1u)
		#define VEML6040_CONF_AF_POS			(1u)
		#define VEML6040_CONF_AF_MASK			(HAL_BIT_CREATE_MASK(VEML6040_CONF_AF_POS, VEML6040_CONF_AF_WIDTH))
		#define VEML6040_CONF_AF_NMASK 			(~(VEML6040_CONF_AF_MASK))
		//!< Proceed one detecting cycle at manual force mode.
		#define VEML6040_CONF_TRIG_WIDTH		(1u)
		#define VEML6040_CONF_TRIG_POS			(2u)
		#define VEML6040_CONF_TRIG_MASK			(HAL_BIT_CREATE_MASK(VEML6040_CONF_TRIG_POS, VEML6040_CONF_TRIG_WIDTH))
		#define VEML6040_CONF_TRIG_NMASK 		(~(VEML6040_CONF_TRIG_MASK))
		//!< Integration time setting
		#define VEML6040_CONF_IT_WIDTH			(3u)
		#define VEML6040_CONF_IT_POS			(4u)
		#define VEML6040_CONF_IT_MASK			(HAL_BIT_CREATE_MASK(VEML6040_CONF_IT_POS, VEML6040_CONF_IT_WIDTH))
		#define VEML6040_CONF_IT_NMASK 			(~(VEML6040_CONF_IT_MASK))
#define VEML6040_RESERVED_1						(0x01u)
#define VEML6040_RESERVED_2						(0x02u)
#define VEML6040_RESERVED_3						(0x03u)
#define VEML6040_RESERVED_4						(0x04u)
#define VEML6040_RESERVED_5						(0x05u)
#define VEML6040_RESERVED_6						(0x06u)
#define VEML6040_RESERVED_7						(0x07u)
	#define VEML6040_RESERVED_LEN				(2u)
	//!< Reserved_L (7 : 0)
	//!< Reserved_H (15 : 8)
#define VEML6040_R_DATA							(0x08u)
#define VEML6040_G_DATA							(0x09u)
#define VEML6040_B_DATA							(0x0Au)
#define VEML6040_W_DATA							(0x0Bu)
	#define VEML6040_DATA_LEN					(2u)
	//!< Data_L (7 : 0)
	//!< Data_H (15 : 8)

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

#endif /* VEML6040_REGMAP_H_ */
/*** EOF ***/
