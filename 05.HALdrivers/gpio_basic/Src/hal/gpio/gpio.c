/**
 * Copyright (c) 2025 OwlTech
 *
 * \file gpio.c
 * \brief
 * \author OwlTech
 * \date Jun 11, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "gpio.h"
#include "hal_reg.h"
#include "gpio_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define GPIO_BASE_DIST (GPIOB_BASE - GPIOA_BASE)
#define GPIO_NUM_OF_PINS_MAX (16u)
#define GPIO_ALT_FUNC_SEL_MAX (16u)


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

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
t_error_code GPIO_configure_port(const t_gpio_port_cfg * const p_gpio_cfg, const t_bool update_alt_func)
{
	t_error_code ret_stat = e_ec_invalid_param;

	const uint32_t gpio_port_sel = p_gpio_cfg->port_sel;
	const uint32_t gpio_pin_sel = p_gpio_cfg->pin_sel;
	const uint32_t gpio_port_base = GPIOA_BASE + (gpio_port_sel * GPIO_BASE_DIST);
	if ((gpio_port_sel < (uint32_t)e_port_max) &&
		(gpio_pin_sel < (uint32_t)GPIO_NUM_OF_PINS_MAX) &&
		(p_gpio_cfg->mode_sel < e_mode_max) &&
		(p_gpio_cfg->alt_func_sel < GPIO_ALT_FUNC_SEL_MAX)) {
		uint32_t gpio_mode_reg = GPIOx_MODER_GET(gpio_port_base);
		const uint32_t gpio_pin_pos = GPIOx_MODERx_POS(gpio_pin_sel);
		HAL_BIT_SET(gpio_mode_reg, gpio_pin_pos, GPIOx_MODER_WIDTH, p_gpio_cfg->mode_sel);
		GPIOx_MODER_SET(gpio_port_base, gpio_mode_reg);

		ret_stat = e_ec_no_error;
	}

	if ((update_alt_func != FALSE) && (ret_stat == e_ec_no_error)){
		if (gpio_pin_sel < GPIOx_AFRHx_PIN_SEL) {
			// GPIO Alternate Function Low Register
			uint32_t gpio_afrl_reg = GPIOx_AFRL_GET(gpio_port_base);
			const uint32_t gpio_afrl_pos = GPIOx_AFRLx_POS(gpio_pin_sel);
			HAL_BIT_SET(gpio_afrl_reg, gpio_afrl_pos, GPIOx_AFRL_WIDTH, p_gpio_cfg->alt_func_sel);
			GPIOx_AFRL_SET(gpio_port_base, gpio_afrl_reg);
		} else {
			// GPIO Alternate Function High Register
			uint32_t gpio_afrh_reg = GPIOx_AFRH_GET(gpio_port_base);
			const uint32_t gpio_afrh_pos = GPIOx_AFRHx_POS(gpio_pin_sel);
			HAL_BIT_SET(gpio_afrh_reg, gpio_afrh_pos, GPIOx_AFRH_WIDTH, p_gpio_cfg->alt_func_sel);
			GPIOx_AFRH_SET(gpio_port_base, gpio_afrh_reg);
		}
	}

	return ret_stat;
}


/*** EOF ***/
