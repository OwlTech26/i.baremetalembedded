/**
 * Copyright (c) 2025 OwlTech
 *
 * \file spi_register.h
 * \brief
 * \author OwlTech
 * \date Nov 21, 2025
 */

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define SPI1_BASE		(0x40013000u)
#define SPI2_I2S2_BASE	(0x40003800u)
#define SPI3_I2S3_BASE 	(0x40003C00u)
#define SPI4_BASE		(0x40013400u)

#define SPI_CR1_OFS							(0x00u) //!< SPI control register 1 (not used in I2S mode).
	#define SPI_CR1_GET(base)				(HAL_REG_READ((base + SPI_CR1_OFS)))
	#define SPI_CR1_SET(base, data)			(HAL_REG_WRITE((base + SPI_CR1_OFS), (uint32_t)data))
		#define SPI_CR1_CPHA_WIDTH			(1u)
		#define SPI_CR1_CPHA_POS			(0u)
		#define SPI_CR1_CPHA_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_CPHA_POS, SPI_CR1_CPHA_WIDTH))
		#define SPI_CR1_CPHA_NMASK 			(~(SPI_CR1_CPHA_MASK))
		#define SPI_CR1_CPOL_WIDTH			(1u)
		#define SPI_CR1_CPOL_POS			(1u)
		#define SPI_CR1_CPOL_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_CPOL_POS, SPI_CR1_CPOL_WIDTH))
		#define SPI_CR1_CPOL_NMASK 			(~(SPI_CR1_CPOL_MASK))
		#define SPI_CR1_MSTR_WIDTH			(1u)
		#define SPI_CR1_MSTR_POS			(2u)
		#define SPI_CR1_MSTR_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_MSTR_POS, SPI_CR1_MSTR_WIDTH))
		#define SPI_CR1_MSTR_NMASK 			(~(SPI_CR1_MSTR_MASK))
		#define SPI_CR1_BR_WIDTH			(3u)
		#define SPI_CR1_BR_POS				(3u)
		#define SPI_CR1_BR_MASK				(HAL_BIT_CREATE_MASK(SPI_CR1_BR_POS, SPI_CR1_BR_WIDTH))
		#define SPI_CR1_BR_NMASK 			(~(SPI_CR1_BR_MASK))
		#define SPI_CR1_SPE_WIDTH			(1u)
		#define SPI_CR1_SPE_POS				(6u)
		#define SPI_CR1_SPE_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_SPE_POS, SPI_CR1_SPE_WIDTH))
		#define SPI_CR1_SPE_NMASK 			(~(SPI_CR1_SPE_MASK))
		#define SPI_CR1_LSB_FIRST_WIDTH		(1u)
		#define SPI_CR1_LSB_FIRST_POS		(7u)
		#define SPI_CR1_LSB_FIRST_MASK		(HAL_BIT_CREATE_MASK(SPI_CR1_LSB_FIRST_POS, SPI_CR1_LSB_FIRST_WIDTH))
		#define SPI_CR1_LSB_FIRST_NMASK 	(~(SPI_CR1_LSB_FIRST_MASK))
		#define SPI_CR1_SSI_WIDTH			(1u)
		#define SPI_CR1_SSI_POS				(8u)
		#define SPI_CR1_SSI_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_SSI_POS, SPI_CR1_SSI_WIDTH))
		#define SPI_CR1_SSI_NMASK 			(~(SPI_CR1_SSI_MASK))
		#define SPI_CR1_SSM_WIDTH			(1u)
		#define SPI_CR1_SSM_POS				(9u)
		#define SPI_CR1_SSM_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_SSM_POS, SPI_CR1_SSM_WIDTH))
		#define SPI_CR1_SSM_NMASK 			(~(SPI_CR1_SSM_MASK))
		#define SPI_CR1_RX_ONLY_WIDTH		(1u)
		#define SPI_CR1_RX_ONLY_POS			(10u)
		#define SPI_CR1_RX_ONLY_MASK		(HAL_BIT_CREATE_MASK(SPI_CR1_RX_ONLY_POS, SPI_CR1_RX_ONLY_WIDTH))
		#define SPI_CR1_RX_ONLY_NMASK 		(~(SPI_CR1_RX_ONLY_MASK))
		#define SPI_CR1_DFF_WIDTH			(1u)
		#define SPI_CR1_DFF_POS				(11u)
		#define SPI_CR1_DFF_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_DFF_POS, SPI_CR1_DFF_WIDTH))
		#define SPI_CR1_DFF_NMASK 			(~(SPI_CR1_DFF_MASK))
		#define SPI_CR1_CRC_NEXT_WIDTH		(1u)
		#define SPI_CR1_CRC_NEXT_POS		(12u)
		#define SPI_CR1_CRC_NEXT_MASK		(HAL_BIT_CREATE_MASK(SPI_CR1_CRC_NEXT_POS, SPI_CR1_CRC_NEXT_WIDTH))
		#define SPI_CR1_CRC_NEXT_NMASK 		(~(SPI_CR1_CRC_NEXT_MASK))
		#define SPI_CR1_CRC_EN_WIDTH		(1u)
		#define SPI_CR1_CRC_EN_POS			(13u)
		#define SPI_CR1_CRC_EN_MASK			(HAL_BIT_CREATE_MASK(SPI_CR1_CRC_EN_POS, SPI_CR1_CRC_EN_WIDTH))
		#define SPI_CR1_CRC_EN_NMASK 		(~(SPI_CR1_CRC_EN_MASK))
		#define SPI_CR1_BIDI_OE_WIDTH		(1u)
		#define SPI_CR1_BIDI_OE_POS			(14u)
		#define SPI_CR1_BIDI_OE_MASK		(HAL_BIT_CREATE_MASK(SPI_CR1_BIDI_OE_POS, SPI_CR1_BIDI_OE_WIDTH))
		#define SPI_CR1_BIDI_OE_NMASK 		(~(SPI_CR1_BIDI_OE_MASK))
		#define SPI_CR1_BIDI_MODE_WIDTH		(1u)
		#define SPI_CR1_BIDI_MODE_POS		(15u)
		#define SPI_CR1_BIDI_MODE_MASK		(HAL_BIT_CREATE_MASK(SPI_CR1_BIDI_MODE_POS, SPI_CR1_BIDI_MODE_WIDTH))
		#define SPI_CR1_BIDI_MODE_NMASK 	(~(SPI_CR1_BIDI_MODE_MASK))
