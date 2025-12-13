/**
 * Copyright (c) 2025 OwlTech
 *
 * \file i2c.c
 * \brief
 * \author OwlTech
 * \date Dec 8, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "i2c.h"

#include "rcc.h"
#include "cast.h"
#include "hal_reg.h"
#include "i2c_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define I2C_SCL_FREQ_MIN_SM					(2u * RCC_CLOCK_FREQ_TO_MHZ)
#define I2C_SCL_FREQ_MIN_FM					(4u * RCC_CLOCK_FREQ_TO_MHZ)
#define I2C_SCL_FREQ_MAX					(50u * RCC_CLOCK_FREQ_TO_MHZ)
#define I2C_SCL_SPEED_SM 					(100000u) //!< Standard mode 100 kHz SCL speed value.
#define I2C_SCL_SPEED_FM2K  				(200000u) //!< Fast mode 200 kHz SCL speed value.
#define I2C_SCL_SPEED_FM4K 					(400000u) //!< Fast mode 400 kHz SCL speed value.
#define I2C_SCL_CC_NODUTY_MIN 				(4u) 	  //!< SCL clock control minimum value in the case of non-duty mode.
#define I2C_SCL_CC_DUTY_MIN 				(1u) 	  //!< SCL clock control minimum value in the case of duty mode.
#define I2C_SCL_FREQ_TO_PERIOD_TIME_NS		(RCC_CLOCK_FREQ_TO_KHZ * RCC_CLOCK_FREQ_TO_MHZ)
#define I2C_SCL_DUTY_RATIO_1_1              (1u + 1u)
#define I2C_SCL_DUTY_RATIO_1_2              (1u + 2u)
#define I2C_SCL_DUTY_RATIO_9_16             (9u + 16u)
#define I2C_SCL_ADDR_7BIT_SHIFT            	(1u)
#define I2C_SCL_ADDR_7BIT_RMASK            	(1u)
#define I2C_SCL_ADDR_7BIT_WMASK	            (0u)


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
static inline void i2c_clear_addr_flag(const t_I2C_RegDef * const p_i2c);

static inline void i2c_master_send_byte(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static uint32_t i2c_calc_ccr_value(const t_i2c_speed scl_speed, const uint32_t apb_freq, const t_bool fmode_duty_16_9_en);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline void i2c_clear_addr_flag(const t_I2C_RegDef * const p_i2c)
{
	uint32_t stat_reg = p_i2c->I2Cx_SR1;
	stat_reg = p_i2c->I2Cx_SR2;
	INTENTINALLY_UNUSED(stat_reg);
}

static inline void i2c_master_send_byte(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr)
{
	// Wait until bus not busy
	while(p_i2c->I2Cx_SR2 == I2C_SR2_BUSY_MASK);

	// Generate start condition
	p_i2c->I2Cx_CR1 |= I2C_CR1_START_MASK;

	// Wait until start generation is completed
	// Note: Until SB is cleared SCL will be streched (pulled Low)
	while((p_i2c->I2Cx_SR1 & I2C_SR1_SB_MASK) == 0u);

	// Transmit slave address + write
	p_i2c->I2Cx_DR = (slave_addr << I2C_SCL_ADDR_7BIT_SHIFT) | I2C_SCL_ADDR_7BIT_WMASK;

	// Wait until address complete
	while((p_i2c->I2Cx_SR1 & I2C_SR1_ADDR_MASK) == 0u);

	// Clear ADDR flag
	i2c_clear_addr_flag(p_i2c);

	// Send memory address
	p_i2c->I2Cx_DR = mem_addr;

	// Wait untill transmitter empty
	while((p_i2c->I2Cx_SR1 & I2C_SR1_TXE_MASK) == 0u);
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static uint32_t i2c_calc_ccr_value(const t_i2c_speed scl_speed, const uint32_t apb_freq, const t_bool fmode_duty_16_9_en)
{
    const uint32_t i2c_freq[e_i2c_spd_max] = {I2C_SCL_SPEED_SM, I2C_SCL_SPEED_FM2K, I2C_SCL_SPEED_FM4K};
    uint32_t i2c_t_ns                      = I2C_SCL_FREQ_TO_PERIOD_TIME_NS / i2c_freq[scl_speed];    // Granularity: [ns]
    const uint32_t t_pclk1_ns              = I2C_SCL_FREQ_TO_PERIOD_TIME_NS / apb_freq; // Granularity: [ns]

    if (scl_speed == e_i2c_spd_sm) {
        /** Standard mode or SMBus:
         *  Thigh = CCR * TPCLK1
         *  Tlow = CCR * TPCLK1
         */
        i2c_t_ns /= I2C_SCL_DUTY_RATIO_1_1;
    } else {
         /** Fm mode:
          * If DUTY = 0:
          * Thigh = CCR * TPCLK1
          * Tlow = 2 * CCR * TPCLK1
          * If DUTY = 1:
          * Thigh = 9 * CCR * TPCLK1
          * Tlow = 16 * CCR * TPCLK1
          */
        i2c_t_ns /= (fmode_duty_16_9_en == FALSE) ? (I2C_SCL_DUTY_RATIO_1_2) : (I2C_SCL_DUTY_RATIO_9_16);
    }

    const uint32_t ret_ccr = i2c_t_ns / t_pclk1_ns;

    return ret_ccr;
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
t_error_code I2C_peri_enable(const t_i2c_port i2c_sel, const uint8_t port_en, const uint8_t lpwrm_en)
{
	/** \paramrange{i2c_sel,e_i2c_1,e_i2c_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (i2c_sel < e_i2c_max) {
		// Enable the peripheral clock for SPI peripheral
		const uint8_t peri_sel[e_i2c_max] = {e_peri_i2c1, e_peri_i2c2, e_peri_i2c3};
		RCC_enable_peri(e_peri_apb1, peri_sel[i2c_sel], port_en, lpwrm_en);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_error_code I2C_peri_reset(const t_i2c_port i2c_sel)
{
	/** \paramrange{i2c_sel,e_i2c_1,e_i2c_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (i2c_sel < e_i2c_max) {
		// Enable the peripheral clock for SPI peripheral
		const uint8_t peri_sel[e_i2c_max] = {e_peri_i2c1, e_peri_i2c2, e_peri_i2c3};
		RCC_reset_peri(e_peri_apb1, peri_sel[i2c_sel]);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_I2C_RegDef * const I2C_get_peri_base(const t_i2c_port i2c_sel)
{
	/** \paramrange{i2c_sel,e_i2c_1,e_i2c_max}
	 */

	const uint32_t i2c_base[e_i2c_max] = {I2C1_BASE, I2C2_BASE, I2C3_BASE};

	t_I2C_RegDef * const ret_base = (i2c_sel < e_i2c_max) ? CAST_TO(t_I2C_RegDef * const, i2c_base[i2c_sel]) : NULL;

	return ret_base;
}

