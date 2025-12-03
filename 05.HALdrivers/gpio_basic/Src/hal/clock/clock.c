/**
 * Copyright (c) 2025 OwlTech
 *
 * \file clock.c
 * \brief
 * \author OwlTech
 * \date Jun 11, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "clock.h"
#include "hal_reg.h"
#include "common_def.h"
#include "rcc_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define CLOCK_RTCPRE_MAX (31u)


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
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static uint32_t clock_calc_peri_address(const uint32_t base_addr, const t_clock_peri clock_sel);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/


/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
static uint32_t clock_calc_peri_address(const uint32_t base_addr, const t_clock_peri clock_sel)
{
	const uint8_t peri_ofs[e_peri_max] = {RCC_AHB1ENR_OFS, RCC_AHB2ENR_OFS, RCC_AHB3ENR_OFS, RCC_APB1ENR_OFS, RCC_APB2ENR_OFS};
	const uint32_t ret_val = base_addr + peri_ofs[clock_sel];

	return ret_val;
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
void CLOCK_enable_source(const t_clock_source clk_src, const t_bool enable)
{
	uint32_t rcc_cr_reg = RCC_CR_GET();
	const uint32_t clk_control[e_clk_src_max] = {RCC_CR_HSI_ON_MASK, RCC_CR_HSE_ON_MASK | RCC_CR_HSE_BYP_MASK, RCC_CR_CSS_ON_MASK,
			RCC_CR_PLL_ON_MASK, RCC_CR_PLLI2S_ON_MASK, RCC_CR_PLLSAI_ON_MASK};
	if (enable != FALSE) {
		rcc_cr_reg |= clk_control[clk_src];
	} else {
		rcc_cr_reg &= ~clk_control[clk_src];
	}
	RCC_CR_SET(rcc_cr_reg);
}

t_bool CLOCK_get_source_stat(const t_clock_source clk_src)
{
	const uint32_t rcc_cr_reg = RCC_CR_GET();
	uint32_t clk_stat = 0u;

	switch (clk_src) {
		case e_clk_hsi:
			clk_stat = HAL_FIELD_GET(rcc_cr_reg, RCC_CR_HSI_RDY_FIELD);
			break;
		case e_clk_hse:
			clk_stat = HAL_FIELD_GET(rcc_cr_reg, RCC_CR_HSE_RDY_FIELD) & HAL_FIELD_GET(rcc_cr_reg, RCC_CR_HSE_BYP_FIELD);
			break;
		case e_clk_css:
			clk_stat = HAL_FIELD_GET(rcc_cr_reg, RCC_CR_CSS_ON_FIELD);
			break;
		case e_clk_pll:
			clk_stat = HAL_FIELD_GET(rcc_cr_reg, RCC_CR_PLL_RDY_FIELD);
			break;
		case e_clk_pll_i2s:
			clk_stat = HAL_FIELD_GET(rcc_cr_reg, RCC_CR_PLLI2S_RDY_FIELD);
			break;
		case e_clk_pll_sai:
			clk_stat = HAL_FIELD_GET(rcc_cr_reg, RCC_CR_PLLSAI_RDY_FIELD);
			break;
		default:
			break;
	}

	return (clk_stat != 0u) ? TRUE : FALSE;
}


t_error_code CLOCK_set_config(const t_clock_cfgr * const p_clk_cfg)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((p_clk_cfg->clk_sw <= e_clk_sys_pll_r) &&
		(p_clk_cfg->clk_hpre <= e_clk_hpre_512) &&
		(p_clk_cfg->clk_ppre1 <= e_clk_ppre_16) &&
		(p_clk_cfg->clk_ppre2 <= e_clk_ppre_16) &&
		(p_clk_cfg->clk_rtcpre <= CLOCK_RTCPRE_MAX) &&
		(p_clk_cfg->clk_mco1 <= e_clk_sys_pll) &&
		(p_clk_cfg->clk_mco1_pre <= e_clk_mco_pre_5) &&
		(p_clk_cfg->clk_mco2 <= e_clk_sys_pll) &&
		(p_clk_cfg->clk_mco2_pre <= e_clk_mco_pre_5)) {

		uint32_t rcc_cfg_reg = 0u;
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_SW_FIELD, p_clk_cfg->clk_sw);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_HPRE_FIELD, p_clk_cfg->clk_hpre);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_PPRE1_FIELD, p_clk_cfg->clk_ppre1);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_PPRE2_FIELD, p_clk_cfg->clk_ppre2);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_RTCPRE_FIELD, p_clk_cfg->clk_rtcpre);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_MCO1_FIELD, p_clk_cfg->clk_mco1);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_MCO1_PRE_FIELD, p_clk_cfg->clk_mco1_pre);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_MCO2_FIELD, p_clk_cfg->clk_mco2);
		HAL_FIELD_SET(rcc_cfg_reg, RCC_CFGR_MCO2_PRE_FIELD, p_clk_cfg->clk_mco2_pre);
		RCC_CFGR_SET(rcc_cfg_reg);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

void CLOCK_get_config(t_clock_cfgr * const p_clk_cfg)
{
	uint32_t rcc_cfg_reg = RCC_CFGR_GET();

	p_clk_cfg->clk_sw = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_SW_FIELD);
	p_clk_cfg->clk_hpre = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_HPRE_FIELD);
	p_clk_cfg->clk_ppre1 = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_PPRE1_FIELD);
	p_clk_cfg->clk_ppre2 = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_PPRE2_FIELD);
	p_clk_cfg->clk_rtcpre = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_RTCPRE_FIELD);
	p_clk_cfg->clk_mco1 = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_MCO1_FIELD);
	p_clk_cfg->clk_mco1_pre = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_MCO1_PRE_FIELD);
	p_clk_cfg->clk_mco2 = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_MCO2_FIELD);
	p_clk_cfg->clk_mco2_pre = HAL_FIELD_GET(rcc_cfg_reg, RCC_CFGR_MCO2_PRE_FIELD);
}


void CLOCK_enable(const t_clock_peri clock_sel, const uint32_t peri_en_mask, const t_bool lpwrm_en)
{
	const uint32_t peri_base = (lpwrm_en == FALSE) ? RCC_BASE : RCC_BASE + (RCC_AHB1LPENR_OFS - RCC_AHB1ENR_OFS);
	const uint32_t peri_bridge_addr = clock_calc_peri_address(peri_base, clock_sel);

	uint32_t peri_reg_val = HAL_REG_READ(peri_bridge_addr);
	peri_reg_val |= peri_en_mask;
	HAL_REG_WRITE(peri_bridge_addr, peri_reg_val);
}

/*** EOF ***/
