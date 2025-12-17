/**
 * Copyright (c) 2025 OwlTech
 *
 * \file seif_tsl2561.c
 * \brief
 * \author OwlTech
 * \date Dec 15, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "seif_tsl2561.h"

#include "mport.h"
#include "hal_reg.h"
#include "tsl2561_regmap.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define SEIF_TSL2561_ADC_CH0_WORD		(TSL2561_DATA0LOW_LEN + TSL2561_DATA0HIGH_LEN)
#define SEIF_TSL2561_ADC_CH1_WORD		(TSL2561_DATA1LOW_LEN + TSL2561_DATA1HIGH_LEN)

#define SEIF_TSL2561_INTEG_13P7_MS		(0u) //!< Scale: 0.034
#define SEIF_TSL2561_INTEG_101_MS		(1u) //!< Scale: 0.252
#define SEIF_TSL2561_INTEG_402_MS		(2u) //!< Scale: 1
#define SEIF_TSL2561_INTEG_MAN			(3u) //!< Manual integration time control.

#define SEIF_TSL2561_INTR_DISABLE			(0u)
#define SEIF_TSL2561_INTR_LEVEL				(1u)
#define SEIF_TSL2561_INTR_SMB_ALERT			(2u)
#define SEIF_TSL2561_INTR_TEST_MODE			(3u)
#define SEIF_TSL2561_INTR_THRES_LOW_WORD	(TSL2561_THRESHLOWLOW_LEN + TSL2561_THRESHLOWHIGH_LEN)
#define SEIF_TSL2561_INTR_THRES_HIGH_WORD	(TSL2561_THRESHHIGHLOW_LEN + TSL2561_THRESHHIGHHIGH_LEN)


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
static inline uint8_t seif_tsl2561_cmd_byte(const uint32_t addr);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static inline uint8_t seif_tsl2561_cmd_word(const uint32_t addr);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline uint8_t seif_tsl2561_cmd_byte(const uint32_t addr)
{
	const uint8_t ret_cmd = TSL2561_COMMAND_CMD_MASK | (addr & TSL2561_COMMAND_ADDRESS_MASK);

	return ret_cmd;
}

static inline uint8_t seif_tsl2561_cmd_word(const uint32_t addr)
{
	return (seif_tsl2561_cmd_byte(addr) | TSL2561_COMMAND_WORD_MASK);
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
uint8_t SEIF_TSL2561_get_id(void)
{
	uint8_t ret_id = 0u;

	MPORT_i2c_byte_read_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_ID), &ret_id, TSL2561_ID_LEN);

	return ret_id;
}

/** \brief Integration time/gain control settings. */
t_error_code SEIF_TSL2561_set_config(const t_tsl2561_integ integ, t_bool gain_16x_en)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if (integ < e_tsl2561_integ_max) {
		const uint8_t integ_vals[e_tsl2561_integ_max] =
			{SEIF_TSL2561_INTEG_13P7_MS, SEIF_TSL2561_INTEG_101_MS, SEIF_TSL2561_INTEG_402_MS, SEIF_TSL2561_INTEG_MAN};
		const uint8_t cfg_val = (b_to_uint32(gain_16x_en) << TSL2561_TIMING_GAIN_POS) | integ_vals[integ];

		MPORT_i2c_byte_write_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_TIMING), &cfg_val, TSL2561_TIMING_LEN);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

uint8_t SEIF_TSL2561_get_config(void)
{
	uint8_t ret_cfg = 0u;

	MPORT_i2c_byte_read_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_TIMING), &ret_cfg, TSL2561_TIMING_LEN);

	return ret_cfg;
}

void SEIF_TSL2561_integ_man_ctrl(const uint8_t timing_reg, const t_bool start_en)
{
	const uint8_t cfg_val =
		(start_en != FALSE) ? (timing_reg | TSL2561_TIMING_MANUAL_MASK) : (timing_reg | TSL2561_TIMING_MANUAL_NMASK);
	MPORT_i2c_byte_write_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_TIMING), &cfg_val, TSL2561_TIMING_LEN);
}