t_error_code I2C_config(const t_i2c_handle * const p_i2c_handle)
{
	t_error_code ret_stat = e_ec_invalid_param;

	const uint32_t apb1_freq = RCC_get_peri_clock_freq(e_peri_apb1);
	const uint32_t apb1_freq_min = (p_i2c_handle->speed == e_i2c_spd_sm) ? I2C_SCL_FREQ_MIN_SM : I2C_SCL_FREQ_MIN_FM;
	if ((apb1_freq >= apb1_freq_min) && (apb1_freq <= I2C_SCL_FREQ_MAX) && (p_i2c_handle->speed < e_i2c_spd_max))
	{
		// Reset device
		p_i2c_handle->p_i2c_reg->I2Cx_CR1 |= I2C_CR1_SWRST_MASK;
		p_i2c_handle->p_i2c_reg->I2Cx_CR1 &= I2C_CR1_SWRST_NMASK;

		// SCL frequency setting
		const uint32_t pclk1_mhz = apb1_freq / RCC_CLOCK_FREQ_TO_MHZ;
		p_i2c_handle->p_i2c_reg->I2Cx_CR2 &= I2C_CR2_FREQ_NMASK;
		p_i2c_handle->p_i2c_reg->I2Cx_CR2 |= (pclk1_mhz & I2C_CR2_FREQ_MASK);

		// Slave device own addressing setting
		const uint32_t device_addr = (p_i2c_handle->addr_mode_10bit_en == FALSE) ?
			((p_i2c_handle->own_addr1 << I2C_OAR1_ADD7_1_POS) & I2C_OAR1_ADD7_1_MASK) : // 7-bit addressing mode
			(p_i2c_handle->own_addr1 & (I2C_OAR1_ADD9_8_MASK | I2C_OAR1_ADD7_1_MASK | I2C_OAR1_ADD0_MASK)); // 10-bit addressing mode
		p_i2c_handle->p_i2c_reg->I2Cx_OAR1 = (b_to_uint32(p_i2c_handle->addr_mode_10bit_en) << I2C_OAR1_ADD_MODE_POS) |
				I2C_OAR1_ADD14_MASK | device_addr; // Note: Bit 14 Should always be kept at 1 by software.
		p_i2c_handle->p_i2c_reg->I2Cx_OAR2 = (p_i2c_handle->own_addr2 == 0u) ? DISABLE : // Dual-addressing mode disabled
				(p_i2c_handle->own_addr2 << I2C_OAR2_ADD7_1_POS) & I2C_OAR2_ENDUAL_MASK; // Dual-addressing mode enabled

		// Set SCL rise time
		p_i2c_handle->p_i2c_reg->I2Cx_TRISE = p_i2c_handle->scl_trise;

		// SCL clock control setting
		const t_bool duty_en = p_i2c_handle->fmode_duty_16_9_en;
		const uint32_t ccr_min = (duty_en == FALSE) ? I2C_SCL_CC_NODUTY_MIN : I2C_SCL_CC_DUTY_MIN;
		const uint32_t ccr_val = i2c_calc_ccr_value(p_i2c_handle->speed, apb1_freq, duty_en);
		if (ccr_val >= ccr_min) {
			const uint32_t master_mode_sel = (p_i2c_handle->speed == e_i2c_spd_sm) ? 0u : I2C_CCR_FPS_MASK;
			p_i2c_handle->p_i2c_reg->I2Cx_CCR = master_mode_sel |
				(b_to_uint32(duty_en) << I2C_CCR_DUTY_POS) |
				((ccr_val << I2C_CCR_CCR_POS) & I2C_CCR_CCR_MASK);

			ret_stat = e_ec_no_error;
		}
	}

	return ret_stat;
}

