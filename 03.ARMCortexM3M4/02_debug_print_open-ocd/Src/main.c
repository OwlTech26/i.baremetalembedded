#include <stdio.h>
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern void initialise_monitor_handles(void);

int main(void)
{
	initialise_monitor_handles();

	printf("Welcome from STM32 OpenOCD DebugPrint!\n");
    /* Loop forever */
	for(;;);
}
