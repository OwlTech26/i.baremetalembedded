/**
 * Copyright (c) 2025 OwlTech
 *
 * \file gpio.h
 * \brief
 * \author OwlTech
 * \date Jun 16, 2025
 */

#ifndef GPIO_REGISTER_H_
#define GPIO_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/



/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define GPIOA_BASE 0x40020000u
#define GPIOB_BASE 0x40020400u
#define GPIOC_BASE 0x40020800u
#define GPIOD_BASE 0x40020C00u
#define GPIOE_BASE 0x40021000u
#define GPIOF_BASE 0x40021400u
#define GPIOG_BASE 0x40021800u
#define GPIOH_BASE 0x40021C00u

#define GPIOx_PORT0                 0
#define GPIOx_PORT1                 1
#define GPIOx_PORT2                 2
#define GPIOx_PORT3                 3
#define GPIOx_PORT4                 4
#define GPIOx_PORT5                 5
#define GPIOx_PORT6                 6
#define GPIOx_PORT7                 7
#define GPIOx_PORT8                 8
#define GPIOx_PORT9                 9
#define GPIOx_PORT10                10
#define GPIOx_PORT11                11
#define GPIOx_PORT12                12
#define GPIOx_PORT13                13
#define GPIOx_PORT14                14
#define GPIOx_PORT15                15

/** \name GPIOx_MODER Registers (x = A..H). */
/**@{*/
#define GPIOx_MODER_OFS					(0x00u) //!< GPIO mode register offset.
	#define GPIOx_MODER_GET(base)		(HAL_REG_READ((base + GPIOx_MODER_OFS)))
	#define GPIOx_MODER_SET(base, data)	(HAL_REG_WRITE((base + GPIOx_MODER_OFS), (uint32_t)data))
	#define GPIOx_MODER_FIELD			GPIOx_MODER
		#define GPIOx_MODER0_POS		(0u)
		#define GPIOx_MODER1_POS		(2u)
		#define GPIOx_MODER2_POS		(4u)
		#define GPIOx_MODER3_POS		(6u)
		#define GPIOx_MODER4_POS		(8u)
		#define GPIOx_MODER5_POS		(10u)
		#define GPIOx_MODER6_POS		(12u)
		#define GPIOx_MODER7_POS		(14u)
		#define GPIOx_MODER8_POS		(16u)
		#define GPIOx_MODER9_POS		(18u)
		#define GPIOx_MODER10_POS		(20u)
		#define GPIOx_MODER11_POS		(22u)
		#define GPIOx_MODER12_POS		(24u)
		#define GPIOx_MODER13_POS		(26u)
		#define GPIOx_MODER14_POS		(28u)
		#define GPIOx_MODER15_POS		(30u)
		#define GPIOx_MODER_WIDTH		(2u)
		#define GPIOx_MODER_MASK(port)	(HAL_FIELD_CREATE_PORT_MASK(GPIOx_MODER_FIELD, port))
		#define GPIOx_MODER_NMASK(port) (~(GPIOx_MODER_MASK(port)))
		#define GPIOx_MODERx_POS(pin)	((uint32_t)pin * GPIOx_MODER_WIDTH)
/**@}*/

/** \name GPIOx_AFRL Registers (x = A..H). */
/**@{*/
#define GPIOx_AFRL_OFS					(0x20u) //!< GPIO alternate function low register offset.
	#define GPIOx_AFRL_GET(base)		(HAL_REG_READ((base + GPIOx_AFRL_OFS)))
	#define GPIOx_AFRL_SET(base, data)	(HAL_REG_WRITE((base + GPIOx_AFRL_OFS), (uint32_t)data))
	#define GPIOx_AFRL_FIELD			GPIOx_AFRL
		#define GPIOx_AFRL0_POS			(0u)
		#define GPIOx_AFRL1_POS			(4u)
		#define GPIOx_AFRL2_POS			(8u)
		#define GPIOx_AFRL3_POS			(12u)
		#define GPIOx_AFRL4_POS			(16u)
		#define GPIOx_AFRL5_POS			(20u)
		#define GPIOx_AFRL6_POS			(24u)
		#define GPIOx_AFRL7_POS			(28u)
		#define GPIOx_AFRL_WIDTH		(4u)
		#define GPIOx_AFRL_MASK(port)	(HAL_FIELD_CREATE_PORT_MASK(GPIOx_AFRL_FIELD, port))
		#define GPIOx_AFRL_NMASK(port) 	(~(GPIOx_AFRL_MASK(port)))
		#define GPIOx_AFRLx_POS(pin)	(pin * GPIOx_AFRL_WIDTH)
/**@}*/

/** \name GPIOx_AFRH Registers (x = A..H). */
/**@{*/
#define GPIOx_AFRH_OFS					(0x24u) //!< GPIO alternate function high register offset.
	#define GPIOx_AFRH_GET(base)		(HAL_REG_READ((base + GPIOx_AFRH_OFS)))
	#define GPIOx_AFRH_SET(base, data)	(HAL_REG_WRITE((base + GPIOx_AFRH_OFS), (uint32_t)data))
	#define GPIOx_AFRH_FIELD			GPIOx_AFRH
		#define GPIOx_AFRH8_POS			(0u)
		#define GPIOx_AFRH9_POS			(4u)
		#define GPIOx_AFRH10_POS		(8u)
		#define GPIOx_AFRH11_POS		(12u)
		#define GPIOx_AFRH12_POS		(16u)
		#define GPIOx_AFRH13_POS		(20u)
		#define GPIOx_AFRH14_POS		(24u)
		#define GPIOx_AFRH15_POS		(28u)
		#define GPIOx_AFRH_WIDTH		(4u)
		#define GPIOx_AFRH_MASK(port)	(HAL_FIELD_CREATE_PORT_MASK(GPIOx_AFRH_FIELD, port))
		#define GPIOx_AFRH_NMASK(port) 	(~(GPIOx_AFRH_MASK(port)))
		#define GPIOx_AFRHx_POS(pin)	((pin % GPIOx_AFRHx_PIN_SEL) * GPIOx_AFRH_WIDTH)
		#define GPIOx_AFRHx_PIN_SEL		(8u)
/**@}*/

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

#endif /* GPIO_REGISTER_H_ */
/*** EOF ***/
