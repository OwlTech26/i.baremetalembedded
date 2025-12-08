/**
 * Copyright (c) 2025 OwlTech
 *
 * \file rtc_register.h
 * \brief
 * \author OwlTech
 * \date Dec 4, 2025
 */

#ifndef RTC_REGISTER_H_
#define RTC_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define RTC_BASE		(0x40002800u) 				  //!< RTC register base address
#define RTC_BKP_BASE	(0x40002800u + RTC_BKPxR_OFS) //!< RTC backup register base address

#define RTC_TR_OFS							(0x00u) //!< RTC calendar time shadow register.
	#define RTC_TR_SU_WIDTH					(4u)
	#define RTC_TR_SU_POS					(0u)
	#define RTC_TR_SU_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_SU_POS, RTC_TR_SU_WIDTH))
	#define RTC_TR_SU_NMASK 				(~(RTC_TR_SU_MASK))
	#define RTC_TR_ST_WIDTH					(3u)
	#define RTC_TR_ST_POS					(4u)
	#define RTC_TR_ST_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_ST_POS, RTC_TR_ST_WIDTH))
	#define RTC_TR_ST_NMASK 				(~(RTC_TR_ST_MASK))
	#define RTC_TR_MNU_WIDTH				(4u)
	#define RTC_TR_MNU_POS					(8u)
	#define RTC_TR_MNU_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_MNU_POS, RTC_TR_MNU_WIDTH))
	#define RTC_TR_MNU_NMASK 				(~(RTC_TR_MNU_MASK))
	#define RTC_TR_MNT_WIDTH				(3u)
	#define RTC_TR_MNT_POS					(12u)
	#define RTC_TR_MNT_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_MNT_POS, RTC_TR_MNT_WIDTH))
	#define RTC_TR_MNT_NMASK 				(~(RTC_TR_MNT_MASK))
	#define RTC_TR_HU_WIDTH					(4u)
	#define RTC_TR_HU_POS					(16u)
	#define RTC_TR_HU_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_HU_POS, RTC_TR_HU_WIDTH))
	#define RTC_TR_HU_NMASK 				(~(RTC_TR_HU_MASK))
	#define RTC_TR_HT_WIDTH					(2u)
	#define RTC_TR_HT_POS					(20u)
	#define RTC_TR_HT_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_HT_POS, RTC_TR_HT_WIDTH))
	#define RTC_TR_HT_NMASK 				(~(RTC_TR_HT_MASK))
	#define RTC_TR_PM_WIDTH					(1u)
	#define RTC_TR_PM_POS					(22u)
	#define RTC_TR_PM_MASK					(HAL_BIT_CREATE_MASK(RTC_TR_PM_POS, RTC_TR_PM_WIDTH))
	#define RTC_TR_PM_NMASK 				(~(RTC_TR_PM_MASK))
