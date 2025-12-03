/**
 * Copyright (c) 2025 OwlTech
 *
 * \file cortex_m4.h
 * \brief
 * \author OwlTech
 * \date Nov 19, 2025
 */

#ifndef CORTEX_M4_H_
#define CORTEX_M4_H_

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
	e_irq_WWDG 			= 0u,  //!< Window Watchdog interrupt
	e_irq_PVD 			= 1u,  //!< PVD through EXTI line detection interrupt
	e_irq_TAMP_STAMP 	= 2u,  //!< Tamper and TimeStamp interrupts through the EXTI line
	e_irq_RTC_WKUP 		= 3u,  //!< RTC Wakeup interrupt through the EXTI line
	e_irq_FLASH 		= 4u,  //!< Flash global interrupt
	e_irq_RCC 			= 5u,  //!< RCC global interrupt
	e_irq_EXTI0 		= 6u,  //!< EXTI Line0 interrupt
	e_irq_EXTI1 		= 7u,  //!< EXTI Line1 interrupt
	e_irq_EXTI2 		= 8u,  //!< EXTI Line2 interrupt
	e_irq_EXTI3 		= 9u,  //!< EXTI Line3 interrupt
	e_irq_EXTI4 		= 10u, //!< EXTI Line4 interrupt
	e_irq_DMA1_Stream0 	= 11u, //!< DMA1 Stream0 global interrupt
	e_irq_DMA1_Stream1 	= 12u, //!< DMA1 Stream1 global interrupt
	e_irq_DMA1_Stream2 	= 13u, //!< DMA1 Stream2 global interrupt
	e_irq_DMA1_Stream3 	= 14u, //!< DMA1 Stream3 global interrupt
	e_irq_DMA1_Stream4 	= 15u, //!< DMA1 Stream4 global interrupt
	e_irq_DMA1_Stream5 	= 16u, //!< DMA1 Stream5 global interrupt
	e_irq_DMA1_Stream6 	= 17u, //!< DMA1 Stream6 global interrupt
	e_irq_ADC 			= 18u, //!< ADC1, ADC2 and ADC3 global interrupts
	e_irq_CAN1_TX 		= 19u, //!< CAN1 TX interrupts
	e_irq_CAN1_RX0 		= 20u, //!< CAN1 RX0 interrupts
	e_irq_CAN1_RX1 		= 21u, //!< CAN1 RX1 interrupt
	e_irq_CAN1_SCE 		= 22u, //!< CAN1 SCE interrupt
	e_irq_EXTI9_5 		= 23u, //!< EXTI Line[9:5] interrupts
	e_irq_TIM1_BRK_TIM9 = 24u, //!< TIM1 Break interrupt and TIM9 global interrupt
	e_irq_TIM1_UP_TIM10	= 25u, //!< TIM1 Update interrupt and TIM10 global interrupt
	e_irq_TIM1_TRG_COM_TIM11 = 26u, //!< TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
	e_irq_TIM1_CC 		= 27u, //!< TIM1 Capture compare interrupt
	e_irq_TIM2 			= 28u, //!< TIM2 global interrupt
	e_irq_TIM3 			= 29u, //!< TIM3 global interrupt
	e_irq_TIM4 			= 30u, //!< TIM4 global interrupt
	e_irq_I2C1_EV 		= 31u, //!< I2C1 event interrupt
	e_irq_I2C1_ER 		= 32u, //!< I2C1 error interrupt
	e_irq_I2C2_EV 		= 33u, //!< I2C2 event interrupt
	e_irq_I2C2_ER 		= 34u, //!< I2C2 error interrupt
	e_irq_SPI1 			= 35u, //!< SPI1 global interrupt
	e_irq_SPI2 			= 36u, //!< SPI2 global interrupt
	e_irq_USART1 		= 37u, //!< USART1 global interrupt
	e_irq_USART2 		= 38u, //!< USART2 global interrupt
	e_irq_USART3 		= 39u, //!< USART3 global interrupt
	e_irq_EXTI15_10 	= 40u, //!< EXTI Line[15:10] interrupts
	e_irq_RTC_Alarm 	= 41u, //!< RTC Alarms (A and B) through EXTI line interrupt
	e_irq_OTG_FS_WKUP 	= 42u, //!< USB On-The-Go FS Wakeup through EXTI line interrupt
	e_irq_TIM8_BRK_TIM12 = 43u, //!< TIM8 break interrupt and TIM12 global interrupt
	e_irq_TIM8_UP_TIM13 = 44u, //!< TIM8 Update interrupt and TIM13 global interrupt
	e_irq_TIM8_TRG_COM_TIM14 = 45u, //!< TIM8 Trigger and Commutation interrupts and TIM14 global interrupt
	e_irq_TIM8_CC 		= 46u, //!< TIM8 Capture compare interrupt
	e_irq_DMA1_Stream7 	= 47u, //!< DMA1 Stream7 global interrupt
	e_irq_FMC 			= 48u, //!< FMC global interrupt
	e_irq_SDIO 			= 49u, //!< SDIO global interrupt
	e_irq_TIM5 			= 50u, //!< TIM5 global interrupt
	e_irq_SPI3 			= 51u, //!< SPI3 global interrupt
	e_irq_UART4 		= 52u, //!< UART4 global interrupt
	e_irq_UART5 		= 53u, //!< UART5 global interrupt
	e_irq_TIM6_DAC 		= 54u, //!< TIM6 global interrupt,DAC1 and DAC2 underrun error interrupts
	e_irq_TIM7 			= 55u, //!< TIM7 global interrupt
	e_irq_DMA2_Stream0 	= 56u, //!< DMA2 Stream0 global interrupt
	e_irq_DMA2_Stream1 	= 57u, //!< DMA2 Stream1 global interrupt
	e_irq_DMA2_Stream2 	= 58u, //!< DMA2 Stream2 global interrupt
	e_irq_DMA2_Stream3 	= 59u, //!< DMA2 Stream3 global interrupt
	e_irq_DMA2_Stream4 	= 60u, //!< DMA2 Stream4 global interrupt
	e_irq_CAN2_TX 		= 63u, //!< CAN2 TX interrupts
	e_irq_CAN2_RX0 		= 64u, //!< CAN2 RX0 interrupts
	e_irq_CAN2_RX1 		= 65u, //!< CAN2 RX1 interrupt
	e_irq_CAN2_SCE 		= 66u, //!< CAN2 SCE interrupt
	e_irq_OTG_FS 		= 67u, //!< USB On The Go FS global interrupt
	e_irq_DMA2_Stream5 	= 68u, //!< DMA2 Stream5 global interrupt
	e_irq_DMA2_Stream6 	= 69u, //!< DMA2 Stream6 global interrupt
	e_irq_DMA2_Stream7 	= 70u, //!< DMA2 Stream7 global interrupt
	e_irq_USART6 		= 71u, //!< USART6 global interrupt
	e_irq_I2C3_EV 		= 72u, //!< I2C3 event interrupt
	e_irq_I2C3_ER 		= 73u, //!< I2C3 error interrupt
	e_irq_OTG_HS_EP1_OUT = 74u, //!< USB On The Go HS End Point 1 Out global interrupt
	e_irq_OTG_HS_EP1_IN = 75u, //!< USB On The Go HS End Point 1 In global interrupt
	e_irq_OTG_HS_WKUP 	= 76u, //!< USB On The Go HS Wakeup through EXTI interrupt
	e_irq_OTG_HS 		= 77u, //!< USB On The Go HS global interrupt
	e_irq_DCMI 			= 78u, //!< DCMI global interrupt
	e_irq_FPU 			= 81u, //!< FPU global interrupt
	e_irq_SPI4 			= 84u, //!< SPI 4 global interrupt
	e_irq_SAI1 			= 87u, //!< SAI1 global interrupt
	e_irq_SAI2 			= 91u, //!< SAI2 global interrupt
	e_irq_QuadSPI 		= 92u, //!< QuadSPI global interrupt
	e_irq_HDMI_CEC 		= 93u, //!< HDMI-CEC global interrupt
	e_irq_SPDIF_Rx 		= 94u, //!< SPDIF-Rx global interrupt
	e_irq_FMPI2C1 		= 95u, //!< FMPI2C1 event interrupt
	e_irq_FMPI2C1_error	= 96u, //!< FMPI2C1 error interrupt
	e_irq_max 			= 97u
} t_nvic_irq;

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
t_error_code CORTEX_M4_nvic_enable_irq(const t_nvic_irq irq_num, const t_bool irq_en);

t_error_code CORTEX_M4_nvic_set_priority(const t_nvic_irq irq_num, const uint32_t irq_prio);

uint32_t CORTEX_M4_nvic_get_priority(const t_nvic_irq irq_num);


void CORTEX_M4_systick_configure(const t_bool tick_int, const t_bool clk_source);

void CORTEX_M4_systick_enable(const t_bool enable);

uint32_t CORTEX_M4_systick_get_tmr(void);

void CORTEX_M4_systick_set_tmr(const uint32_t curr_val);

t_bool CORTEX_M4_systick_underflow(void);

uint32_t CORTEX_M4_systick_get_preload(void);

void CORTEX_M4_systick_set_preload(const uint32_t reload_val);

#endif /* CORTEX_M4_H_ */
/*** EOF ***/
