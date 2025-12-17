/**
 * Copyright (c) 2025 OwlTech
 *
 * \file tsl2561_regmap.h
 * \brief
 * \author OwlTech
 * \date Dec 15, 2025
 */

#ifndef TSL2561_REGMAP_H_
#define TSL2561_REGMAP_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define TSL2561_ADDR_GND						(0b0101001u) //!< ADDR_SEL = GND
#define TSL2561_ADDR_FLOAT						(0b0111001u) //!< ADDR_SEL = FLOAT
#define TSL2561_ADDR_VDD						(0b1001001u) //!< ADDR_SEL = VDD
#define TSL2561_ADDR							TSL2561_ADDR_FLOAT

#define TSL2561_COMMAND_FIELD
	//!< Register Address. This field selects the specific control or status register for following write and read command.
	#define TSL2561_COMMAND_ADDRESS_WIDTH		(4u)
	#define TSL2561_COMMAND_ADDRESS_POS			(0u)
	#define TSL2561_COMMAND_ADDRESS_MASK		(HAL_BIT_CREATE_MASK(TSL2561_COMMAND_ADDRESS_POS, TSL2561_COMMAND_ADDRESS_WIDTH))
	#define TSL2561_COMMAND_ADDRESS_NMASK 		(~(TSL2561_COMMAND_ADDRESS_MASK))
	//!< Block Write/Read Protocol. 1 indicates that this transaction is using either the Block Write or the Block Read protocol.
	#define TSL2561_COMMAND_BLOCK_WIDTH			(1u)
	#define TSL2561_COMMAND_BLOCK_POS			(4u)
	#define TSL2561_COMMAND_BLOCK_MASK			(HAL_BIT_CREATE_MASK(TSL2561_COMMAND_BLOCK_POS, TSL2561_COMMAND_BLOCK_WIDTH))
	#define TSL2561_COMMAND_BLOCK_NMASK 		(~(TSL2561_COMMAND_BLOCK_MASK))
	//!< SMB Write/Read Word Protocol. 1 indicates that this SMB transaction is using either the SMB Write Word or Read Word protocol.
	#define TSL2561_COMMAND_WORD_WIDTH			(1u)
	#define TSL2561_COMMAND_WORD_POS			(5u)
	#define TSL2561_COMMAND_WORD_MASK			(HAL_BIT_CREATE_MASK(TSL2561_COMMAND_WORD_POS, TSL2561_COMMAND_WORD_WIDTH))
	#define TSL2561_COMMAND_WORD_NMASK 			(~(TSL2561_COMMAND_WORD_MASK))
	//!< Interrupt clear. Clears any pending interrupt. This bit is a write-one-to-clear bit. It is self clearing.
	#define TSL2561_COMMAND_CLEAR_WIDTH			(1u)
	#define TSL2561_COMMAND_CLEAR_POS			(6u)
	#define TSL2561_COMMAND_CLEAR_MASK			(HAL_BIT_CREATE_MASK(TSL2561_COMMAND_CLEAR_POS, TSL2561_COMMAND_CLEAR_WIDTH))
	#define TSL2561_COMMAND_CLEAR_NMASK 		(~(TSL2561_COMMAND_CLEAR_MASK))
	//!< Select command register. Must write as 1.
	#define TSL2561_COMMAND_CMD_WIDTH			(1u)
	#define TSL2561_COMMAND_CMD_POS				(7u)
	#define TSL2561_COMMAND_CMD_MASK			(HAL_BIT_CREATE_MASK(TSL2561_COMMAND_CMD_POS, TSL2561_COMMAND_CMD_WIDTH))
	#define TSL2561_COMMAND_CMD_NMASK 			(~(TSL2561_COMMAND_CMD_MASK))
#define TSL2561_CONTROL							(0x00u)
	#define TSL2561_CONTROL_LEN					(1u)
	#define TSL2561_CONTROL_POWER_OFF			(0u)
	#define TSL2561_CONTROL_POWER_ON			(3u)
		#define TSL2561_CONTROL_POWER_WIDTH		(2u)
		#define TSL2561_CONTROL_POWER_POS		(0u)
		#define TSL2561_CONTROL_POWER_MASK		(HAL_BIT_CREATE_MASK(TSL2561_CONTROL_POWER_POS, TSL2561_CONTROL_POWER_WIDTH))
		#define TSL2561_CONTROL_POWER_NMASK 	(~(TSL2561_CONTROL_POWER_MASK))
