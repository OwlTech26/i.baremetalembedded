#include <stdio.h>
#include <stdint.h>

#define BYTES             1u              //!< size of a byte
#define WORDS             (4u * BYTES)    //!< size of an (32-bit) word
#define NUM_OF_BYTE_BITS  (8u)    //!< Number of bits inside a Byte

// Interrupt Set-enable Registers
#define NVIC_ISER0_BASE		(0xE000E100u)
#define NVIC_ISER1_BASE		(0xE000E104u)
// Interrupt Set-pending Registers
#define NVIC_ISPR0_BASE		(0XE000E200u)
#define NVIC_ISPR1_BASE		(0XE000E204u)
// Interrupt Priority Registers
#define NVIC_IPR0_BASE		(0xE000E400u)
#define NVIC_IPR1_BASE		(0xE000E404u)

#define IRQ_NUM_TIMER2		(28u)
#define IRQ_NUM_I2C1		(31u)
#define IRQ_NUM_USART3		(39u)

extern void initialise_monitor_handles(void);


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

static void irq_prio_config(const uint8_t irq_num, const uint8_t prio_val);

static void irq_prio_config(const uint8_t irq_num, const uint8_t prio_val)
{
	// 1. Calculate IPRx
	const uint8_t iprx = (irq_num / WORDS) * WORDS;
	uint32_t * const p_ipr_reg = (uint32_t *)(NVIC_IPR0_BASE + iprx);

	// 2. Calculate position in IPRx
	const uint8_t irq_pos = (irq_num % WORDS) * NUM_OF_BYTE_BITS;

	// 3. Configure the priority value
	*p_ipr_reg &= ~(0xFFu << irq_pos); // Clear
	*p_ipr_reg |= (prio_val << irq_pos); // Set
}

int main(void)
{
	initialise_monitor_handles();

	puts("--- Cortex M3/M4 Interrupts ---");

#if 0
	// 1. Manually pend the but for USART3 IRQ
	uint32_t * const p_ispr1_reg = (uint32_t *)NVIC_ISPR1_BASE;
	*p_ispr1_reg |= (1u << (IRQ_NUM_USART3 % 32u));

	// 2. Enable the USART3 IRQ
	uint32_t * const p_iser1_reg = (uint32_t *)NVIC_ISER1_BASE;
	*p_iser1_reg |= (1u << (IRQ_NUM_USART3 % 32u));
#endif

	// 1. Configure the priority for the peripherals
	irq_prio_config(IRQ_NUM_TIMER2, 0x80u);
	irq_prio_config(IRQ_NUM_I2C1, 0x70u); // Higher priority

	// 2. Set the IT pending bit in the NVIC PR
	uint32_t * const p_ispr0_reg = (uint32_t *)NVIC_ISPR0_BASE;
	*p_ispr0_reg |= (1u << IRQ_NUM_TIMER2);


	// 3. Enable the IRQs in NVIC ISER
	uint32_t * const p_iser0_reg = (uint32_t *)NVIC_ISER0_BASE;
	*p_iser0_reg |= (1u << IRQ_NUM_I2C1);
	*p_iser0_reg |= (1u << IRQ_NUM_TIMER2);

	printf(" === RETURN FROM INTERRUPT ===\n");

    /* Loop forever */
	for(;;);
}


// === IRQ Handlers ===
void TIM2_IRQHandler(void)
{
	printf("in TIMER2 ISR\n");
	uint32_t * const p_ispr0_reg = (uint32_t *)NVIC_ISPR0_BASE;
	*p_ispr0_reg |= (1u << IRQ_NUM_I2C1);
	while(1);
}

void I2C1_EV_IRQHandler(void)
{
	printf("in I2C1 ISR\n");
}

void USART3_IRQHandler(void)
{
	printf("in USART3 ISR\n");
}
