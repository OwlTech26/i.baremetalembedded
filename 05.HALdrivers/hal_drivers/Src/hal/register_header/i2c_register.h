/**
 * Copyright (c) 2025 OwlTech
 *
 * \file i2c_register.h
 * \brief
 * \author OwlTech
 * \date Dec 8, 2025
 */

#ifndef I2C_REGISTER_H_
#define I2C_REGISTER_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define I2C1_BASE		(0x40005400u)
#define I2C2_BASE		(0x40005800u)
#define I2C3_BASE		(0x40005C00u)

#define I2C_CR1_OFS							(0x00u) //!< I2C control register 1.
	#define I2C_CR1_GET(base)				(HAL_REG_READ((base + I2C_CR1_OFS)))
	#define I2C_CR1_SET(base, data)			(HAL_REG_WRITE((base + I2C_CR1_OFS), (uint32_t)data))
		#define I2C_CR1_PE_WIDTH			(1u)
		#define I2C_CR1_PE_POS				(0u)
		#define I2C_CR1_PE_MASK				(HAL_BIT_CREATE_MASK(I2C_CR1_PE_POS, I2C_CR1_PE_WIDTH))
		#define I2C_CR1_PE_NMASK 			(~(I2C_CR1_PE_MASK))
		#define I2C_CR1_SMBUS_WIDTH			(1u)
		#define I2C_CR1_SMBUS_POS			(1u)
		#define I2C_CR1_SMBUS_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_SMBUS_POS, I2C_CR1_SMBUS_WIDTH))
		#define I2C_CR1_SMBUS_NMASK 		(~(I2C_CR1_SMBUS_MASK))
		#define I2C_CR1_SMBTYPE_WIDTH		(1u)
		#define I2C_CR1_SMBTYPE_POS			(3u)
		#define I2C_CR1_SMBTYPE_MASK		(HAL_BIT_CREATE_MASK(I2C_CR1_SMBTYPE_POS, I2C_CR1_SMBTYPE_WIDTH))
		#define I2C_CR1_SMBTYPE_NMASK 		(~(I2C_CR1_SMBTYPE_MASK))
		#define I2C_CR1_ENARP_WIDTH			(1u)
		#define I2C_CR1_ENARP_POS			(4u)
		#define I2C_CR1_ENARP_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_ENARP_POS, I2C_CR1_ENARP_WIDTH))
		#define I2C_CR1_ENARP_NMASK 		(~(I2C_CR1_ENARP_MASK))
		#define I2C_CR1_ENPEC_WIDTH			(1u)
		#define I2C_CR1_ENPEC_POS			(5u)
		#define I2C_CR1_ENPEC_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_ENPEC_POS, I2C_CR1_ENPEC_WIDTH))
		#define I2C_CR1_ENPEC_NMASK 		(~(I2C_CR1_ENPEC_MASK))
		#define I2C_CR1_ENGC_WIDTH			(1u)
		#define I2C_CR1_ENGC_POS			(6u)
		#define I2C_CR1_ENGC_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_ENGC_POS, I2C_CR1_ENGC_WIDTH))
		#define I2C_CR1_ENGC_NMASK 			(~(I2C_CR1_ENGC_MASK))
		#define I2C_CR1_NOSTRETCH_WIDTH		(1u)
		#define I2C_CR1_NOSTRETCH_POS		(7u)
		#define I2C_CR1_NOSTRETCH_MASK		(HAL_BIT_CREATE_MASK(I2C_CR1_NOSTRETCH_POS, I2C_CR1_NOSTRETCH_WIDTH))
		#define I2C_CR1_NOSTRETCH_NMASK 	(~(I2C_CR1_NOSTRETCH_MASK))
		#define I2C_CR1_START_WIDTH			(1u)
		#define I2C_CR1_START_POS			(8u)
		#define I2C_CR1_START_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_START_POS, I2C_CR1_START_WIDTH))
		#define I2C_CR1_START_NMASK 		(~(I2C_CR1_START_MASK))
		#define I2C_CR1_STOP_WIDTH			(1u)
		#define I2C_CR1_STOP_POS			(9u)
		#define I2C_CR1_STOP_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_STOP_POS, I2C_CR1_STOP_WIDTH))
		#define I2C_CR1_STOP_NMASK 			(~(I2C_CR1_STOP_MASK))
		#define I2C_CR1_ACK_WIDTH			(1u)
		#define I2C_CR1_ACK_POS				(10u)
		#define I2C_CR1_ACK_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_ACK_POS, I2C_CR1_ACK_WIDTH))
		#define I2C_CR1_ACK_NMASK 			(~(I2C_CR1_ACK_MASK))
		#define I2C_CR1_POS_WIDTH			(1u)
		#define I2C_CR1_POS_POS				(11u)
		#define I2C_CR1_POS_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_POS_POS, I2C_CR1_POS_WIDTH))
		#define I2C_CR1_POS_NMASK 			(~(I2C_CR1_POS_MASK))
		#define I2C_CR1_PEC_WIDTH			(1u)
		#define I2C_CR1_PEC_POS				(12u)
		#define I2C_CR1_PEC_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_PEC_POS, I2C_CR1_PEC_WIDTH))
		#define I2C_CR1_PEC_NMASK 			(~(I2C_CR1_PEC_MASK))
		#define I2C_CR1_ALERT_WIDTH			(1u)
		#define I2C_CR1_ALERT_POS			(13u)
		#define I2C_CR1_ALERT_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_ALERT_POS, I2C_CR1_ALERT_WIDTH))
		#define I2C_CR1_ALERT_NMASK 		(~(I2C_CR1_ALERT_MASK))
		#define I2C_CR1_SWRST_WIDTH			(1u)
		#define I2C_CR1_SWRST_POS			(15u)
		#define I2C_CR1_SWRST_MASK			(HAL_BIT_CREATE_MASK(I2C_CR1_SWRST_POS, I2C_CR1_SWRST_WIDTH))
		#define I2C_CR1_SWRST_NMASK 		(~(I2C_CR1_SWRST_MASK))