#define RTC_DR_OFS							(0x04u) //!< RTC calendar date shadow register.
	#define RTC_DR_DU_WIDTH					(4u)
	#define RTC_DR_DU_POS					(0u)
	#define RTC_DR_DU_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_DU_POS, RTC_DR_DU_WIDTH))
	#define RTC_DR_DU_NMASK 				(~(RTC_DR_DU_MASK))
	#define RTC_DR_DT_WIDTH					(2u)
	#define RTC_DR_DT_POS					(4u)
	#define RTC_DR_DT_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_DT_POS, RTC_DR_DT_WIDTH))
	#define RTC_DR_DT_NMASK 				(~(RTC_DR_DT_MASK))
	#define RTC_DR_MU_WIDTH					(4u)
	#define RTC_DR_MU_POS					(8u)
	#define RTC_DR_MU_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_MU_POS, RTC_DR_MU_WIDTH))
	#define RTC_DR_MU_NMASK 				(~(RTC_DR_MU_MASK))
	#define RTC_DR_MT_WIDTH					(1u)
	#define RTC_DR_MT_POS					(12u)
	#define RTC_DR_MT_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_MT_POS, RTC_DR_MT_WIDTH))
	#define RTC_DR_MT_NMASK 				(~(RTC_DR_MT_MASK))
	#define RTC_DR_WDU_WIDTH				(3u)
	#define RTC_DR_WDU_POS					(13u)
	#define RTC_DR_WDU_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_WDU_POS, RTC_DR_WDU_WIDTH))
	#define RTC_DR_WDU_NMASK 				(~(RTC_DR_WDU_MASK))
	#define RTC_DR_YU_WIDTH					(4u)
	#define RTC_DR_YU_POS					(16u)
	#define RTC_DR_YU_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_YU_POS, RTC_DR_YU_WIDTH))
	#define RTC_DR_YU_NMASK 				(~(RTC_DR_YU_MASK))
	#define RTC_DR_YT_WIDTH					(4u)
	#define RTC_DR_YT_POS					(20u)
	#define RTC_DR_YT_MASK					(HAL_BIT_CREATE_MASK(RTC_DR_YT_POS, RTC_DR_YT_WIDTH))
	#define RTC_DR_YT_NMASK 				(~(RTC_DR_YT_MASK))
