#include <stdio.h>
#include <stdint.h>

extern void initialise_monitor_handles(void);

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define SHCRS_BASE			(0xE000ED24u)
#define UFSR_BASE			(0xE000ED2Au)
#define CCR_BASE			(0xE000ED14u)
#define SHCRS_MEMFAULTENA 	(16u)
#define SHCRS_BUSFAULTENA 	(17u)
#define SHCRS_USGFAULTENA 	(18u)
#define CCR_DIV0_TRP	 	(4u)
#define INSTR_SRAM_ADDRESS	(0x20010000u)

int int_division(const int x, const int y);

int int_division(const int x, const int y)
{
	return (x / y);
}

int main(void)
{
	initialise_monitor_handles();

	printf("--- FAULT HANDLING ---\n");

	// 1. Enable ALL configurable exceptions like: usage, memory manage and bus FAULT.
	uint32_t * const p_shcrs_reg = (uint32_t * const)SHCRS_BASE;
	*p_shcrs_reg |= ((1u << SHCRS_MEMFAULTENA) | (1u << SHCRS_BUSFAULTENA) | (1u << SHCRS_USGFAULTENA));

	// 2. Enable divide by 0 trap
	uint32_t * const p_ccr_reg = (uint32_t * const)CCR_BASE;
	*p_ccr_reg |= (1u << CCR_DIV0_TRP); // Trap enabling at division by 0

	// 3. Attempt to divide by 0
	const int res = int_division(10 , 0);
	(void)res;

    /* Loop forever */
	for(;;);
}

// 2. Implement FAULT handlers
void HardFault_Handler(void)
{
	printf("Exception: HardFault\n");
	while(1);
}

void MemManage_Handler(void)
{
	printf("Exception: MemManage\n");
	while(1);
}

void BusFault_Handler(void)
{
	printf("Exception: BusManage\n");
	while(1);
}

// To get the correct value of MSP without epilog
__attribute__((naked)) void UsageFault_Handler(void)
{
	// Extracting the value of MSP which is the base address of the stack -> saving it during the exception handling
	// From thread mode to handler mode
	__asm("MRS r0, MSP"); // Copy MSP to r0 register
	__asm("B UsageFault_Handler_c"); // Branch to UseageFaultHandler C function

}

void UsageFault_Handler_c(const uint32_t * const p_base_stack_frame) // -> value of r0 will be captured in the function parameter
{
	const uint32_t * const p_ufsr_reg = (const uint32_t * const)UFSR_BASE;
	printf("Exception - UsageFault\n");
	printf("UFSR = %#lX\n", (*p_ufsr_reg) & 0xFFFFu);
	printf("--- Top of the stack after exception triggered ---\n");
	printf("BaseStackFrame = %p\n", p_base_stack_frame);
	printf("Value of R0    = %#lx\n", p_base_stack_frame[0u]);
	printf("Value of R1    = %#lx\n", p_base_stack_frame[1u]);
	printf("Value of R2    = %#lx\n", p_base_stack_frame[2u]);
	printf("Value of R3    = %#lx\n", p_base_stack_frame[3u]);
	printf("Value of R12   = %#lx\n", p_base_stack_frame[4u]);
	printf("Value of LR    = %#lx\n", p_base_stack_frame[5u]);
	printf("Value of PC    = %#lx\n", p_base_stack_frame[6u]);
	printf("Value of XPSR  = %#lx\n", p_base_stack_frame[7u]);

	while(1);
}

void UsageFault_Handler_orig_c(void)
{
	// Does not capture the proper value of MSP because of C function epilog.
	__asm("MRS r0, MSP"); // Copy MSP to r0 register
	register uint32_t msp_value  __asm("r0"); // Using 'register' keyword tells the compiler to place local variable in a register instead of the STACK
	const uint32_t * const p_msp = (const uint32_t * const) msp_value;
	const uint32_t * const p_ufsr_reg = (const uint32_t * const)UFSR_BASE;
	printf("Exception - UsageFault\n");
	printf("UFSR = %#lX\n", (*p_ufsr_reg) & 0xFFFFu);
	printf("--- Top of the stack after exception triggered ---\n");
	printf("MSP  = %p\n", p_msp);
	while(1);
}