uint8_t SEIF_TSL2561_get_pwr(void)
{
	uint8_t ret_id = 0u;

	MPORT_i2c_byte_read_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_CONTROL), &ret_id, TSL2561_CONTROL_LEN);

	return ret_id & TSL2561_CONTROL_POWER_MASK;
}

void SEIF_TSL2561_set_pwr(const t_bool pwr_on)
{
	const uint8_t pwr_ctrl = ((pwr_on == FALSE) ? TSL2561_CONTROL_POWER_OFF : TSL2561_CONTROL_POWER_ON) & TSL2561_CONTROL_POWER_MASK;

	MPORT_i2c_byte_write_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_CONTROL), &pwr_ctrl, TSL2561_CONTROL_LEN);
}

uint16_t SEIF_TSL2561_read_visible_ir(void)
{
	uint16_t ret_lux = 0u;
	uint8_t * const p_adc_raw_data = CAST_TO(uint8_t * const, &ret_lux);

	// Read ADC channel0 full word for visible light and infrared
	MPORT_i2c_byte_read_reg(TSL2561_ADDR, seif_tsl2561_cmd_word(TSL2561_DATA0LOW), p_adc_raw_data, SEIF_TSL2561_ADC_CH0_WORD);

	return ret_lux;
}

uint16_t SEIF_TSL2561_read_ir_only(void)
{
	uint16_t ret_lux = 0u;
	uint8_t * p_adc_raw_data = CAST_TO(uint8_t *, &ret_lux);

	// Read ADC channel1 full word for infrared only
	MPORT_i2c_byte_read_reg(TSL2561_ADDR, seif_tsl2561_cmd_word(TSL2561_DATA1LOW), p_adc_raw_data, SEIF_TSL2561_ADC_CH1_WORD);

	return ret_lux;
}

void SEIF_TSL2561_set_it_threshold(const uint16_t thres_low, const uint16_t thres_high)
{
	const uint8_t * const p_thres_low = CAST_TO(const uint8_t * const, &thres_low);
	const uint8_t * const p_thres_high = CAST_TO(const uint8_t * const, &thres_high);
	MPORT_i2c_byte_write_reg(TSL2561_ADDR, seif_tsl2561_cmd_word(TSL2561_THRESHLOWLOW), p_thres_low, SEIF_TSL2561_INTR_THRES_LOW_WORD);
	MPORT_i2c_byte_write_reg(TSL2561_ADDR, seif_tsl2561_cmd_word(TSL2561_THRESHHIGHLOW), p_thres_high, SEIF_TSL2561_INTR_THRES_HIGH_WORD);
}

t_error_code SEIF_TSL2561_set_it_ctrl(const t_tsl2561_intr intr, const uint8_t intr_pers_sel)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((intr < e_tsl2561_intr_max) && (intr_pers_sel)) {
		const uint8_t intr_values[e_tsl2561_intr_max] ={ SEIF_TSL2561_INTR_DISABLE, SEIF_TSL2561_INTR_LEVEL, SEIF_TSL2561_INTR_SMB_ALERT, SEIF_TSL2561_INTR_TEST_MODE};
		const uint8_t it_ctrl = (intr_values[intr] << TSL2561_INTERRUPT_INTR_POS) | intr_pers_sel;
		MPORT_i2c_byte_write_reg(TSL2561_ADDR, seif_tsl2561_cmd_byte(TSL2561_INTERRUPT), &it_ctrl, TSL2561_INTERRUPT_LEN);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

void SEIF_TSL2561_clear_it(void)
{
	const uint8_t cmd = TSL2561_COMMAND_CMD_MASK | TSL2561_COMMAND_CLEAR_MASK;
	MPORT_i2c_send_cmd(TSL2561_ADDR, cmd);
}

/*** EOF ***/
