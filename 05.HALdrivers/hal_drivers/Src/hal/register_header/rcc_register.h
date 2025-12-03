/**
 * Copyright (c) 2025 OwlTech
 *
 * \file rcc_register.h
 * \brief Reset and Clock Control STM32F446xx MCU specific register header file.
 * \author OwlTech
 * \date Jun 11, 2025
 */

#ifndef RCC_REGISTER_H_
#define RCC_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define RCC_BASE 0x40023800u

/** \name Reset / Clock Control Registers. */
/**@{*/
#define RCC_CR_OFS							(0x00u) //!< Clock control register offset.
	#define RCC_CR_GET()					(HAL_REG_READ((RCC_BASE + RCC_CR_OFS)))
	#define RCC_CR_SET(data)				(HAL_REG_WRITE((RCC_BASE + RCC_CR_OFS), (uint32_t)data))
		#define RCC_CR_HSI_ON_POS			(0u)
		#define RCC_CR_HSI_ON_WIDTH			(1u)
		#define RCC_CR_HSI_ON_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_HSI_ON_POS, RCC_CR_HSI_ON_WIDTH))
		#define RCC_CR_HSI_ON_NMASK			(~RCC_CR_HSI_ON_MASK)
		#define RCC_CR_HSI_RDY_POS			(1u)
		#define RCC_CR_HSI_RDY_WIDTH		(1u)
		#define RCC_CR_HSI_RDY_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_HSI_RDY_POS, RCC_CR_HSI_RDY_WIDTH))
		#define RCC_CR_HSI_RDY_NMASK		(~RCC_CR_HSI_RDY_MASK)
		#define RCC_CR_HSI_TRIM_POS			(3u)
		#define RCC_CR_HSI_TRIM_WIDTH		(5u)
		#define RCC_CR_HSI_TRIM_MASK		(HAL_BIT_CREATE_MASK(RCC_CR_HSI_TRIM_POS, RCC_CR_HSI_TRIM_WIDTH))
		#define RCC_CR_HSI_TRIM_NMASK		(~RCC_CR_HSI_TRIM_MASK)
		#define RCC_CR_HSI_CAL_POS			(8u)
		#define RCC_CR_HSI_CAL_WIDTH		(8u)
		#define RCC_CR_HSI_CAL_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_HSI_CAL_POS, RCC_CR_HSI_CAL_WIDTH))
		#define RCC_CR_HSI_CAL_NMASK		(~RCC_CR_HSI_CAL_MASK)
		#define RCC_CR_HSE_ON_POS			(16u)
		#define RCC_CR_HSE_ON_WIDTH			(1u)
		#define RCC_CR_HSE_ON_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_HSE_ON_POS, RCC_CR_HSE_ON_WIDTH))
		#define RCC_CR_HSE_ON_NMASK			(~RCC_CR_HSE_ON_MASK)
		#define RCC_CR_HSE_RDY_POS			(17u)
		#define RCC_CR_HSE_RDY_WIDTH		(1u)
		#define RCC_CR_HSE_RDY_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_HSE_RDY_POS, RCC_CR_HSE_RDY_WIDTH))
		#define RCC_CR_HSE_RDY_NMASK		(~RCC_CR_HSE_RDY_MASK)
		#define RCC_CR_HSE_BYP_POS			(18u)
		#define RCC_CR_HSE_BYP_WIDTH		(1u)
		#define RCC_CR_HSE_BYP_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_HSE_BYP_POS, RCC_CR_HSE_BYP_WIDTH))
		#define RCC_CR_HSE_BYP_NMASK		(~RCC_CR_HSE_BYP_MASK)
		#define RCC_CR_CSS_ON_POS			(18u)
		#define RCC_CR_CSS_ON_WIDTH			(1u)
		#define RCC_CR_CSS_ON_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_CSS_ON_POS, RCC_CR_CSS_ON_WIDTH))
		#define RCC_CR_CSS_ON_NMASK			(~RCC_CR_CSS_ON_MASK)
		#define RCC_CR_PLL_ON_POS			(24u)
		#define RCC_CR_PLL_ON_WIDTH			(1u)
		#define RCC_CR_PLL_ON_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_PLL_ON_POS, RCC_CR_PLL_ON_WIDTH))
		#define RCC_CR_PLL_ON_NMASK			(~RCC_CR_PLL_ON_MASK)
		#define RCC_CR_PLL_RDY_POS			(25u)
		#define RCC_CR_PLL_RDY_WIDTH		(1u)
		#define RCC_CR_PLL_RDY_MASK			(HAL_BIT_CREATE_MASK(RCC_CR_PLL_RDY_POS, RCC_CR_PLL_RDY_WIDTH))
		#define RCC_CR_PLL_RDY_NMASK		(~RCC_CR_PLL_RDY_MASK)
		#define RCC_CR_PLLI2S_ON_POS		(26u)
		#define RCC_CR_PLLI2S_ON_WIDTH		(1u)
		#define RCC_CR_PLLI2S_ON_MASK		(HAL_BIT_CREATE_MASK(RCC_CR_PLLI2S_ON_POS, RCC_CR_PLLI2S_ON_WIDTH))
		#define RCC_CR_PLLI2S_ON_NMASK		(~RCC_CR_PLLI2S_ON_MASK)
		#define RCC_CR_PLLI2S_RDY_POS		(27u)
		#define RCC_CR_PLLI2S_RDY_WIDTH		(1u)
		#define RCC_CR_PLLI2S_RDY_MASK		(HAL_BIT_CREATE_MASK(RCC_CR_PLLI2S_RDY_POS, RCC_CR_PLLI2S_RDY_WIDTH))
		#define RCC_CR_PLLI2S_RDY_NMASK		(~RCC_CR_PLLI2S_RDY_MASK)
		#define RCC_CR_PLLSAI_ON_POS		(28u)
		#define RCC_CR_PLLSAI_ON_WIDTH		(1u)
		#define RCC_CR_PLLSAI_ON_MASK		(HAL_BIT_CREATE_MASK(RCC_CR_PLLSAI_ON_POS, RCC_CR_PLLSAI_ON_WIDTH))
		#define RCC_CR_PLLSAI_ON_NMASK		(~RCC_CR_PLLSAI_ON_MASK)
		#define RCC_CR_PLLSAI_RDY_POS		(29u)
		#define RCC_CR_PLLSAI_RDY_WIDTH		(1u)
		#define RCC_CR_PLLSAI_RDY_MASK		(HAL_BIT_CREATE_MASK(RCC_CR_PLLSAI_RDY_POS, RCC_CR_PLLSAI_RDY_WIDTH))
		#define RCC_CR_PLLSAI_RDY_NMASK		(~RCC_CR_PLLSAI_RDY_MASK)
