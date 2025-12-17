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

#include "rcc.h"
#include "exti.h"
#include "hal_reg.h"
#include "syscfg_register.h"
#include "cortex_m4.h"
#include "gpio_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define GPIOx_AFRL_PIN_MAX	  (e_gpio_pin_max / 2)

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
static uint8_t gpio_exti_pin_mux(const t_gpio_port port_sel);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */


/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static uint8_t gpio_exti_pin_mux(const t_gpio_port port_sel)
{
	static const uint8_t exti_cfg[e_gpio_max] =
		// PA		PB		PC			PD		PE		PF		PG		  PH (Only for EXTI0..EXTI3)
		{0b0000u, 0b0001u, 0b0010u, 0b0011u, 0b0100u, 0b0101u, 0b0110u, 0b0111u};

	return exti_cfg[port_sel];
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
t_error_code GPIO_port_enable(const t_gpio_port gpio_port_sel, const uint8_t port_en, const uint8_t lpwrm_en)
{
	/** \paramrange{gpio_port_sel,e_port_a,e_port_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (gpio_port_sel < e_gpio_max) {
		// Enable the peripheral clock for GPIOA peripheral
		const t_ahb1_peri_sel peri_sel[e_gpio_max] = {e_peri_gpioa, e_peri_gpiob, e_peri_gpioc, e_peri_gpiod,
				e_peri_gpioe, e_peri_gpiof, e_peri_gpiog, e_peri_gpioh};
		RCC_enable_peri(e_peri_ahb1, peri_sel[gpio_port_sel], port_en, lpwrm_en);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_error_code GPIO_port_reset(const t_gpio_port gpio_port_sel)
{
	/** \paramrange{gpio_port_sel,e_port_a,e_port_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (gpio_port_sel < e_gpio_max) {
		// Enable the peripheral clock for GPIOA peripheral
		const t_ahb1_peri_sel peri_sel[e_gpio_max] = {e_peri_gpioa, e_peri_gpiob, e_peri_gpioc, e_peri_gpiod,
				e_peri_gpioe, e_peri_gpiof, e_peri_gpiog, e_peri_gpioh};
		RCC_reset_peri(e_peri_ahb1, peri_sel[gpio_port_sel]);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_GPIO_RegDef * const GPIO_get_port_base(const t_gpio_port gpio_port_sel)
{
	/** \paramrange{gpio_port_sel,e_port_a,e_port_max}
	 */

	const uint32_t gpio_base[e_gpio_max] = {GPIOA_BASE,GPIOB_BASE,GPIOC_BASE,GPIOD_BASE,GPIOE_BASE,GPIOF_BASE,GPIOG_BASE,GPIOH_BASE};

	t_GPIO_RegDef * const ret_base = (gpio_port_sel < e_gpio_max) ? CAST_TO(t_GPIO_RegDef * const, gpio_base[gpio_port_sel]) : NULL;

	return ret_base;
}


t_error_code GPIO_port_config(const t_gpio_handle * const p_gpio_handle, const t_gpio_pin pin_sel)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((pin_sel < e_gpio_pin_max) &&
		(p_gpio_handle->mode_sel < e_gpio_mode_max) &&
		(p_gpio_handle->speed < e_gpio_speed_max) &&
		(p_gpio_handle->pupd < e_gpio_pupd_max) &&
		(p_gpio_handle->alt_func_sel < GPIO_ALT_FUNC_SEL_MAX)) {

		// Set Mode
		p_gpio_handle->p_gpio_reg->GPIOx_MODER &= GPIOx_MODER_NMASK(pin_sel);
		p_gpio_handle->p_gpio_reg->GPIOx_MODER |= ((uint32_t)p_gpio_handle->mode_sel << GPIOx_MODER_POS(pin_sel));

		// Set open-drain / push-pull output
		if (p_gpio_handle->open_drain_en == FALSE) {
			p_gpio_handle->p_gpio_reg->GPIOx_OTYPER &= GPIOx_OTYPER_NMASK(pin_sel); // push-pull
		} else {
			p_gpio_handle->p_gpio_reg->GPIOx_OTYPER |= GPIOx_OTYPER_MASK(pin_sel); // open-drain
		}

		// Set Speed
		p_gpio_handle->p_gpio_reg->GPIOx_OSPEEDR &= GPIOx_OSPEEDR_NMASK(pin_sel);
		p_gpio_handle->p_gpio_reg->GPIOx_OSPEEDR |= (p_gpio_handle->speed << GPIOx_OSPEEDR_POS(pin_sel));

		// Set PUPD driver
		p_gpio_handle->p_gpio_reg->GPIOx_PUPDR &= GPIOx_PUPDR_NMASK(pin_sel);
		p_gpio_handle->p_gpio_reg->GPIOx_PUPDR |= (p_gpio_handle->pupd << GPIOx_PUPDR_POS(pin_sel));

		ret_stat = e_ec_no_error;
	}

	// Alternate function configuration
	if ((p_gpio_handle->mode_sel == e_gpio_mode_alt_func) && (ret_stat == e_ec_no_error)) {
		if (pin_sel < GPIOx_AFRL_PIN_MAX) {
			// GPIO Alternate Function Low Register
			p_gpio_handle->p_gpio_reg->GPIOx_AFRL &= GPIOx_AFRL_NMASK(pin_sel);
			p_gpio_handle->p_gpio_reg->GPIOx_AFRL |= (p_gpio_handle->alt_func_sel << GPIOx_AFRL_POS(pin_sel));
		} else {
			// GPIO Alternate Function High Register
			p_gpio_handle->p_gpio_reg->GPIOx_AFRH &= GPIOx_AFRH_NMASK(pin_sel);
			p_gpio_handle->p_gpio_reg->GPIOx_AFRH |= (p_gpio_handle->alt_func_sel << GPIOx_AFRH_POS(pin_sel));
		}
	}

	return ret_stat;
}

