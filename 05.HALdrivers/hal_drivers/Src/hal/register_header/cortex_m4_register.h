/**
 * Copyright (c) 2025 OwlTech
 *
 * \file cortex_m4_register.h
 * \brief
 * \author OwlTech
 * \date Nov 20, 2025
 */

#ifndef CORTEX_M4_REGISTER_H_
#define CORTEX_M4_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
/** \name Cortex-M4 peripherals base address */
/**@{*/
#define SCB_BASE1		0xE000E008u //!< SyStem Control Block 1.
#define SYST_BASE		0xE000E010u //!< System timer
#define NVIC_BASE1		0xE000E100u //!< Nested Vectored Interrupt Controller
#define SCB_BASE2		0xE000ED00u //!< SyStem Control Block 2.
#define MTR_BASE		0xE000ED90u //!< MPU Type Register
#define MPU_BASE 		0xE000ED90u //!< Memory Protection Unit
#define NVIC_BASE2		0xE000EF00u //!< Nested Vectored Interrupt Controller
#define FPU_BASE		0xE000EF30u //!< Floating Point Unit
/**@}*/


/** \name System timer */
#define SYST_CSR_OFS							(0x00u) //!< SysTick Control and Status Register
	#define SYST_CSR_GET()						(HAL_REG_READ((SYST_BASE + SYST_CSR_OFS)))
	#define SYST_CSR_SET(data)					(HAL_REG_WRITE((SYST_BASE + SYST_CSR_OFS), (uint32_t)data))
		#define SYST_CSR_ENABLE_WIDTH			(1u)
		#define SYST_CSR_ENABLE_POS				(0u)
		#define SYST_CSR_ENABLE_MASK			(HAL_BIT_CREATE_MASK(SYST_CSR_ENABLE_POS, SYST_CSR_ENABLE_WIDTH))
		#define SYST_CSR_ENABLE_NMASK 			(~(SYST_CSR_ENABLE_MASK))
		#define SYST_CSR_TICKINT_WIDTH			(1u)
		#define SYST_CSR_TICKINT_POS			(1u)
		#define SYST_CSR_TICKINT_MASK			(HAL_BIT_CREATE_MASK(SYST_CSR_TICKINT_POS, SYST_CSR_TICKINT_WIDTH))
		#define SYST_CSR_TICKINT_NMASK 			(~(SYST_CSR_TICKINT_MASK))
		#define SYST_CSR_CLKSOURCE_WIDTH		(1u)
		#define SYST_CSR_CLKSOURCE_POS			(2u)
		#define SYST_CSR_CLKSOURCE_MASK			(HAL_BIT_CREATE_MASK(SYST_CSR_CLKSOURCE_POS, SYST_CSR_CLKSOURCE_WIDTH))
		#define SYST_CSR_CLKSOURCE_NMASK 		(~(SYST_CSR_CLKSOURCE_MASK))
		#define SYST_CSR_COUNTFLAG_WIDTH		(1u)
		#define SYST_CSR_COUNTFLAG_POS			(16u)
		#define SYST_CSR_COUNTFLAG_MASK			(HAL_BIT_CREATE_MASK(SYST_CSR_COUNTFLAG_POS, SYST_CSR_COUNTFLAG_WIDTH))
		#define SYST_CSR_COUNTFLAG_NMASK 		(~(SYST_CSR_COUNTFLAG_MASK))
#define SYST_RVR_OFS							(0x04u) //!< SysTick Reload Value Register
	#define SYST_RVR_GET()						(HAL_REG_READ((SYST_BASE + SYST_RVR_OFS)))
	#define SYST_RVR_SET(data)					(HAL_REG_WRITE((SYST_BASE + SYST_RVR_OFS), (uint32_t)data))
		#define SYST_RVR_WIDTH					(24u)
		#define SYST_RVR_POS					(0u)
		#define SYST_RVR_MASK					(HAL_BIT_CREATE_MASK(SYST_RVR_POS, SYST_RVR_WIDTH))
		#define SYST_RVR_NMASK 					(~(SYST_RVR_MASK))
#define SYST_CVR_OFS							(0x08u) //!< SysTick Current Value Register
	#define SYST_CVR_GET()						(HAL_REG_READ((SYST_BASE + SYST_CVR_OFS)))
	#define SYST_CVR_SET(data)					(HAL_REG_WRITE((SYST_BASE + SYST_CVR_OFS), (uint32_t)data))
		#define SYST_CVR_WIDTH					(24u)
		#define SYST_CVR_POS					(0u)
		#define SYST_CVR_MASK					(HAL_BIT_CREATE_MASK(SYST_CVR_POS, SYST_CVR_WIDTH))
		#define SYST_CVR_NMASK 					(~(SYST_CVR_MASK))
#define SYST_CALIB_OFS							(0x1Cu) //!< SysTick Calibration Value Register
	#define SYST_CALIB_GET()					(HAL_REG_READ((SYST_BASE + SYST_CALIB_OFS)))
	#define SYST_CALIB_SET(data)				(HAL_REG_WRITE((SYST_BASE + SYST_CALIB_OFS), (uint32_t)data))
		#define SYST_CALIB_TENMS_WIDTH			(24u)
		#define SYST_CALIB_TENMS_POS			(0u)
		#define SYST_CALIB_TENMS_MASK			(HAL_BIT_CREATE_MASK(SYST_CALIB_TENMS_POS, SYST_CALIB_TENMS_WIDTH))
		#define SYST_CALIB_TENMS_NMASK 			(~(SYST_CALIB_TENMS_MASK))
		#define SYST_CALIB_SKEW_WIDTH			(1u)
		#define SYST_CALIB_SKEW_POS				(30u)
		#define SYST_CALIB_SKEW_MASK			(HAL_BIT_CREATE_MASK(SYST_CALIB_SKEW_POS, SYST_CALIB_SKEW_WIDTH))
		#define SYST_CALIB_SKEW_NMASK 			(~(SYST_CALIB_SKEW_MASK))
		#define SYST_CALIB_NOREF_WIDTH			(1u)
		#define SYST_CALIB_NOREF_POS			(31u)
		#define SYST_CALIB_NOREF_MASK			(HAL_BIT_CREATE_MASK(SYST_CALIB_NOREF_POS, SYST_CALIB_NOREF_WIDTH))
		#define SYST_CALIB_NOREF_NMASK 			(~(SYST_CALIB_NOREF_MASK))