#define SPI_CR2_OFS							(0x04u) //!< SPI control register 2 (not used in I2S mode).
	#define SPI_CR2_GET(base)				(HAL_REG_READ((base + SPI_CR2_OFS)))
	#define SPI_CR2_SET(base, data)			(HAL_REG_WRITE((base + SPI_CR2_OFS), (uint32_t)data))
		#define SPI_CR2_RXDMAEN_WIDTH		(1u)
		#define SPI_CR2_RXDMAEN_POS			(0u)
		#define SPI_CR2_RXDMAEN_MASK		(HAL_BIT_CREATE_MASK(SPI_CR2_RXDMAEN_POS, SPI_CR2_RXDMAEN_WIDTH))
		#define SPI_CR2_RXDMAEN_NMASK 		(~(SPI_CR2_RXDMAEN_MASK))
		#define SPI_CR2_TXDMAEN_WIDTH		(1u)
		#define SPI_CR2_TXDMAEN_POS			(1u)
		#define SPI_CR2_TXDMAEN_MASK		(HAL_BIT_CREATE_MASK(SPI_CR2_TXDMAEN_POS, SPI_CR2_TXDMAEN_WIDTH))
		#define SPI_CR2_TXDMAEN_NMASK 		(~(SPI_CR2_TXDMAEN_MASK))
		#define SPI_CR2_SSOE_WIDTH			(1u)
		#define SPI_CR2_SSOE_POS			(2u)
		#define SPI_CR2_SSOE_MASK			(HAL_BIT_CREATE_MASK(SPI_CR2_SSOE_POS, SPI_CR2_SSOE_WIDTH))
		#define SPI_CR2_SSOE_NMASK 			(~(SPI_CR2_SSOE_MASK))
		#define SPI_CR2_FRF_WIDTH			(1u)
		#define SPI_CR2_FRF_POS				(4u)
		#define SPI_CR2_FRF_MASK			(HAL_BIT_CREATE_MASK(SPI_CR2_FRF_POS, SPI_CR2_FRF_WIDTH))
		#define SPI_CR2_FRF_NMASK 			(~(SPI_CR2_FRF_MASK))
		#define SPI_CR2_ERRIE_WIDTH			(1u)
		#define SPI_CR2_ERRIE_POS			(5u)
		#define SPI_CR2_ERRIE_MASK			(HAL_BIT_CREATE_MASK(SPI_CR2_ERRIE_POS, SPI_CR2_ERRIE_WIDTH))
		#define SPI_CR2_ERRIE_NMASK 		(~(SPI_CR2_ERRIE_MASK))
		#define SPI_CR2_RXNEIE_WIDTH		(1u)
		#define SPI_CR2_RXNEIE_POS			(6u)
		#define SPI_CR2_RXNEIE_MASK			(HAL_BIT_CREATE_MASK(SPI_CR2_RXNEIE_POS, SPI_CR2_RXNEIE_WIDTH))
		#define SPI_CR2_RXNEIE_NMASK 		(~(SPI_CR2_RXNEIE_MASK))
		#define SPI_CR2_TXEIE_WIDTH			(1u)
		#define SPI_CR2_TXEIE_POS			(7u)
		#define SPI_CR2_TXEIE_MASK			(HAL_BIT_CREATE_MASK(SPI_CR2_TXEIE_POS, SPI_CR2_TXEIE_WIDTH))
		#define SPI_CR2_TXEIE_NMASK 		(~(SPI_CR2_TXEIE_MASK))
