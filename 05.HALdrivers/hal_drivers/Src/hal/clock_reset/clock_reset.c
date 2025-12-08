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
#include "clock_reset.h"

#include "common_def.h"
#include "hal_reg.h"
#include "rcc_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define RCC	(CAST_TO(t_RCC_RegDef * const, RCC_BASE))

#define AHB1_PERI_RESET(bf)		do{ (RCC->AHB1RSTR |= (1u << bf)); (RCC->AHB1RSTR &= ~(1u << bf)); }while(0)
#define AHB2_PERI_RESET(bf)		do{ (RCC->AHB2RSTR |= (1u << bf)); (RCC->AHB1RSTR &= ~(1u << bf)); }while(0)
#define AHB3_PERI_RESET(bf)		do{ (RCC->AHB3RSTR |= (1u << bf)); (RCC->AHB1RSTR &= ~(1u << bf)); }while(0)
#define APB1_PERI_RESET(bf)		do{ (RCC->APB1RSTR |= (1u << bf)); (RCC->APB1RSTR &= ~(1u << bf)); }while(0)
#define APB2_PERI_RESET(bf)		do{ (RCC->APB2RSTR |= (1u << bf)); (RCC->APB2RSTR &= ~(1u << bf)); }while(0)

#define CLOCK_RTCPRE_MAX (31u)


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t      	  RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t      RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t      RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t      RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t      RESERVED4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t      RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t      RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
	volatile uint32_t CKGATENR;
	volatile uint32_t DCKCFGR2;
} t_RCC_RegDef;



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
static uint32_t clock_reset_calc_peri_address(const uint32_t base_addr, const t_clock_peri clock_sel);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/


/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
static uint32_t clock_reset_calc_peri_address(const uint32_t base_addr, const t_clock_peri clock_sel)
{
	const uint8_t peri_ofs[e_peri_max] = {RCC_AHB1ENR_OFS, RCC_AHB2ENR_OFS, RCC_AHB3ENR_OFS, RCC_APB1ENR_OFS, RCC_APB2ENR_OFS};
	const uint32_t ret_val = base_addr + peri_ofs[clock_sel];

	return ret_val;
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
void CLOCK_RESET_enable_source(const t_clock_source clk_src, const t_bool enable)
{
	const uint32_t clk_control[e_clk_src_max] = {RCC_CR_HSI_ON_MASK, RCC_CR_HSE_ON_MASK | RCC_CR_HSE_BYP_MASK, RCC_CR_CSS_ON_MASK,
			RCC_CR_PLL_ON_MASK, RCC_CR_PLLI2S_ON_MASK, RCC_CR_PLLSAI_ON_MASK};

	if (enable != FALSE) {
		RCC->CR |= clk_control[clk_src];
	} else {
		RCC->CR &= ~clk_control[clk_src];
	}
}

t_bool CLOCK_RESET_get_source_stat(const t_clock_source clk_src)
{
	const uint32_t rcc_cr_reg = RCC_CR_GET();
	uint32_t clk_stat = 0u;

	switch (clk_src) {
		case e_clk_hsi:
			clk_stat = HAL_BIT_GET(rcc_cr_reg, RCC_CR_HSI_ON_POS, RCC_CR_HSI_ON_WIDTH);
			break;
		case e_clk_hse:
			clk_stat = HAL_BIT_GET(rcc_cr_reg, RCC_CR_HSE_RDY_POS, RCC_CR_HSI_ON_WIDTH) &
				HAL_BIT_GET(rcc_cr_reg, RCC_CR_HSE_BYP_POS, RCC_CR_HSE_BYP_WIDTH);
			break;
		case e_clk_css:
			clk_stat = HAL_BIT_GET(rcc_cr_reg, RCC_CR_CSS_ON_POS, RCC_CR_CSS_ON_WIDTH);
			break;
		case e_clk_pll:
			clk_stat = HAL_BIT_GET(rcc_cr_reg, RCC_CR_PLL_RDY_POS, RCC_CR_PLL_RDY_WIDTH);
			break;
		case e_clk_pll_i2s:
			clk_stat = HAL_BIT_GET(rcc_cr_reg, RCC_CR_PLLI2S_RDY_POS, RCC_CR_PLLI2S_RDY_WIDTH);
			break;
		case e_clk_pll_sai:
			clk_stat = HAL_BIT_GET(rcc_cr_reg, RCC_CR_PLLSAI_RDY_POS, RCC_CR_PLLSAI_RDY_WIDTH);
			break;
		default:
			break;
	}

	return (clk_stat != 0u) ? TRUE : FALSE;
}


t_error_code CLOCK_RESET_set_config(const t_clock_cfgr * const p_clk_cfg)
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
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_SW_POS, RCC_CFGR_SW_WIDTH, p_clk_cfg->clk_sw);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_HPRE_POS, RCC_CFGR_HPRE_WIDTH, p_clk_cfg->clk_hpre);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_PPRE1_POS, RCC_CFGR_PPRE1_WIDTH, p_clk_cfg->clk_ppre1);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_PPRE2_POS, RCC_CFGR_PPRE2_WIDTH, p_clk_cfg->clk_ppre2);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_RTCPRE_POS, RCC_CFGR_RTCPRE_WIDTH, p_clk_cfg->clk_rtcpre);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_MCO1_POS, RCC_CFGR_MCO1_WIDTH, p_clk_cfg->clk_mco1);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_MCO1_PRE_POS, RCC_CFGR_MCO1_PRE_WIDTH, p_clk_cfg->clk_mco1_pre);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_MCO2_POS, RCC_CFGR_MCO2_WIDTH, p_clk_cfg->clk_mco2);
		HAL_BIT_SET(rcc_cfg_reg, RCC_CFGR_MCO2_PRE_POS, RCC_CFGR_MCO2_PRE_WIDTH, p_clk_cfg->clk_mco2_pre);
		RCC_CFGR_SET(rcc_cfg_reg);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

