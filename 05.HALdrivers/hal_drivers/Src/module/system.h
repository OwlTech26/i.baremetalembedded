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

/** \name Inputs. */
/**@{*/
#define SYS_GPIO_BTN_PORT 		(e_gpio_c)
#define SYS_PIN_ONBOARD_BTN 	(e_gpio_pin_13)
#define SYS_LUX_INT_GPIO_PORT 	(e_gpio_b)
#define SYS_LUX_INT_IN			(e_gpio_pin_6) // D10 PB6
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

/** \name USART port. */
/**@{*/
#define SYS_USART_PERI		(e_usart_2)
#define SYS_USART_ALT_FUNC 	(7u)
#define SYS_USART_GPIO_PORT (e_gpio_a)
#define SYS_USART_TX		(e_gpio_pin_2) // D1 PA2
#define SYS_USART_RX		(e_gpio_pin_3) // D0 PA3
/**@}*/

/** \name Sensor Modules. */
/**@{*/
#define SYS_TSL2561_CHIP_ID 			(0x50u) //!< TSL2561T/FN/CL, rev.: 0
#define SYS_TSL2561_CFG_INTEG_INIT 		(e_tsl2561_integ_402_ms) //!<
#define SYS_TSL2561_CFG_GAIN_INIT 		(FALSE) //!<
#define SYS_TSL2561_CFG_IT_THRES_LOW 	(80u) //!<
#define SYS_TSL2561_CFG_IT_THRES_HIGH 	(500u) //!<
#define SYS_TSL2561_CFG_IT_TYPE			(e_tsl2561_intr_it_level) //!<
#define SYS_TSL2561_CFG_IT_PERS 		(8u) //!<

#define SYS_VEML6040_CFG_INTEG_INIT 	(e_veml6040_integ_320_ms) //!<
#define SYS_VEML60401_CFG_AF_INIT 		(FALSE) //!< Auto Mode.

#define SYS_DS1307_CHIP_ID 				(0x00u) //!<
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