void I2C_peri_ctrl(t_I2C_RegDef * const p_i2c, const t_bool i2c_en)
{
	if (i2c_en != FALSE) { 	// Enable I2C periphery
		p_i2c->I2Cx_CR1 |= I2C_CR1_PE_MASK;
	} else { 				// Disable I2C periphery
		p_i2c->I2Cx_CR1 &= I2C_CR1_PE_NMASK;
	}
}

// ToDo: implemented 7 bit addressing mode only.
void I2C_read_byte(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr, uint8_t * const p_data)
{
	i2c_master_send_byte(p_i2c, slave_addr, mem_addr);

	// Generate re-start condition
	p_i2c->I2Cx_CR1 |= I2C_CR1_START_MASK;

	// Wait until re-start generation is completed
	while((p_i2c->I2Cx_SR1 & I2C_SR1_SB_MASK) == 0u);

	// Transmit slave address + read
	p_i2c->I2Cx_DR = (slave_addr << I2C_SCL_ADDR_7BIT_SHIFT) | I2C_SCL_ADDR_7BIT_RMASK;

	// Wait until address complete
	while((p_i2c->I2Cx_SR1 & I2C_SR1_ADDR_MASK) == 0u);

	// Disable acknowledge
	p_i2c->I2Cx_CR1 &= I2C_CR1_ACK_NMASK;

	// Clear ADDR flag
	i2c_clear_addr_flag(p_i2c);

	// Generate stop condition
	p_i2c->I2Cx_CR1 |= I2C_CR1_STOP_MASK;

	// Wait until data received
	while((p_i2c->I2Cx_SR1 & I2C_SR1_RXNE_MASK) == 0u);

	// Read data
	*p_data = p_i2c->I2Cx_DR;
}

void I2C_read_byte_burst(t_I2C_RegDef * const p_i2c, const uint8_t slave_addr, const uint8_t mem_addr, uint8_t * const p_data, const uint32_t data_len)
{
	i2c_master_send_byte(p_i2c, slave_addr, mem_addr);

	// Generate re-start condition
	p_i2c->I2Cx_CR1 |= I2C_CR1_START_MASK;
	// Wait until re-start generation is completed
	while((p_i2c->I2Cx_SR1 & I2C_SR1_SB_MASK) == 0u);
	// Transmit slave address + read
	p_i2c->I2Cx_DR = (slave_addr << I2C_SCL_ADDR_7BIT_SHIFT) | I2C_SCL_ADDR_7BIT_RMASK;
	// Wait until address complete
	while((p_i2c->I2Cx_SR1 & I2C_SR1_ADDR_MASK) == 0u);
	// Clear ADDR flag
	i2c_clear_addr_flag(p_i2c);
	// Enable acknowledge
	p_i2c->I2Cx_CR1 |= I2C_CR1_ACK_MASK;

	// Read data
	uint32_t rx_buf_len = data_len;
	uint8_t * p_rx_buf = CAST_TO(uint8_t *, p_data);
	while (rx_buf_len > 0u) {
		if (rx_buf_len == 1u) { // Last Byte to be read
			// Disable acknowledge
			p_i2c->I2Cx_CR1 &= I2C_CR1_ACK_NMASK;
			// Generate stop condition
			p_i2c->I2Cx_CR1 |= I2C_CR1_STOP_MASK;
		}
		// Wait until data received
		while((p_i2c->I2Cx_SR1 & I2C_SR1_RXNE_MASK) == 0u);
		*p_rx_buf = p_i2c->I2Cx_DR;
		p_rx_buf++;
		rx_buf_len--;
	}
}

/*** EOF ***/
