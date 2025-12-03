/**
 * Copyright (c) 2025 OwlTech
 *
 * \file syscfg_register.h
 * \brief System Configuration Controller STM32F446xx MCU specific register header file.
 * \author OwlTech
 * \date Nov 12, 2025
 */

#ifndef SYSCFG_REGISTER_H_
#define SYSCFG_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define SYSCFG_EXTICR_NUM 							(4u)
#define SYSCFG_EXTI_IN_EXTICR 						(4u)
#define SYSCFG_EXTI_TOTAL 							(SYSCFG_EXTICR_NUM * SYSCFG_EXTI_IN_EXTICR)

#define SYSCFG_BASE 0x40013800u

#define SYSCFG_MEMRMP_OFS							(0x00u) //!< Memory re-map register offset.
	#define SYSCFG_MEMRMP_GET()						(HAL_REG_READ((SYSCFG_BASE + SYSCFG_MEMRMP_OFS)))
	#define SYSCFG_MEMRMP_SET(data)					(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_MEMRMP_OFS), (uint32_t)data))
		#define SYSCFG_MEMRMP_MEM_MODE_WIDTH		(3u)
		#define SYSCFG_MEMRMP_MEM_MODE_POS			(0u)
		#define SYSCFG_MEMRMP_MEM_MODE_MASK			(HAL_BIT_CREATE_MASK(SYSCFG_MEMRMP_MEM_MODE_POS, SYSCFG_MEMRMP_MEM_MODE_WIDTH))
		#define SYSCFG_MEMRMP_MEM_MODE_NMASK 		(~(SYSCFG_MEMRMP_MEM_MODE_MASK))
		#define SYSCFG_MEMRMP_SWP_FMC_WIDTH			(2u)
		#define SYSCFG_MEMRMP_SWP_FMC_POS			(10u)
		#define SYSCFG_MEMRMP_SWP_FMC_MASK			(HAL_BIT_CREATE_MASK(SYSCFG_MEMRMP_SWP_FMC_POS, SYSCFG_MEMRMP_SWP_FMC_WIDTH))
		#define SYSCFG_MEMRMP_SWP_FMC_NMASK 		(~(SYSCFG_MEMRMP_SWP_FMC_MASK))
#define SYSCFG_PMC_OFS								(0x04u) //!< Peripheral mode register offset.
	#define SYSCFG_PMC_GET()						(HAL_REG_READ((SYSCFG_BASE + SYSCFG_PMC_OFS)))
	#define SYSCFG_PMC_SET(data)					(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_PMC_OFS), (uint32_t)data))
		#define SYSCFG_PMC_ADCxDC22_WIDTH			(3u)
		#define SYSCFG_PMC_ADCxDC22_POS				(16u)
		#define SYSCFG_PMC_ADCxDC22_MASK			(HAL_BIT_CREATE_MASK(SYSCFG_PMC_ADCxDC22_POS, SYSCFG_PMC_ADCxDC22_WIDTH))
		#define SYSCFG_PMC_ADCxDC22_NMASK 			(~(SYSCFG_PMC_ADCxDC22_MASK))
#define SYSCFG_EXTICR1_OFS							(0x08u) //!< External interrupt configuration register 1 offset.
	#define SYSCFG_EXTICR1_GET()					(HAL_REG_READ((SYSCFG_BASE + SYSCFG_EXTICR1_OFS)))
	#define SYSCFG_EXTICR1_SET(data)				(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_EXTICR1_OFS), (uint32_t)data))
		#define SYSCFG_EXTICR1_EXTIx_WIDTH			(4u)
		#define SYSCFG_EXTICR1_EXTIx_POS(idx)		((idx % SYSCFG_EXTI_IN_EXTICR) * SYSCFG_EXTICR1_EXTIx_WIDTH)
		#define SYSCFG_EXTICR1_EXTIx_MASK(idx)		(HAL_BIT_CREATE_MASK(SYSCFG_EXTICR1_EXTIx_POS(idx), SYSCFG_EXTICR1_EXTIx_WIDTH))
		#define SYSCFG_EXTICR1_EXTIx_NMASK(idx)		(~(SYSCFG_EXTICR1_EXTIx_MASK(idx)))
#define SYSCFG_EXTICR2_OFS							(0x0Cu) //!< External interrupt configuration register 2 offset.
	#define SYSCFG_EXTICR2_GET()					(HAL_REG_READ((SYSCFG_BASE + SYSCFG_EXTICR2_OFS)))
	#define SYSCFG_EXTICR2_SET(data)				(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_EXTICR2_OFS), (uint32_t)data))
		#define SYSCFG_EXTICR2_EXTIx_WIDTH			(4u)
		#define SYSCFG_EXTICR2_EXTIx_POS(idx)		((idx % SYSCFG_EXTI_IN_EXTICR) * SYSCFG_EXTICR2_EXTIx_WIDTH)
		#define SYSCFG_EXTICR2_EXTIx_MASK(idx)		(HAL_BIT_CREATE_MASK(SYSCFG_EXTICR2_EXTIx_POS(idx), SYSCFG_EXTICR2_EXTIx_WIDTH))
		#define SYSCFG_EXTICR2_EXTIx_NMASK(idx)		(~(SYSCFG_EXTICR2_EXTIx_MASK(idx)))
