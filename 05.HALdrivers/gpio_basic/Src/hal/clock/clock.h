/**
 * Copyright (c) 2025 OwlTech
 *
 * \file clock.h
 * \brief
 * \author OwlTech
 * \date Jun 11, 2025
 */

#ifndef CLOCK_H_
#define CLOCK_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "common_def.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Periphery bridges. */
typedef enum {
	e_peri_ahb1 = 0u,
	e_peri_ahb2 = 1u,
	e_peri_ahb3 = 2u,
	e_peri_apb1 = 3u,
	e_peri_apb2 = 4u,
	e_peri_max  = 5u
} t_clock_peri;

/** \brief System clock switch configuration. */
typedef enum {
	e_clk_sys_hsi = 0u,
	e_clk_sys_hse = 1u,
	e_clk_sys_pll_p = 2u,
	e_clk_sys_pll_r = 3u
} t_clock_cfg_sw;

/** \brief HPRE AHB prescaler configuration. */
typedef enum {
	e_clk_hpre_0 	= 0u,
	e_clk_hpre_2 	= 8u,
	e_clk_hpre_4   	= 9u,
	e_clk_hpre_8   	= 10u,
	e_clk_hpre_16  	= 11u,
	e_clk_hpre_64  	= 12u,
	e_clk_hpre_128 	= 13u,
	e_clk_hpre_256 	= 14u,
	e_clk_hpre_512 	= 15u
} t_clock_cfg_hpre;

/** \brief HPRE AHB prescaler configuration. */
typedef enum {
	e_clk_ppre_0 	= 0u,
	e_clk_ppre_2 	= 4u,
	e_clk_ppre_4   	= 5u,
	e_clk_ppre_8   	= 6u,
	e_clk_ppre_16  	= 7u,
} t_clock_cfg_ppre;

/** \brief Microcontroller clock output. */
typedef enum {
	e_clk_mco_hsi = 0u, //!< HSI clock selected.
	e_clk_mco_lse = 1u, //!< LSE oscillator selected
	e_clk_mco_hse = 2u, //!< HSE oscillator selected
	e_clk_sys_pll = 3u //!< PLL clock selected.
} t_clock_cfg_mco;

/** \brief HPRE AHB prescaler configuration. */
typedef enum {
	e_clk_mco_pre_0 	= 0u,
	e_clk_mco_pre_2 	= 4u,
	e_clk_mco_pre_3   	= 5u,
	e_clk_mco_pre_4   	= 6u,
	e_clk_mco_pre_5  	= 7u,
} t_clock_cfg_mco_pre;

/** \brief Clock configuration. */
typedef struct {
	t_clock_cfg_sw clk_sw; //!< System clock switch.
	t_clock_cfg_sw clk_sws; //!< System clock switch status.
	t_clock_cfg_hpre clk_hpre; //!< AHB prescaler.
	t_clock_cfg_ppre clk_ppre1; //!< APB low-speed prescaler (APB1).
	t_clock_cfg_ppre clk_ppre2; //!< APB high-speed prescaler (APB2).
	uint8_t clk_rtcpre; //!< HSE division factor for RTC clock.
	t_clock_cfg_mco clk_mco1; //!< Microcontroller clock output 1.
	t_clock_cfg_mco_pre clk_mco1_pre; //!< MCO1 prescaler.
	t_clock_cfg_mco clk_mco2; //!< Microcontroller clock output 2.
	t_clock_cfg_mco_pre clk_mco2_pre; //!< MCO1 prescaler.
} t_clock_cfgr;

/** \brief Enable/disable clock. */
typedef enum {
	e_clk_hsi 			= 0u,
	e_clk_hse 			= 1u,
	e_clk_css 			= 2u,
	e_clk_pll 			= 3u,
	e_clk_pll_i2s 		= 4u,
	e_clk_pll_sai		= 5u,
	e_clk_src_max		= 6u
} t_clock_source;

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
void CLOCK_enable_source(const t_clock_source clk_src, const t_bool enable);

t_bool CLOCK_get_source_stat(const t_clock_source clk_src);

t_bool CLOCK_get_source_stat(const t_clock_source clk_src);

/** \brief System clock configuration setter.
 *  \param[in] p_clk_cfg Clock configuration parameters.
 *
 *  \return Configuration status.
 *  \retval e_ec_no_error Success.
 *  \retval e_ec_invalid_param Invalid parameter.
 */
t_error_code CLOCK_set_config(const t_clock_cfgr * const p_clk_cfg);

/** \brief System clock configuration getter.
 *  \param[out] p_clk_cfg Clock configuration parameters.
 */
void CLOCK_get_config(t_clock_cfgr * const p_clk_cfg);

/** \brief Enables the periphery clock(s) for the selected bridge.
 *  \param[in] clock_sel Selected bridge clock.
 *  \param[in] peri_en_mask Periphery enable mask.
 *  \param[in] lpwrm_en Low Power Mode enable.
 */
void CLOCK_enable(const t_clock_peri clock_sel, const uint32_t peri_en_mask, const t_bool lpwrm_en);

#endif /* CLOCK_H_ */
/*** EOF ***/
