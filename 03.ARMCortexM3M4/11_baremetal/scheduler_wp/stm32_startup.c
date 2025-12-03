#include <stdint.h>

#define SRAM_START		0x20000000u
#define SRAM_SIZE 		(128u * 1024u)
#define SRAM_END		(SRAM_START + SRAM_SIZE)
#define STACK_START		SRAM_END
#define RESERVED		(0x00000000u)

extern uint32_t _etext;
extern uint32_t _la_data;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);
void __libc_init_array(void);



void Reset_handler(void);
// Alias: alias name can be givven for a function.
// Weak: can be overridden with the same function name (like dummy function).
void NMI_handler					(void) __attribute__ ((weak, alias("Default_handler")));
void HardFault_handler				(void) __attribute__ ((weak, alias("Default_handler")));
void MemManage_handler 				(void) __attribute__ ((weak, alias("Default_handler")));
void BusFault_handler 				(void) __attribute__ ((weak, alias("Default_handler")));
void UsageFault_handler 			(void) __attribute__ ((weak, alias("Default_handler")));
void SVC_handler 					(void) __attribute__ ((weak, alias("Default_handler")));
void DebugMon_handler 				(void) __attribute__ ((weak, alias("Default_handler")));
void PendSV_handler   				(void) __attribute__ ((weak, alias("Default_handler")));
void SysTick_handler  				(void) __attribute__ ((weak, alias("Default_handler")));
void WWDG_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));
void PVD_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));             
void TAMP_STAMP_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));      
void RTC_WKUP_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));
void FLASH_IRQ_handler              (void) __attribute__ ((weak, alias("Default_handler")));
void RCC_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));
void EXTI0_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));           
void EXTI1_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));           
void EXTI2_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));           
void EXTI3_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));           
void EXTI4_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));           
void DMA1_Stream0_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void DMA1_Stream1_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void DMA1_Stream2_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void DMA1_Stream3_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void DMA1_Stream4_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void DMA1_Stream5_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void DMA1_Stream6_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));    
void ADC_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));             
void CAN1_TX_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void CAN1_RX0_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));        
void CAN1_RX1_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));        
void CAN1_SCE_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));        
void EXTI9_5_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void TIM1_BRK_TIM9_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));   
void TIM1_UP_TIM10_IRQ_handler 		(void) __attribute__ ((weak, alias("Default_handler")));   
void TIM1_TRG_COM_TIM11_IRQ_handler (void) __attribute__ ((weak, alias("Default_handler")));
void TIM1_CC_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void TIM2_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));            
void TIM3_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));            
void TIM4_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));            
void I2C1_EV_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void I2C1_ER_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void I2C2_EV_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void I2C2_ER_IRQ_handler 			(void) __attribute__ ((weak, alias("Default_handler")));         
void SPI1_IRQ_handler  				(void) __attribute__ ((weak, alias("Default_handler")));           
void SPI2_IRQ_handler 				(void) __attribute__ ((weak, alias("Default_handler")));            
void USART1_IRQ_handler  			(void) __attribute__ ((weak, alias("Default_handler")));         
void USART2_IRQ_handler  			(void) __attribute__ ((weak, alias("Default_handler")));        
void USART3_IRQ_handler   			(void) __attribute__ ((weak, alias("Default_handler")));        
void EXTI15_10_IRQ_handler   		(void) __attribute__ ((weak, alias("Default_handler")));     
void RTC_Alarm_IRQ_handler    		(void) __attribute__ ((weak, alias("Default_handler")));    
void OTG_FS_WKUP_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler"))); 
void TIM8_BRK_TIM12_IRQ_handler   	(void) __attribute__ ((weak, alias("Default_handler")));
void TIM8_UP_TIM13_IRQ_handler    	(void) __attribute__ ((weak, alias("Default_handler")));
void TIM8_TRG_COM_TIM14_IRQ_handler (void) __attribute__ ((weak, alias("Default_handler")));
void TIM8_CC_IRQ_handler          	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA1_Stream7_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void FSMC_IRQ_handler             	(void) __attribute__ ((weak, alias("Default_handler")));
void SDIO_IRQ_handler             	(void) __attribute__ ((weak, alias("Default_handler")));
void TIM5_IRQ_handler             	(void) __attribute__ ((weak, alias("Default_handler")));
void SPI3_IRQ_handler             	(void) __attribute__ ((weak, alias("Default_handler")));
void UART4_IRQ_handler            	(void) __attribute__ ((weak, alias("Default_handler")));
void UART5_IRQ_handler            	(void) __attribute__ ((weak, alias("Default_handler")));
void TIM6_DAC_IRQ_handler         	(void) __attribute__ ((weak, alias("Default_handler")));
void TIM7_IRQ_handler             	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream0_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream1_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream2_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream3_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream4_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void ETH_IRQ_handler              	(void) __attribute__ ((weak, alias("Default_handler")));
void ETH_WKUP_IRQ_handler         	(void) __attribute__ ((weak, alias("Default_handler")));
void CAN2_TX_IRQ_handler          	(void) __attribute__ ((weak, alias("Default_handler")));
void CAN2_RX0_IRQ_handler         	(void) __attribute__ ((weak, alias("Default_handler")));
void CAN2_RX1_IRQ_handler         	(void) __attribute__ ((weak, alias("Default_handler")));
void CAN2_SCE_IRQ_handler         	(void) __attribute__ ((weak, alias("Default_handler")));
void OTG_FS_IRQ_handler           	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream5_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream6_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void DMA2_Stream7_IRQ_handler     	(void) __attribute__ ((weak, alias("Default_handler")));
void USART6_IRQ_handler           	(void) __attribute__ ((weak, alias("Default_handler")));
void I2C3_EV_IRQ_handler          	(void) __attribute__ ((weak, alias("Default_handler")));
void I2C3_ER_IRQ_handler          	(void) __attribute__ ((weak, alias("Default_handler")));
void OTG_HS_EP1_OUT_IRQ_handler   	(void) __attribute__ ((weak, alias("Default_handler")));
void OTG_HS_EP1_IN_IRQ_handler    	(void) __attribute__ ((weak, alias("Default_handler")));
void OTG_HS_WKUP_IRQ_handler      	(void) __attribute__ ((weak, alias("Default_handler")));
void OTG_HS_IRQ_handler           	(void) __attribute__ ((weak, alias("Default_handler")));
void DCMI_IRQ_handler             	(void) __attribute__ ((weak, alias("Default_handler")));
void HASH_RNG_IRQ_handler         	(void) __attribute__ ((weak, alias("Default_handler")));
void FPU_IRQ_handler              	(void) __attribute__ ((weak, alias("Default_handler")));
void SPI4_IRQ_handler              	(void) __attribute__ ((weak, alias("Default_handler")));
void SAI1_IRQ_handler              	(void) __attribute__ ((weak, alias("Default_handler")));
void SAI2_IRQ_handler              	(void) __attribute__ ((weak, alias("Default_handler")));
void QUADSPI_IRQ_handler            (void) __attribute__ ((weak, alias("Default_handler")));
void HDMI_CEC_IRQ_handler           (void) __attribute__ ((weak, alias("Default_handler")));
void SPDIF_Rx_IRQ_handler           (void) __attribute__ ((weak, alias("Default_handler")));
void FMPI2C1_IRQ_handler            (void) __attribute__ ((weak, alias("Default_handler")));
void FMPI2C1_ERROR_IRQ_handler      (void) __attribute__ ((weak, alias("Default_handler")));

