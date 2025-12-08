/**
 * Copyright (c) 2025 OwlTech
 *
 * \file pwr_register.h
 * \brief
 * \author OwlTech
 * \date Dec 4, 2025
 */

#ifndef PWR_REGISTER_H_
#define PWR_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define PWR_BASE		(0x40007000u) 				  //!< PWR register base address

#define PWR_CR_OFS								(0x00u) //!< PWR power control register.
	#define PWR_CR_GET()						(HAL_REG_READ(PWR_BASE + PWR_CR_OFS))
	#define PWR_CR_SET(data)					(HAL_REG_WRITE((PWR_BASE + PWR_CR_OFS), (uint32_t)data))
		#define PWR_CR_LPDS_WIDTH				(1u)
		#define PWR_CR_LPDS_POS					(0u)
		#define PWR_CR_LPDS_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_LPDS_POS, PWR_CR_LPDS_WIDTH))
		#define PWR_CR_LPDS_NMASK 				(~(PWR_CR_LPDS_MASK))
		#define PWR_CR_PDDS_WIDTH				(1u)
		#define PWR_CR_PDDS_POS					(1u)
		#define PWR_CR_PDDS_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_PDDS_POS, PWR_CR_PDDS_WIDTH))
		#define PWR_CR_PDDS_NMASK 				(~(PWR_CR_PDDS_MASK))
		#define PWR_CR_CWUF_WIDTH				(1u)
		#define PWR_CR_CWUF_POS					(2u)
		#define PWR_CR_CWUF_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_CWUF_POS, PWR_CR_CWUF_WIDTH))
		#define PWR_CR_CWUF_NMASK 				(~(PWR_CR_CWUF_MASK))
		#define PWR_CR_CSBF_WIDTH				(1u)
		#define PWR_CR_CSBF_POS					(3u)
		#define PWR_CR_CSBF_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_CSBF_POS, PWR_CR_CSBF_WIDTH))
		#define PWR_CR_CSBF_NMASK 				(~(PWR_CR_CSBF_MASK))
		#define PWR_CR_PVDE_WIDTH				(1u)
		#define PWR_CR_PVDE_POS					(4u)
		#define PWR_CR_PVDE_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_PVDE_POS, PWR_CR_PVDE_WIDTH))
		#define PWR_CR_PVDE_NMASK 				(~(PWR_CR_PVDE_MASK))
		#define PWR_CR_PLS_WIDTH				(3u)
		#define PWR_CR_PLS_POS					(5u)
		#define PWR_CR_PLS_MASK					(HAL_BIT_CREATE_MASK(PWR_CR_PLS_POS, PWR_CR_PLS_WIDTH))
		#define PWR_CR_PLS_NMASK 				(~(PWR_CR_PLS_MASK))
		#define PWR_CR_DBP_WIDTH				(1u)
		#define PWR_CR_DBP_POS					(8u)
		#define PWR_CR_DBP_MASK					(HAL_BIT_CREATE_MASK(PWR_CR_DBP_POS, PWR_CR_DBP_WIDTH))
		#define PWR_CR_DBP_NMASK 				(~(PWR_CR_DBP_MASK))
		#define PWR_CR_FPDS_WIDTH				(1u)
		#define PWR_CR_FPDS_POS					(9u)
		#define PWR_CR_FPDS_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_FPDS_POS, PWR_CR_FPDS_WIDTH))
		#define PWR_CR_FPDS_NMASK 				(~(PWR_CR_FPDS_MASK))
		#define PWR_CR_LPUDS_WIDTH				(1u)
		#define PWR_CR_LPUDS_POS				(10u)
		#define PWR_CR_LPUDS_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_LPUDS_POS, PWR_CR_LPUDS_WIDTH))
		#define PWR_CR_LPUDS_NMASK 				(~(PWR_CR_LPUDS_MASK))
		#define PWR_CR_MRUDS_WIDTH				(11u)
		#define PWR_CR_MRUDS_POS				(0u)
		#define PWR_CR_MRUDS_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_MRUDS_POS, PWR_CR_MRUDS_WIDTH))
		#define PWR_CR_MRUDS_NMASK 				(~(PWR_CR_MRUDS_MASK))
		#define PWR_CR_ADCDC1_WIDTH				(1u)
		#define PWR_CR_ADCDC1_POS				(13u)
		#define PWR_CR_ADCDC1_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_ADCDC1_POS, PWR_CR_ADCDC1_WIDTH))
		#define PWR_CR_ADCDC1_NMASK 			(~(PWR_CR_ADCDC1_MASK))
		#define PWR_CR_VOS_WIDTH				(2u)
		#define PWR_CR_VOS_POS					(14u)
		#define PWR_CR_VOS_MASK					(HAL_BIT_CREATE_MASK(PWR_CR_VOS_POS, PWR_CR_VOS_WIDTH))
		#define PWR_CR_VOS_NMASK 				(~(PWR_CR_VOS_MASK))
		#define PWR_CR_ODEN_WIDTH				(1u)
		#define PWR_CR_ODEN_POS					(16u)
		#define PWR_CR_ODEN_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_ODEN_POS, PWR_CR_ODEN_WIDTH))
		#define PWR_CR_ODEN_NMASK 				(~(PWR_CR_ODEN_MASK))
		#define PWR_CR_ODSWEN_WIDTH				(1u)
		#define PWR_CR_ODSWEN_POS				(17u)
		#define PWR_CR_ODSWEN_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_ODSWEN_POS, PWR_CR_ODSWEN_WIDTH))
		#define PWR_CR_ODSWEN_NMASK 			(~(PWR_CR_ODSWEN_MASK))
		#define PWR_CR_UDEN_WIDTH				(2u)
		#define PWR_CR_UDEN_POS					(18u)
		#define PWR_CR_UDEN_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_UDEN_POS, PWR_CR_UDEN_WIDTH))
		#define PWR_CR_UDEN_NMASK 				(~(PWR_CR_UDEN_MASK))
		#define PWR_CR_FMSSR_WIDTH				(1u)
		#define PWR_CR_FMSSR_POS				(20u)
		#define PWR_CR_FMSSR_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_FMSSR_POS, PWR_CR_FMSSR_WIDTH))
		#define PWR_CR_FMSSR_NMASK 				(~(PWR_CR_FMSSR_MASK))
		#define PWR_CR_FISSR_WIDTH				(1u)
		#define PWR_CR_FISSR_POS				(21u)
		#define PWR_CR_FISSR_MASK				(HAL_BIT_CREATE_MASK(PWR_CR_FISSR_POS, PWR_CR_FISSR_WIDTH))
		#define PWR_CR_FISSR_NMASK 				(~(PWR_CR_FISSR_MASK))