#define SPI_SR_OFS							(0x08u) //!< SPI status register.
	#define SPI_SR_GET(base)				(HAL_REG_READ((base + SPI_SR_OFS)))
	#define SPI_SR_SET(base, data)			(HAL_REG_WRITE((base + SPI_SR_OFS), (uint32_t)data))
		#define SPI_SR_RXNE_WIDTH			(1u)
		#define SPI_SR_RXNE_POS				(0u)
		#define SPI_SR_RXNE_MASK			(HAL_BIT_CREATE_MASK(SPI_SR_RXNE_POS, SPI_SR_RXNE_WIDTH))
		#define SPI_SR_RXNE_NMASK 			(~(SPI_SR_RXNE_MASK))
		#define SPI_SR_TXE_WIDTH			(1u)
		#define SPI_SR_TXE_POS				(1u)
		#define SPI_SR_TXE_MASK				(HAL_BIT_CREATE_MASK(SPI_SR_TXE_POS, SPI_SR_TXE_WIDTH))
		#define SPI_SR_TXE_NMASK 			(~(SPI_SR_TXE_MASK))
		#define SPI_SR_CHSIDE_WIDTH			(1u)
		#define SPI_SR_CHSIDE_POS			(2u)
		#define SPI_SR_CHSIDE_MASK			(HAL_BIT_CREATE_MASK(SPI_SR_CHSIDE_POS, SPI_SR_CHSIDE_WIDTH))
		#define SPI_SR_CHSIDE_NMASK 		(~(SPI_SR_CHSIDE_MASK))
		#define SPI_SR_UDR_WIDTH			(1u)
		#define SPI_SR_UDR_POS				(3u)
		#define SPI_SR_UDR_MASK				(HAL_BIT_CREATE_MASK(SPI_SR_UDR_POS, SPI_SR_UDR_WIDTH))
		#define SPI_SR_UDR_NMASK 			(~(SPI_SR_UDR_MASK))
		#define SPI_SR_CRCERR_WIDTH			(1u)
		#define SPI_SR_CRCERR_POS			(4u)
		#define SPI_SR_CRCERR_MASK			(HAL_BIT_CREATE_MASK(SPI_SR_CRCERR_POS, SPI_SR_CRCERR_WIDTH))
		#define SPI_SR_CRCERR_NMASK 		(~(SPI_SR_CRCERR_MASK))
		#define SPI_SR_MODF_WIDTH			(1u)
		#define SPI_SR_MODF_POS				(5u)
		#define SPI_SR_MODF_MASK			(HAL_BIT_CREATE_MASK(SPI_SR_MODF_POS, SPI_SR_MODF_WIDTH))
		#define SPI_SR_MODF_NMASK 			(~(SPI_SR_MODF_MASK))
		#define SPI_SR_OVR_WIDTH			(1u)
		#define SPI_SR_OVR_POS				(6u)
		#define SPI_SR_OVR_MASK				(HAL_BIT_CREATE_MASK(SPI_SR_OVR_POS, SPI_SR_OVR_WIDTH))
		#define SPI_SR_OVR_NMASK 			(~(SPI_SR_OVR_MASK))
		#define SPI_SR_BSY_WIDTH			(1u)
		#define SPI_SR_BSY_POS				(7u)
		#define SPI_SR_BSY_MASK				(HAL_BIT_CREATE_MASK(SPI_SR_BSY_POS, SPI_SR_BSY_WIDTH))
		#define SPI_SR_BSY_NMASK 			(~(SPI_SR_BSY_MASK))
		#define SPI_SR_FRE_WIDTH			(1u)
		#define SPI_SR_FRE_POS				(8u)
		#define SPI_SR_FRE_MASK				(HAL_BIT_CREATE_MASK(SPI_SR_FRE_POS, SPI_SR_FRE_WIDTH))
		#define SPI_SR_FRE_NMASK 			(~(SPI_SR_FRE_MASK))
