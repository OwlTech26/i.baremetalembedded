#include <stdio.h>
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);

#define SRAM_START 				0x20000000U
#define SRAM_SIZE  				(128 * 1024)
#define SRAM_END  				((SRAM_START) + (SRAM_SIZE))
#define STACK_START 			SRAM_END

#define STACK_MSP_START 		STACK_START
#define STACK_MSP_END   		(STACK_MSP_START - 512)
#define STACK_PSP_START 		STACK_MSP_END

__attribute__((naked)) void change_sp_to_psp(void);
void generate_exception(void);

__attribute__((naked)) void change_sp_to_psp(void)
{
	__asm volatile(".equ ASM_SRAM_END, (0x20000000 + ((128 * 1024)))");
	__asm volatile(".equ ASM_PSP_START, (ASM_SRAM_END - 512)");
	__asm volatile(
		"LDR R0, =ASM_PSP_START\n\t" // Initialize R0 to PSP start address
		"MSR PSP,R0\n\t" // Moves R0 value to PSP register
		"MOV R0,#0x2\n\t" // Loads 0x2 immediately to R0
		"MSR CONTROL,R0\n\t" // Moves R0 value to CONTROL register -> changes SPSEL to 1
		"BX LR" // Return: BX - Branch Indirect, LR - Return address capture register
	);
}

void generate_exception(void)
{
	__asm volatile("SVC #0x2");
}

int main(void)
{
	initialise_monitor_handles();

	printf("--- Bank Stack Pointers ---\n");

	change_sp_to_psp();

	printf("Return from stack manipulation.\n");

	generate_exception();

    /* Loop forever */
	for(;;);
}

void SVC_Handler(void)
{
	printf("-> SVC_Handler()\n");
}