#define I2C_CR2_OFS							(0x04u) //!< I2C control register 2.
	#define I2C_CR2_GET(base)				(HAL_REG_READ((base + I2C_CR2_OFS)))
	#define I2C_CR2_SET(base, data)			(HAL_REG_WRITE((base + I2C_CR2_OFS), (uint32_t)data))
		#define I2C_CR2_FREQ_WIDTH			(6u)
		#define I2C_CR2_FREQ_POS			(0u)
		#define I2C_CR2_FREQ_MASK			(HAL_BIT_CREATE_MASK(I2C_CR2_FREQ_POS, I2C_CR2_FREQ_WIDTH))
		#define I2C_CR2_FREQ_NMASK 			(~(I2C_CR2_FREQ_MASK))
		#define I2C_CR2_ITERREN_WIDTH		(1u)
		#define I2C_CR2_ITERREN_POS			(8u)
		#define I2C_CR2_ITERREN_MASK		(HAL_BIT_CREATE_MASK(I2C_CR2_ITERREN_POS, I2C_CR2_ITERREN_WIDTH))
		#define I2C_CR2_ITERREN_NMASK 		(~(I2C_CR2_ITERREN_MASK))
		#define I2C_CR2_ITEVTEN_WIDTH		(1u)
		#define I2C_CR2_ITEVTEN_POS			(9u)
		#define I2C_CR2_ITEVTEN_MASK		(HAL_BIT_CREATE_MASK(I2C_CR2_ITEVTEN_POS, I2C_CR2_ITEVTEN_WIDTH))
		#define I2C_CR2_ITEVTEN_NMASK 		(~(I2C_CR2_ITEVTEN_MASK))
		#define I2C_CR2_ITBUFEN_WIDTH		(1u)
		#define I2C_CR2_ITBUFEN_POS			(10u)
		#define I2C_CR2_ITBUFEN_MASK		(HAL_BIT_CREATE_MASK(I2C_CR2_ITBUFEN_POS, I2C_CR2_ITBUFEN_WIDTH))
		#define I2C_CR2_ITBUFEN_NMASK 		(~(I2C_CR2_ITBUFEN_MASK))
		#define I2C_CR2_DMAEN_WIDTH			(1u)
		#define I2C_CR2_DMAEN_POS			(11u)
		#define I2C_CR2_DMAEN_MASK			(HAL_BIT_CREATE_MASK(I2C_CR2_DMAEN_POS, I2C_CR2_DMAEN_WIDTH))
		#define I2C_CR2_DMAEN_NMASK 		(~(I2C_CR2_DMAEN_MASK))
		#define I2C_CR2_LAST_WIDTH			(1u)
		#define I2C_CR2_LAST_POS			(12u)
		#define I2C_CR2_LAST_MASK			(HAL_BIT_CREATE_MASK(I2C_CR2_LAST_POS, I2C_CR2_LAST_WIDTH))
		#define I2C_CR2_LAST_NMASK 			(~(I2C_CR2_LAST_MASK))