#define RTC_CR_OFS							(0x08u) //!< RTC control register register.
	#define RTC_CR_WUCKSEL_WIDTH			(3u)
	#define RTC_CR_WUCKSEL_POS				(0u)
	#define RTC_CR_WUCKSEL_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_WUCKSEL_POS, RTC_CR_WUCKSEL_WIDTH))
	#define RTC_CR_WUCKSEL_NMASK 			(~(RTC_CR_WUCKSEL_MASK))
	#define RTC_CR_TSEDGE_WIDTH				(1u)
	#define RTC_CR_TSEDGE_POS				(3u)
	#define RTC_CR_TSEDGE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_TSEDGE_POS, RTC_CR_TSEDGE_WIDTH))
	#define RTC_CR_TSEDGE_NMASK 			(~(RTC_CR_TSEDGE_MASK))
	#define RTC_CR_REFCKON_WIDTH			(1u)
	#define RTC_CR_REFCKON_POS				(u)
	#define RTC_CR_REFCKON_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_REFCKON_POS, RTC_CR_REFCKON_WIDTH))
	#define RTC_CR_REFCKON_NMASK 			(~(RTC_CR_REFCKON_MASK))
	#define RTC_CR_BYPSHAD_WIDTH			(1u)
	#define RTC_CR_BYPSHAD_POS				(5u)
	#define RTC_CR_BYPSHAD_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_BYPSHAD_POS, RTC_CR_BYPSHAD_WIDTH))
	#define RTC_CR_BYPSHAD_NMASK 			(~(RTC_CR_BYPSHAD_MASK))
	#define RTC_CR_FMT_WIDTH				(1u)
	#define RTC_CR_FMT_POS					(6u)
	#define RTC_CR_FMT_MASK					(HAL_BIT_CREATE_MASK(RTC_CR_FMT_POS, RTC_CR_FMT_WIDTH))
	#define RTC_CR_FMT_NMASK 				(~(RTC_CR_FMT_MASK))
	#define RTC_CR_DCE_WIDTH				(1u)
	#define RTC_CR_DCE_POS					(7u)
	#define RTC_CR_DCE_MASK					(HAL_BIT_CREATE_MASK(RTC_CR_DCE_POS, RTC_CR_DCE_WIDTH))
	#define RTC_CR_DCE_NMASK 				(~(RTC_CR_DCE_MASK))
	#define RTC_CR_ALRAE_WIDTH				(1u)
	#define RTC_CR_ALRAE_POS				(8u)
	#define RTC_CR_ALRAE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_ALRAE_POS, RTC_CR_ALRAE_WIDTH))
	#define RTC_CR_ALRAE_NMASK 				(~(RTC_CR_ALRAE_MASK))
	#define RTC_CR_ALRBE_WIDTH				(1u)
	#define RTC_CR_ALRBE_POS				(9u)
	#define RTC_CR_ALRBE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_ALRBE_POS, RTC_CR_ALRBE_WIDTH))
	#define RTC_CR_ALRBE_NMASK 				(~(RTC_CR_ALRBE_MASK))
	#define RTC_CR_WUTE_WIDTH				(1u)
	#define RTC_CR_WUTE_POS					(10u)
	#define RTC_CR_WUTE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_WUTE_POS, RTC_CR_WUTE_WIDTH))
	#define RTC_CR_WUTE_NMASK 				(~(RTC_CR_WUTE_MASK))
	#define RTC_CR_TSE_WIDTH				(1u)
	#define RTC_CR_TSE_POS					(11u)
	#define RTC_CR_TSE_MASK					(HAL_BIT_CREATE_MASK(RTC_CR_TSE_POS, RTC_CR_TSE_WIDTH))
	#define RTC_CR_TSE_NMASK 				(~(RTC_CR_TSE_MASK))
	#define RTC_CR_ALRAIE_WIDTH				(1u)
	#define RTC_CR_ALRAIE_POS				(12u)
	#define RTC_CR_ALRAIE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_ALRAIE_POS, RTC_CR_ALRAIE_WIDTH))
	#define RTC_CR_ALRAIE_NMASK 			(~(RTC_CR_ALRAIE_MASK))
	#define RTC_CR_ALRBIE_WIDTH				(1u)
	#define RTC_CR_ALRBIE_POS				(13u)
	#define RTC_CR_ALRBIE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_ALRBIE_POS, RTC_CR_ALRBIE_WIDTH))
	#define RTC_CR_ALRBIE_NMASK 			(~(RTC_CR_ALRBIE_MASK))
	#define RTC_CR_WUTIE_WIDTH				(1u)
	#define RTC_CR_WUTIE_POS				(14u)
	#define RTC_CR_WUTIE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_WUTIE_POS, RTC_CR_WUTIE_WIDTH))
	#define RTC_CR_WUTIE_NMASK 				(~(RTC_CR_WUTIE_MASK))
	#define RTC_CR_TSIE_WIDTH				(1u)
	#define RTC_CR_TSIE_POS					(15u)
	#define RTC_CR_TSIE_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_TSIE_POS, RTC_CR_TSIE_WIDTH))
	#define RTC_CR_TSIE_NMASK 				(~(RTC_CR_TSIE_MASK))
	#define RTC_CR_ADD1H_WIDTH				(1u)
	#define RTC_CR_ADD1H_POS				(16u)
	#define RTC_CR_ADD1H_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_ADD1H_POS, RTC_CR_ADD1H_WIDTH))
	#define RTC_CR_ADD1H_NMASK 				(~(RTC_CR_ADD1H_MASK))
	#define RTC_CR_SUB1H_WIDTH				(1u)
	#define RTC_CR_SUB1H_POS				(17u)
	#define RTC_CR_SUB1H_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_SUB1H_POS, RTC_CR_SUB1H_WIDTH))
	#define RTC_CR_SUB1H_NMASK 				(~(RTC_CR_SUB1H_MASK))
	#define RTC_CR_BKP_WIDTH				(1u)
	#define RTC_CR_BKP_POS					(18u)
	#define RTC_CR_BKP_MASK					(HAL_BIT_CREATE_MASK(RTC_CR_BKP_POS, RTC_CR_BKP_WIDTH))
	#define RTC_CR_BKP_NMASK 				(~(RTC_CR_BKP_MASK))
	#define RTC_CR_COSEL_WIDTH				(1u)
	#define RTC_CR_COSEL_POS				(19u)
	#define RTC_CR_COSEL_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_COSEL_POS, RTC_CR_COSEL_WIDTH))
	#define RTC_CR_COSEL_NMASK 				(~(RTC_CR_COSEL_MASK))
	#define RTC_CR_POL_WIDTH				(1u)
	#define RTC_CR_POL_POS					(20u)
	#define RTC_CR_POL_MASK					(HAL_BIT_CREATE_MASK(RTC_CR_POL_POS, RTC_CR_POL_WIDTH))
	#define RTC_CR_POL_NMASK 				(~(RTC_CR_POL_MASK))
	#define RTC_CR_OSEL_WIDTH				(2u)
	#define RTC_CR_OSEL_POS					(21u)
	#define RTC_CR_OSEL_MASK				(HAL_BIT_CREATE_MASK(RTC_CR_OSEL_POS, RTC_CR_OSEL_WIDTH))
	#define RTC_CR_OSEL_NMASK 				(~(RTC_CR_OSEL_MASK))
	#define RTC_CR_COE_WIDTH				(1u)
	#define RTC_CR_COE_POS					(23u)
	#define RTC_CR_COE_MASK					(HAL_BIT_CREATE_MASK(RTC_CR_COE_POS, RTC_CR_COE_WIDTH))
	#define RTC_CR_COE_NMASK 				(~(RTC_CR_COE_MASK))
