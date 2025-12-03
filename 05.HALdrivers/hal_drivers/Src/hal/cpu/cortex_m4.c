/**
 * Copyright (c) 2025 OwlTech
 *
 * \file cortex_m4.c
 * \brief
 * \author OwlTech
 * \date Nov 14, 2025
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "cortex_m4.h"

#include "hal_reg.h"
#include "cortex_m4_register.h"


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

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
/** \brief Selects the register offset for ISER/ICER/ISPR/ICPR/IABR NVIC registers according to the IRQ number.
 *  \param 
 *  \return 
 *  	\retval 
 */
static inline uint32_t cortex_m4_nvic_get_reg_offset(const uint32_t irq_num, const uint32_t reg0_ofs);


/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
/** \brief */
static inline uint32_t cortex_m4_nvic_get_reg_offset(const uint32_t irq_num, const uint32_t reg0_ofs)
{
	const uint32_t ret_ofs = ((irq_num / NVIC_IRQ_CHANNEL_PER_REG) * WORDS) + reg0_ofs;

	return ret_ofs;
}

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
/** \brief */

/******************************************************************************/
/*-----------------------API Function Implementations-------------------------*/
/******************************************************************************/
/** \brief */
t_error_code CORTEX_M4_nvic_enable_irq(const t_nvic_irq irq_num, const t_bool irq_en)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if (irq_num < e_irq_max) {
		ret_stat = e_ec_no_error;

		const uint8_t irq_bf = irq_num % NVIC_IRQ_CHANNEL_PER_REG;

		if (irq_en != FALSE) { // Enable IRQ
			const uint32_t iser_ofs_sel = cortex_m4_nvic_get_reg_offset(irq_num, NVIC_ISER0_OFS);
			switch (iser_ofs_sel) {
				case NVIC_ISER0_OFS: // IRQ 0..31
					NVIC_ISER0_SET(NVIC_ISER_IRQ_MASK(irq_bf));
					break;
				case NVIC_ISER1_OFS: // IRQ 32..63
					NVIC_ISER1_SET(NVIC_ISER_IRQ_MASK(irq_bf));
					break;
				case NVIC_ISER2_OFS: // IRQ 64..96
					NVIC_ISER2_SET(NVIC_ISER_IRQ_MASK(irq_bf));
					break;
				default:
					ret_stat = e_ec_unspecified_error;
					break;
			}
		} else { // Disable IRQ
			const uint8_t icer_ofs_sel = cortex_m4_nvic_get_reg_offset(irq_num, NVIC_ICER0_OFS);
			switch (icer_ofs_sel) {
				case NVIC_ICER0_OFS: // IRQ 0..31
					NVIC_ICER0_SET(NVIC_ICER_IRQ_MASK(irq_bf));
					break;
				case NVIC_ICER1_OFS: // IRQ 32..63
					NVIC_ICER1_SET(NVIC_ICER_IRQ_MASK(irq_bf));
					break;
				case NVIC_ICER2_OFS: // IRQ 64..96
					NVIC_ISER2_SET(NVIC_ICER_IRQ_MASK(irq_bf));
					break;
				default:
					ret_stat = e_ec_unspecified_error;
					break;
			}
		}
	}

	return ret_stat;
}

t_error_code CORTEX_M4_nvic_set_priority(const t_nvic_irq irq_num, const uint32_t irq_prio)
{
	t_error_code ret_stat = e_ec_invalid_param;

	if ((irq_num < e_irq_max) && (irq_prio < NVIC_IRQ_PRIO_LEVEL_MAX)) {
		const uint8_t ipr_reg_idx = irq_num / NVIC_IRQ_NUM_PER_PRIO_REG;
		uint32_t ipr_reg = NVIC_IPRx_GET(ipr_reg_idx);
		ipr_reg &= NVIC_IPRx_NMASK(irq_num);
		ipr_reg |= (irq_prio << NVIC_IPRx_POS(irq_num));
		NVIC_IPRx_SET(ipr_reg_idx, ipr_reg);

		ret_stat = e_ec_no_error;
	}

	return ret_stat;
}

uint32_t CORTEX_M4_nvic_get_priority(const t_nvic_irq irq_num)
{
	const uint8_t ipr_reg_idx = irq_num / NVIC_IRQ_NUM_PER_PRIO_REG;
	const uint32_t ipr_reg = NVIC_IPRx_GET(ipr_reg_idx);

	const uint32_t ret_val = (ipr_reg & NVIC_IPRx_MASK(irq_num)) >> NVIC_IPRx_POS(irq_num);

	return ret_val;
}


void CORTEX_M4_systick_configure(const t_bool tick_int, const t_bool clk_source)
{
	uint32_t systick_csr = SYST_CSR_GET();
	systick_csr &= (SYST_CSR_TICKINT_NMASK & SYST_CSR_CLKSOURCE_NMASK);
	systick_csr |= ((b_to_uint32(tick_int) << SYST_CSR_TICKINT_POS) | (b_to_uint32(clk_source) << SYST_CSR_CLKSOURCE_POS));
	SYST_CSR_SET(systick_csr);
}

void CORTEX_M4_systick_enable(const t_bool enable)
{
	uint32_t systick_csr = SYST_CSR_GET();
	if (enable != FALSE) {
		systick_csr |=  SYST_CSR_ENABLE_MASK;
	} else {
		systick_csr &=  SYST_CSR_ENABLE_NMASK;
	}
	SYST_CSR_SET(systick_csr);
}

uint32_t CORTEX_M4_systick_get_tmr(void)
{
	return SYST_CVR_GET();
}

void CORTEX_M4_systick_set_tmr(const uint32_t curr_val)
{
	SYST_CVR_SET(curr_val);
}

t_bool CORTEX_M4_systick_underflow(void)
{
	const uint32_t systick_stat = (SYST_CSR_GET() & SYST_CSR_COUNTFLAG_MASK) >> SYST_CSR_COUNTFLAG_POS;

	return (systick_stat != 0u) ? TRUE : FALSE;
}

uint32_t CORTEX_M4_systick_get_preload(void)
{
	return SYST_RVR_GET();
}

void CORTEX_M4_systick_set_preload(const uint32_t reload_val)
{
	SYST_RVR_SET(reload_val);
}

/*** EOF ***/