#define SYSCFG_EXTICR3_OFS							(0x10u) //!< External interrupt configuration register 3 offset.
	#define SYSCFG_EXTICR3_GET()					(HAL_REG_READ((SYSCFG_BASE + SYSCFG_EXTICR3_OFS)))
	#define SYSCFG_EXTICR3_SET(data)				(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_EXTICR3_OFS), (uint32_t)data))
		#define SYSCFG_EXTICR3_EXTIx_WIDTH			(4u)
		#define SYSCFG_EXTICR3_EXTIx_POS(idx)		((idx % SYSCFG_EXTI_IN_EXTICR) * SYSCFG_EXTICR3_EXTIx_WIDTH)
		#define SYSCFG_EXTICR3_EXTIx_MASK(idx)		(HAL_BIT_CREATE_MASK(SYSCFG_EXTICR3_EXTIx_POS(idx), SYSCFG_EXTICR3_EXTIx_WIDTH))
		#define SYSCFG_EXTICR3_EXTIx_NMASK(idx)		(~(SYSCFG_EXTICR3_EXTIx_MASK(idx)))
#define SYSCFG_EXTICR4_OFS							(0x14u) //!< External interrupt configuration register 4 offset.
	#define SYSCFG_EXTICR4_GET()					(HAL_REG_READ((SYSCFG_BASE + SYSCFG_EXTICR4_OFS)))
	#define SYSCFG_EXTICR4_SET(data)				(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_EXTICR4_OFS), (uint32_t)data))
		#define SYSCFG_EXTICR4_EXTIx_WIDTH			(4u)
		#define SYSCFG_EXTICR4_EXTIx_POS(idx)		((idx % SYSCFG_EXTI_IN_EXTICR) * SYSCFG_EXTICR4_EXTIx_WIDTH)
		#define SYSCFG_EXTICR4_EXTIx_MASK(idx)		(HAL_BIT_CREATE_MASK(SYSCFG_EXTICR4_EXTIx_POS(idx), SYSCFG_EXTICR4_EXTIx_WIDTH))
		#define SYSCFG_EXTICR4_EXTIx_NMASK(idx)		(~(SYSCFG_EXTICR4_EXTIx_MASK(idx)))
#define SYSCFG_CMPCR_OFS							(0x20u) //!< Compensation cell control register offset.
	#define SYSCFG_CMPCR_GET()						(HAL_REG_READ((SYSCFG_BASE + SYSCFG_CMPCR_OFS)))
	#define SYSCFG_CMPCR_SET(data)					(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_CMPCR_OFS), (uint32_t)data))
		#define SYSCFG_CMPCR_CMD_PD_WIDTH			(1u)
		#define SYSCFG_CMPCR_CMD_PD_POS				(0u)
		#define SYSCFG_CMPCR_CMD_PD_MASK			(HAL_BIT_CREATE_MASK(SYSCFG_CMPCR_CMD_PD_POS, SYSCFG_CMPCR_CMD_PD_WIDTH))
		#define SYSCFG_CMPCR_CMD_PD_NMASK 			(~(SYSCFG_CMPCR_CMD_PD_MASK))
		#define SYSCFG_CMPCR_READY_WIDTH			(1u)
		#define SYSCFG_CMPCR_READY_POS				(8u)
		#define SYSCFG_CMPCR_READY_MASK				(HAL_BIT_CREATE_MASK(SYSCFG_CMPCR_READY_POS, SYSCFG_CMPCR_READY_WIDTH))
		#define SYSCFG_CMPCR_READY_NMASK 			(~(SYSCFG_CMPCR_READY_MASK))
#define SYSCFG_CFGR_OFS								(0x2Cu) //!< Configuration register offset.
	#define SYSCFG_CFGR_GET()						(HAL_REG_READ((SYSCFG_BASE + SYSCFG_CFGR_OFS)))
	#define SYSCFG_CFGR_SET(data)					(HAL_REG_WRITE((SYSCFG_BASE + SYSCFG_CFGR_OFS), (uint32_t)data))
		#define SYSCFG_CFGR_FMPI2C1_SCL_WIDTH		(1u)
		#define SYSCFG_CFGR_FMPI2C1_SCL_POS			(0u)
		#define SYSCFG_CFGR_FMPI2C1_SCL_MASK		(HAL_BIT_CREATE_MASK(SYSCFG_CFGR_FMPI2C1_SCL_POS, SYSCFG_CFGR_FMPI2C1_SCL_WIDTH))
		#define SYSCFG_CFGR_FMPI2C1_SCL_NMASK 		(~(SYSCFG_CFGR_FMPI2C1_SCL_MASK))
		#define SYSCFG_CFGR_FMPI2C1_SDA_WIDTH		(1u)
		#define SYSCFG_CFGR_FMPI2C1_SDA_POS			(1u)
		#define SYSCFG_CFGR_FMPI2C1_SDA_MASK		(HAL_BIT_CREATE_MASK(SYSCFG_CFGR_FMPI2C1_SDA_POS, SYSCFG_CFGR_FMPI2C1_SDA_WIDTH))
		#define SYSCFG_CFGR_FMPI2C1_SDA_NMASK 		(~(SYSCFG_CFGR_FMPI2C1_SDA_MASK))


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
typedef struct {
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[SYSCFG_EXTICR_NUM];
	volatile uint32_t RESERVED1[2];
	volatile uint32_t CMPCR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t CFGR;
} t_SYSCFG_RegDef;

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

#endif /* SYSCFG_REGISTER_H_ */
/*** EOF ***/
