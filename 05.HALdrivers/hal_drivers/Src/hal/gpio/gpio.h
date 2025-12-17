/**
 * Copyright (c) 2025 OwlTech
 *
 * \file gpio.h
 * \brief
 * \author OwlTech
 * \date Nov 3, 2025
 */

#ifndef GPIO_H_
#define GPIO_H_

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
typedef struct {
	volatile uint32_t GPIOx_MODER;
	volatile uint32_t GPIOx_OTYPER;
	volatile uint32_t GPIOx_OSPEEDR;
	volatile uint32_t GPIOx_PUPDR;
	volatile const uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_LCKR;
	volatile uint32_t GPIOx_AFRL;
	volatile uint32_t GPIOx_AFRH;
} t_GPIO_RegDef;

/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef enum {
	e_gpio_a = 0u,
	e_gpio_b = 1u,
	e_gpio_c = 2u,
	e_gpio_d = 3u,
	e_gpio_e = 4u,
	e_gpio_f = 5u,
	e_gpio_g = 6u,
	e_gpio_h = 7u,
	e_gpio_max = 8u
} t_gpio_port;

typedef enum {
	e_gpio_pin_0 = 0u,
	e_gpio_pin_1 = 1u,
	e_gpio_pin_2 = 2u,
	e_gpio_pin_3 = 3u,
	e_gpio_pin_4 = 4u,
	e_gpio_pin_5 = 5u,
	e_gpio_pin_6 = 6u,
	e_gpio_pin_7 = 7u,
	e_gpio_pin_8 = 8u,
	e_gpio_pin_9 = 9u,
	e_gpio_pin_10 = 10u,
	e_gpio_pin_11 = 11u,
	e_gpio_pin_12 = 12u,
	e_gpio_pin_13 = 13u,
	e_gpio_pin_14 = 14u,
	e_gpio_pin_15 = 15u,
	e_gpio_pin_max = 16u
} t_gpio_pin;

typedef enum {
	e_gpio_mode_input 		= 0u,
	e_gpio_mode_output 		= 1u,
	e_gpio_mode_alt_func 	= 2u,
	e_gpio_mode_analog 		= 3u,
	e_gpio_mode_max 		= 4u
} t_gpio_mode;

typedef enum {
	e_gpio_speed_low 	= 0u,
	e_gpio_speed_medium = 1u,
	e_gpio_speed_fast 	= 2u,
	e_gpio_speed_high 	= 3u,
	e_gpio_speed_max 	= 4u
} t_gpio_speed;

typedef enum {
	e_gpio_pupd_no	 	= 0u,
	e_gpio_pupd_pu	 	= 1u,
	e_gpio_pupd_pd	 	= 2u,
	e_gpio_pupd_max 	= 3u
} t_gpio_pupd;

typedef enum {
	e_gpio_it_trg_sel_ft 		= 0u,
	e_gpio_it_trg_sel_rt 		= 1u,
	e_gpio_it_trg_sel_rft 		= 2u,
	e_gpio_it_trg_sel_max 		= 3u
} t_gpio_it_trg_sel;

typedef struct {
	t_GPIO_RegDef * const p_gpio_reg;
	t_gpio_mode 		  mode_sel;
	t_bool 			  	  open_drain_en;
	t_gpio_speed 		  speed;
	t_gpio_pupd			  pupd;
	uint8_t 			  alt_func_sel;
} t_gpio_handle;


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
t_error_code GPIO_port_enable(const t_gpio_port gpio_port_sel, const uint8_t port_en, const uint8_t lpwrm_en);

t_error_code GPIO_port_reset(const t_gpio_port gpio_port_sel);

/** \brief GPIO port initialization.
 *
 * \param[in] gpio_port_sel GPIO port selector.
 *
 * \return Pointer to the selected memory-mapped GPIO port.
 */
t_GPIO_RegDef * const GPIO_get_port_base(const t_gpio_port gpio_port_sel);


/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
t_error_code GPIO_port_config(const t_gpio_handle * const p_gpio_handle, const t_gpio_pin pin_sel);

void GPIO_set_port_data(t_GPIO_RegDef * const p_gpio_reg, const uint16_t set_val);

void GPIO_set_pin(t_GPIO_RegDef * const p_gpio_reg, const t_gpio_pin pin_sel, const uint8_t set_val);

uint16_t GPIO_get_port_data(const t_GPIO_RegDef * const p_gpio_reg);

uint8_t GPIO_get_pin(const t_GPIO_RegDef * const p_gpio_reg, const t_gpio_pin pin_sel);

void GPIO_toggle_pin(t_GPIO_RegDef * const p_gpio_reg, const t_gpio_pin pin_sel);

t_error_code GPIO_interrupt_config(const t_gpio_port port_sel, const t_gpio_pin pin_sel, const uint32_t pin_irq_prio, const t_gpio_it_trg_sel trg_sel);

void GPIO_irq_handle(const t_gpio_pin pin_sel);

#endif /* GPIO_H_ */
/*** EOF ***/
