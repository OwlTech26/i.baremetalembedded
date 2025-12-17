/**
 * Copyright (c) 2025 OwlTech
 *
 * \file seif_veml6040.h
 * \brief
 * \author OwlTech
 * \date Dec 15, 2025
 */

#ifndef SEIF_VEML6040_H_
#define SEIF_VEML6040_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include "common_def.h"


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef enum {
	e_veml6040_integ_40_ms		= 0u,
	e_veml6040_integ_80_ms		= 1u,
	e_veml6040_integ_160_ms		= 2u,
	e_veml6040_integ_320_ms		= 3u,
	e_veml6040_integ_640_ms		= 4u,
	e_veml6040_integ_1280_ms	= 5u,
	e_veml6040_integ_max		= 6u
} t_veml6040_integ;

typedef enum {
	e_veml6040_mem_0		= 0u,
	e_veml6040_mem_1		= 1u,
	e_veml6040_mem_2		= 2u,
	e_veml6040_mem_3		= 3u,
	e_veml6040_mem_4		= 4u,
	e_veml6040_mem_5		= 5u,
	e_veml6040_mem_6		= 6u,
	e_veml6040_mem_max		= 7u
} t_veml6040_memory;

typedef struct {
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	uint16_t white;
} t_veml6040_data;

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
void SEIF_VEML6040_set_id(const uint16_t chip_id);

uint16_t SEIF_VEML6040_get_id(void);

t_error_code SEIF_VEML6040_set_config(const t_veml6040_integ integ, const t_bool fmode_en, const t_bool pwr_on);

uint8_t SEIF_VEML6040_get_config(void);

void SEIF_VEML6040_set_pwr(const uint8_t conf_reg, const t_bool pwr_on);

void SEIF_VEML6040_single_meas(const uint8_t conf_reg);

void SEIF_VEML6040_read_light_data(t_veml6040_data * const p_data);

t_error_code SEIF_VEML6040_write_mem(const t_veml6040_memory mem_sel_start, const uint16_t * const p_data, const uint32_t data_len);

t_error_code SEIF_VEML6040_read_mem(const t_veml6040_memory mem_sel_start, uint16_t * const p_data, const uint32_t data_len);





#endif /* SEIF_VEML6040_H_ */
/*** EOF ***/
