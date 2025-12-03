/**
 * Copyright (c) 2025 OwlTech
 *
 * \file gpio.h
 * \brief General Purpose Input-Output STM32F446xx MCU specific register header file.
 * \author OwlTech
 * \date Nov 3, 2025
 */

#ifndef GPIO_REGISTER_H_
#define GPIO_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/



/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define GPIO_ALT_FUNC_SEL_MAX (16u)

#define GPIOA_BASE 0x40020000u
#define GPIOB_BASE 0x40020400u
#define GPIOC_BASE 0x40020800u
#define GPIOD_BASE 0x40020C00u
#define GPIOE_BASE 0x40021000u
#define GPIOF_BASE 0x40021400u
#define GPIOG_BASE 0x40021800u
#define GPIOH_BASE 0x40021C00u

/** \name GPIO port mode register (x = A..H). */
/**@{*/
#define GPIOx_MODER_OFS							(0x00u)
	#define GPIOx_MODER_GET(base)				(HAL_REG_READ((base + GPIOx_MODER_OFS)))
	#define GPIOx_MODER_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_MODER_OFS), (uint32_t)data))
		#define GPIOx_MODER_WIDTH				(2u)
		#define GPIOx_MODER_POS(pin)			(pin * GPIOx_MODER_WIDTH)
		#define GPIOx_MODER_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_MODER_POS(pin), GPIOx_MODER_WIDTH))
		#define GPIOx_MODER_NMASK(pin) 			(~(GPIOx_MODER_MASK(pin)))
/**@}*/

/** \name GPIO port output type register (x = A..H). */
/**@{*/
#define GPIOx_OTYPER_OFS							(0x04u)
	#define GPIOx_OTYPER_GET(base)					(HAL_REG_READ((base + GPIOx_OTYPER_OFS)))
	#define GPIOx_OTYPER_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_OTYPER_OFS), (uint32_t)data))
		#define GPIOx_OTYPER_WIDTH					(1u)
		#define GPIOx_OTYPER_POS(pin)				(pin * GPIOx_OTYPER_WIDTH)
		#define GPIOx_OTYPER_MASK(pin)				(HAL_BIT_CREATE_MASK(GPIOx_OTYPER_POS(pin), GPIOx_OTYPER_WIDTH))
		#define GPIOx_OTYPER_NMASK(pin) 			(~(GPIOx_OTYPER_MASK(pin)))
/**@}*/

/** \name GPIO port output speed register (x = A..H). */
/**@{*/
#define GPIOx_OSPEEDR_OFS							(0x08u)
	#define GPIOx_OSPEEDR_GET(base)					(HAL_REG_READ((base + GPIOx_OSPEEDR_OFS)))
	#define GPIOx_OSPEEDR_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_OSPEEDR_OFS), (uint32_t)data))
		#define GPIOx_OSPEEDR_WIDTH					(2u)
		#define GPIOx_OSPEEDR_POS(pin)				(pin * GPIOx_OSPEEDR_WIDTH)
		#define GPIOx_OSPEEDR_MASK(pin)				(HAL_BIT_CREATE_MASK(GPIOx_OSPEEDR_POS(pin), GPIOx_OSPEEDR_WIDTH))
		#define GPIOx_OSPEEDR_NMASK(pin) 			(~(GPIOx_OSPEEDR_MASK(pin)))
/**@}*/

/** \name GPIO port pull-up/pull-down register (x = A..H). */
#define GPIOx_PUPDR_OFS							(0x0Cu)
	#define GPIOx_PUPDR_GET(base)				(HAL_REG_READ((base + GPIOx_PUPDR_OFS)))
	#define GPIOx_PUPDR_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_PUPDR_OFS), (uint32_t)data))
		#define GPIOx_PUPDR_WIDTH				(2u)
		#define GPIOx_PUPDR_POS(pin)			(pin * GPIOx_PUPDR_WIDTH)
		#define GPIOx_PUPDR_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_PUPDR_POS(pin), GPIOx_PUPDR_WIDTH))
		#define GPIOx_PUPDR_NMASK(pin) 			(~(GPIOx_PUPDR_MASK(pin)))
/**@}*/

/** \name GPIO port input data register (x = A..H). */
/**@{*/
#define GPIOx_IDR_OFS							(0x10u)
	#define GPIOx_IDR_GET(base)					(HAL_REG_READ((base + GPIOx_IDR_OFS)))
	#define GPIOx_IDR_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_IDR_OFS), (uint32_t)data))
		#define GPIOx_IDR_WIDTH					(1u)
		#define GPIOx_IDR_POS(pin)				(pin * GPIOx_IDR_WIDTH)
		#define GPIOx_IDR_MASK(pin)				(HAL_BIT_CREATE_MASK(GPIOx_IDR_POS(pin), GPIOx_IDR_WIDTH))
		#define GPIOx_IDR_NMASK(pin) 			(~(GPIOx_IDR_MASK(pin)))
		#define GPIOx_IDR_GET_PIN(data, pin)	(HAL_BIT_GET(data, pin, GPIOx_IDR_WIDTH))