#define PWR_CSR_OFS								(0x04u) //!< PWR power control/status register.
	#define PWR_CSR_GET()						(HAL_REG_READ(PWR_BASE + PWR_CSR_OFS))
	#define PWR_CSR_SET(data)					(HAL_REG_WRITE((PWR_BASE + PWR_CSR_OFS), (uint32_t)data))
		#define PWR_CSR_WUF_WIDTH				(1u)
		#define PWR_CSR_WUF_POS					(0u)
		#define PWR_CSR_WUF_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_WUF_POS, PWR_CSR_WUF_WIDTH))
		#define PWR_CSR_WUF_NMASK 				(~(PWR_CSR_WUF_MASK))
		#define PWR_CSR_SBF_WIDTH				(1u)
		#define PWR_CSR_SBF_POS					(1u)
		#define PWR_CSR_SBF_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_SBF_POS, PWR_CSR_SBF_WIDTH))
		#define PWR_CSR_SBF_NMASK 				(~(PWR_CSR_SBF_MASK))
		#define PWR_CSR_PVDO_WIDTH				(1u)
		#define PWR_CSR_PVDO_POS				(2u)
		#define PWR_CSR_PVDO_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_PVDO_POS, PWR_CSR_PVDO_WIDTH))
		#define PWR_CSR_PVDO_NMASK 				(~(PWR_CSR_PVDO_MASK))
		#define PWR_CSR_BRR_WIDTH				(1u)
		#define PWR_CSR_BRR_POS					(3u)
		#define PWR_CSR_BRR_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_BRR_POS, PWR_CSR_BRR_WIDTH))
		#define PWR_CSR_BRR_NMASK 				(~(PWR_CSR_BRR_MASK))
		#define PWR_CSR_EWUP2_WIDTH				(1u)
		#define PWR_CSR_EWUP2_POS				(7u)
		#define PWR_CSR_EWUP2_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_EWUP2_POS, PWR_CSR_EWUP2_WIDTH))
		#define PWR_CSR_EWUP2_NMASK 			(~(PWR_CSR_EWUP2_MASK))
		#define PWR_CSR_EWUP1_WIDTH				(1u)
		#define PWR_CSR_EWUP1_POS				(8u)
		#define PWR_CSR_EWUP1_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_EWUP1_POS, PWR_CSR_EWUP1_WIDTH))
		#define PWR_CSR_EWUP1_NMASK 			(~(PWR_CSR_EWUP1_MASK))
		#define PWR_CSR_BRE_WIDTH				(1u)
		#define PWR_CSR_BRE_POS					(9u)
		#define PWR_CSR_BRE_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_BRE_POS, PWR_CSR_BRE_WIDTH))
		#define PWR_CSR_BRE_NMASK 				(~(PWR_CSR_BRE_MASK))
		#define PWR_CSR_VOSRDY_WIDTH			(1u)
		#define PWR_CSR_VOSRDY_POS				(14u)
		#define PWR_CSR_VOSRDY_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_VOSRDY_POS, PWR_CSR_VOSRDY_WIDTH))
		#define PWR_CSR_VOSRDY_NMASK 			(~(PWR_CSR_VOSRDY_MASK))
		#define PWR_CSR_ODRDY_WIDTH				(1u)
		#define PWR_CSR_ODRDY_POS				(16u)
		#define PWR_CSR_ODRDY_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_ODRDY_POS, PWR_CSR_ODRDY_WIDTH))
		#define PWR_CSR_ODRDY_NMASK 			(~(PWR_CSR_ODRDY_MASK))
		#define PWR_CSR_ODSWRDY_WIDTH			(1u)
		#define PWR_CSR_ODSWRDY_POS				(17u)
		#define PWR_CSR_ODSWRDY_MASK			(HAL_BIT_CREATE_MASK(PWR_CSR_ODSWRDY_POS, PWR_CSR_ODSWRDY_WIDTH))
		#define PWR_CSR_ODSWRDY_NMASK 			(~(PWR_CSR_ODSWRDY_MASK))
		#define PWR_CSR_UDRDY_WIDTH				(2u)
		#define PWR_CSR_UDRDY_POS				(18u)
		#define PWR_CSR_UDRDY_MASK				(HAL_BIT_CREATE_MASK(PWR_CSR_UDRDY_POS, PWR_CSR_UDRDY_WIDTH))
		#define PWR_CSR_UDRDY_NMASK 			(~(PWR_CSR_UDRDY_MASK))


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

#endif /* PWR_REGISTER_H_ */
/*** EOF ***/
