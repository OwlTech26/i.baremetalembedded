
#include <stdio.h>
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);

#define ALIAS_BASE   0x22000000U
#define BITBAND_BASE 0x20000000U

int main(void)
{
	initialise_monitor_handles();

	printf("--- Bit-Banding Sample ---\n");

	uint8_t *ptr = (uint8_t *)0x20000200u;

	*ptr = 0xFFu;

	// Normal method
	// Clearing 7th bit position
	*ptr &= ~( 1 << 7);

	// Reset to 0xFF
	*ptr = 0xFFu;

	// Bit banding method
	printf("Before bit banding: %#X\n", (unsigned int)*ptr);
	uint8_t *alias_addr = (uint8_t*) (ALIAS_BASE+(32 * (0x20000200-BITBAND_BASE))+ 7 * 4);

	//clearing 7th bit of address 0x20000200
	*alias_addr = 0;
	printf("After bit banding: %#X\n", (unsigned int)*ptr);

    /* Loop forever */
	for(;;);
}