/** Overall 97 Exceptions
   - 15 System
   - 82 Interrupts
   Creating all of them is not required. A single default handler is enough.
*/
const uint32_t vectors[] __attribute__ ((section (".isr_vector"))) = {
	STACK_START,
	(uint32_t)&Reset_handler,
	(uint32_t)&NMI_handler,
	(uint32_t)&HardFault_handler,
	(uint32_t)&MemManage_handler, 
	(uint32_t)&BusFault_handler,
	(uint32_t)&UsageFault_handler,
	RESERVED,
	RESERVED,
	RESERVED,
	RESERVED,
	(uint32_t)&SVC_handler,
	(uint32_t)&DebugMon_handler,
	RESERVED,
	(uint32_t)&PendSV_handler,
	(uint32_t)&SysTick_handler,
	(uint32_t)&WWDG_IRQ_handler,
	(uint32_t)&PVD_IRQ_handler,
	(uint32_t)&TAMP_STAMP_IRQ_handler,
	(uint32_t)&RTC_WKUP_IRQ_handler,
	(uint32_t)&FLASH_IRQ_handler,
	(uint32_t)&RCC_IRQ_handler,
	(uint32_t)&EXTI0_IRQ_handler,
	(uint32_t)&EXTI1_IRQ_handler,
	(uint32_t)&EXTI2_IRQ_handler,
	(uint32_t)&EXTI3_IRQ_handler,
	(uint32_t)&EXTI4_IRQ_handler,
	(uint32_t)&DMA1_Stream0_IRQ_handler,
	(uint32_t)&DMA1_Stream1_IRQ_handler,
	(uint32_t)&DMA1_Stream2_IRQ_handler,
	(uint32_t)&DMA1_Stream3_IRQ_handler,
	(uint32_t)&DMA1_Stream4_IRQ_handler,
	(uint32_t)&DMA1_Stream5_IRQ_handler,
	(uint32_t)&DMA1_Stream6_IRQ_handler,
	(uint32_t)&ADC_IRQ_handler,
	(uint32_t)&CAN1_TX_IRQ_handler,
	(uint32_t)&CAN1_RX0_IRQ_handler,
	(uint32_t)&CAN1_RX1_IRQ_handler,
	(uint32_t)&CAN1_SCE_IRQ_handler,
	(uint32_t)&EXTI9_5_IRQ_handler,
	(uint32_t)&TIM1_BRK_TIM9_IRQ_handler,
	(uint32_t)&TIM1_UP_TIM10_IRQ_handler,
	(uint32_t)&TIM1_TRG_COM_TIM11_IRQ_handler,
	(uint32_t)&TIM1_CC_IRQ_handler,
	(uint32_t)&TIM2_IRQ_handler,
	(uint32_t)&TIM3_IRQ_handler,
	(uint32_t)&TIM4_IRQ_handler,
	(uint32_t)&I2C1_EV_IRQ_handler,
	(uint32_t)&I2C1_ER_IRQ_handler,
	(uint32_t)&I2C2_EV_IRQ_handler,
	(uint32_t)&I2C2_ER_IRQ_handler,
	(uint32_t)&SPI1_IRQ_handler,
	(uint32_t)&SPI2_IRQ_handler,
	(uint32_t)&USART1_IRQ_handler,
	(uint32_t)&USART2_IRQ_handler,
	(uint32_t)&USART3_IRQ_handler,
	(uint32_t)&EXTI15_10_IRQ_handler,
	(uint32_t)&RTC_Alarm_IRQ_handler,
	(uint32_t)&OTG_FS_WKUP_IRQ_handler,
	(uint32_t)&TIM8_BRK_TIM12_IRQ_handler,
	(uint32_t)&TIM8_UP_TIM13_IRQ_handler,
	(uint32_t)&TIM8_TRG_COM_TIM14_IRQ_handler,
	(uint32_t)&TIM8_CC_IRQ_handler,
	(uint32_t)&DMA1_Stream7_IRQ_handler,
	(uint32_t)&FSMC_IRQ_handler,
	(uint32_t)&SDIO_IRQ_handler,
	(uint32_t)&TIM5_IRQ_handler,
	(uint32_t)&SPI3_IRQ_handler,
	(uint32_t)&UART4_IRQ_handler,
	(uint32_t)&UART5_IRQ_handler,
	(uint32_t)&TIM6_DAC_IRQ_handler,
	(uint32_t)&TIM7_IRQ_handler,
	(uint32_t)&DMA2_Stream0_IRQ_handler,
	(uint32_t)&DMA2_Stream1_IRQ_handler,
	(uint32_t)&DMA2_Stream2_IRQ_handler,
	(uint32_t)&DMA2_Stream3_IRQ_handler,
	(uint32_t)&DMA2_Stream4_IRQ_handler,
	RESERVED,
	RESERVED,
	(uint32_t)&CAN2_TX_IRQ_handler,
	(uint32_t)&CAN2_RX0_IRQ_handler,
	(uint32_t)&CAN2_RX1_IRQ_handler,
	(uint32_t)&CAN2_SCE_IRQ_handler,
	(uint32_t)&OTG_FS_IRQ_handler,
	(uint32_t)&DMA2_Stream5_IRQ_handler,
	(uint32_t)&DMA2_Stream6_IRQ_handler,
	(uint32_t)&DMA2_Stream7_IRQ_handler,
	(uint32_t)&USART6_IRQ_handler,
	(uint32_t)&I2C3_EV_IRQ_handler,
	(uint32_t)&I2C3_ER_IRQ_handler,
	(uint32_t)&OTG_HS_EP1_OUT_IRQ_handler,
	(uint32_t)&OTG_HS_EP1_IN_IRQ_handler,
	(uint32_t)&OTG_HS_WKUP_IRQ_handler,
	(uint32_t)&OTG_HS_IRQ_handler,
	(uint32_t)&DCMI_IRQ_handler,
	RESERVED,
	RESERVED,
	(uint32_t)&FPU_IRQ_handler,
	RESERVED,
	RESERVED,
	(uint32_t)&SPI4_IRQ_handler,
	RESERVED,
	RESERVED,
	(uint32_t)&SAI1_IRQ_handler,
	RESERVED,
	RESERVED,
	RESERVED,
	(uint32_t)&SAI2_IRQ_handler,
	(uint32_t)&QUADSPI_IRQ_handler,
	(uint32_t)&HDMI_CEC_IRQ_handler,
	(uint32_t)&SPDIF_Rx_IRQ_handler,
	(uint32_t)&FMPI2C1_IRQ_handler,
	(uint32_t)&FMPI2C1_ERROR_IRQ_handler,
};

void Reset_handler(void)
{
	// Copy .data section to SRAM_END
	const uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
	uint8_t *p_dest_data = (uint8_t *)&_sdata; // SRAM
	const uint8_t *p_src_data = (uint8_t *)&_la_data; // FLASH
	
	for (uint32_t i=0u; i<data_size; ++i) {
		*p_dest_data++ = *p_src_data++;
	}
	
	// Initialize the .bss section to 0 in SRAM
	const uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	uint8_t *p_dest_bss = (uint8_t *)&_sbss; // SRAM
	
	for (uint32_t i=0u; i<bss_size; ++i) {
		*p_dest_bss++ = 0u;
	}
	
	// Call init functions of std libraries
	__libc_init_array();
	
	// Call main()
	main();
}

void Default_handler(void)
{
	while(1);
}