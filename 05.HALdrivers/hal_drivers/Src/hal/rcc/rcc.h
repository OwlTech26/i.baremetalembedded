/**
 * Copyright (c) 2025 OwlTech
 *
 * \file clock.h
 * \brief
 * \author OwlTech
 * \date Nov 04, 2025
 */

#ifndef RCC_H_
#define RCC_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "common_def.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define RCC_CLOCK_FREQ_TO_KHZ		1000u
#define RCC_CLOCK_FREQ_TO_MHZ		1000000u


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
	e_clk_sys_hsi 	= 0u,
	e_clk_sys_hse 	= 1u,
	e_clk_sys_pll_p = 2u,
	e_clk_sys_pll_r = 3u,
	e_clk_sys_max 	= 4u
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
	e_clk_hpre_512 	= 15u,
	e_clk_hpre_max 	= 16u
} t_clock_cfg_hpre;

/** \brief PPRE APB prescaler configuration. */
typedef enum {
	e_clk_ppre_0 	= 0u,
	e_clk_ppre_2 	= 4u,
	e_clk_ppre_4   	= 5u,
	e_clk_ppre_8   	= 6u,
	e_clk_ppre_16  	= 7u,
	e_clk_ppre_max 	= 8u
} t_clock_cfg_ppre;

/** \brief Microcontroller clock output. */
typedef enum {
	e_clk_mco_hsi = 0u, //!< HSI clock selected.
	e_clk_mco_lse = 1u, //!< LSE oscillator selected
	e_clk_mco_hse = 2u, //!< HSE oscillator selected
	e_clk_sys_pll = 3u, //!< PLL clock selected.
	e_clk_mco_max = 4u
} t_clock_cfg_mco;

/** \brief HPRE AHB prescaler configuration. */
typedef enum {
	e_clk_mco_pre_0 	= 0u,
	e_clk_mco_pre_2 	= 4u,
	e_clk_mco_pre_3   	= 5u,
	e_clk_mco_pre_4   	= 6u,
	e_clk_mco_pre_5  	= 7u,
	e_clk_mco_pre_max  	= 8u
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

typedef enum {
	e_peri_gpioa		= 0u,
	e_peri_gpiob		= 1u,
	e_peri_gpioc		= 2u,
	e_peri_gpiod		= 3u,
	e_peri_gpioe		= 4u,
	e_peri_gpiof		= 5u,
	e_peri_gpiog		= 6u,
	e_peri_gpioh		= 7u,
	e_peri_crc			= 12u,
	e_peri_bpk_sram		= 18u,
	e_peri_dma1			= 21u,
	e_peri_dma2			= 22u,
	e_peri_otghs		= 29u,
	e_peri_otghs_ulp	= 30u
} t_ahb1_peri_sel;

typedef enum {
	e_peri_tim2			= 0u,
	e_peri_tim3			= 1u,
	e_peri_tim4			= 2u,
	e_peri_tim5			= 3u,
	e_peri_tim6			= 4u,
	e_peri_tim7			= 5u,
	e_peri_tim12		= 6u,
	e_peri_tim13		= 7u,
	e_peri_tim14		= 8u,
	e_peri_wwdg			= 11u,
	e_peri_spi2			= 14u,
	e_peri_spi3			= 15u,
	e_peri_spdifrx		= 16u,
	e_peri_usart2		= 17u,
	e_peri_usart3		= 18u,
	e_peri_usart4		= 19u,
	e_peri_usart5		= 20u,
	e_peri_i2c1			= 21u,
	e_peri_i2c2			= 22u,
	e_peri_i2c3			= 23u,
	e_peri_fmpi2c1		= 24u,
	e_peri_can1			= 25u,
	e_peri_can2			= 26u,
	e_peri_cec			= 27u,
	e_peri_pwr			= 28u,
	e_peri_dac			= 29u
} t_apb1_peri_sel;

typedef enum {
	e_peri_tim1			= 0u,
	e_peri_tim8			= 1u,
	e_peri_usart1		= 4u,
	e_peri_usart6		= 5u,
	e_peri_adc1			= 8u,
	e_peri_adc2			= 9u,
	e_peri_adc3			= 10u,
	e_peri_sdio			= 11u,
	e_peri_spi1			= 12u,
	e_peri_spi4			= 13u,
	e_peri_syscfg		= 14u,
	e_peri_tim9			= 16u,
	e_peri_tim10		= 17u,
	e_peri_tim11		= 18u,
	e_peri_sai1			= 22u,
	e_peri_sai2			= 23u
} t_apb2_peri_sel;

typedef enum {
	e_clk_rtc_none = 0u,
	e_clk_rtc_lse  = 1u,
	e_clk_rtc_lsi  = 2u,
	e_clk_rtc_hse  = 3u,
	e_clk_rtc_max  = 4u
} t_clock_rtc_src;


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
void RCC_enable_source(const t_clock_source clk_src, const t_bool enable);

t_bool RCC_get_source_stat(const t_clock_source clk_src);

t_bool RCC_get_source_stat(const t_clock_source clk_src);

/** \brief System clock configuration setter.
 *  \param[in] p_clk_cfg Clock configuration parameters.
 *
 *  \return Configuration status.
 *  \retval e_ec_no_error Success.
 *  \retval e_ec_invalid_param Invalid parameter.
 */
t_error_code RCC_set_config(const t_clock_cfgr * const p_clk_cfg);

/** \brief System clock configuration getter.
 *  \param[out] p_clk_cfg Clock configuration parameters.
 */
void RCC_get_config(t_clock_cfgr * const p_clk_cfg);

/** \brief Enables the periphery clock(s) for the selected bridge.
 *  \param[in] clock_sel Selected bridge clock.
 *  \param[in] peri_bf_pos Periphery bitfield position.
 *  \param[in] clock_en Clock Enable/Disable..
 *  \param[in] lpwrm_en Low Power Mode enable.
 */
void RCC_enable_peri(const t_clock_peri clock_sel, const uint8_t peri_bf_pos, const uint8_t clock_en, const uint8_t lpwrm_en);

/** \brief Enables the periphery clock(s) for the selected bridge.
 *  \param[in] clock_sel Selected bridge clock.
 *  \param[in] peri_bf_pos Periphery bitfield position.
 */
void RCC_reset_peri(const t_clock_peri clock_sel, const uint8_t peri_bf_pos);

/** \brief Enables the internal low-speed oscillator.
 *  \param[in] lsion_en LSION Enable/Disable.
 */
void RCC_lsion_enable(const t_bool lsion_en);

void RCC_backup_domain_reset(void);

void RCC_rtc_clock_sel(t_clock_rtc_src rtc_clk_sel);

void RCC_rtc_enable(const t_bool rtc_en);

uint32_t RCC_get_peri_clock_freq(const t_clock_peri peri_clk_sel);

#endif /* RCC_H_ */
/*** EOF ***/
