/**
 * Copyright (c) 2025 OwlTech
 *
 * \file usart_register.h
 * \brief
 * \author OwlTech
 * \date Feb 10, 2026
 */

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define USART1_BASE		(0x40011000u)
#define USART2_BASE		(0x40004400u)
#define USART3_BASE		(0x40004800u)
#define UART4_BASE		(0x40004C00u)
#define UART5_BASE		(0x40005000u)
#define USART6_BASE		(0x40011400u)

#define USART_SR_OFS						(0x00u) //!< USART status register.
	#define USART_SR_GET(base)				(HAL_REG_READ((base + USART_SR_OFS)))
	#define USART_SR_SET(base, data)		(HAL_REG_WRITE((base + USART_SR_OFS), (uint32_t)data))
		#define USART_SR_PE_WIDTH			(1u)
		#define USART_SR_PE_POS				(0u)
		#define USART_SR_PE_MASK			(HAL_BIT_CREATE_MASK(USART_SR_PE_POS, USART_SR_PE_WIDTH))
		#define USART_SR_PE_NMASK 			(~(USART_SR_PE_MASK))
		#define USART_SR_FE_WIDTH			(1u)
		#define USART_SR_FE_POS				(1u)
		#define USART_SR_FE_MASK			(HAL_BIT_CREATE_MASK(USART_SR_FE_POS, USART_SR_FE_WIDTH))
		#define USART_SR_FE_NMASK 			(~(USART_SR_FE_MASK))
		#define USART_SR_NF_WIDTH			(1u)
		#define USART_SR_NF_POS				(2u)
		#define USART_SR_NF_MASK			(HAL_BIT_CREATE_MASK(USART_SR_NF_POS, USART_SR_NF_WIDTH))
		#define USART_SR_NF_NMASK 			(~(USART_SR_NF_MASK))
		#define USART_SR_ORE_WIDTH			(1u)
		#define USART_SR_ORE_POS			(3u)
		#define USART_SR_ORE_MASK			(HAL_BIT_CREATE_MASK(USART_SR_ORE_POS, USART_SR_ORE_WIDTH))
		#define USART_SR_ORE_NMASK 			(~(USART_SR_ORE_MASK))
		#define USART_SR_IDLE_WIDTH			(1u)
		#define USART_SR_IDLE_POS			(4u)
		#define USART_SR_IDLE_MASK			(HAL_BIT_CREATE_MASK(USART_SR_IDLE_POS, USART_SR_IDLE_WIDTH))
		#define USART_SR_IDLE_NMASK 		(~(USART_SR_IDLE_MASK))
		#define USART_SR_RXNE_WIDTH			(1u)
		#define USART_SR_RXNE_POS			(5u)
		#define USART_SR_RXNE_MASK			(HAL_BIT_CREATE_MASK(USART_SR_RXNE_POS, USART_SR_RXNE_WIDTH))
		#define USART_SR_RXNE_NMASK 		(~(USART_SR_RXNE_MASK))
		#define USART_SR_TC_WIDTH			(1u)
		#define USART_SR_TC_POS				(6u)
		#define USART_SR_TC_MASK			(HAL_BIT_CREATE_MASK(USART_SR_TC_POS, USART_SR_TC_WIDTH))
		#define USART_SR_TC_NMASK 			(~(USART_SR_TC_MASK))
		#define USART_SR_TXE_WIDTH			(1u)
		#define USART_SR_TXE_POS			(7u)
		#define USART_SR_TXE_MASK			(HAL_BIT_CREATE_MASK(USART_SR_TXE_POS, USART_SR_TXE_WIDTH))
		#define USART_SR_TXE_NMASK 			(~(USART_SR_TXE_MASK))
		#define USART_SR_LBD_WIDTH			(1u)
		#define USART_SR_LBD_POS			(8u)
		#define USART_SR_LBD_MASK			(HAL_BIT_CREATE_MASK(USART_SR_LBD_POS, USART_SR_LBD_WIDTH))
		#define USART_SR_LBD_NMASK 			(~(USART_SR_LBD_MASK))
		#define USART_SR_CTS_WIDTH			(1u)
		#define USART_SR_CTS_POS			(9u)
		#define USART_SR_CTS_MASK			(HAL_BIT_CREATE_MASK(USART_SR_CTS_POS, USART_SR_CTS_WIDTH))
		#define USART_SR_CTS_NMASK 			(~(USART_SR_CTS_MASK))
