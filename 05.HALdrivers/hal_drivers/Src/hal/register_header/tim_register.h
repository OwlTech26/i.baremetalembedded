/**
 * Copyright (c) 2025 OwlTech
 *
 * \file tim_register.h
 * \brief
 * \author OwlTech
 * \date Nov 21, 2025
 */

#ifndef TIM_REGISTER_H_
#define TIM_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
/** \name General Purpose Timers 1. */
/**@{*/
#define TIM2_BASE	(0x40000000u)	//!< 32 bit timer.
#define TIM3_BASE	(0x40000400u)	//!< 16 bit timer.
#define TIM4_BASE	(0x40000800u)	//!< 16 bit timer.
#define TIM5_BASE	(0x40000C00u)	//!< 32 bit timer.

#define TIMx_CR1_OFS							(0x00u) //!< TIMx control register 1. offset.
	#define TIMx_CR1_GET(base)					(HAL_REG_READ((base + TIMx_CR1_OFS)))
	#define TIMx_CR1_SET(base, data)			(HAL_REG_WRITE((base + TIMx_CR1_OFS), (uint32_t)data))
		#define TIMx_CR1_CEN_WIDTH				(1u)
		#define TIMx_CR1_CEN_POS				(0u)
		#define TIMx_CR1_CEN_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_CEN_POS, TIMx_CR1_CEN_WIDTH))
		#define TIMx_CR1_CEN_NMASK 				(~(TIMx_CR1_CEN_MASK))
		#define TIMx_CR1_UDIS_WIDTH				(1u)
		#define TIMx_CR1_UDIS_POS				(0u)
		#define TIMx_CR1_UDIS_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_UDIS_POS, TIMx_CR1_UDIS_WIDTH))
		#define TIMx_CR1_UDIS_NMASK 			(~(TIMx_CR1_UDIS_MASK))
		#define TIMx_CR1_URS_WIDTH				(1u)
		#define TIMx_CR1_URS_POS				(2u)
		#define TIMx_CR1_URS_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_URS_POS, TIMx_CR1_URS_WIDTH))
		#define TIMx_CR1_URS_NMASK 				(~(TIMx_CR1_URS_MASK))
		#define TIMx_CR1_OPM_WIDTH				(1u)
		#define TIMx_CR1_OPM_POS				(3u)
		#define TIMx_CR1_OPM_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_OPM_POS, TIMx_CR1_OPM_WIDTH))
		#define TIMx_CR1_OPM_NMASK 				(~(TIMx_CR1_OPM_MASK))
		#define TIMx_CR1_DIR_WIDTH				(1u)
		#define TIMx_CR1_DIR_POS				(4u)
		#define TIMx_CR1_DIR_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_DIR_POS, TIMx_CR1_DIR_WIDTH))
		#define TIMx_CR1_DIR_NMASK 				(~(TIMx_CR1_DIR_MASK))
		#define TIMx_CR1_CMS_WIDTH				(2u)
		#define TIMx_CR1_CMS_POS				(5u)
		#define TIMx_CR1_CMS_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_CMS_POS, TIMx_CR1_CMS_WIDTH))
		#define TIMx_CR1_CMS_NMASK 				(~(TIMx_CR1_CMS_MASK))
		#define TIMx_CR1_ARPE_WIDTH				(1u)
		#define TIMx_CR1_ARPE_POS				(7u)
		#define TIMx_CR1_ARPE_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_ARPE_POS, TIMx_CR1_ARPE_WIDTH))
		#define TIMx_CR1_ARPE_NMASK 			(~(TIMx_CR1_ARPE_MASK))
		#define TIMx_CR1_CKD_WIDTH				(2u)
		#define TIMx_CR1_CKD_POS				(8u)
		#define TIMx_CR1_CKD_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR1_CKD_POS, TIMx_CR1_CKD_WIDTH))
		#define TIMx_CR1_CKD_NMASK 				(~(TIMx_CR1_CKD_MASK))
#define TIMx_CR2_OFS							(0x04u) //!< TIMx control register 2. offset.
	#define TIMx_CR2_GET(base)					(HAL_REG_READ((base + TIMx_CR2_OFS)))
	#define TIMx_CR2_SET(base, data)			(HAL_REG_WRITE((base + TIMx_CR2_OFS), (uint32_t)data))
		#define TIMx_CR2_CCDS_WIDTH				(1u)
		#define TIMx_CR2_CCDS_POS				(3u)
		#define TIMx_CR2_CCDS_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR2_CCDS_POS, TIMx_CR2_CCDS_WIDTH))
		#define TIMx_CR2_CCDS_NMASK 			(~(TIMx_CR2_CCDS_MASK))
		#define TIMx_CR2_MMS_WIDTH				(3u)
		#define TIMx_CR2_MMS_POS				(4u)
		#define TIMx_CR2_MMS_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR2_MMS_POS, TIMx_CR2_MMS_WIDTH))
		#define TIMx_CR2_MMS_NMASK 				(~(TIMx_CR2_MMS_MASK))
		#define TIMx_CR2_TI1S_WIDTH				(1u)
		#define TIMx_CR2_TI1S_POS				(7u)
		#define TIMx_CR2_TI1S_MASK				(HAL_BIT_CREATE_MASK(TIMx_CR2_TI1S_POS, TIMx_CR2_TI1S_WIDTH))
		#define TIMx_CR2_TI1S_NMASK 			(~(TIMx_CR2_TI1S_MASK))
/**@{*/


/** \name General Purpose Timers 2. */
#define TIM6_BASE	(0x40001000u)
#define TIM7_BASE	(0x40001400u)
#define TIM9_BASE	(0x40014000u)
#define TIM10_BASE	(0x40014400u)
#define TIM11_BASE	(0x40014800u)
#define TIM12_BASE	(0x40001800u)
#define TIM13_BASE	(0x40001C00u)
#define TIM14_BASE	(0x40002000u)
/**@{*/

/** \name Advanced Purpose Timers */
/**@{*/
#define TIM1_BASE	(0x40010000u)
#define TIM8_BASE	(0x40010400u)
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

#endif /* TIM_REGISTER_H_ */
/*** EOF ***/