#define RCC_PLLCFGR_OFS						(0x04u) //!< PLL Configuration register offset.
#define RCC_CFGR_OFS						(0x08u) //!< Clock Configuration register offset.
	#define RCC_CFGR_GET()					(HAL_REG_READ((RCC_BASE + RCC_CFGR_OFS)))
	#define RCC_CFGR_SET(data)				(HAL_REG_WRITE((RCC_BASE + RCC_CFGR_OFS), (uint32_t)data))
		#define  RCC_CFGR_SW_POS			(0u)
		#define  RCC_CFGR_SW_WIDTH			(2u)
		#define  RCC_CFGR_SW_MASK			(HAL_BIT_CREATE_MASK(RCC_CFGR_SW_POS, RCC_CFGR_SW_WIDTH))
		#define  RCC_CFGR_SW_NMASK			(~RCC_CFGR_SW_MASK)
		#define  RCC_CFGR_SWS_POS			(2u)
		#define  RCC_CFGR_SWS_WIDTH			(2u)
		#define  RCC_CFGR_SWS_MASK			(HAL_BIT_CREATE_MASK(RCC_CFGR_SWS_POS, RCC_CFGR_SWS_WIDTH))
		#define  RCC_CFGR_SWS_NMASK			(~RCC_CFGR_SWS_MASK)
		#define  RCC_CFGR_HPRE_POS			(4u)
		#define  RCC_CFGR_HPRE_WIDTH		(4u)
		#define  RCC_CFGR_HPRE_MASK			(HAL_BIT_CREATE_MASK(RCC_CFGR_HPRE_POS, RCC_CFGR_HPRE_WIDTH))
		#define  RCC_CFGR_HPRE_NMASK		(~RCC_CFGR_HPRE_MASK)
		#define  RCC_CFGR_PPRE1_POS			(10u)
		#define  RCC_CFGR_PPRE1_WIDTH		(3u)
		#define  RCC_CFGR_PPRE1_MASK		(HAL_BIT_CREATE_MASK(RCC_CFGR_PPRE1_POS, RCC_CFGR_PPRE1_WIDTH))
		#define  RCC_CFGR_PPRE1_NMASK		(~RCC_CFGR_PPRE1_MASK)
		#define  RCC_CFGR_PPRE2_POS			(13u)
		#define  RCC_CFGR_PPRE2_WIDTH		(3u)
		#define  RCC_CFGR_PPRE2_MASK		(HAL_BIT_CREATE_MASK(RCC_CFGR_PPRE2_POS, RCC_CFGR_PPRE2_WIDTH))
		#define  RCC_CFGR_PPRE2_NMASK		(~RCC_CFGR_PPRE2_MASK)
		#define  RCC_CFGR_RTCPRE_POS		(16u)
		#define  RCC_CFGR_RTCPRE_WIDTH		(5u)
		#define  RCC_CFGR_RTCPRE_MASK		(HAL_BIT_CREATE_MASK(RCC_CFGR_RTCPRE_POS, RCC_CFGR_RTCPRE_WIDTH))
		#define  RCC_CFGR_RTCPRE_NMASK		(~RCC_CFGR_RTCPRE_MASK)
		#define  RCC_CFGR_MCO1_POS			(21u)
		#define  RCC_CFGR_MCO1_WIDTH		(2u)
		#define  RCC_CFGR_MCO1_MASK			(HAL_BIT_CREATE_MASK(RCC_CFGR_MCO1_POS, RCC_CFGR_MCO1_WIDTH))
		#define  RCC_CFGR_MCO1_NMASK		(~RCC_CFGR_MCO1_MASK)
		#define  RCC_CFGR_MCO1_PRE_POS		(24u)
		#define  RCC_CFGR_MCO1_PRE_WIDTH	(3u)
		#define  RCC_CFGR_MCO1_PRE_MASK		(HAL_BIT_CREATE_MASK(RCC_CFGR_MCO1_PRE_POS, RCC_CFGR_MCO1_PRE_WIDTH))
		#define  RCC_CFGR_MCO1_PRE_NMASK	(~RCC_CFGR_MCO1_PRE_MASK)
		#define  RCC_CFGR_MCO2_PRE_POS		(27u)
		#define  RCC_CFGR_MCO2_PRE_WIDTH	(3u)
		#define  RCC_CFGR_MCO2_PRE_MASK		(HAL_BIT_CREATE_MASK(RCC_CFGR_MCO2_PRE_POS, RCC_CFGR_MCO2_PRE_WIDTH))
		#define  RCC_CFGR_MCO2_PRE_NMASK	(~RCC_CFGR_MCO2_PRE_MASK)
		#define  RCC_CFGR_MCO2_POS			(30u)
		#define  RCC_CFGR_MCO2_WIDTH		(2u)
		#define  RCC_CFGR_MCO2_MASK			(HAL_BIT_CREATE_MASK(RCC_CFGR_MCO2_POS, RCC_CFGR_MCO2_WIDTH))
		#define  RCC_CFGR_MCO2_NMASK		(~RCC_CFGR_MCO2_MASK)