#define USART_DR_OFS						(0x04u) //!< USART data register.
	#define USART_DR_GET(base)				(HAL_REG_READ((base + USART_DR_OFS)))
	#define USART_DR_SET(base, data)		(HAL_REG_WRITE((base + USART_DR_OFS), (uint32_t)data))
	#define USART_DR_WIDTH					(9u)
	#define USART_DR_POS					(0u)
	#define USART_DR_MASK					(HAL_BIT_CREATE_MASK(USART_DR_POS, USART_DR_WIDTH))
	#define USART_DR_NMASK 					(~(USART_DR_MASK))
#define USART_BRR_OFS						(0x08u) //!< USART status register.
	#define USART_BRR_GET(base)				(HAL_REG_READ((base + USART_BRR_OFS)))
	#define USART_BRR_SET(base, data)		(HAL_REG_WRITE((base + USART_BRR_OFS), (uint32_t)data))
		#define USART_BRR_DIV_F_WIDTH		(4u)
		#define USART_BRR_DIV_F_POS			(0u)
		#define USART_BRR_DIV_F_MASK		(HAL_BIT_CREATE_MASK(USART_BRR_DIV_F_POS, USART_BRR_DIV_F_WIDTH))
		#define USART_BRR_DIV_F_NMASK 		(~(USART_BRR_DIV_F_MASK))
		#define USART_BRR_DIV_M_WIDTH		(12u)
		#define USART_BRR_DIV_M_POS			(4u)
		#define USART_BRR_DIV_M_MASK		(HAL_BIT_CREATE_MASK(USART_BRR_DIV_M_POS, USART_BRR_DIV_M_WIDTH))
		#define USART_BRR_DIV_M_NMASK 		(~(USART_BRR_DIV_M_MASK))
