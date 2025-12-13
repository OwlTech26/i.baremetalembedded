/**
 * Copyright (c) 2025 OwlTech
 *
 * \file spi.c
 * \brief
 * \author OwlTech
 * \date Nov 21, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "spi.h"

#include "rcc.h"
#include "cast.h"
#include "cortex_m4.h"
#include "hal_reg.h"
#include "spi_register.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/


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
static inline t_bool spi_check_tx_buffer_empty(const t_SPI_RegDef * const p_spi);

static inline t_bool spi_check_rx_buffer_nempty(const t_SPI_RegDef * const p_spi);

static inline t_bool spi_check_tx_busy(const t_SPI_RegDef * const p_spi);

static inline void spi_clear_ovr_flag(t_SPI_RegDef * const p_spi);

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static void spi_rxne_interrupt_handle(t_spi_it_handle * const p_spi_handle);

static void spi_txe_interrupt_handle(t_spi_it_handle * const p_spi_handle);

static void spi_ovr_interrupt_handle(t_spi_it_handle * const p_spi_handle);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline t_bool spi_check_tx_buffer_empty(const t_SPI_RegDef * const p_spi)
{
	return ((p_spi->SPIx_SR & SPI_SR_TXE_MASK) == 0u) ? FALSE : TRUE;
}

static inline t_bool spi_check_rx_buffer_nempty(const t_SPI_RegDef * const p_spi)
{
	return ((p_spi->SPIx_SR & SPI_SR_RXNE_MASK) == 0u) ? FALSE : TRUE;
}

static inline t_bool spi_check_tx_busy(const t_SPI_RegDef * const p_spi)
{
	return ((p_spi->SPIx_SR & SPI_SR_BSY_MASK) == 0u) ? FALSE : TRUE;
}

static inline void spi_clear_ovr_flag(t_SPI_RegDef * const p_spi)
{
	uint8_t spi_reg = p_spi->SPIx_DR;
	spi_reg = p_spi->SPIx_SR;
	INTENTINALLY_UNUSED(spi_reg);
}



/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */
static void spi_rxne_interrupt_handle(t_spi_it_handle * const p_spi_handle)
{
	const t_bool dff_16_bit = ((p_spi_handle->p_spi_reg->SPIx_CR1 & SPI_CR1_DFF_MASK) != 0u) ? TRUE : FALSE;

	// Check Data Frame Format
	if (dff_16_bit != FALSE) { // 16-bit Data Format
		*((uint16_t *)p_spi_handle->p_rx_buffer) = (uint16_t)p_spi_handle->p_spi_reg->SPIx_DR;
		p_spi_handle->rx_len--;
		p_spi_handle->p_rx_buffer++;
	} else { // 8-bit data format
		*p_spi_handle->p_rx_buffer = (uint8_t)p_spi_handle->p_spi_reg->SPIx_DR;
	}
	p_spi_handle->p_rx_buffer++;
	p_spi_handle->rx_len--;

	// Close the communication, send DONE signal
	if (p_spi_handle->rx_len == 0u) {
		SPI_rx_it_close(p_spi_handle);

		SPI_api_event_cb(p_spi_handle, e_spi_event_rx_done);
	}
}

static void spi_txe_interrupt_handle(t_spi_it_handle * const p_spi_handle)
{
	const t_bool dff_16_bit = ((p_spi_handle->p_spi_reg->SPIx_CR1 & SPI_CR1_DFF_MASK) != 0u) ? TRUE : FALSE;

	// Check Data Frame Format
	if (dff_16_bit != FALSE) { // 16-bit Data Format
		p_spi_handle->p_spi_reg->SPIx_DR = *((uint16_t *)p_spi_handle->p_tx_buffer);
		p_spi_handle->tx_len--;
		p_spi_handle->p_tx_buffer++;
	} else { // 8-bit data format
		p_spi_handle->p_spi_reg->SPIx_DR = *p_spi_handle->p_tx_buffer;
	}
	p_spi_handle->p_tx_buffer++;
	p_spi_handle->tx_len--;

	// Close the communication, send DONE signal
	if (p_spi_handle->tx_len == 0u) {
		SPI_tx_it_close(p_spi_handle);

		SPI_api_event_cb(p_spi_handle, e_spi_event_tx_done);
	}
}