#define RTC_ISR_OFS							(0x0Cu) //!< RTC initialization and status register.
	#define RTC_ISR_ALRAWF_WIDTH			(1u)
	#define RTC_ISR_ALRAWF_POS				(0u)
	#define RTC_ISR_ALRAWF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_ALRAWF_POS, RTC_ISR_ALRAWF_WIDTH))
	#define RTC_ISR_ALRAWF_NMASK 			(~(RTC_ISR_ALRAWF_MASK))
	#define RTC_ISR_ALRBWF_WIDTH			(1u)
	#define RTC_ISR_ALRBWF_POS				(1u)
	#define RTC_ISR_ALRBWF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_ALRBWF_POS, RTC_ISR_ALRBWF_WIDTH))
	#define RTC_ISR_ALRBWF_NMASK 			(~(RTC_ISR_ALRBWF_MASK))
	#define RTC_ISR_WUTWF_WIDTH				(1u)
	#define RTC_ISR_WUTWF_POS				(2u)
	#define RTC_ISR_WUTWF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_WUTWF_POS, RTC_ISR_WUTWF_WIDTH))
	#define RTC_ISR_WUTWF_NMASK 			(~(RTC_ISR_WUTWF_MASK))
	#define RTC_ISR_SHPF_WIDTH				(1u)
	#define RTC_ISR_SHPF_POS				(3u)
	#define RTC_ISR_SHPF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_SHPF_POS, RTC_ISR_SHPF_WIDTH))
	#define RTC_ISR_SHPF_NMASK 				(~(RTC_ISR_SHPF_MASK))
	#define RTC_ISR_INITS_WIDTH				(1u)
	#define RTC_ISR_INITS_POS				(4u)
	#define RTC_ISR_INITS_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_INITS_POS, RTC_ISR_INITS_WIDTH))
	#define RTC_ISR_INITS_NMASK 			(~(RTC_ISR_INITS_MASK))
	#define RTC_ISR_RSF_WIDTH				(1u)
	#define RTC_ISR_RSF_POS					(5u)
	#define RTC_ISR_RSF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_RSF_POS, RTC_ISR_RSF_WIDTH))
	#define RTC_ISR_RSF_NMASK 				(~(RTC_ISR_RSF_MASK))
	#define RTC_ISR_INITF_WIDTH				(1u)
	#define RTC_ISR_INITF_POS				(6u)
	#define RTC_ISR_INITF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_INITF_POS, RTC_ISR_INITF_WIDTH))
	#define RTC_ISR_INITF_NMASK 			(~(RTC_ISR_INITF_MASK))
	#define RTC_ISR_INIT_WIDTH				(1u)
	#define RTC_ISR_INIT_POS				(7u)
	#define RTC_ISR_INIT_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_INIT_POS, RTC_ISR_INIT_WIDTH))
	#define RTC_ISR_INIT_NMASK 				(~(RTC_ISR_INIT_MASK))
	#define RTC_ISR_ALRAF_WIDTH				(1u)
	#define RTC_ISR_ALRAF_POS				(8u)
	#define RTC_ISR_ALRAF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_ALRAF_POS, RTC_ISR_ALRAF_WIDTH))
	#define RTC_ISR_ALRAF_NMASK 			(~(RTC_ISR_ALRAF_MASK))
	#define RTC_ISR_ALRBF_WIDTH				(1u)
	#define RTC_ISR_ALRBF_POS				(9u)
	#define RTC_ISR_ALRBF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_ALRBF_POS, RTC_ISR_ALRBF_WIDTH))
	#define RTC_ISR_ALRBF_NMASK 			(~(RTC_ISR_ALRBF_MASK))
	#define RTC_ISR_WUTF_WIDTH				(1u)
	#define RTC_ISR_WUTF_POS				(10u)
	#define RTC_ISR_WUTF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_WUTF_POS, RTC_ISR_WUTF_WIDTH))
	#define RTC_ISR_WUTF_NMASK 				(~(RTC_ISR_WUTF_MASK))
	#define RTC_ISR_TSF_WIDTH				(1u)
	#define RTC_ISR_TSF_POS					(11u)
	#define RTC_ISR_TSF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_TSF_POS, RTC_ISR_TSF_WIDTH))
	#define RTC_ISR_TSF_NMASK 				(~(RTC_ISR_TSF_MASK))
	#define RTC_ISR_TSOVF_WIDTH				(1u)
	#define RTC_ISR_TSOVF_POS				(12u)
	#define RTC_ISR_TSOVF_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_TSOVF_POS, RTC_ISR_TSOVF_WIDTH))
	#define RTC_ISR_TSOVF_NMASK 			(~(RTC_ISR_TSOVF_MASK))
	#define RTC_ISR_TAMP1F_WIDTH			(1u)
	#define RTC_ISR_TAMP1F_POS				(13u)
	#define RTC_ISR_TAMP1F_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_TAMP1F_POS, RTC_ISR_TAMP1F_WIDTH))
	#define RTC_ISR_TAMP1F_NMASK 			(~(RTC_ISR_TAMP1F_MASK))
	#define RTC_ISR_TAMP2F_WIDTH			(1u)
	#define RTC_ISR_TAMP2F_POS				(14u)
	#define RTC_ISR_TAMP2F_MASK				(HAL_BIT_CREATE_MASK(RTC_ISR_TAMP2F_POS, RTC_ISR_TAMP2F_WIDTH))
	#define RTC_ISR_TAMP2F_NMASK 			(~(RTC_ISR_TAMP2F_MASK))
	#define RTC_ISR_RECALPF_WIDTH			(1u)
	#define RTC_ISR_RECALPF_POS				(16u)
	#define RTC_ISR_RECALPF_MASK			(HAL_BIT_CREATE_MASK(RTC_ISR_RECALPF_POS, RTC_ISR_RECALPF_WIDTH))
	#define RTC_ISR_RECALPF_NMASK 			(~(RTC_ISR_RECALPF_MASK))