#define I2C_OAR1_OFS						(0x08u) //!< I2C own address register 1.
	#define I2C_OAR1_GET(base)				(HAL_REG_READ((base + I2C_OAR1_OFS)))
	#define I2C_OAR1_SET(base, data)		(HAL_REG_WRITE((base + I2C_OAR1_OFS), (uint32_t)data))
		#define I2C_OAR1_ADD0_WIDTH			(1u)
		#define I2C_OAR1_ADD0_POS			(0u)
		#define I2C_OAR1_ADD0_MASK			(HAL_BIT_CREATE_MASK(I2C_OAR1_ADD0_POS, I2C_OAR1_ADD0_WIDTH))
		#define I2C_OAR1_ADD0_NMASK 		(~(I2C_OAR1_ADD0_MASK))
		#define I2C_OAR1_ADD7_1_WIDTH		(7u)
		#define I2C_OAR1_ADD7_1_POS			(1u)
		#define I2C_OAR1_ADD7_1_MASK		(HAL_BIT_CREATE_MASK(I2C_OAR1_ADD7_1_POS, I2C_OAR1_ADD7_1_WIDTH))
		#define I2C_OAR1_ADD7_1_NMASK 		(~(I2C_OAR1_ADD7_1_MASK))
		#define I2C_OAR1_ADD9_8_WIDTH		(2u)
		#define I2C_OAR1_ADD9_8_POS			(8u)
		#define I2C_OAR1_ADD9_8_MASK		(HAL_BIT_CREATE_MASK(I2C_OAR1_ADD9_8_POS, I2C_OAR1_ADD9_8_WIDTH))
		#define I2C_OAR1_ADD9_8_NMASK 		(~(I2C_OAR1_ADD9_8_MASK))
		#define I2C_OAR1_ADD14_WIDTH		(1u)
		#define I2C_OAR1_ADD14_POS			(14u)
		#define I2C_OAR1_ADD14_MASK			(HAL_BIT_CREATE_MASK(I2C_OAR1_ADD14_POS, I2C_OAR1_ADD14_WIDTH))
		#define I2C_OAR1_ADD14_NMASK 		(~(I2C_OAR1_ADD14_MASK))
		#define I2C_OAR1_ADD_MODE_WIDTH		(1u)
		#define I2C_OAR1_ADD_MODE_POS		(15u)
		#define I2C_OAR1_ADD_MODE_MASK		(HAL_BIT_CREATE_MASK(I2C_OAR1_ADD_MODE_POS, I2C_OAR1_ADD_MODE_WIDTH))
		#define I2C_OAR1_ADD_MODE_NMASK 	(~(I2C_OAR1_ADD_MODE_MASK))
#define I2C_OAR2_OFS						(0x0Cu) //!< I2C own address register 2.
	#define I2C_OAR2_GET(base)				(HAL_REG_READ((base + I2C_OAR2_OFS)))
	#define I2C_OAR2_SET(base, data)		(HAL_REG_WRITE((base + I2C_OAR2_OFS), (uint32_t)data))
		#define I2C_OAR2_ENDUAL_WIDTH		(1u)
		#define I2C_OAR2_ENDUAL_POS			(0u)
		#define I2C_OAR2_ENDUAL_MASK		(HAL_BIT_CREATE_MASK(I2C_OAR2_ENDUAL_POS, I2C_OAR2_ENDUAL_WIDTH))
		#define I2C_OAR2_ENDUAL_NMASK 		(~(I2C_OAR2_ENDUAL_MASK))
		#define I2C_OAR2_ADD7_1_WIDTH		(7u)
		#define I2C_OAR2_ADD7_1_POS			(1u)
		#define I2C_OAR2_ADD7_1_MASK		(HAL_BIT_CREATE_MASK(I2C_OAR2_ADD7_1_POS, I2C_OAR2_ADD7_1_WIDTH))
		#define I2C_OAR2_ADD7_1_NMASK 		(~(I2C_OAR2_ADD7_1_MASK))