/**@}*/

/** \name GPIO port output data register (x = A..H). */
/**@{*/
#define GPIOx_ODR_OFS							(0x14u)
	#define GPIOx_ODR_GET(base)					(HAL_REG_READ((base + GPIOx_ODR_OFS)))
	#define GPIOx_ODR_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_ODR_OFS), (uint32_t)data))
		#define GPIOx_ODR_WIDTH					(1u)
		#define GPIOx_ODR_POS(pin)				(pin * GPIOx_ODR_WIDTH)
		#define GPIOx_ODR_MASK(pin)				(HAL_BIT_CREATE_MASK(GPIOx_ODR_POS(pin), GPIOx_ODR_WIDTH))
		#define GPIOx_ODR_NMASK(pin) 			(~(GPIOx_ODR_MASK(pin)))
/**@}*/

/** \name GPIO port bit set/reset register (x = A..H). */
/**@{*/
#define GPIOx_BSRR_OFS							(0x18u)
	#define GPIOx_BSRR_GET(base)				(HAL_REG_READ((base + GPIOx_BSRR_OFS)))
	#define GPIOx_BSRR_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_BSRR_OFS), (uint32_t)data))
		#define GPIOx_BSRR_WIDTH				(1u)
		#define GPIOx_BSSR_BS_POS(pin)			(pin * GPIOx_BSRR_WIDTH)
		#define GPIOx_BSSR_BR_POS(pin)			((pin * GPIOx_BSRR_WIDTH) + 16u)
		#define GPIOx_BSRR_BR_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_BSSR_BS_POS(pin), GPIOx_BSRR_WIDTH))
		#define GPIOx_BSRR_BS_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_BSSR_BR_POS(pin), GPIOx_BSRR_WIDTH))
/**@}*/

/** \name GPIO port configuration lock register (x = A..H). */
/**@{*/
#define GPIOx_LCKR_OFS							(0x1Cu)
	#define GPIOx_LCKR_GET(base)				(HAL_REG_READ((base + GPIOx_LCKR_OFS)))
	#define GPIOx_LCKR_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_LCKR_OFS), (uint32_t)data))
		#define GPIOx_LCKR_WIDTH				(1u)
		#define GPIOx_LCKR_POS(pin)				(pin * GPIOx_LCKR_WIDTH)
		#define GPIOx_LCKR_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_LCKR_POS(pin), GPIOx_LCKR_WIDTH))
		#define GPIOx_LCKR_NMASK(pin) 			(~(GPIOx_LCKR_MASK(pin)))
/**@}*/

/** \name GPIOx_AFRL Registers (x = A..H). */
/**@{*/
#define GPIOx_AFRL_OFS							(0x20u)
	#define GPIOx_AFRL_GET(base)				(HAL_REG_READ((base + GPIOx_AFRL_OFS)))
	#define GPIOx_AFRL_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_AFRL_OFS), (uint32_t)data))
		#define GPIOx_AFRL_WIDTH				(4u)
		#define GPIOx_AFRL_POS(pin)				((pin % 8) * GPIOx_AFRL_WIDTH)
		#define GPIOx_AFRL_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_AFRL_POS(pin), pin))
		#define GPIOx_AFRL_NMASK(pin) 			(~(GPIOx_AFRL_MASK(pin)))
/**@}*/

/** \name GPIOx_AFRH Registers (x = A..H). */
/**@{*/
#define GPIOx_AFRH_OFS							(0x24u)
	#define GPIOx_AFRH_GET(base)				(HAL_REG_READ((base + GPIOx_AFRH_OFS)))
	#define GPIOx_AFRH_SET(base, data)			(HAL_REG_WRITE((base + GPIOx_AFRH_OFS), (uint32_t)data))
		#define GPIOx_AFRH_POS(pin)				((pin % 8u) * GPIOx_AFRH_WIDTH)
		#define GPIOx_AFRH_WIDTH				(4u)
		#define GPIOx_AFRH_MASK(pin)			(HAL_BIT_CREATE_MASK(GPIOx_AFRH_POS(pin), pin))
		#define GPIOx_AFRH_NMASK(pin) 			(~(GPIOx_AFRH_MASK(pin)))
/**@}*/

/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief  */


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

#endif /* GPIO_REGISTER_H_ */
/*** EOF ***/
