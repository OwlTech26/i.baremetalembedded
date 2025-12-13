/**
 * Copyright (c) 2025 OwlTech
 *
 * \file system.h
 * \brief
 * \author OwlTech
 * \date Jun 12, 2025
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/



/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
/** \name Ouput LEDs. */
/**@{*/
#define SYS_GPIO_LED_PORT 	(e_gpio_a)
#define SYS_PIN_STAT_LED 	(e_gpio_pin_5)
#define SYS_PIN_RED_LED 	(e_gpio_pin_8)
#define SYS_PIN_YEL_LED 	(e_gpio_pin_6)
#define SYS_PIN_GRN_LED 	(e_gpio_pin_7)
/**@}*/

/** \name Input buttons. */
/**@{*/
#define SYS_GPIO_BTN_PORT 	(e_gpio_c)
#define SYS_PIN_ONBOARD_BTN (e_gpio_pin_13)
/**@}*/

/** \name SPI port. */
/**@{*/
#define SYS_SPI_PERI 		(e_spi_1)
#define SYS_SPI_ALT_FUNC 	(5u)
#define SYS_SPI_GPIO_PORT 	(e_gpio_a)
#define SYS_SPI_SCK			(e_gpio_pin_5) // D13 PA5
#define SYS_SPI_MISO		(e_gpio_pin_6) // D12 PA6
#define SYS_SPI_MOSI		(e_gpio_pin_7) // D11 PA7
#define SYS_SPI_CS			(e_gpio_pin_9) // D8  PA9
/**@}*/

/** \name I2C port. */
/**@{*/
#define SYS_I2C_PERI		(e_i2c_1)
#define SYS_I2C_ALT_FUNC 	(4u)
#define SYS_I2C_GPIO_PORT 	(e_gpio_b)
#define SYS_I2C_SCL			(e_gpio_pin_8) // D15 PB8
#define SYS_I2C_SDA			(e_gpio_pin_9) // D14 PB9
#define SYS_I2C_OAR_ADDR 	(123u)
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

#endif /* SYSTEM_H_ */
/*** EOF ***/
