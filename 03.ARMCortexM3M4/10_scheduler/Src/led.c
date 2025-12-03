/*
 * led.c
 *
 *  Created on: Dec 20, 2023
 *      Author: bagolyzsolt
 */

#include <stdint.h>
#include "led.h"

/** Periphery Address Base */
#define RCC_BASE			0x40023800u
#define RCC_AHB1ENR_OFS		0x30u
#define GPIO_A_BASE			0x40020000u // PA5
#define GPIO_MODE_OFS		0x0u
#define GPIO_OUT_DATA_OFS	0x14u

void LED_init(void)
{
	uint32_t * const p_rcc_ahb1_reg = (uint32_t * const)(RCC_BASE + RCC_AHB1ENR_OFS);
	*p_rcc_ahb1_reg |= ( 1u << 0u);

	// Configure User LED as GPIO output
	uint32_t * const p_gpio_mode_reg = (uint32_t * const)(GPIO_A_BASE + GPIO_MODE_OFS);
	*p_gpio_mode_reg |= (1u << (2u * LED_USR));

	LED_off(LED_USR);
}

void LED_on(const uint32_t led_no)
{
	uint32_t * const p_gpio_data_reg = (uint32_t * const)(GPIO_A_BASE + GPIO_OUT_DATA_OFS);
	*p_gpio_data_reg |= ( 1u << led_no);
}

void LED_off(const uint32_t led_no)
{
	uint32_t * const p_gpio_data_reg = (uint32_t * const)(GPIO_A_BASE + GPIO_OUT_DATA_OFS);
	*p_gpio_data_reg &= ~(1u << led_no);
}

void LED_delay(const uint32_t count)
{
	for(uint32_t i=0u ; i<count; i++);
}