#define USART_CR1_OFS						(0x0Cu) //!< USART control register 1.
	#define USART_CR1_GET(base)				(HAL_REG_READ((base + USART_CR1_OFS)))
	#define USART_CR1_SET(base, data)		(HAL_REG_WRITE((base + USART_CR1_OFS), (uint32_t)data))
		#define USART_CR1_SBK_WIDTH			(1u)
		#define USART_CR1_SBK_POS			(0u)
		#define USART_CR1_SBK_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_SBK_POS, USART_CR1_SBK_WIDTH))
		#define USART_CR1_SBK_NMASK 		(~(USART_CR1_SBK_MASK))
		#define USART_CR1_RWU_WIDTH			(1u)
		#define USART_CR1_RWU_POS			(1u)
		#define USART_CR1_RWU_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_RWU_POS, USART_CR1_RWU_WIDTH))
		#define USART_CR1_RWU_NMASK 		(~(USART_CR1_RWU_MASK))
		#define USART_CR1_RE_WIDTH			(1u)
		#define USART_CR1_RE_POS			(2u)
		#define USART_CR1_RE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_RE_POS, USART_CR1_RE_WIDTH))
		#define USART_CR1_RE_NMASK 			(~(USART_CR1_RE_MASK))
		#define USART_CR1_TE_WIDTH			(1u)
		#define USART_CR1_TE_POS			(3u)
		#define USART_CR1_TE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_TE_POS, USART_CR1_TE_WIDTH))
		#define USART_CR1_TE_NMASK 			(~(USART_CR1_TE_MASK))
		#define USART_CR1_IDLEIE_WIDTH		(1u)
		#define USART_CR1_IDLEIE_POS		(4u)
		#define USART_CR1_IDLEIE_MASK		(HAL_BIT_CREATE_MASK(USART_CR1_IDLEIE_POS, USART_CR1_IDLEIE_WIDTH))
		#define USART_CR1_IDLEIE_NMASK 		(~(USART_CR1_IDLEIE_MASK))
		#define USART_CR1_RXNEIE_WIDTH		(1u)
		#define USART_CR1_RXNEIE_POS		(5u)
		#define USART_CR1_RXNEIE_MASK		(HAL_BIT_CREATE_MASK(USART_CR1_RXNEIE_POS, USART_CR1_RXNEIE_WIDTH))
		#define USART_CR1_RXNEIE_NMASK 		(~(USART_CR1_RXNEIE_MASK))
		#define USART_CR1_TCIE_WIDTH		(1u)
		#define USART_CR1_TCIE_POS			(6u)
		#define USART_CR1_TCIE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_TCIE_POS, USART_CR1_TCIE_WIDTH))
		#define USART_CR1_TCIE_NMASK 		(~(USART_CR1_TCIE_MASK))
		#define USART_CR1_TXEIE_WIDTH		(1u)
		#define USART_CR1_TXEIE_POS			(7u)
		#define USART_CR1_TXEIE_MASK		(HAL_BIT_CREATE_MASK(USART_CR1_TXEIE_POS, USART_CR1_TXEIE_WIDTH))
		#define USART_CR1_TXEIE_NMASK 		(~(USART_CR1_TXEIE_MASK))
		#define USART_CR1_PEIE_WIDTH		(1u)
		#define USART_CR1_PEIE_POS			(8u)
		#define USART_CR1_PEIE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_PEIE_POS, USART_CR1_PEIE_WIDTH))
		#define USART_CR1_PEIE_NMASK 		(~(USART_CR1_PEIE_MASK))
		#define USART_CR1_PS_WIDTH			(1u)
		#define USART_CR1_PS_POS			(9u)
		#define USART_CR1_PS_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_PS_POS, USART_CR1_PS_WIDTH))
		#define USART_CR1_PS_NMASK 			(~(USART_CR1_PS_MASK))
		#define USART_CR1_PCE_WIDTH			(1u)
		#define USART_CR1_PCE_POS			(10u)
		#define USART_CR1_PCE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_PCE_POS, USART_CR1_PCE_WIDTH))
		#define USART_CR1_PCE_NMASK 		(~(USART_CR1_PCE_MASK))
		#define USART_CR1_WAKE_WIDTH		(1u)
		#define USART_CR1_WAKE_POS			(11u)
		#define USART_CR1_WAKE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_WAKE_POS, USART_CR1_WAKE_WIDTH))
		#define USART_CR1_WAKE_NMASK 		(~(USART_CR1_WAKE_MASK))
		#define USART_CR1_M_WIDTH			(1u)
		#define USART_CR1_M_POS				(12u)
		#define USART_CR1_M_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_M_POS, USART_CR1_M_WIDTH))
		#define USART_CR1_M_NMASK 			(~(USART_CR1_M_MASK))
		#define USART_CR1_UE_WIDTH			(1u)
		#define USART_CR1_UE_POS			(13u)
		#define USART_CR1_UE_MASK			(HAL_BIT_CREATE_MASK(USART_CR1_UE_POS, USART_CR1_UE_WIDTH))
		#define USART_CR1_UE_NMASK 			(~(USART_CR1_UE_MASK))
		#define USART_CR1_OVER8_WIDTH		(1u)
		#define USART_CR1_OVER8_POS			(15u)
		#define USART_CR1_OVER8_MASK		(HAL_BIT_CREATE_MASK(USART_CR1_OVER8_POS, USART_CR1_OVER8_WIDTH))
		#define USART_CR1_OVER8_NMASK 		(~(USART_CR1_OVER8_MASK))
