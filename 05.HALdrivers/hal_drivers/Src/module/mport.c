/**
 * Copyright (c) 2025 OwlTech
 *
 * \file mport.c
 * \brief
 * \author OwlTech
 * \date Nov 27, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "mport.h"

#include "gpio.h"
#include "spi.h"
#include "i2c.h"
#include "system.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define MPORT_ERR_STAT_GPIO_EN		(1u << 0u)
#define MPORT_ERR_STAT_GPIO_CFG		(1u << 1u)
#define MPORT_ERR_STAT_SPI_EN		(1u << 2u)
#define MPORT_ERR_STAT_SPI_CFG		(1u << 3u)
#define MPORT_ERR_STAT_I2C_EN		(1u << 4u)
#define MPORT_ERR_STAT_I2C_CFG		(1u << 5u)

/** \name SPI configuration Parameters. */
/**@{*/
#define MPORT_SPI_PIN_NUM_ALT_MODE	(3u)
#define SPI_IRQ_PRIO_CTRL 			(15u)
/**@{*/

/** \name I2C configuration Parameters. */
/**@{*/
#define MPORT_I2C_PIN_NUM_ALT_MODE		(2u)
#define MPORT_I2C_SCL_SM_MAX_RISE_TIME  (17u)
/**@{*/


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
t_error_code MPORT_spi_init(void)
{
	t_error_code ret_stat = e_ec_invalid_param;
	uint32_t err_stat = ERR_STAT_NO_ERROR;

	// 1. Enable GPIO port for SPI
	const t_error_code spi_gpio_en_stat = GPIO_port_enable(SYS_SPI_GPIO_PORT, ENABLE, DISABLE);
	err_stat |= (spi_gpio_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_GPIO_EN;

	// 2. Configure GPIO pins for SPI
	t_GPIO_RegDef * const p_gpio_spi = GPIO_get_port_base(SYS_SPI_GPIO_PORT);
	t_gpio_handle gpio_spi_cfg = {
		.p_gpio_reg = p_gpio_spi,
		.mode_sel = e_gpio_mode_alt_func,
		.open_drain_en = FALSE,
		.speed = e_gpio_speed_fast,
		.pupd = e_gpio_pupd_no,
		.alt_func_sel = SYS_SPI_ALT_FUNC
	};
	uint8_t succ_cnt = 0u;
	const uint8_t spi_pins[MPORT_SPI_PIN_NUM_ALT_MODE] = {SYS_SPI_SCK, SYS_SPI_MISO, SYS_SPI_MOSI};
	for (uint8_t pin_sel= 0u; pin_sel < MPORT_SPI_PIN_NUM_ALT_MODE; pin_sel++) {
		succ_cnt += (e_ec_no_error == GPIO_port_config(&gpio_spi_cfg, spi_pins[pin_sel])) ? 1u : 0u;
	}
	gpio_spi_cfg.mode_sel = e_gpio_mode_output;
	gpio_spi_cfg.pupd = e_gpio_pupd_pu;
	const t_error_code gpio_cs_cfg_stat = GPIO_port_config(&gpio_spi_cfg, SYS_SPI_CS); // Configure SW driven CS
	err_stat |= ((succ_cnt == MPORT_SPI_PIN_NUM_ALT_MODE) && (gpio_cs_cfg_stat == e_ec_no_error)) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_GPIO_CFG;

	// 3. Enable SPI port
	const t_error_code spi_en_stat = SPI_peri_enable(SYS_SPI_PERI, ENABLE, DISABLE);
	err_stat |= (spi_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_SPI_EN;

	// 4. Configure SPI port
	const t_spi_handle spi_cfg = {
		.p_spi_reg 		= SPI_get_peri_base(SYS_SPI_PERI),
		.master_en		= TRUE,
		.bus_cfg 		= e_spi_full_duplex,
		.speed 			= e_spi_br_8,
		.dff_16bit_en 	= FALSE,
		.cpol_en 		= FALSE,
		.cpha_en 		= FALSE,
		.ssm_en 		= TRUE
	};
	const t_error_code spi_cfg_stat = SPI_config(&spi_cfg);
	err_stat |= (spi_cfg_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_SPI_CFG;

	// 5. PUll up CS line
	GPIO_set_pin(p_gpio_spi, SYS_SPI_CS, TRUE);

	if (ERR_STAT_NO_ERROR == err_stat) {
		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_error_code MPORT_i2c_init(void)
{
	t_error_code ret_stat = e_ec_invalid_param;
	uint32_t err_stat = ERR_STAT_NO_ERROR;

	// 1. Enable GPIO port for I2C
	const t_error_code spi_gpio_en_stat = GPIO_port_enable(SYS_I2C_GPIO_PORT, ENABLE, DISABLE);
	err_stat |= (spi_gpio_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_GPIO_EN;

	// 2. Configure GPIO pins for I2C
	t_GPIO_RegDef * const p_gpio_spi = GPIO_get_port_base(SYS_I2C_GPIO_PORT);
	t_gpio_handle gpio_spi_cfg = {
		.p_gpio_reg = p_gpio_spi,
		.mode_sel = e_gpio_mode_alt_func,
		.open_drain_en = TRUE,
		.speed = e_gpio_speed_medium,
		.pupd = e_gpio_pupd_pu,
		.alt_func_sel = SYS_I2C_ALT_FUNC
	};
	uint8_t succ_cnt = 0u;
	const uint8_t spi_pins[MPORT_I2C_PIN_NUM_ALT_MODE] = {SYS_I2C_SCL, SYS_I2C_SDA};
	for (uint8_t pin_sel= 0u; pin_sel < MPORT_I2C_PIN_NUM_ALT_MODE; pin_sel++) {
		succ_cnt += (e_ec_no_error == GPIO_port_config(&gpio_spi_cfg, spi_pins[pin_sel])) ? 1u : 0u;
	}
	err_stat |= (succ_cnt == MPORT_I2C_PIN_NUM_ALT_MODE) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_GPIO_CFG;

	// 3. Enable I2C port
	const t_error_code i2C_en_stat = I2C_peri_enable(SYS_I2C_PERI, ENABLE, DISABLE);
	err_stat |= (i2C_en_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_I2C_EN;

	// 4. Configure I2C port
	t_I2C_RegDef * const p_i2c_reg = I2C_get_peri_base(SYS_I2C_PERI);
	t_i2c_handle i2c_handle = {
		.p_i2c_reg = p_i2c_reg,
		.addr_mode_10bit_en = FALSE,
		.own_addr1 = SYS_I2C_OAR_ADDR,
		.own_addr2 = 0u,
		.speed = e_i2c_spd_sm,
		.fmode_duty_16_9_en = FALSE,
		.scl_trise = MPORT_I2C_SCL_SM_MAX_RISE_TIME
	};
	const t_error_code i2c_cfg_stat = I2C_config(&i2c_handle);
	err_stat |= (i2c_cfg_stat == e_ec_no_error) ? ERR_STAT_NO_ERROR : MPORT_ERR_STAT_I2C_CFG;

	if (ERR_STAT_NO_ERROR == err_stat) {
		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

void MPORT_spi_byte_write_reg(const uint8_t * const p_write_data, const uint8_t data_len)
{
	t_GPIO_RegDef * const p_gpio_spi = GPIO_get_port_base(SYS_SPI_GPIO_PORT);
	t_SPI_RegDef * const p_spi = SPI_get_peri_base(SYS_SPI_PERI);

	SPI_peri_ctrl(p_spi, TRUE);
	GPIO_set_pin(p_gpio_spi, SYS_SPI_CS, FALSE);
	SPI_tx_data(p_spi, p_write_data, data_len);
	GPIO_set_pin(p_gpio_spi, SYS_SPI_CS, TRUE);
	SPI_peri_ctrl(p_spi, FALSE);
}

void MPORT_spi_byte_read_reg(const uint8_t read_addr, uint8_t * const p_read_data, const uint8_t data_len)
{
	t_GPIO_RegDef * const p_gpio_spi = GPIO_get_port_base(SYS_SPI_GPIO_PORT);
	t_SPI_RegDef * const p_spi = SPI_get_peri_base(SYS_SPI_PERI);

	SPI_peri_ctrl(p_spi, TRUE);
	GPIO_set_pin(p_gpio_spi, SYS_SPI_CS, FALSE);
	SPI_tx_data(p_spi, &read_addr, 1u);
	SPI_rx_data(p_spi, p_read_data, data_len);
	GPIO_set_pin(p_gpio_spi, SYS_SPI_CS, TRUE);
	SPI_peri_ctrl(p_spi, FALSE);
}

void MPORT_i2c_byte_read_reg(const uint8_t slave_addr, const uint8_t mem_addr, uint8_t * const p_read_data)
{
	t_I2C_RegDef * const p_i2c = I2C_get_peri_base(SYS_I2C_PERI);

	I2C_peri_ctrl(p_i2c, TRUE);
	I2C_read_byte(p_i2c, slave_addr, mem_addr, p_read_data);
	I2C_peri_ctrl(p_i2c, FALSE);
}

void MPORT_i2c_byte_read_reg_burst(const uint8_t slave_addr, const uint8_t mem_addr, uint8_t * const p_read_data, const uint8_t data_len)
{
	t_I2C_RegDef * const p_i2c = I2C_get_peri_base(SYS_I2C_PERI);

	I2C_peri_ctrl(p_i2c, TRUE);
	I2C_read_byte_burst(p_i2c, slave_addr, mem_addr, p_read_data, data_len);
	I2C_peri_ctrl(p_i2c, FALSE);
}

/*** EOF ***/