void GPIO_set_port_data(t_GPIO_RegDef * const p_gpio_reg, const uint16_t set_val)
{
	p_gpio_reg->GPIOx_ODR = set_val;
}

void GPIO_set_pin(t_GPIO_RegDef * const p_gpio_reg, const t_gpio_pin pin_sel, const uint8_t set_val)
{
	if (set_val != 0u) {
		p_gpio_reg->GPIOx_BSRR |= GPIOx_BSRR_BR_MASK(pin_sel);
	} else {
		p_gpio_reg->GPIOx_BSRR |= GPIOx_BSRR_BS_MASK(pin_sel);
	}
}

uint16_t GPIO_get_port_data(const t_GPIO_RegDef * const p_gpio_reg)
{
	return ((uint16_t)p_gpio_reg->GPIOx_IDR);
}

uint8_t GPIO_get_pin(const t_GPIO_RegDef * const p_gpio_reg, const t_gpio_pin pin_sel)
{
	const uint8_t ret_val = GPIOx_IDR_GET_PIN(GPIO_get_port_data(p_gpio_reg), pin_sel);

	return ret_val;
}

void GPIO_toggle_pin(t_GPIO_RegDef * const p_gpio_reg, const t_gpio_pin pin_sel)
{
	p_gpio_reg->GPIOx_ODR ^= GPIOx_ODR_MASK(pin_sel);
}

