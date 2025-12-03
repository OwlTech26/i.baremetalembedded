/**
 * Copyright (c) 2025 OwlTech
 *
 * \file seif_bmp280.h
 * \brief Sensor Interface for BMP280.
 * \author OwlTech
 * \date Dec 1, 2025
 */

#ifndef SEIF_BMP280_H_
#define SEIF_BMP280_H_

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
	e_bmp280_mode_sleep		= 0u,
	e_bmp280_mode_forced	= 1u,
	e_bmp280_mode_normal	= 3u,
	e_bmp280_mode_max		= 4u
} t_bmp280_mode;

typedef enum {
	e_bmp280_osrs_none		= 0u,
	e_bmp280_osrs_1x		= 1u,
	e_bmp280_osrs_2x		= 2u,
	e_bmp280_osrs_4x		= 3u,
	e_bmp280_osrs_8x		= 4u,
	e_bmp280_osrs_16x		= 5u,
	e_bmp280_osrs_max		= 8u
} t_bmp280_osrs;

typedef struct {
	t_bmp280_mode mode;
	t_bmp280_osrs press_ovs;
	t_bmp280_osrs temp_ovs;
} t_bmp280_ctrl_meas;

/** \brief BMP280 compensation parameter structure. */
typedef struct {	 // LSB  / MSB
	uint16_t dig_t1; // 0x88 / 0x89
	int16_t  dig_t2; // 0x8A / 0x8B
	int16_t  dig_t3; // 0x8C / 0x8D
	uint16_t dig_p1; // 0x8E / 0x8F
	int16_t  dig_p2; // 0x90 / 0x91
	int16_t  dig_p3; // 0x92 / 0x93
	int16_t  dig_p4; // 0x94 / 0x95
	int16_t  dig_p5; // 0x96 / 0x97
	int16_t  dig_p6; // 0x98 / 0x99
	int16_t  dig_p7; // 0x9A / 0x9B
	int16_t  dig_p8; // 0x9C / 0x9D
	int16_t  dig_p9; // 0x9E / 0x9F
	// RESERVED		 // 0xA0 / 0XA1
} t_bmp280_comp_params;

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
uint8_t SEIF_BMP280_get_id(void);

t_error_code SEIF_BMP280_set_meas_mode(const t_bmp280_ctrl_meas * const p_ctrl_meas);

uint8_t SEIF_BMP280_get_meas_mode(void);

uint32_t SEIF_BMP280_get_press_raw(void);

uint32_t SEIF_BMP280_get_temp_raw(void);

void SEIF_BMP280_get_comp_params(t_bmp280_comp_params * const p_comp_params);

/** \brief Get temperature in DegC, resolution is 0.01 DegC.
 *  \param
 *  \return Temperature in DegC.
 *  	\retval E.g.: "5123" equals to 51.23 DegC.
 */
int32_t SEIF_BMP280_get_temp_degc(const t_bmp280_comp_params * const p_comp_params, uint32_t * const p_temp_raw);

/** \brief Get pressure in Pa in Q23.8 format.
 *  \param
 *  \return Temperature in DegC.
 *  	\retval E.g.: "5123" equals to 51.23 DegC.
 */
uint32_t SEIF_BMP280_get_press_pa(const t_bmp280_comp_params * const p_comp_params, const uint32_t temp_raw);

#endif /* SEIF_BMP280_H_ */
/*** EOF ***/
