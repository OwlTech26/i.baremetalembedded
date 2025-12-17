/**
 * Copyright (c) 2025 OwlTech
 *
 * \file seif_veml6040.c
 * \brief
 * \author OwlTech
 * \date Dec 15, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "seif_veml6040.h"

#include "mport.h"
#include "hal_reg.h"
#include "veml6040_regmap.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define VEML6040_CHIP_ID_MEM_SEL	(e_veml6040_mem_0)

#define SEIF_VEML6040_INTEG_40_MS		(0u) //!< Sens. max: 0.25168, lux max: 16496
#define SEIF_VEML6040_INTEG_80_MS		(1u) //!< Sens. max: 0.12584, lux max: 8248
#define SEIF_VEML6040_INTEG_160_MS		(2u) //!< Sens. max: 0.06292, lux max: 4124
#define SEIF_VEML6040_INTEG_320_MS		(3u) //!< Sens. max: 0.03146, lux max: 2062
#define SEIF_VEML6040_INTEG_640_MS		(4u) //!< Sens. max: 0.01573, lux max: 1031
#define SEIF_VEML6040_INTEG_1280_MS		(5u) //! Sens. max: 0.007865, lux max: 515.4

#define SEIF_VEML6040_NUM_OF_LIGHTS		(4u) //! Red, Green, Blue, White

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
static uint8_t seif_veml6040_addr_mem_sel(const t_veml6040_memory mem_sel);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */


/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static uint8_t seif_veml6040_addr_mem_sel(const t_veml6040_memory mem_sel)
{
	const uint8_t mem_addr[e_veml6040_mem_max] = {VEML6040_RESERVED_1, VEML6040_RESERVED_2, VEML6040_RESERVED_3,
		VEML6040_RESERVED_4, VEML6040_RESERVED_5, VEML6040_RESERVED_6, VEML6040_RESERVED_7};

	return mem_addr[mem_sel];
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
void SEIF_VEML6040_set_id(const uint16_t chip_id)
{
	const uint8_t * const p_chip_id = CAST_TO(const uint8_t * const, &chip_id);
	MPORT_i2c_byte_write_reg(VEML6040_ADDR, seif_veml6040_addr_mem_sel(VEML6040_CHIP_ID_MEM_SEL), p_chip_id, VEML6040_RESERVED_LEN);
}

uint16_t SEIF_VEML6040_get_id(void)
{
	uint16_t ret_id = 0u;

	uint8_t * const p_chip_id = CAST_TO(uint8_t * const, &ret_id);
	MPORT_i2c_byte_read_reg(VEML6040_ADDR, seif_veml6040_addr_mem_sel(VEML6040_CHIP_ID_MEM_SEL), p_chip_id, VEML6040_RESERVED_LEN);

	return ret_id;
}

t_error_code SEIF_VEML6040_set_config(const t_veml6040_integ integ, const t_bool fmode_en, const t_bool pwr_on)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if (integ < e_veml6040_integ_max) {
		const uint8_t integ_vals[e_veml6040_integ_max] = {SEIF_VEML6040_INTEG_40_MS, SEIF_VEML6040_INTEG_80_MS,
			SEIF_VEML6040_INTEG_160_MS, SEIF_VEML6040_INTEG_320_MS, SEIF_VEML6040_INTEG_640_MS, SEIF_VEML6040_INTEG_1280_MS};
		const uint8_t cfg_val = (integ_vals[integ] << VEML6040_CONF_IT_POS) |
			(b_to_uint32(fmode_en) << VEML6040_CONF_AF_POS) | ((pwr_on == FALSE) ? VEML6040_CONF_SD_MASK : 0u);

		MPORT_i2c_byte_write_reg(VEML6040_ADDR, VEML6040_CONF, &cfg_val, VEML6040_CONF_LEN);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

uint8_t SEIF_VEML6040_get_config(void)
{
	uint8_t ret_cfg = 0u;

	MPORT_i2c_byte_read_reg(VEML6040_ADDR, VEML6040_CONF, &ret_cfg, VEML6040_CONF_LEN);

	return ret_cfg;
}

void SEIF_VEML6040_set_pwr(const uint8_t conf_reg, const t_bool pwr_on)
{
	const uint8_t pwr_ctrl = conf_reg | ((pwr_on == FALSE) ? VEML6040_CONF_SD_MASK : 0u);

	MPORT_i2c_byte_write_reg(VEML6040_ADDR, VEML6040_CONF, &pwr_ctrl, VEML6040_CONF_LEN);
}

void SEIF_VEML6040_single_meas(const uint8_t conf_reg)
{
	// ToDo: Test is needed. It might be similar to TSL2561 manual integration mode. The feature is not fully clear in the data sheet.

	// Set one time detect cycle trigger at manual force mode.
	uint8_t trg_ctrl = conf_reg | VEML6040_CONF_TRIG_MASK | VEML6040_CONF_AF_MASK;
	MPORT_i2c_byte_write_reg(VEML6040_ADDR, VEML6040_CONF, &trg_ctrl, VEML6040_CONF_LEN);
	// Clear one time detect cycle trigger.
	trg_ctrl &= (VEML6040_CONF_TRIG_NMASK & VEML6040_CONF_AF_NMASK);
	MPORT_i2c_byte_write_reg(VEML6040_ADDR, VEML6040_CONF, &trg_ctrl, VEML6040_CONF_LEN);
}

void SEIF_VEML6040_read_light_data(t_veml6040_data * const p_data)
{
	const uint8_t light_addr[SEIF_VEML6040_NUM_OF_LIGHTS] = {VEML6040_R_DATA, VEML6040_G_DATA, VEML6040_B_DATA, VEML6040_W_DATA};
	uint8_t * const p_light_raw_data = CAST_TO(uint8_t * const, p_data);

	for (uint32_t light_sel=0u; light_sel<SEIF_VEML6040_NUM_OF_LIGHTS; light_sel++) {
		// Read light word
		MPORT_i2c_byte_read_reg(VEML6040_ADDR, light_addr[light_sel], &p_light_raw_data[light_sel * VEML6040_DATA_LEN], VEML6040_DATA_LEN);
	}
}

t_error_code SEIF_VEML6040_write_mem(const t_veml6040_memory mem_sel_start, const uint16_t * const p_data, const uint32_t data_len)
{
	t_error_code ret_stat = e_ec_invalid_param;

	// ToDo: Placeholder only.

	return ret_stat;
}

t_error_code SEIF_VEML6040_read_mem(const t_veml6040_memory mem_sel_start, uint16_t * const p_data, const uint32_t data_len)
{
	t_error_code ret_stat = e_ec_invalid_param;

	// ToDo: Placeholder only.

	return ret_stat;
}

/*** EOF ***/