#define SPI_DR_OFS							(0x0Cu) //!< SPI data register.
	#define SPI_DR_GET(base)				(HAL_REG_READ((base + SPI_DR_OFS)))
	#define SPI_DR_SET(base, data)			(HAL_REG_WRITE((base + SPI_DR_OFS), (uint32_t)data))
	#define SPI_DR_WIDTH					(16u)
	#define SPI_DR_POS						(0u)
	#define SPI_DR_MASK						(HAL_BIT_CREATE_MASK(SPI_DR_POS, SPI_DR_WIDTH))
	#define SPI_DR_NMASK 					(~(SPI_DR_MASK))
#define SPI_CRCPR_OFS						(0x10u) //!< SPI CRC polynomial register (not used in I2S mode).
	#define SPI_CRCPR_GET(base)				(HAL_REG_READ((base + SPI_CRCPR_OFS)))
	#define SPI_CRCPR_SET(base, data)		(HAL_REG_WRITE((base + SPI_CRCPR_OFS), (uint32_t)data))
	#define SPI_CRCPR_WIDTH					(16u)
	#define SPI_CRCPR_POS					(0u)
	#define SPI_CRCPR_MASK					(HAL_BIT_CREATE_MASK(SPI_CRCPR_POS, SPI_CRCPR_WIDTH))
	#define SPI_CRCPR_NMASK 				(~(SPI_CRCPR_MASK))
#define SPI_RXCRC_OFS						(0x14u) //!< SPI RX CRC register (not used in I2S mode).
	#define SPI_RXCRC_GET(base)				(HAL_REG_READ((base + SPI_RXCRC_OFS)))
	#define SPI_RXCRC_SET(base, data)		(HAL_REG_WRITE((base + SPI_RXCRC_OFS), (uint32_t)data))
	#define SPI_RXCRC_WIDTH					(16u)
	#define SPI_RXCRC_POS					(0u)
	#define SPI_RXCRC_MASK					(HAL_BIT_CREATE_MASK(SPI_RXCRC_POS, SPI_RXCRC_WIDTH))
	#define SPI_RXCRC_NMASK 				(~(SPI_RXCRC_MASK))
#define SPI_TXCRC_OFS						(0x18u) //!< SPI TX CRC register (not used in I2S mode).
	#define SPI_TXCRC_GET(base)				(HAL_REG_READ((base + SPI_TXCRC_OFS)))
	#define SPI_TXCRC_SET(base, data)		(HAL_REG_WRITE((base + SPI_TXCRC_OFS), (uint32_t)data))
	#define SPI_TXCRC_WIDTH					(16u)
	#define SPI_TXCRC_POS					(0u)
	#define SPI_TXCRC_MASK					(HAL_BIT_CREATE_MASK(SPI_TXCRC_POS, SPI_TXCRC_WIDTH))
	#define SPI_TXCRC_NMASK 				(~(SPI_TXCRC_MASK))