#define I2C_DR_OFS							(0x10u) //!< I2C data register.
	#define I2C_DR_GET(base)				(HAL_REG_READ((base + I2C_DR_OFS)))
	#define I2C_DR_SET(base, data)			(HAL_REG_WRITE((base + I2C_DR_OFS), (uint32_t)data))
	#define I2C_DR_WIDTH					(8u)
	#define I2C_DR_POS						(0u)
	#define I2C_DR_MASK						(HAL_BIT_CREATE_MASK(I2C_DR_POS, I2C_DR_WIDTH))
	#define I2C_DR_NMASK 					(~(I2C_DR_MASK))
#define I2C_SR1_OFS							(0x14u) //!< I2C status register 1.
	#define I2C_SR1_GET(base)				(HAL_REG_READ((base + I2C_SR1_OFS)))
	#define I2C_SR1_SET(base, data)			(HAL_REG_WRITE((base + I2C_SR1_OFS), (uint32_t)data))
		#define I2C_SR1_SB_WIDTH			(1u)
		#define I2C_SR1_SB_POS				(0u)
		#define I2C_SR1_SB_MASK				(HAL_BIT_CREATE_MASK(I2C_SR1_SB_POS, I2C_SR1_SB_WIDTH))
		#define I2C_SR1_SB_NMASK 			(~(I2C_SR1_SB_MASK))
		#define I2C_SR1_ADDR_WIDTH			(1u)
		#define I2C_SR1_ADDR_POS			(1u)
		#define I2C_SR1_ADDR_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_ADDR_POS, I2C_SR1_ADDR_WIDTH))
		#define I2C_SR1_ADDR_NMASK 			(~(I2C_SR1_ADDR_MASK))
		#define I2C_SR1_BTF_WIDTH			(1u)
		#define I2C_SR1_BTF_POS				(2u)
		#define I2C_SR1_BTF_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_BTF_POS, I2C_SR1_BTF_WIDTH))
		#define I2C_SR1_BTF_NMASK 			(~(I2C_SR1_BTF_MASK))
		#define I2C_SR1_ADD10_WIDTH			(1u)
		#define I2C_SR1_ADD10_POS			(3u)
		#define I2C_SR1_ADD10_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_ADD10_POS, I2C_SR1_ADD10_WIDTH))
		#define I2C_SR1_ADD10_NMASK 		(~(I2C_SR1_ADD10_MASK))
		#define I2C_SR1_STOPF_WIDTH			(1u)
		#define I2C_SR1_STOPF_POS			(4u)
		#define I2C_SR1_STOPF_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_STOPF_POS, I2C_SR1_STOPF_WIDTH))
		#define I2C_SR1_STOPF_NMASK 		(~(I2C_SR1_STOPF_MASK))
		#define I2C_SR1_RXNE_WIDTH			(1u)
		#define I2C_SR1_RXNE_POS			(6u)
		#define I2C_SR1_RXNE_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_RXNE_POS, I2C_SR1_RXNE_WIDTH))
		#define I2C_SR1_RXNE_NMASK 			(~(I2C_SR1_RXNE_MASK))
		#define I2C_SR1_TXE_WIDTH			(1u)
		#define I2C_SR1_TXE_POS				(7u)
		#define I2C_SR1_TXE_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_TXE_POS, I2C_SR1_TXE_WIDTH))
		#define I2C_SR1_TXE_NMASK 			(~(I2C_SR1_TXE_MASK))
		#define I2C_SR1_BERR_WIDTH			(1u)
		#define I2C_SR1_BERR_POS			(8u)
		#define I2C_SR1_BERR_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_BERR_POS, I2C_SR1_BERR_WIDTH))
		#define I2C_SR1_BERR_NMASK 			(~(I2C_SR1_BERR_MASK))
		#define I2C_SR1_ARLO_WIDTH			(1u)
		#define I2C_SR1_ARLO_POS			(9u)
		#define I2C_SR1_ARLO_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_ARLO_POS, I2C_SR1_ARLO_WIDTH))
		#define I2C_SR1_ARLO_NMASK 			(~(I2C_SR1_ARLO_MASK))
		#define I2C_SR1_AF_WIDTH			(1u)
		#define I2C_SR1_AF_POS				(10u)
		#define I2C_SR1_AF_MASK				(HAL_BIT_CREATE_MASK(I2C_SR1_AF_POS, I2C_SR1_AF_WIDTH))
		#define I2C_SR1_AF_NMASK 			(~(I2C_SR1_AF_MASK))
		#define I2C_SR1_OVR_WIDTH			(1u)
		#define I2C_SR1_OVR_POS				(11u)
		#define I2C_SR1_OVR_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_OVR_POS, I2C_SR1_OVR_WIDTH))
		#define I2C_SR1_OVR_NMASK 			(~(I2C_SR1_OVR_MASK))
		#define I2C_SR1_PECERR_WIDTH		(1u)
		#define I2C_SR1_PECERR_POS			(12u)
		#define I2C_SR1_PECERR_MASK			(HAL_BIT_CREATE_MASK(I2C_SR1_PECERR_POS, I2C_SR1_PECERR_WIDTH))
		#define I2C_SR1_PECERR_NMASK 		(~(I2C_SR1_PECERR_MASK))
		#define I2C_SR1_TIMEOUT_WIDTH		(1u)
		#define I2C_SR1_TIMEOUT_POS			(14u)
		#define I2C_SR1_TIMEOUT_MASK		(HAL_BIT_CREATE_MASK(I2C_SR1_TIMEOUT_POS, I2C_SR1_TIMEOUT_WIDTH))
		#define I2C_SR1_TIMEOUT_NMASK 		(~(I2C_SR1_TIMEOUT_MASK))
		#define I2C_SR1_SMBALERT_WIDTH		(1u)
		#define I2C_SR1_SMBALERT_POS		(15u)
		#define I2C_SR1_SMBALERT_MASK		(HAL_BIT_CREATE_MASK(I2C_SR1_SMBALERT_POS, I2C_SR1_SMBALERT_WIDTH))
		#define I2C_SR1_SMBALERT_NMASK 		(~(I2C_SR1_SMBALERT_MASK))