void CLOCK_RESET_get_config(t_clock_cfgr * const p_clk_cfg)
{
	const uint32_t rcc_cfg_reg = RCC_CFGR_GET();

	p_clk_cfg->clk_sw = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_SW_POS, RCC_CFGR_SW_WIDTH);
	p_clk_cfg->clk_hpre = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_HPRE_POS, RCC_CFGR_HPRE_WIDTH);
	p_clk_cfg->clk_ppre1 = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_PPRE1_POS, RCC_CFGR_PPRE1_WIDTH);
	p_clk_cfg->clk_ppre2 = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_PPRE2_POS, RCC_CFGR_PPRE2_WIDTH);
	p_clk_cfg->clk_rtcpre = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_RTCPRE_POS, RCC_CFGR_RTCPRE_WIDTH);
	p_clk_cfg->clk_mco1 = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_MCO1_POS, RCC_CFGR_MCO1_WIDTH);
	p_clk_cfg->clk_mco1_pre = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_MCO1_PRE_POS, RCC_CFGR_MCO1_PRE_WIDTH);
	p_clk_cfg->clk_mco2 = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_MCO2_POS, RCC_CFGR_MCO2_WIDTH);
	p_clk_cfg->clk_mco2_pre = HAL_BIT_GET(rcc_cfg_reg, RCC_CFGR_MCO2_PRE_POS, RCC_CFGR_MCO2_PRE_WIDTH);
}


void CLOCK_RESET_enable_peri(const t_clock_peri clock_sel,  const uint8_t peri_bf_pos, const uint8_t clock_en, const uint8_t lpwrm_en)
{
	const uint32_t peri_base = (lpwrm_en == DISABLE) ? RCC_BASE : RCC_BASE + (RCC_AHB1LPENR_OFS - RCC_AHB1ENR_OFS);
	const uint32_t peri_bridge_addr = clock_reset_calc_peri_address(peri_base, clock_sel);

	const uint32_t peri_en_mask = RCC_AHB1ENR_MASK(peri_bf_pos);
	uint32_t peri_reg_val = HAL_REG_READ(peri_bridge_addr);
	if (clock_en == ENABLE) {
		peri_reg_val |= peri_en_mask;
	} else {
		peri_reg_val &= ~peri_en_mask;
	}
	HAL_REG_WRITE(peri_bridge_addr, peri_reg_val);
}

void CLOCK_RESET_reset_peri(const t_clock_peri clock_sel, const uint8_t peri_bf_pos)
{
	switch (clock_sel) {
		case e_peri_ahb1:
			AHB1_PERI_RESET(peri_bf_pos);
			break;
		case e_peri_ahb2:
			AHB2_PERI_RESET(peri_bf_pos);
			break;
		case e_peri_ahb3:
			AHB3_PERI_RESET(peri_bf_pos);
			break;
		case e_peri_apb1:
			APB1_PERI_RESET(peri_bf_pos);
			break;
		case e_peri_apb2:
			APB2_PERI_RESET(peri_bf_pos);
			break;
		default:
			// NOP
			break;
	}
}

void CLOCK_RESET_lsion_enable(const t_bool lsion_en)
{
	uint32_t rcc_csr_reg = RCC_CSR_GET();
	if (lsion_en != FALSE) {
		rcc_csr_reg |= RCC_CSR_LSION_MASK;
	} else {
		rcc_csr_reg &= RCC_CSR_LSION_NMASK;
	}
	RCC_CSR_SET(rcc_csr_reg);

	while ((RCC_CSR_GET() & RCC_CSR_LSIRDY_MASK) == 0u);
}

void CLOCK_RESET_backup_domain_reset(void)
{
	uint32_t rcc_bdcr_reg = RCC_BDCR_GET();
	rcc_bdcr_reg |= RCC_BDCR_BDRST_MASK; // Force reset
	RCC_BDCR_SET(rcc_bdcr_reg);
	rcc_bdcr_reg &= RCC_BDCR_BDRST_NMASK; // Release reset
	RCC_BDCR_SET(rcc_bdcr_reg);
}

void CLOCK_RESET_rtc_clock_sel(t_clock_rtc_src rtc_clk_sel)
{
	uint32_t rcc_bdcr_reg = RCC_BDCR_GET();
	rcc_bdcr_reg &= RCC_BDCR_RTCSEL_NMASK;
	rcc_bdcr_reg |= ((uint32_t)rtc_clk_sel << RCC_BDCR_RTCSEL_POS);
	RCC_BDCR_SET(rcc_bdcr_reg);
}

void CLOCK_RESET_rtc_enable(const t_bool rtc_en)
{
	uint32_t rcc_bdcr_reg = RCC_BDCR_GET();
	if (rtc_en != FALSE) {
		rcc_bdcr_reg |= RCC_BDCR_RTCEN_MASK;
	} else {
		rcc_bdcr_reg &= RCC_BDCR_RTCEN_NMASK;
	}
	RCC_BDCR_SET(rcc_bdcr_reg);
}

/*** EOF ***/