#define RCC_CIR_OFS							(0x0cu) //!< Clock interrupt register offset.
#define RCC_AHB1RSTR_OFS					(0x10u) //!< AHB1 peripheral reset register offset.
#define RCC_AHB2RSTR_OFS					(0x14u) //!< AHB2 peripheral reset register offset.
#define RCC_AHB3RSTR_OFS					(0x18u) //!< AHB3 peripheral reset register offset.
/** 0x1C Reserved. */
#define RCC_APB1RSTR_OFS					(0x20u) //!< APB1 peripheral reset register offset.
#define RCC_APB2RSTR_OFS					(0x24u) //!< APB2 peripheral reset register offset.
/** 0x28 Reserved. */
/** 0x2C Reserved. */
#define RCC_AHB1ENR_OFS						(0x30u) //!< AHB1 peripheral enable register offset.
	#define  RCC_AHB1ENR_GET()				(HAL_REG_READ((RCC_BASE + RCC_AHB1ENR_OFS)))
	#define  RCC_AHB1ENR_SET(data)			(HAL_REG_WRITE((RCC_BASE + RCC_AHB1ENR_OFS), (uint32_t)data))
		#define RCC_AHB1ENR_WIDTH			(1u)
		#define RCC_AHB1ENR_POS(bf)			(bf * RCC_AHB1ENR_WIDTH)
		#define RCC_AHB1ENR_MASK(bf)		(HAL_BIT_CREATE_MASK(RCC_AHB1ENR_POS(bf), RCC_AHB1ENR_WIDTH))
		#define RCC_AHB1ENR_NMASK(bf) 		(~(RCC_AHB1ENR_MASK(bf)))
