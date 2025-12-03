
#include <stdio.h>
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);

void static inline generate_interrupt(void);
void static inline change_access_unpriv_mode(void);

// Executes THREAD MODE of the processor
void static inline generate_interrupt(void)
{
	uint32_t * const p_stir_reg = (uint32_t * const)0xE00EF00; // Software Trigger Interrupt Register
	uint32_t * const p_iser0_reg = (uint32_t * const)0xE00E100; // Interrupt Set-enable Register

	// Enable IRQ3 interrupt
	*p_iser0_reg |= (1u << 3u);

	// Generate an interrupt from SW for IRQ3
	*p_stir_reg = (3u & 0x1FFu);
}

void static inline change_access_unpriv_mode(void)
{
	// Read Control Register
	__asm volatile("MRS R0,CONTROL"); // Read CONTROL register
	__asm volatile("ORR R0,R0,#0x01"); // Set unpriviliged mode
	__asm volatile("MSR CONTROL,R0"); // Write back changes to CONTROL register
}

int main(void)
{
	initialise_monitor_handles();

	printf("--- Cortex M3/M4 Access Level ---\n");

	printf("In THREAD mode, before IT.\n");
#if 0
	// Order is important! IT settings cannot be accessed in unprivileged mode.
	change_access_unpriv_mode();
	generate_interrupt();
#endif

	// EPSR T-bit check
	void (*fun_ptr)(void);
	// fun_ptr = change_access_unpriv_mode;
	fun_ptr = (void *)0x8000215; // Normal operation
	fun_ptr = (void *)0x8000214; // Causes usage operation
	fun_ptr();


    /* Loop forever */
	for(;;);
}

// ISR executes in HANDLER MODE of the processor.
void RTC_WKUP_IRQHandler(void)
{
	printf("In handler mode : ISR.\n");
}

// HardFault Handler
void HardFault_Handler(void)
{
	printf("Hard fault detected!\n");
	while(1);
}
