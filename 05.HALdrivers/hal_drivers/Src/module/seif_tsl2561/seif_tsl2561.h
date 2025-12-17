/**
 * Copyright (c) 2025 OwlTech
 *
 * \file seif_tsl2561.h
 * \brief
 * \author OwlTech
 * \date Dec 15, 2025
 */

#ifndef SEIF_TSL2561_H_
#define SEIF_TSL2561_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "common_def.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define SEIF_TSL2561_INT_PERSIST_MAX	(16u)


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef enum {
	e_tsl2561_integ_13p7_ms		= 0u,
	e_tsl2561_integ_101_ms		= 1u,
	e_tsl2561_integ_402_ms		= 2u,
	e_tsl2561_integ_man_ctrl	= 3u,
	e_tsl2561_integ_max			= 4u
} t_tsl2561_integ;

typedef enum {
	e_tsl2561_intr_disable		= 0u, //!< Interrupt output disabled.
	e_tsl2561_intr_it_level		= 1u, //!< Level Interrupt.
	e_tsl2561_intr_smb_alert	= 2u, //!< SMBAlert compliant.
	e_tsl2561_intr_test_mode	= 3u, //!< Test Mode: Sets interrupt and functions as mode 10.
	e_tsl2561_intr_max			= 4u
} t_tsl2561_intr;

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
uint8_t SEIF_TSL2561_get_id(void);

t_error_code SEIF_TSL2561_set_config(const t_tsl2561_integ integ, t_bool gain_16x_en);

uint8_t SEIF_TSL2561_get_config(void);

void SEIF_TSL2561_integ_man_ctrl(const uint8_t timing_reg, const t_bool start_en);

uint8_t SEIF_TSL2561_get_pwr(void);

void SEIF_TSL2561_set_pwr(const t_bool pwr_on);

uint16_t SEIF_TSL2561_read_visible_ir(void);

uint16_t SEIF_TSL2561_read_ir_only(void);

void SEIF_TSL2561_set_it_threshold(const uint16_t thres_low, const uint16_t thres_high);

t_error_code SEIF_TSL2561_set_it_ctrl(const t_tsl2561_intr intr, const uint8_t intr_pers_sel);

void SEIF_TSL2561_clear_it(void);

#endif /* SEIF_TSL2561_H_ */
/*** EOF ***/