#define RTC_PRER_OFS						(0x10u) //!< RTC prescaler register.
	#define RTC_PRER_PREDIV_S_WIDTH			(15u)
	#define RTC_PRER_PREDIV_S_POS			(0u)
	#define RTC_PRER_PREDIV_S_MASK			(HAL_BIT_CREATE_MASK(RTC_PRER_PREDIV_S_POS, RTC_PRER_PREDIV_S_WIDTH))
	#define RTC_PRER_PREDIV_S_NMASK 		(~(RTC_PRER_PREDIV_S_MASK))
	#define RTC_PRER_PREDIV_A_WIDTH			(7u)
	#define RTC_PRER_PREDIV_A_POS			(16u)
	#define RTC_PRER_PREDIV_A_MASK			(HAL_BIT_CREATE_MASK(RTC_PRER_PREDIV_A_POS, RTC_PRER_PREDIV_A_WIDTH))
	#define RTC_PRER_PREDIV_A_NMASK 		(~(RTC_PRER_PREDIV_A_MASK))
#define RTC_WUTR_OFS						(0x14u) //!< RTC wakeup timer register.
#define RTC_CALIBR_OFS						(0x18u) //!< RTC calibration register.
#define RTC_ALRMAR_OFS						(0x1Cu) //!< RTC alarm A register.
#define RTC_ALRMBR_OFS						(0x20u) //!< RTC alarm B register.
	#define RTC_ALRMxR_SU_WIDTH				(4u)
	#define RTC_ALRMxR_SU_POS				(0u)
	#define RTC_ALRMxR_SU_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_SU_POS, RTC_ALRMxR_SU_WIDTH))
	#define RTC_ALRMxR_SU_NMASK 			(~(RTC_ALRMxR_SU_MASK))
	#define RTC_ALRMxR_ST_WIDTH				(3u)
	#define RTC_ALRMxR_ST_POS				(4u)
	#define RTC_ALRMxR_ST_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_ST_POS, RTC_ALRMxR_ST_WIDTH))
	#define RTC_ALRMxR_ST_NMASK 			(~(RTC_ALRMxR_ST_MASK))
	#define RTC_ALRMxR_MSK1_WIDTH			(1u)
	#define RTC_ALRMxR_MSK1_POS				(7u)
	#define RTC_ALRMxR_MSK1_MASK			(HAL_BIT_CREATE_MASK(RTC_ALRMxR_MSK1_POS, RTC_ALRMxR_MSK1_WIDTH))
	#define RTC_ALRMxR_MSK1_NMASK 			(~(RTC_ALRMxR_MSK1_MASK))
	#define RTC_ALRMxR_MNU_WIDTH			(4u)
	#define RTC_ALRMxR_MNU_POS				(8u)
	#define RTC_ALRMxR_MNU_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_MNU_POS, RTC_ALRMxR_MNU_WIDTH))
	#define RTC_ALRMxR_MNU_NMASK 			(~(RTC_ALRMxR_MNU_MASK))
	#define RTC_ALRMxR_MNT_WIDTH			(3u)
	#define RTC_ALRMxR_MNT_POS				(12u)
	#define RTC_ALRMxR_MNT_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_MNT_POS, RTC_ALRMxR_MNT_WIDTH))
	#define RTC_ALRMxR_MNT_NMASK 			(~(RTC_ALRMxR_MNT_MASK))
	#define RTC_ALRMxR_MSK2_WIDTH			(1u)
	#define RTC_ALRMxR_MSK2_POS				(15u)
	#define RTC_ALRMxR_MSK2_MASK			(HAL_BIT_CREATE_MASK(RTC_ALRMxR_MSK2_POS, RTC_ALRMxR_MSK2_WIDTH))
	#define RTC_ALRMxR_MSK2_NMASK 			(~(RTC_ALRMxR_MSK2_MASK))
	#define RTC_ALRMxR_HU_WIDTH				(4u)
	#define RTC_ALRMxR_HU_POS				(16u)
	#define RTC_ALRMxR_HU_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_HU_POS, RTC_ALRMxR_HU_WIDTH))
	#define RTC_ALRMxR_HU_NMASK 			(~(RTC_ALRMxR_HU_MASK))
	#define RTC_ALRMxR_HT_WIDTH				(2u)
	#define RTC_ALRMxR_HT_POS				(20u)
	#define RTC_ALRMxR_HT_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_HT_POS, RTC_ALRMxR_HT_WIDTH))
	#define RTC_ALRMxR_HT_NMASK 			(~(RTC_ALRMxR_HT_MASK))
	#define RTC_ALRMxR_PM_WIDTH				(1u)
	#define RTC_ALRMxR_PM_POS				(22u)
	#define RTC_ALRMxR_PM_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_PM_POS, RTC_ALRMxR_PM_WIDTH))
	#define RTC_ALRMxR_PM_NMASK 			(~(RTC_ALRMxR_PM_MASK))
	#define RTC_ALRMxR_MSK3_WIDTH			(1u)
	#define RTC_ALRMxR_MSK3_POS				(23u)
	#define RTC_ALRMxR_MSK3_MASK			(HAL_BIT_CREATE_MASK(RTC_ALRMxR_MSK3_POS, RTC_ALRMxR_MSK3_WIDTH))
	#define RTC_ALRMxR_MSK3_NMASK 			(~(RTC_ALRMxR_MSK3_MASK))
	#define RTC_ALRMxR_DU_WIDTH				(4u)
	#define RTC_ALRMxR_DU_POS				(24u)
	#define RTC_ALRMxR_DU_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_DU_POS, RTC_ALRMxR_DU_WIDTH))
	#define RTC_ALRMxR_DU_NMASK 			(~(RTC_ALRMxR_DU_MASK))
	#define RTC_ALRMxR_DT_WIDTH				(2u)
	#define RTC_ALRMxR_DT_POS				(28u)
	#define RTC_ALRMxR_DT_MASK				(HAL_BIT_CREATE_MASK(RTC_ALRMxR_DT_POS, RTC_ALRMxR_DT_WIDTH))
	#define RTC_ALRMxR_DT_NMASK 			(~(RTC_ALRMxR_DT_MASK))
	#define RTC_ALRMxR_WDSEL_WIDTH			(1u)
	#define RTC_ALRMxR_WDSEL_POS			(30u)
	#define RTC_ALRMxR_WDSEL_MASK			(HAL_BIT_CREATE_MASK(RTC_ALRMxR_WDSEL_POS, RTC_ALRMxR_WDSEL_WIDTH))
	#define RTC_ALRMxR_WDSEL_NMASK 			(~(RTC_ALRMxR_WDSEL_MASK))
	#define RTC_ALRMxR_MSK4_WIDTH			(1u)
	#define RTC_ALRMxR_MSK4_POS				(31u)
	#define RTC_ALRMxR_MSK4_MASK			(HAL_BIT_CREATE_MASK(RTC_ALRMxR_MSK4_POS, RTC_ALRMxR_MSK4_WIDTH))
	#define RTC_ALRMxR_MSK4_NMASK 			(~(RTC_ALRMxR_MSK4_MASK))