#define USART_CR2_OFS						(0x10u) //!< USART control register 2.
	#define USART_CR2_GET(base)				(HAL_REG_READ((base + USART_CR2_OFS)))
	#define USART_CR2_SET(base, data)		(HAL_REG_WRITE((base + USART_CR2_OFS), (uint32_t)data))
		#define USART_CR2_ADD_WIDTH			(4u)
		#define USART_CR2_ADD_POS			(0u)
		#define USART_CR2_ADD_MASK			(HAL_BIT_CREATE_MASK(USART_CR2_ADD_POS, USART_CR2_ADD_WIDTH))
		#define USART_CR2_ADD_NMASK 		(~(USART_CR2_ADD_MASK))
		#define USART_CR2_LBDL_WIDTH		(1u)
		#define USART_CR2_LBDL_POS			(5u)
		#define USART_CR2_LBDL_MASK			(HAL_BIT_CREATE_MASK(USART_CR2_LBDL_POS, USART_CR2_LBDL_WIDTH))
		#define USART_CR2_LBDL_NMASK 		(~(USART_CR2_LBDL_MASK))
		#define USART_CR2_LBDIE_WIDTH		(1u)
		#define USART_CR2_LBDIE_POS			(6u)
		#define USART_CR2_LBDIE_MASK		(HAL_BIT_CREATE_MASK(USART_CR2_LBDIE_POS, USART_CR2_LBDIE_WIDTH))
		#define USART_CR2_LBDIE_NMASK 		(~(USART_CR2_LBDIE_MASK))
		#define USART_CR2_LBCL_WIDTH		(1u)
		#define USART_CR2_LBCL_POS			(8u)
		#define USART_CR2_LBCL_MASK			(HAL_BIT_CREATE_MASK(USART_CR2_LBCL_POS, USART_CR2_LBCL_WIDTH))
		#define USART_CR2_LBCL_NMASK 		(~(USART_CR2_LBCL_MASK))
		#define USART_CR2_CPHA_WIDTH		(1u)
		#define USART_CR2_CPHA_POS			(9u)
		#define USART_CR2_CPHA_MASK			(HAL_BIT_CREATE_MASK(USART_CR2_CPHA_POS, USART_CR2_CPHA_WIDTH))
		#define USART_CR2_CPHA_NMASK 		(~(USART_CR2_CPHA_MASK))
		#define USART_CR2_CPOL_WIDTH		(1u)
		#define USART_CR2_CPOL_POS			(10u)
		#define USART_CR2_CPOL_MASK			(HAL_BIT_CREATE_MASK(USART_CR2_CPOL_POS, USART_CR2_CPOL_WIDTH))
		#define USART_CR2_CPOL_NMASK 		(~(USART_CR2_CPOL_MASK))
		#define USART_CR2_CLKEN_WIDTH		(1u)
		#define USART_CR2_CLKEN_POS			(11u)
		#define USART_CR2_CLKEN_MASK		(HAL_BIT_CREATE_MASK(USART_CR2_CLKEN_POS, USART_CR2_CLKEN_WIDTH))
		#define USART_CR2_CLKEN_NMASK 		(~(USART_CR2_CLKEN_MASK))
		#define USART_CR2_STOP_WIDTH		(2u)
		#define USART_CR2_STOP_POS			(12u)
		#define USART_CR2_STOP_MASK			(HAL_BIT_CREATE_MASK(USART_CR2_STOP_POS, USART_CR2_STOP_WIDTH))
		#define USART_CR2_STOP_NMASK 		(~(USART_CR2_STOP_MASK))
		#define USART_CR2_LINEN_WIDTH		(1u)
		#define USART_CR2_LINEN_POS			(14u)
		#define USART_CR2_LINEN_MASK		(HAL_BIT_CREATE_MASK(USART_CR2_LINEN_POS, USART_CR2_LINEN_WIDTH))
		#define USART_CR2_LINEN_NMASK 		(~(USART_CR2_LINEN_MASK))