#define RCC_AHB2ENR_OFS						(0x34u) //!< AHB2 peripheral enable register offset.
#define RCC_AHB3ENR_OFS						(0x38u) //!< AHB3 peripheral enable register offset.
/** 0x3c Reserved. */
#define RCC_APB1ENR_OFS						(0x40u) //!< APB1 peripheral enable register offset.
#define RCC_APB2ENR_OFS						(0x44u) //!< APB2 peripheral enable register offset.
/** 0x48 Reserved. */
/** 0x4c Reserved. */
#define RCC_AHB1LPENR_OFS					(0x50u) //!< AHB1 peripheral enable in low power register offset.
#define RCC_AHB2LPENR_OFS					(0x54u) //!< AHB2 peripheral enable in low power register offset.
#define RCC_AHB3LPENR_OFS					(0x58u) //!< AHB3 peripheral enable in low power register offset.
/** 0x5c Reserved. */
#define RCC_APB1LPENR_OFS					(0x60u) //!< APB1 peripheral enable in low power register offset.
#define RCC_APB2LPENR_OFS					(0x64u) //!< APB2 peripheral enable in low power register offset.
/** 0x68 Reserved. */
/** 0x6c Reserved. */
#define RCC_BDCR_OFS						(0x70u) //!< Backup Domain control register offset.
#define RCC_CSR_OFS							(0x74u) //!< Clock control and status register offset.
/** 0x78 Reserved. */
/** 0x7c Reserved. */
#define RCC_SSCGR_OFS						(0x80u) //!< Spread spectrum clock generation register offset.
#define RCC_PLLI2SCFGR_OFS					(0x84u) //!< PLLI2S configuration register offset.
#define RCC_PLLSAICFGR_OFS					(0x88u) //!< PLLSAI configuration register offset.
#define RCC_DCKCFGR_OFS						(0x8Cu) //!< Dedicated clocks configuration register offset.
#define RCC_CKGATENR_OFS					(0x90u) //!< RCC clocks gated enable register offset.
#define RCC_DCKCFGR2_OFS					(0x94u) //!< RCC Dedicated Clocks Configuration Register 2.
/**@}*/

/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */

#endif /* RCC_REGISTER_H_ */