#define RTC_WPR_OFS							(0x24u) //!< RTC write protection register.
	#define RTC_WPR_WIDTH					(8u)
	#define RTC_WPR_POS						(0u)
	#define RTC_WPR_MASK					(HAL_BIT_CREATE_MASK(RTC_WPR_POS, RTC_WPR_WIDTH))
	#define RTC_WPR_NMASK 					(~(RTC_WPR_MASK))
#define RTC_SSR_OFS							(0x28u) //!< RTC sub second register.
#define RTC_SHIFTR_OFS						(0x2Cu) //!< RTC shift control register.
#define RTC_TSTR_OFS						(0x30u) //!< RTC time stamp time register.
#define RTC_TSDR_OFS						(0x34u) //!< RTC time stamp date register.
#define RTC_TSSSR_OFS						(0x38u) //!< RTC timestamp sub second register.
#define RTC_CALR_OFS						(0x3Cu) //!< RTC calibration register.
#define RTC_TAFCR_OFS						(0x40u) //!< RTC tamper and alternate function configuration register.
#define RTC_ALRMASSR_OFS					(0x44u) //!< RTC alarm A sub second register.
#define RTC_ALRMBSSR_OFS					(0x48u) //!< RTC alarm B sub second register.
#define RTC_BKPxR_OFS						(0x50u) //!< RTC backup registers: 0x50..0x9C
	#define RTC_BKPxR_NUM					(19u) 	//!< Number of RTC backup registers.


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

#endif /* RTC_REGISTER_H_ */
/*** EOF ***/
