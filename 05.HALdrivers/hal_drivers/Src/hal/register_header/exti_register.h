/**
 * Copyright (c) 2025 OwlTech
 *
 * \file exti_register.h
 * \brief External Interrupt/Event controller STM32F446xx MCU specific register header file.
 * \author OwlTech
 * \date Nov 11, 2025
 */

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define EXTI_BASE 0x40013C00u

#define EXTI_IMR_OFS						(0x00u) //!< Interrupt mask register offset.
	#define EXTI_IMR_GET()					(HAL_REG_READ((EXTI_BASE + EXTI_IMR_OFS)))
	#define EXTI_IMR_SET(data)				(HAL_REG_WRITE((EXTI_BASE + EXTI_IMR_OFS), (uint32_t)data))
	#define EXTI_IMR_WIDTH					(1u)
	#define EXTI_IMR_MASK(pos)				(HAL_BIT_CREATE_MASK(pos, EXTI_IMR_WIDTH))
	#define EXTI_IMR_NMASK(pos)				(~EXTI_IMR_MASK(pos))
#define EXTI_EMR_OFS						(0x04u) //!< Event mask register offset.
	#define EXTI_EMR_GET()					(HAL_REG_READ((EXTI_BASE + EXTI_EMR_OFS)))
	#define EXTI_EMR_SET(data)				(HAL_REG_WRITE((EXTI_BASE + EXTI_EMR_OFS), (uint32_t)data))
	#define EXTI_EMR_WIDTH					(1u)
	#define EXTI_EMR_MASK(pos)				(HAL_BIT_CREATE_MASK(pos, EXTI_EMR_WIDTH))
	#define EXTI_EMR_NMASK(pos)				(~EXTI_EMR_MASK(pos))
#define EXTI_RTSR_OFS						(0x08u) //!< Rising trigger selection register offset.
	#define EXTI_RTSR_GET()					(HAL_REG_READ((EXTI_BASE + EXTI_RTSR_OFS)))
	#define EXTI_RTSR_SET(data)				(HAL_REG_WRITE((EXTI_BASE + EXTI_RTSR_OFS), (uint32_t)data))
	#define EXTI_RTSR_WIDTH					(1u)
	#define EXTI_RTSR_MASK(pos)				(HAL_BIT_CREATE_MASK(pos, EXTI_RTSR_WIDTH))
	#define EXTI_RTSR_NMASK(pos)			(~EXTI_RTSR_MASK(pos))
#define EXTI_FTSR_OFS						(0x0Cu) //!< Falling trigger selection register offset.
	#define EXTI_FTSR_GET()					(HAL_REG_READ((EXTI_BASE + EXTI_FTSR_OFS)))
	#define EXTI_FTSR_SET(data)				(HAL_REG_WRITE((EXTI_BASE + EXTI_FTSR_OFS), (uint32_t)data))
	#define EXTI_FTSR_WIDTH					(1u)
	#define EXTI_FTSR_MASK(pos)				(HAL_BIT_CREATE_MASK(pos, EXTI_FTSR_WIDTH))
	#define EXTI_FTSR_NMASK(pos)			(~EXTI_FTSR_MASK(pos))
#define EXTI_SWIER_OFS						(0x10u) //!< Software interrupt event register offset.
	#define EXTI_SWIER_GET()				(HAL_REG_READ((EXTI_BASE + EXTI_SWIER_OFS)))
	#define EXTI_SWIER_SET(data)			(HAL_REG_WRITE((EXTI_BASE + EXTI_SWIER_OFS), (uint32_t)data))
	#define EXTI_SWIER_WIDTH				(1u)
	#define EXTI_SWIER_MASK(pos)			(HAL_BIT_CREATE_MASK(pos, EXTI_SWIER_WIDTH))
	#define EXTI_SWIER_NMASK(pos)			(~EXTI_SWIER_MASK(pos))
#define EXTI_PR_OFS							(0x14u) //!< Pending register offset.
	#define EXTI_PR_GET()					(HAL_REG_READ((EXTI_BASE + EXTI_PR_OFS)))
	#define EXTI_PR_SET(data)				(HAL_REG_WRITE((EXTI_BASE + EXTI_PR_OFS), (uint32_t)data))
	#define EXTI_PR_WIDTH					(1u)
	#define EXTI_PR_MASK(pos)				(HAL_BIT_CREATE_MASK(pos, EXTI_PR_WIDTH))
	#define EXTI_PR_NMASK(pos)				(~EXTI_PR_MASK(pos))


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief  */


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

#endif /* EXTI_REGISTER_H_ */
/*** EOF ***/