#define USART_CR3_OFS						(0x14u) //!< USART control register 3.
	#define USART_CR3_GET(base)				(HAL_REG_READ((base + USART_CR3_OFS)))
	#define USART_CR3_SET(base, data)		(HAL_REG_WRITE((base + USART_CR3_OFS), (uint32_t)data))
		#define USART_CR3_EIE_WIDTH			(1u)
		#define USART_CR3_EIE_POS			(0u)
		#define USART_CR3_EIE_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_EIE_POS, USART_CR3_EIE_WIDTH))
		#define USART_CR3_EIE_NMASK 		(~(USART_CR3_EIE_MASK))
		#define USART_CR3_IREN_WIDTH		(1u)
		#define USART_CR3_IREN_POS			(1u)
		#define USART_CR3_IREN_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_IREN_POS, USART_CR3_IREN_WIDTH))
		#define USART_CR3_IREN_NMASK 		(~(USART_CR3_IREN_MASK))
		#define USART_CR3_IRLP_WIDTH		(1u)
		#define USART_CR3_IRLP_POS			(2u)
		#define USART_CR3_IRLP_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_IRLP_POS, USART_CR3_IRLP_WIDTH))
		#define USART_CR3_IRLP_NMASK 		(~(USART_CR3_IRLP_MASK))
		#define USART_CR3_HDSEL_WIDTH		(1u)
		#define USART_CR3_HDSEL_POS			(3u)
		#define USART_CR3_HDSEL_MASK		(HAL_BIT_CREATE_MASK(USART_CR3_HDSEL_POS, USART_CR3_HDSEL_WIDTH))
		#define USART_CR3_HDSEL_NMASK 		(~(USART_CR3_HDSEL_MASK))
		#define USART_CR3_NACK_WIDTH		(1u)
		#define USART_CR3_NACK_POS			(4u)
		#define USART_CR3_NACK_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_NACK_POS, USART_CR3_NACK_WIDTH))
		#define USART_CR3_NACK_NMASK 		(~(USART_CR3_NACK_MASK))
		#define USART_CR3_SCEN_WIDTH		(1u)
		#define USART_CR3_SCEN_POS			(5u)
		#define USART_CR3_SCEN_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_SCEN_POS, USART_CR3_SCEN_WIDTH))
		#define USART_CR3_SCEN_NMASK 		(~(USART_CR3_SCEN_MASK))
		#define USART_CR3_DMAR_WIDTH		(1u)
		#define USART_CR3_DMAR_POS			(6u)
		#define USART_CR3_DMAR_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_DMAR_POS, USART_CR3_DMAR_WIDTH))
		#define USART_CR3_DMAR_NMASK 		(~(USART_CR3_DMAR_MASK))
		#define USART_CR3_DMAT_WIDTH		(1u)
		#define USART_CR3_DMAT_POS			(7u)
		#define USART_CR3_DMAT_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_DMAT_POS, USART_CR3_DMAT_WIDTH))
		#define USART_CR3_DMAT_NMASK 		(~(USART_CR3_DMAT_MASK))
		#define USART_CR3_RTSE_WIDTH		(1u)
		#define USART_CR3_RTSE_POS			(8u)
		#define USART_CR3_RTSE_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_RTSE_POS, USART_CR3_RTSE_WIDTH))
		#define USART_CR3_RTSE_NMASK 		(~(USART_CR3_RTSE_MASK))
		#define USART_CR3_CTSE_WIDTH		(1u)
		#define USART_CR3_CTSE_POS			(9u)
		#define USART_CR3_CTSE_MASK			(HAL_BIT_CREATE_MASK(USART_CR3_CTSE_POS, USART_CR3_CTSE_WIDTH))
		#define USART_CR3_CTSE_NMASK 		(~(USART_CR3_CTSE_MASK))
		#define USART_CR3_CTSIE_WIDTH		(1u)
		#define USART_CR3_CTSIE_POS			(10u)
		#define USART_CR3_CTSIE_MASK		(HAL_BIT_CREATE_MASK(USART_CR3_CTSIE_POS, USART_CR3_CTSIE_WIDTH))
		#define USART_CR3_CTSIE_NMASK 		(~(USART_CR3_CTSIE_MASK))
		#define USART_CR3_ONEBIT_WIDTH		(1u)
		#define USART_CR3_ONEBIT_POS		(11u)
		#define USART_CR3_ONEBIT_MASK		(HAL_BIT_CREATE_MASK(USART_CR3_ONEBIT_POS, USART_CR3_ONEBIT_WIDTH))
		#define USART_CR3_ONEBIT_NMASK 		(~(USART_CR3_ONEBIT_MASK))
#define USART_GTPR_OFS						(0x18u) //!< USART guard time and prescaler register.
	#define USART_GTPR_GET(base)			(HAL_REG_READ((base + USART_GTPR_OFS)))
	#define USART_GTPR_SET(base, data)		(HAL_REG_WRITE((base + USART_GTPR_OFS), (uint32_t)data))
		#define USART_GTPR_PSC_WIDTH		(8u)
		#define USART_GTPR_PSC_POS			(0u)
		#define USART_GTPR_PSC_MASK			(HAL_BIT_CREATE_MASK(USART_GTPR_PSC_POS, USART_GTPR_PSC_WIDTH))
		#define USART_GTPR_PSC_NMASK 		(~(USART_GTPR_PSC_MASK))
		#define USART_GTPR_GT_WIDTH			(8u)
		#define USART_GTPR_GT_POS			(8u)
		#define USART_GTPR_GT_MASK			(HAL_BIT_CREATE_MASK(USART_GTPR_GT_POS, USART_GTPR_GT_WIDTH))
		#define USART_GTPR_GT_NMASK 		(~(USART_GTPR_GT_MASK))



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

#endif /* USART_REGISTER_H_ */
/*** EOF ***/