static void spi_ovr_interrupt_handle(t_spi_it_handle * const p_spi_handle)
{
	if (p_spi_handle->spi_tx_bsy == FALSE) {
		spi_clear_ovr_flag(p_spi_handle->p_spi_reg);
	}

	SPI_api_event_cb(p_spi_handle, e_spi_event_ovr_error);
}

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
t_error_code SPI_peri_enable(const t_spi_port spi_sel, const uint8_t port_en, const uint8_t lpwrm_en)
{
	/** \paramrange{spi_sel,e_spi_1,e_spi_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (spi_sel < e_spi_max) {
		// Enable the peripheral clock for SPI peripheral
		const uint8_t peri_sel[e_spi_max] = {e_peri_spi1, e_peri_spi2, e_peri_spi3, e_peri_spi4};
		const t_clock_peri peri_bus = ((spi_sel == e_spi_1) || (spi_sel == e_spi_4)) ? e_peri_apb2 : e_peri_apb1;
		RCC_enable_peri(peri_bus, peri_sel[spi_sel], port_en, lpwrm_en);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_error_code SPI_peri_reset(const t_spi_port spi_sel)
{
	/** \paramrange{spi_sel,e_spi_1,e_spi_max}
	 */

	t_error_code ret_stat = e_ec_invalid_param;

	if (spi_sel < e_spi_max) {
		// Enable the peripheral clock for SPI peripheral
		const uint8_t peri_sel[e_spi_max] = {e_peri_spi1, e_peri_spi2, e_peri_spi3, e_peri_spi4};
		const t_clock_peri peri_bus = ((spi_sel == e_spi_1) || (spi_sel == e_spi_4)) ? e_peri_apb2 : e_peri_apb1;
		RCC_reset_peri(peri_bus, peri_sel[spi_sel]);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

t_SPI_RegDef * const SPI_get_peri_base(const t_spi_port spi_sel)
{
	/** \paramrange{spi_sel,e_spi_1,e_spi_max}
	 */

	const uint32_t spi_base[e_spi_max] = {SPI1_BASE, SPI2_I2S2_BASE, SPI3_I2S3_BASE, SPI4_BASE};

	t_SPI_RegDef * const ret_base = (spi_sel < e_spi_max) ? CAST_TO(t_SPI_RegDef * const, spi_base[spi_sel]) : NULL;

	return ret_base;
}

t_error_code SPI_config(const t_spi_handle * const p_spi_handle)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((p_spi_handle->bus_cfg < e_spi_bus_cfg_max) &&
		(p_spi_handle->speed < e_spi_br_max)) {
		uint32_t spi_cr1_reg = p_spi_handle->p_spi_reg->SPIx_CR1;

		// Configure CPHA, CPOL, device mode, speed, data frame rate
		spi_cr1_reg &= (SPI_CR1_CPHA_NMASK & SPI_CR1_CPOL_NMASK & SPI_CR1_MSTR_NMASK & SPI_CR1_BR_NMASK & SPI_CR1_DFF_NMASK);
		spi_cr1_reg |= ((b_to_uint32(p_spi_handle->cpha_en) << SPI_CR1_CPHA_POS) |
						(b_to_uint32(p_spi_handle->cpol_en) << SPI_CR1_CPOL_POS) |
						(b_to_uint32(p_spi_handle->master_en) << SPI_CR1_MSTR_POS) |
						((uint32_t)(p_spi_handle->speed) << SPI_CR1_BR_POS) |
						(b_to_uint32(p_spi_handle->dff_16bit_en) << SPI_CR1_DFF_POS));

		// Configure Software Slave Management
		if (p_spi_handle->ssm_en == FALSE) {
			spi_cr1_reg &= (SPI_CR1_SSI_NMASK & SPI_CR1_SSM_NMASK);
			p_spi_handle->p_spi_reg->SPIx_CR2 |= SPI_CR2_SSOE_MASK;
		} else {
			spi_cr1_reg |= (SPI_CR1_SSI_MASK | SPI_CR1_SSM_MASK);
			p_spi_handle->p_spi_reg->SPIx_CR2 &= SPI_CR2_SSOE_NMASK;
		}

		// Configure transfer mode
		switch (p_spi_handle->bus_cfg) {
			case e_spi_full_duplex:
				spi_cr1_reg &= SPI_CR1_BIDI_MODE_NMASK;
				break;
			case e_spi_half_duplex:
				spi_cr1_reg |= SPI_CR1_BIDI_MODE_MASK;
				break;
			case e_spi_simplex_txonly:
				spi_cr1_reg &= SPI_CR1_BIDI_MODE_NMASK;
				spi_cr1_reg &= SPI_CR1_RX_ONLY_NMASK;
				break;
			case e_spi_simplex_rxonly:
				spi_cr1_reg &= SPI_CR1_BIDI_MODE_NMASK;
				spi_cr1_reg |= SPI_CR1_RX_ONLY_MASK;
				break;
			default:
				break;
		}

		p_spi_handle->p_spi_reg->SPIx_CR1 = spi_cr1_reg;

		ret_stat = e_ec_no_error;
	}


	return ret_stat;
}

void SPI_peri_ctrl(t_SPI_RegDef * const p_spi, const t_bool spi_en)
{
	if (spi_en != FALSE) {
		p_spi->SPIx_CR1 |= SPI_CR1_SPE_MASK;
	} else {
		// ToDo: The correct disable procedure is (except when receive-only mode is used
		// 1. Wait until RXNE=1
		// 2. Wait until TXE=1 and then wait until BSY=0 before disabling the SPI
		// 3. Read received data

		// ToDo: The correct disable procedure for certain receive-only modes is:
		// 1. Interrupt the receive flow by disabling SPI (SPE=0) in the specific time window while the last data frame is ongoing.
		// 2. Wait until BSY=0 (the last data frame is processed).
		// 3. Read received data.

		/** Note: To stop a continuous receive sequence, a specific time window must be respected during
		 * the reception of the last data frame. It starts when the first bit is sampled and ends before
		 * the last bit transfer starts.
		 */
		p_spi->SPIx_CR1 &= SPI_CR1_SPE_NMASK;
	}
}

void SPI_tx_data(t_SPI_RegDef * const p_spi, const uint8_t * const p_data, const uint32_t data_len)
{
	const t_bool dff_16_bit = ((p_spi->SPIx_CR1 & SPI_CR1_DFF_MASK) != 0u) ? TRUE : FALSE;
	uint32_t buf_idx = 0u;
	while (buf_idx < data_len) {
		// 1. Wait until transmit buffer empty
		while(spi_check_tx_buffer_empty(p_spi) == FALSE);

		// 2. Check Data Frame Format
		if (dff_16_bit != FALSE) { // 16-bit Data Format
			const uint16_t * const p_data_16bit = CAST_TO(const uint16_t * const, p_data);
			p_spi->SPIx_DR = p_data_16bit[buf_idx++];
		} else { // 8-bit data format
			p_spi->SPIx_DR = p_data[buf_idx];
		}

		buf_idx++;
	}
	// 3. Wait until transmit buffer empty
	while(spi_check_tx_buffer_empty(p_spi) == FALSE);
	// 4. Wait for BUSY flag to reset
	while(spi_check_tx_busy(p_spi) != FALSE);
	// 5. Clear overrun (OVR) flag
	spi_clear_ovr_flag(p_spi);
}

void SPI_rx_data(t_SPI_RegDef * const p_spi, uint8_t * const p_data, const uint32_t data_len)
{
	const t_bool dff_16_bit = ((p_spi->SPIx_CR1 & SPI_CR1_DFF_MASK) != 0u) ? TRUE : FALSE;
	uint32_t buf_idx = 0u;
	while (buf_idx < data_len) {
		// 1. Send dummy data to generate clock
		p_spi->SPIx_DR = 0u;
		// 2. Wait until receive buffer not empty
		while(spi_check_rx_buffer_nempty(p_spi) == FALSE);
		// 3. Check Data Frame Format
		if (dff_16_bit != FALSE) { // 16-bit Data Format
			uint16_t * const p_data_16bit = CAST_TO(uint16_t * const, p_data);
			p_data_16bit[buf_idx++] = (uint16_t)p_spi->SPIx_DR;
		} else { // 8-bit data format
			p_data[buf_idx] = (uint8_t)p_spi->SPIx_DR;
		}

		buf_idx++;
	}
}

const t_bool SPI_tx_data_it(t_spi_it_handle * const p_spi_handle, const uint8_t * const p_data, const uint32_t data_len)
{
	if (p_spi_handle->spi_tx_bsy == FALSE) {
		p_spi_handle->spi_tx_bsy = TRUE;

		p_spi_handle->p_tx_buffer = CAST_TO(uint8_t *, p_data);
		p_spi_handle->tx_len = data_len;

		p_spi_handle->p_spi_reg->SPIx_CR2 |= SPI_CR2_TXEIE_MASK;

		// Transmit data via ISR
	}

	return p_spi_handle->spi_tx_bsy;
}

t_bool SPI_rx_data_it(t_spi_it_handle * const p_spi_handle, uint8_t * const p_data, const uint32_t data_len)
{
	if (p_spi_handle->spi_rx_bsy == FALSE) {
		p_spi_handle->spi_rx_bsy = TRUE;

		p_spi_handle->p_rx_buffer = CAST_TO(uint8_t *, p_data);
		p_spi_handle->rx_len = data_len;

		p_spi_handle->p_spi_reg->SPIx_CR2 |= SPI_CR2_RXNEIE_MASK;

		// Receive data via ISR
	}

	return p_spi_handle->spi_rx_bsy;
}

t_error_code SPI_interrupt_config(const t_spi_port spi_sel, uint32_t spi_irq_prio)
{
	t_error_code ret_stat = e_ec_invalid_param;

	// Set interrupt priority and enable IT in NVIC
	const uint8_t nvic_exti_irq[] = {e_irq_SPI1, e_irq_SPI2, e_irq_SPI3, e_irq_SPI4};
	if (spi_sel < NUM_OF_ARRAY(nvic_exti_irq)) {
		const t_error_code it_prio_stat = CORTEX_M4_nvic_set_priority(nvic_exti_irq[spi_sel], spi_irq_prio);
		const t_error_code it_en_stat = CORTEX_M4_nvic_enable_irq(nvic_exti_irq[spi_sel], ENABLE);

		ret_stat = ((it_prio_stat == e_ec_no_error) && (it_en_stat == e_ec_no_error)) ? e_ec_no_error : e_ec_invalid_param;
	}

	return ret_stat;
}

void SPI_init_it_handle(t_spi_it_handle * const p_spi_handle, t_SPI_RegDef * const p_spi)
{
	p_spi_handle->p_spi_reg   = p_spi;
	p_spi_handle->p_tx_buffer = NULL;
	p_spi_handle->p_rx_buffer = NULL;
	p_spi_handle->tx_len	  = 0u;
	p_spi_handle->rx_len	  = 0u;
	p_spi_handle->spi_tx_bsy  = FALSE;
	p_spi_handle->spi_rx_bsy  = FALSE;
}

void SPI_irq_handle(t_spi_it_handle * const p_spi_handle)
{
	// Fetch event root cause
	const uint32_t spi_stat = p_spi_handle->p_spi_reg->SPIx_SR;
	const uint32_t spi_cr2	= p_spi_handle->p_spi_reg->SPIx_CR2;
	if (((spi_stat & SPI_SR_RXNE_MASK) != 0u) && ((spi_cr2 & SPI_CR2_RXNEIE_MASK) != 0u)) {
		// 1. Data received in Rx buffer (event: RXNE, enable: RXNEIE)
		spi_rxne_interrupt_handle(p_spi_handle);
	} else if (((spi_stat & SPI_SR_TXE_MASK) != 0u) && ((spi_cr2 & SPI_CR2_TXEIE_MASK) != 0u)) {
		// 2. Transmit Tx buffer ready to be loaded (event: TXE, enable: TXEIE)
		spi_txe_interrupt_handle(p_spi_handle);
	} else if (((spi_stat & SPI_SR_MODF_MASK) != 0u) && ((spi_cr2 & SPI_CR2_ERRIE_MASK) != 0u)) {
		// 3. Master mode fault (event: MODF, enable: ERRIE)

	} else if (((spi_stat & SPI_SR_OVR_MASK) != 0u) && ((spi_cr2 & SPI_CR2_ERRIE_MASK) != 0u)) {
		// 4. Overrun error (event: OVR, enable: ERRIE)
		spi_ovr_interrupt_handle(p_spi_handle);
	} else if (((spi_stat & SPI_SR_CRCERR_MASK) != 0u) && ((spi_cr2 & SPI_CR2_ERRIE_MASK) != 0u)) {
		// 5. CRC error (event: CRCERR, enable: ERRIE)

	} else if (((spi_stat & SPI_SR_FRE_MASK) != 0u) && ((spi_cr2 & SPI_CR2_ERRIE_MASK) != 0u)) {
		// 6. TI frame format error (event: FRE, enable: ERRIE)

	} else {
		// NOP
	}
}

void SPI_tx_it_close(t_spi_it_handle * const p_spi_handle)
{
	p_spi_handle->p_spi_reg->SPIx_CR2 &= SPI_CR2_TXEIE_NMASK;
	p_spi_handle->p_tx_buffer = NULL;
	p_spi_handle->tx_len = 0u;
	p_spi_handle->spi_tx_bsy = FALSE;
}

void SPI_rx_it_close(t_spi_it_handle * const p_spi_handle){
	p_spi_handle->p_spi_reg->SPIx_CR2 &= SPI_CR2_RXNEIE_NMASK;
	p_spi_handle->rx_len = 0u;
	p_spi_handle->p_rx_buffer = NULL;
	p_spi_handle->spi_rx_bsy = FALSE;
}

__WEAK void SPI_api_event_cb(const t_spi_it_handle * const p_spi_handle, const t_spi_event spi_event)
{
	// Implement SPI event callback at application level.
}

void SPI1_IRQHandler(void)
{
	t_SPI_RegDef * const p_spi = SPI_get_peri_base(e_spi_1);
	t_spi_it_handle spi_handle;
	SPI_init_it_handle(&spi_handle, p_spi);
	SPI_irq_handle(&spi_handle);
}

/*** EOF ***/