#define I2C_SR2_OFS							(0x18u) //!< I2C status register 2.
	#define I2C_SR2_GET(base)				(HAL_REG_READ((base + I2C_SR2_OFS)))
		#define I2C_SR2_MSL_WIDTH			(1u)
		#define I2C_SR2_MSL_POS				(0u)
		#define I2C_SR2_MSL_MASK			(HAL_BIT_CREATE_MASK(I2C_SR2_MSL_POS, I2C_SR2_MSL_WIDTH))
		#define I2C_SR2_MSL_NMASK 			(~(I2C_SR2_MSL_MASK))
		#define I2C_SR2_BUSY_WIDTH			(1u)
		#define I2C_SR2_BUSY_POS			(1u)
		#define I2C_SR2_BUSY_MASK			(HAL_BIT_CREATE_MASK(I2C_SR2_BUSY_POS, I2C_SR2_BUSY_WIDTH))
		#define I2C_SR2_BUSY_NMASK 			(~(I2C_SR2_BUSY_MASK))
		#define I2C_SR2_TRA_WIDTH			(1u)
		#define I2C_SR2_TRA_POS				(2u)
		#define I2C_SR2_TRA_MASK			(HAL_BIT_CREATE_MASK(I2C_SR2_TRA_POS, I2C_SR2_TRA_WIDTH))
		#define I2C_SR2_TRA_NMASK 			(~(I2C_SR2_TRA_MASK))
		#define I2C_SR2_GENCALL_WIDTH		(1u)
		#define I2C_SR2_GENCALL_POS			(4u)
		#define I2C_SR2_GENCALL_MASK		(HAL_BIT_CREATE_MASK(I2C_SR2_GENCALL_POS, I2C_SR2_GENCALL_WIDTH))
		#define I2C_SR2_GENCALL_NMASK 		(~(I2C_SR2_GENCALL_MASK))
		#define I2C_SR2_SMBDEFAULT_WIDTH	(1u)
		#define I2C_SR2_SMBDEFAULT_POS		(5u)
		#define I2C_SR2_SMBDEFAULT_MASK		(HAL_BIT_CREATE_MASK(I2C_SR2_SMBDEFAULT_POS, I2C_SR2_SMBDEFAULT_WIDTH))
		#define I2C_SR2_SMBDEFAULT_NMASK 	(~(I2C_SR2_SMBDEFAULT_MASK))
		#define I2C_SR2_SMBHOST_WIDTH		(1u)
		#define I2C_SR2_SMBHOST_POS			(6u)
		#define I2C_SR2_SMBHOST_MASK		(HAL_BIT_CREATE_MASK(I2C_SR2_SMBHOST_POS, I2C_SR2_SMBHOST_WIDTH))
		#define I2C_SR2_SMBHOST_NMASK 		(~(I2C_SR2_SMBHOST_MASK))
		#define I2C_SR2_DUALF_WIDTH			(1u)
		#define I2C_SR2_DUALF_POS			(7u)
		#define I2C_SR2_DUALF_MASK			(HAL_BIT_CREATE_MASK(I2C_SR2_DUALF_POS, I2C_SR2_DUALF_WIDTH))
		#define I2C_SR2_DUALF_NMASK 		(~(I2C_SR2_DUALF_MASK))
		#define I2C_SR2_PEC_WIDTH			(8u)
		#define I2C_SR2_PEC_POS				(8u)
		#define I2C_SR2_PEC_MASK			(HAL_BIT_CREATE_MASK(I2C_SR2_PEC_POS, I2C_SR2_PEC_WIDTH))
		#define I2C_SR2_PEC_NMASK 			(~(I2C_SR2_PEC_MASK))