t_error_code GPIO_interrupt_config(const t_gpio_port port_sel, const t_gpio_pin pin_sel, const uint32_t pin_irq_prio, const t_gpio_it_trg_sel trg_sel)
{
	t_error_code ret_stat = e_ec_invalid_param;

	// GPIO PORT H is supported only by EXTI0..EXTI3
	const uint8_t exti_idx = (uint8_t)pin_sel;
	const t_bool b_exti_port_support = ((port_sel == e_gpio_h) && (exti_idx >= SYSCFG_EXTI_IN_EXTICR)) ? FALSE : TRUE;
	if ((port_sel < e_gpio_max) &&
		(pin_sel < e_gpio_pin_max) &&
		(trg_sel < e_gpio_it_trg_sel_max) &&
		(exti_idx <	SYSCFG_EXTI_TOTAL) &&
		(b_exti_port_support != FALSE))	{

		// Set GPIO EXTI path in the system configuration
		const uint8_t exti_reg_sel = (exti_idx / SYSCFG_EXTICR_NUM);

		// Enable SYSCFG clock
		RCC_enable_peri(e_peri_apb2, e_peri_syscfg, ENABLE, FALSE);
		t_SYSCFG_RegDef * const p_syscfg_reg = CAST_TO(t_SYSCFG_RegDef * const, SYSCFG_BASE);
		const uint8_t exti_data = gpio_exti_pin_mux(port_sel);
		switch (exti_reg_sel) {
			case 0u: // SYS_CFG EXTICR1 register
				p_syscfg_reg->EXTICR[exti_reg_sel] &= SYSCFG_EXTICR1_EXTIx_NMASK(exti_idx);
				p_syscfg_reg->EXTICR[exti_reg_sel] |= exti_data << SYSCFG_EXTICR1_EXTIx_POS(exti_idx);
				break;
			case 1u: // SYS_CFG EXTICR2 register
				p_syscfg_reg->EXTICR[exti_reg_sel] &= SYSCFG_EXTICR2_EXTIx_NMASK(exti_idx);
				p_syscfg_reg->EXTICR[exti_reg_sel] |= exti_data << SYSCFG_EXTICR2_EXTIx_POS(exti_idx);
				break;
			case 2u: // SYS_CFG EXTICR3 register
				p_syscfg_reg->EXTICR[exti_reg_sel] &= SYSCFG_EXTICR3_EXTIx_NMASK(exti_idx);
				p_syscfg_reg->EXTICR[exti_reg_sel] |= exti_data << SYSCFG_EXTICR3_EXTIx_POS(exti_idx);
				break;
			case 3u: // SYS_CFG EXTICR4 register
				p_syscfg_reg->EXTICR[exti_reg_sel] &= SYSCFG_EXTICR4_EXTIx_NMASK(exti_idx);
				p_syscfg_reg->EXTICR[exti_reg_sel] |= exti_data << SYSCFG_EXTICR4_EXTIx_POS(exti_idx);
				break;
			default:
				break;
		}

		// Interrupt EXTI configuration
		const t_exti_it_mode it_mode_sel = (trg_sel == e_gpio_it_trg_sel_ft) ? e_exti_it_ft :
				(trg_sel == e_gpio_it_trg_sel_rt) ? e_exti_it_rt : e_exti_it_rft;
		ret_stat = EXTI_interrupt_enable(pin_sel, it_mode_sel);

		// Set interrupt priority and enable IT in NVIC
		const uint8_t nvic_exti_irq[] = {e_irq_EXTI0, e_irq_EXTI1, e_irq_EXTI2, e_irq_EXTI3, e_irq_EXTI4, e_irq_EXTI9_5, e_irq_EXTI15_10};
		const uint32_t nvic_irq_idx = ((pin_sel >= e_gpio_pin_0) && (pin_sel < e_gpio_pin_5)) ? pin_sel :
				((pin_sel >= e_gpio_pin_5) && (pin_sel < e_gpio_pin_10)) ? (NUM_OF_ARRAY(nvic_exti_irq) - 2u) : (NUM_OF_ARRAY(nvic_exti_irq) - 1u);

		if ((ret_stat == e_ec_no_error) && (nvic_irq_idx < NUM_OF_ARRAY(nvic_exti_irq))) {
			const t_error_code it_prio_stat = CORTEX_M4_nvic_set_priority(nvic_exti_irq[nvic_irq_idx], pin_irq_prio);
			const t_error_code it_en_stat = CORTEX_M4_nvic_enable_irq(nvic_exti_irq[nvic_irq_idx], ENABLE);

			ret_stat = ((it_prio_stat == e_ec_no_error) && (it_en_stat == e_ec_no_error)) ? e_ec_no_error : e_ec_invalid_param;
		}
	}

	return ret_stat;
}

void GPIO_irq_handle(const t_gpio_pin pin_sel)
{
	EXTI_irq_handle(pin_sel);
}


/*** EOF ***/