#define TSL2561_TIMING							(0x01u) //!< Integration time/gain control
	#define TSL2561_TIMING_LEN					1u
		//!< Integrate time. This field selects the integration time for each conversion.
		#define TSL2561_TIMING_INTEG_WIDTH		(2u)
		#define TSL2561_TIMING_INTEG_POS		(0u)
		#define TSL2561_TIMING_INTEG_MASK		(HAL_BIT_CREATE_MASK(TSL2561_TIMING_INTEG_POS, TSL2561_TIMING_INTEG_WIDTH))
		#define TSL2561_TIMING_INTEG_NMASK 		(~(TSL2561_TIMING_INTEG_MASK))
		//!< Manual timing control. Writing a 1 begins an integration cycle. Writing a 0 stops an integration cycle. NOTE: This field only has meaning when INTEG = 11. It is ignored at all.
		#define TSL2561_TIMING_MANUAL_WIDTH		(1u)
		#define TSL2561_TIMING_MANUAL_POS		(3u)
		#define TSL2561_TIMING_MANUAL_MASK		(HAL_BIT_CREATE_MASK(TSL2561_TIMING_MANUAL_POS, TSL2561_TIMING_MANUAL_WIDTH))
		#define TSL2561_TIMING_MANUAL_NMASK 	(~(TSL2561_TIMING_MANUAL_MASK))
		//!< Switches gain between low gain and high gain modes. Writing a 0 selects low gain (1×); writing a 1 selects high gain (16×).
		#define TSL2561_TIMING_GAIN_WIDTH		(1u)
		#define TSL2561_TIMING_GAIN_POS			(4u)
		#define TSL2561_TIMING_GAIN_MASK		(HAL_BIT_CREATE_MASK(TSL2561_TIMING_GAIN_POS, TSL2561_TIMING_GAIN_WIDTH))
		#define TSL2561_TIMING_GAIN_NMASK 		(~(TSL2561_TIMING_GAIN_MASK))
#define TSL2561_THRESHLOWLOW					(0x02u) //!< Low byte of low interrupt threshold
	#define TSL2561_THRESHLOWLOW_LEN			(1u)
#define TSL2561_THRESHLOWHIGH					(0x03u) //!< High byte of low interrupt threshold
	#define TSL2561_THRESHLOWHIGH_LEN			(1u)
#define TSL2561_THRESHHIGHLOW					(0x04u) //!< Low byte of high interrupt threshold
	#define TSL2561_THRESHHIGHLOW_LEN			(1u)
#define TSL2561_THRESHHIGHHIGH					(0x05u) //!< High byte of high interrupt threshold
	#define TSL2561_THRESHHIGHHIGH_LEN			(1u)
#define TSL2561_INTERRUPT						(0x06u) //!< Interrupt control
	#define TSL2561_INTERRUPT_LEN				1u
		//!< Interrupt persistence. Controls rate of interrupts to the host processor.
		#define TSL2561_INTERRUPT_PERSIST_WIDTH	(4u)
		#define TSL2561_INTERRUPT_PERSIST_POS	(0u)
		#define TSL2561_INTERRUPT_PERSIST_MASK	(HAL_BIT_CREATE_MASK(TSL2561_INTERRUPT_PERSIST_POS, TSL2561_INTERRUPT_PERSIST_WIDTH))
		#define TSL2561_INTERRUPT_PERSIST_NMASK (~(TSL2561_INTERRUPT_PERSIST_MASK))
		//!< INTR Control Select. This field determines mode of interrupt logic.
		#define TSL2561_INTERRUPT_INTR_WIDTH	(2u)
		#define TSL2561_INTERRUPT_INTR_POS		(4u)
		#define TSL2561_INTERRUPT_INTR_MASK		(HAL_BIT_CREATE_MASK(TSL2561_INTERRUPT_INTR_POS, TSL2561_INTERRUPT_INTR_WIDTH))
		#define TSL2561_INTERRUPT_INTR_NMASK 	(~(TSL2561_INTERRUPT_INTR_MASK))
#define TSL2561_ID								(0x0Au) //!< Part number/ Rev ID
	#define TSL2561_ID_LEN						(1u)
		#define TSL2561_ID_REVNO_WIDTH			(4u)
		#define TSL2561_ID_REVNO_POS			(0u)
		#define TSL2561_ID_REVNO_MASK			(HAL_BIT_CREATE_MASK(TSL2561_ID_REVNO_POS, TSL2561_ID_REVNO_WIDTH))
		#define TSL2561_ID_REVNO_NMASK 			(~(TSL2561_ID_REVNO_MASK))
		#define TSL2561_ID_PARTNO_WIDTH			(4u)
		#define TSL2561_ID_PARTNO_POS			(4u)
		#define TSL2561_ID_PARTNO_MASK			(HAL_BIT_CREATE_MASK(TSL2561_ID_PARTNO_POS, TSL2561_ID_PARTNO_WIDTH))
		#define TSL2561_ID_PARTNO_NMASK 		(~(TSL2561_ID_PARTNO_MASK))
#define TSL2561_DATA0LOW						(0x0Cu) //!< Low byte of ADC channel 0
	#define TSL2561_DATA0LOW_LEN				(1u)
#define TSL2561_DATA0HIGH						(0x0Du) //!< High byte of ADC channel 0
	#define TSL2561_DATA0HIGH_LEN				(1u)
#define TSL2561_DATA1LOW						(0x0Eu) //!< Low byte of ADC channel 1
	#define TSL2561_DATA1LOW_LEN				(1u)
#define TSL2561_DATA1HIGH						(0x0Fu) //!< High byte of ADC channel 1
	#define TSL2561_DATA1HIGH_LEN				(1u)

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

#endif /* TSL2561_REGMAP_H_ */
/*** EOF ***/
