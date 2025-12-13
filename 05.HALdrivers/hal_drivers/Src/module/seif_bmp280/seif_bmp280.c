/**
 * Copyright (c) 2025 OwlTech
 *
 * \file seif_bmp280.c
 * \brief BMP280 temperature and pressure sensor.
 * \author OwlTech
 * \date Dec 1, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "seif_bmp280.h"

#include "mport.h"
#include "bmp280_regmap.h"
#include "cast.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define BMP280_WRITE_MASK	(0x7Fu)

#define BMP280_RAW_DATA_BYTE_LEN			(0x3u)
#define BMP280_RAW_DATA_MSB_IDX				(0u)
#define BMP280_RAW_DATA_LSB_IDX				(1u)
#define BMP280_RAW_DATA_XLSB_IDX			(2u)

#define BMP280_COMP_PARAM_RESERVED_BYTE		(2u)
#define BMP280_COMP_PARAM_BYTE_SIZE			(BMP280_REG_CALIB_IDX_MAX + 1u - BMP280_COMP_PARAM_RESERVED_BYTE)
#define BMP280_NUM_OF_COMP_PARAMS			(BMP280_COMP_PARAM_BYTE_SIZE / 2u)


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
static inline uint32_t seif_bmp280_assemble_raw_data_20bit(const uint8_t p_raw_buff[BMP280_RAW_DATA_BYTE_LEN]);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static int32_t seif_bmp280_calc_temp_fine(const uint32_t temp_raw, t_bmp280_comp_params * const p_comp_params);

static uint32_t seif_bmp280_press_comp(const uint32_t press_raw, t_bmp280_comp_params * const p_comp_params, const uint32_t temp_raw);

static int32_t seif_bmp280_temp_comp(const uint32_t temp_raw, t_bmp280_comp_params * const p_comp_params);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline uint32_t seif_bmp280_assemble_raw_data_20bit(const uint8_t p_raw_buff[BMP280_RAW_DATA_BYTE_LEN])
{
	// Organize to common 20 bits (independent from resolution)
	const uint32_t ret_val = (((uint32_t)p_raw_buff[BMP280_RAW_DATA_MSB_IDX] << NUM_OF_HALF_WORD_BITS) |
			((uint32_t)p_raw_buff[BMP280_RAW_DATA_LSB_IDX] << NUM_OF_BYTE_BITS) |
			((uint32_t)p_raw_buff[BMP280_RAW_DATA_XLSB_IDX])) >> NUM_OF_NIBBLE_BITS;

	return ret_val;
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static int32_t seif_bmp280_calc_temp_fine(const uint32_t temp_raw, t_bmp280_comp_params * const p_comp_params)
{
	const int32_t coeff_t1 = ((int32_t)((temp_raw >> 3) - (p_comp_params->dig_t1 << 1)) * p_comp_params->dig_t2) >> 11;
	const int32_t ct1 = (int32_t)((temp_raw >> 4) - p_comp_params->dig_t1);
	const int32_t coeff_t2 = (((ct1 * ct1) >> 12) * p_comp_params->dig_t3) >> 14;
	const int32_t ret_val = coeff_t1 + coeff_t2;

	return ret_val;
}

static int32_t seif_bmp280_temp_comp(const uint32_t temp_raw, t_bmp280_comp_params * const p_comp_params)
{
	const int32_t temp_fine = seif_bmp280_calc_temp_fine(temp_raw, p_comp_params);
	const int32_t ret_val = (temp_fine * 5 + 128) >> 8;

	return ret_val;
}

static uint32_t seif_bmp280_press_comp(const uint32_t press_raw, t_bmp280_comp_params * const p_comp_params, const uint32_t temp_raw)
{
	uint32_t ret_val = 0u;

	const int32_t temp_fine = seif_bmp280_calc_temp_fine(temp_raw, p_comp_params);
	int64_t coeff_p1 = (int64_t)temp_fine - 128000;
	const int64_t coeff_p1_sqr = coeff_p1 * coeff_p1;
	int64_t coeff_p2 = coeff_p1_sqr * p_comp_params->dig_p6;
	coeff_p2 += ((coeff_p1 * p_comp_params->dig_p5) << 17);
	coeff_p2 += ((int64_t)p_comp_params->dig_p4 << 35);
	coeff_p1 = ((coeff_p1_sqr * p_comp_params->dig_p3) >> 8) + ((coeff_p1 * p_comp_params->dig_p2) << 12);
	coeff_p1 = (((((int64_t)1 << 47) + coeff_p1)) * p_comp_params->dig_p1) >> 33;

	if (coeff_p1 != 0) {
		int64_t press = 1048576 - press_raw;
		press = (((press << 31) - coeff_p2) * 3125) / coeff_p1;
		coeff_p1 = ((int64_t)p_comp_params->dig_p9 * (press >> 13) * (press >> 13)) >> 25;
		coeff_p2 = ((int64_t)p_comp_params->dig_p8 * press) >> 19;
		press = ((press + coeff_p1 + coeff_p2) >> 8) + ((int64_t)p_comp_params->dig_p7 << 4);

		ret_val = (uint32_t)press;
	}


	return ret_val;
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
uint8_t SEIF_BMP280_get_id(void)
{
	uint8_t raw_buf = 0u;
	MPORT_spi_byte_read_reg(BMP280_REG_ID, &raw_buf, BMP280_REG_ID_LEN);

	return raw_buf;
}

t_error_code SEIF_BMP280_set_meas_mode(const t_bmp280_ctrl_meas * const p_ctrl_meas)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((p_ctrl_meas->mode < e_bmp280_mode_max) && (p_ctrl_meas->press_ovs < e_bmp280_osrs_max) && (p_ctrl_meas->temp_ovs < e_bmp280_osrs_max)) {
		const uint8_t bmp_write_cmd[] = {BMP280_CTRL_MEAS & BMP280_WRITE_MASK,
			(p_ctrl_meas->temp_ovs << BMP280_CTRL_MEAS_OSRS_T_POS) |
			(p_ctrl_meas->press_ovs << BMP280_CTRL_MEAS_OSRS_P_POS) |
			(p_ctrl_meas->mode << BMP280_CTRL_MEAS_MODE_POS)};
		MPORT_spi_byte_write_reg(bmp_write_cmd, NUM_OF_ARRAY(bmp_write_cmd));

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

uint8_t SEIF_BMP280_get_meas_mode()
{
	uint8_t raw_buf = 0u;
	MPORT_spi_byte_read_reg(BMP280_CTRL_MEAS, &raw_buf, BMP280_CTRL_MEAS_LEN);

	return raw_buf;
}

uint32_t SEIF_BMP280_get_press_raw(void)
{
	uint8_t raw_buf[BMP280_RAW_DATA_BYTE_LEN] = {0};
	MPORT_spi_byte_read_reg(BMP280_PRESS_MSB, raw_buf, BMP280_RAW_DATA_BYTE_LEN);
	const uint32_t ret_val = seif_bmp280_assemble_raw_data_20bit(raw_buf);

	return ret_val;
}

uint32_t SEIF_BMP280_get_temp_raw(void)
{
	uint8_t raw_buf[BMP280_RAW_DATA_BYTE_LEN] = {0};
	MPORT_spi_byte_read_reg(BMP280_TEMP_MSB, raw_buf, BMP280_RAW_DATA_BYTE_LEN);
	const uint32_t ret_val = seif_bmp280_assemble_raw_data_20bit(raw_buf);

	return ret_val;
}

void SEIF_BMP280_get_comp_params(t_bmp280_comp_params * const p_comp_params)
{
	uint8_t raw_buf[BMP280_COMP_PARAM_BYTE_SIZE] = {0};
	MPORT_spi_byte_read_reg(BMP280_REG_CALIB, raw_buf, BMP280_COMP_PARAM_BYTE_SIZE);

	const uint16_t * const p_calib_src = CAST_TO(const uint16_t * const, raw_buf);
	uint16_t * const p_calib_dst = CAST_TO(uint16_t * const, p_comp_params);
	for (uint32_t i=0u; i<BMP280_NUM_OF_COMP_PARAMS; ++i) {
		p_calib_dst[i] = p_calib_src[i];
	}
}

int32_t SEIF_BMP280_get_temp_degc(const t_bmp280_comp_params * const p_comp_params, uint32_t * const p_temp_raw)
{
	const uint32_t temp_raw = SEIF_BMP280_get_temp_raw();
	*p_temp_raw = temp_raw;

	return seif_bmp280_temp_comp(temp_raw, CAST_TO(t_bmp280_comp_params * const, p_comp_params));
}

uint32_t SEIF_BMP280_get_press_pa(const t_bmp280_comp_params * const p_comp_params, const uint32_t temp_raw)
{
	const uint32_t press_raw = SEIF_BMP280_get_press_raw();

	return seif_bmp280_press_comp(press_raw, CAST_TO(t_bmp280_comp_params * const, p_comp_params), temp_raw);
}

/*** EOF ***/