/**@{*/



/** \name Nested Vectored Interrupt Controller. */
/**@{*/
#define NVIC_IRQ_PRIO_LEVEL_MAX			(16u) 	//!< Number of programmable priority levels
#define NVIC_IRQ_NUM_PER_PRIO_REG		(4u) 	//!< Number of IRQs in IPR
#define NVIC_IRQ_CHANNEL_PER_REG		(32u) 	//!< Number of maskable interrupt channel per ISER/ICER/ISPR/ICPR/IABR

#define NVIC_ISER_IRQ_WIDTH				(1u)
#define NVIC_ISER_IRQ_POS(bf)			(bf * NVIC_ISER_IRQ_WIDTH)
#define NVIC_ISER_IRQ_MASK(bf)			(HAL_BIT_CREATE_MASK(NVIC_ISER_IRQ_POS(bf), NVIC_ISER_IRQ_WIDTH))
#define NVIC_ISER_IRQ_NMASK(bf)			(~(NVIC_ISER_IRQ_MASK))
#define NVIC_ISER0_OFS					(0x00u) //!< Interrupt Set-enable Register 0.
	#define NVIC_ISER0_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ISER0_OFS)))
	#define NVIC_ISER0_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ISER0_OFS), (uint32_t)data))
#define NVIC_ISER1_OFS					(0x04u) //!< Interrupt Set-enable Register 1.
	#define NVIC_ISER1_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ISER1_OFS)))
	#define NVIC_ISER1_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ISER1_OFS), (uint32_t)data))
#define NVIC_ISER2_OFS					(0x08u) //!< Interrupt Set-enable Register 2.
	#define NVIC_ISER2_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ISER2_OFS)))
	#define NVIC_ISER2_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ISER2_OFS), (uint32_t)data))
#define NVIC_ISER3_OFS					(0x0Cu) //!< Interrupt Set-enable Register 3.
	#define NVIC_ISER3_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ISER3_OFS)))
	#define NVIC_ISER3_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ISER3_OFS), (uint32_t)data))

#define NVIC_ICER_IRQ_WIDTH				(1u)
#define NVIC_ICER_IRQ_POS(bf)			(bf * NVIC_ICER_IRQ_WIDTH)
#define NVIC_ICER_IRQ_MASK(bf)			(HAL_BIT_CREATE_MASK(NVIC_ICER_IRQ_POS(bf), NVIC_ICER_IRQ_WIDTH))
#define NVIC_ICER_IRQ_NMASK(bf)			(~(NVIC_ICER_IRQ_MASK))
#define NVIC_ICER0_OFS					(0x80u) //!< Interrupt Set-enable Register 0.
	#define NVIC_ICER0_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ICER0_OFS)))
	#define NVIC_ICER0_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ICER0_OFS), (uint32_t)data))
#define NVIC_ICER1_OFS					(0x84u) //!< Interrupt Set-enable Register 1.
	#define NVIC_ICER1_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ICER1_OFS)))
	#define NVIC_ICER1_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ICER1_OFS), (uint32_t)data))
#define NVIC_ICER2_OFS					(0x88u) //!< Interrupt Set-enable Register 2.
	#define NVIC_ICER2_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ICER2_OFS)))
	#define NVIC_ICER2_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ICER2_OFS), (uint32_t)data))
#define NVIC_ICER3_OFS					(0x8Cu) //!< Interrupt Set-enable Register 3.
	#define NVIC_ICER3_GET()			(HAL_REG_READ((NVIC_BASE1 + NVIC_ICER3_OFS)))
	#define NVIC_ICER3_SET(data)		(HAL_REG_WRITE((NVIC_BASE1 + NVIC_ICER3_OFS), (uint32_t)data))

#define NVIC_IPR0_OFS					(0x300u)
#define NVIC_IPRx_GET(idx)				(HAL_REG_READ(((idx * WORDS) + NVIC_IPR0_OFS + NVIC_BASE1)))
#define NVIC_IPRx_SET(idx, data)		(HAL_REG_WRITE(((idx * WORDS) + NVIC_IPR0_OFS + NVIC_BASE1), (uint32_t)data))
	#define NVIC_IPRx_WIDTH				(8u)
	#define NVIC_IPRx_IMPLEMENTED_BF	(4u)
	#define NVIC_IPRx_POS(irqn)			(((irqn % NVIC_IRQ_NUM_PER_PRIO_REG) * NVIC_IPRx_WIDTH) + NVIC_IPRx_IMPLEMENTED_BF)
	#define NVIC_IPRx_MASK(irqn)		(HAL_BIT_CREATE_MASK(NVIC_IPRx_POS(irqn), NVIC_IPRx_WIDTH))
	#define NVIC_IPRx_NMASK(irqn) 		(~(NVIC_IPRx_MASK(irqn)))
/**@}*/



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

#endif /* CORTEX_M4_REGISTER_H_ */
/*** EOF ***/
