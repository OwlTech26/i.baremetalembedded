#include <stdio.h>
#include <stdint.h>
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);

static inline const unsigned int asm_sum(const uint32_t val_1, const uint32_t val_2);
static inline void asm_copy(const int val);
static inline const uint32_t asm_get_control_reg(void);

static inline const unsigned int asm_sum(const uint32_t val_1, const uint32_t val_2)
{
	// Initialize memory
	uint32_t * const p_r1 = (uint32_t * const)0x20001000u;
	uint32_t * const p_r2 = (uint32_t * const)0x20001004u;
	*p_r1 = val_1;
	*p_r2 = val_2;
	// Add memory content via inline assembly
	__asm volatile("LDR R1,=#0x20001000"); // Initialize content of memory location 0x20001000
	__asm volatile("LDR R2,=#0x20001004"); // Initialize content of memory location 0x20001004
	__asm volatile(
		"LDR R0,[R1]\n\t" // Load R1 memory content into R0
		"LDR R1,[R2]\n\t" // Load R2 memory content into R1
		"ADD R0,R0,R1\n\t" // Add R0 and R1 into R0
		"STR R0,[R2]\n\t"); // Store back the R0 sum into R1 memory location

	return (const unsigned int)*p_r2;
}

static inline void asm_copy(const int val)
{
	// Copy 'val' into the R0 general register.
	__asm volatile("MOV R0,%0": :"r"(val): ); // Copy 'val' into the R0 'r' general register. %0 is the operand index 0.
}

static inline const uint32_t asm_get_control_reg(void)
{
	uint32_t ret_reg = 0u;

	// Copy control register value (special register)
	__asm volatile("MRS %0,CONTROL":"=r"(ret_reg)::); // '=' constraint modifier (write-only), 'r' constraint character

	return ret_reg;
}

int main(void)
{
	initialise_monitor_handles();

	printf("STM32 System is Active.\n");

	/** Inline Assembly Examples
	 * __asm volatile(code : output operand list : input operand list : clobber_list);
	 * __asm volatile("MOV R0,R1":::);
	 **/

	printf("Inline assembly result: 0x6 + 0x4 = %#X\n", asm_sum(0x6u, 0x4u));
	asm_copy(50);
	printf("Control register: %#X\n", (unsigned int)asm_get_control_reg);

	// Copy var1 to var2
	int var1=10, var2=0;
	__asm volatile("MOV %0,%1": "=r"(var2): "r"(var1));
	printf("Copy_1: var1=%d, var2=%d\n", var1, var2);

	var2 = 258;
	int * p_var2 = &var2;
	__asm volatile("LDR %0,[%1]": "=r"(var1): "r"(p_var2):);
	printf("Copy_2: var1=%d, var2=%d\n", var1, var2);



    /* Loop forever */
	for(;;);
}