#define SPI_I2SCFGR_OFS						(0x1Cu) //!< SPI_I2S configuration register.
	#define SPI_I2SCFGR_GET(base)			(HAL_REG_READ((base + SPI_I2SCFGR_OFS)))
	#define SPI_I2SCFGR_SET(base, data)		(HAL_REG_WRITE((base + SPI_I2SCFGR_OFS), (uint32_t)data))
		#define SPI_I2SCFGR_CHLEN_WIDTH		(1u)
		#define SPI_I2SCFGR_CHLEN_POS		(0u)
		#define SPI_I2SCFGR_CHLEN_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_CHLEN_POS, SPI_I2SCFGR_CHLEN_WIDTH))
		#define SPI_I2SCFGR_CHLEN_NMASK 	(~(SPI_I2SCFGR_CHLEN_MASK))
		#define SPI_I2SCFGR_DATLEN_WIDTH	(2u)
		#define SPI_I2SCFGR_DATLEN_POS		(1u)
		#define SPI_I2SCFGR_DATLEN_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_DATLEN_POS, SPI_I2SCFGR_DATLEN_WIDTH))
		#define SPI_I2SCFGR_DATLEN_NMASK 	(~(SPI_I2SCFGR_DATLEN_MASK))
		#define SPI_I2SCFGR_CKPOL_WIDTH		(1u)
		#define SPI_I2SCFGR_CKPOL_POS		(3u)
		#define SPI_I2SCFGR_CKPOL_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_CKPOL_POS, SPI_I2SCFGR_CKPOL_WIDTH))
		#define SPI_I2SCFGR_CKPOL_NMASK 	(~(SPI_I2SCFGR_CKPOL_MASK))
		#define SPI_I2SCFGR_I2SSTD_WIDTH	(2u)
		#define SPI_I2SCFGR_I2SSTD_POS		(4u)
		#define SPI_I2SCFGR_I2SSTD_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_I2SSTD_POS, SPI_I2SCFGR_I2SSTD_WIDTH))
		#define SPI_I2SCFGR_I2SSTD_NMASK 	(~(SPI_I2SCFGR_I2SSTD_MASK))
		#define SPI_I2SCFGR_PCMSYNC_WIDTH	(1u)
		#define SPI_I2SCFGR_PCMSYNC_POS		(7u)
		#define SPI_I2SCFGR_PCMSYNC_MASK	(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_PCMSYNC_POS, SPI_I2SCFGR_PCMSYNC_WIDTH))
		#define SPI_I2SCFGR_PCMSYNC_NMASK 	(~(SPI_I2SCFGR_PCMSYNC_MASK))
		#define SPI_I2SCFGR_I2SCFG_WIDTH	(2u)
		#define SPI_I2SCFGR_I2SCFG_POS		(8u)
		#define SPI_I2SCFGR_I2SCFG_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_I2SCFG_POS, SPI_I2SCFGR_I2SCFG_WIDTH))
		#define SPI_I2SCFGR_I2SCFG_NMASK 	(~(SPI_I2SCFGR_I2SCFG_MASK))
		#define SPI_I2SCFGR_I2SE_WIDTH		(1u)
		#define SPI_I2SCFGR_I2SE_POS		(10u)
		#define SPI_I2SCFGR_I2SE_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_I2SE_POS, SPI_I2SCFGR_I2SE_WIDTH))
		#define SPI_I2SCFGR_I2SE_NMASK 		(~(SPI_I2SCFGR_I2SE_MASK))
		#define SPI_I2SCFGR_I2SMOD_WIDTH	(1u)
		#define SPI_I2SCFGR_I2SMOD_POS		(11u)
		#define SPI_I2SCFGR_I2SMOD_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_I2SMOD_POS, SPI_I2SCFGR_I2SMOD_WIDTH))
		#define SPI_I2SCFGR_I2SMOD_NMASK 	(~(SPI_I2SCFGR_I2SMOD_MASK))
		#define SPI_I2SCFGR_ASTREN_WIDTH	(1u)
		#define SPI_I2SCFGR_ASTREN_POS		(12u)
		#define SPI_I2SCFGR_ASTREN_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SCFGR_ASTREN_POS, SPI_I2SCFGR_ASTREN_WIDTH))
		#define SPI_I2SCFGR_ASTREN_NMASK 	(~(SPI_I2SCFGR_ASTREN_MASK))
#define SPI_I2SPR_OFS						(0x20u) //!< SPI_I2S prescaler register.
	#define SPI_I2SPR_GET(base)				(HAL_REG_READ((base + SPI_I2SPR_OFS)))
	#define SPI_I2SPR_SET(base, data)		(HAL_REG_WRITE((base + SPI_I2SPR_OFS), (uint32_t)data))
		#define SPI_I2SPR_I2SDIV_WIDTH		(8u)
		#define SPI_I2SPR_I2SDIV_POS		(0u)
		#define SPI_I2SPR_I2SDIV_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SPR_I2SDIV_POS, SPI_I2SPR_I2SDIV_WIDTH))
		#define SPI_I2SPR_I2SDIV_NMASK 		(~(SPI_I2SPR_I2SDIV_MASK))
		#define SPI_I2SPR_ODD_WIDTH			(1u)
		#define SPI_I2SPR_ODD_POS			(8u)
		#define SPI_I2SPR_ODD_MASK			(HAL_BIT_CREATE_MASK(SPI_I2SPR_ODD_POS, SPI_I2SPR_ODD_WIDTH))
		#define SPI_I2SPR_ODD_NMASK 		(~(SPI_I2SPR_ODD_MASK))
		#define SPI_I2SPR_MCKOE_WIDTH		(1u)
		#define SPI_I2SPR_MCKOE_POS			(9u)
		#define SPI_I2SPR_MCKOE_MASK		(HAL_BIT_CREATE_MASK(SPI_I2SPR_MCKOE_POS, SPI_I2SPR_MCKOE_WIDTH))
		#define SPI_I2SPR_MCKOE_NMASK 		(~(SPI_I2SPR_MCKOE_MASK))


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

#endif /* SPI_REGISTER_H_ */
/*** EOF ***/