#define I2C_CCR_OFS							(0x1Cu) //!< I2C clock control register.
	#define I2C_CCR_GET(base)				(HAL_REG_READ((base + I2C_CCR_OFS)))
	#define I2C_CCR_SET(base, data)			(HAL_REG_WRITE((base + I2C_CCR_OFS), (uint32_t)data))
		#define I2C_CCR_CCR_WIDTH			(12u)
		#define I2C_CCR_CCR_POS				(0u)
		#define I2C_CCR_CCR_MASK			(HAL_BIT_CREATE_MASK(I2C_CCR_CCR_POS, I2C_CCR_CCR_WIDTH))
		#define I2C_CCR_CCR_NMASK 			(~(I2C_CCR_CCR_MASK))
		#define I2C_CCR_DUTY_WIDTH			(1u)
		#define I2C_CCR_DUTY_POS			(14u)
		#define I2C_CCR_DUTY_MASK			(HAL_BIT_CREATE_MASK(I2C_CCR_DUTY_POS, I2C_CCR_DUTY_WIDTH))
		#define I2C_CCR_DUTY_NMASK 			(~(I2C_CCR_DUTY_MASK))
		#define I2C_CCR_FPS_WIDTH			(1u)
		#define I2C_CCR_FPS_POS				(15u)
		#define I2C_CCR_FPS_MASK			(HAL_BIT_CREATE_MASK(I2C_CCR_FPS_POS, I2C_CCR_FPS_WIDTH))
		#define I2C_CCR_FPS_NMASK 			(~(I2C_CCR_FPS_MASK))
#define I2C_TRISE_OFS						(0x20u) //!< I2C rise time register.
	#define I2C_TRISE_GET(base)				(HAL_REG_READ((base + I2C_TRISE_OFS)))
	#define I2C_TRISE_SET(base, data)		(HAL_REG_WRITE((base + I2C_TRISE_OFS), (uint32_t)data))
	#define I2C_TRISE_WIDTH					(6u)
	#define I2C_TRISE_POS					(0u)
	#define I2C_TRISE_MASK					(HAL_BIT_CREATE_MASK(I2C_TRISE_POS, I2C_TRISE_WIDTH))
	#define I2C_TRISE_NMASK 				(~(I2C_TRISE_MASK))
#define I2C_FLTR_OFS						(0x24u) //!< I2C filter register.
	#define I2C_FLTR_GET(base)				(HAL_REG_READ((base + I2C_FLTR_OFS)))
	#define I2C_FLTR_SET(base, data)		(HAL_REG_WRITE((base + I2C_FLTR_OFS), (uint32_t)data))
		#define I2C_FLTR_DNF_WIDTH			(4u)
		#define I2C_FLTR_DNF_POS			(0u)
		#define I2C_FLTR_DNF_MASK			(HAL_BIT_CREATE_MASK(I2C_FLTR_DNF_POS, I2C_FLTR_DNF_WIDTH))
		#define I2C_FLTR_DNF_NMASK 			(~(I2C_FLTR_DNF_MASK))
		#define I2C_FLTR_ANOFF_WIDTH		(1u)
		#define I2C_FLTR_ANOFF_POS			(4u)
		#define I2C_FLTR_ANOFF_MASK			(HAL_BIT_CREATE_MASK(I2C_FLTR_ANOFF_POS, I2C_FLTR_ANOFF_WIDTH))
		#define I2C_FLTR_ANOFF_NMASK 		(~(I2C_FLTR_ANOFF_MASK))

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

#endif /* I2C_REGISTER_H_ */
/*** EOF ***/
