/*
 * main.h
 *
 *  Created on: Dec 8, 2023
 *      Author: bagolyzsolt
 */

#ifndef MAIN_H_
#define MAIN_H_

#define INTERRUPT_DISABLE()		do{__asm volatile ("MOV R0,#0x1"); __asm volatile ("MSR PRIMASK,R0");} while(0)
#define INTERRUPT_ENABLE()		do{__asm volatile ("MOV R0,#0x0"); __asm volatile ("MSR PRIMASK,R0");} while(0)

/** Compiler specific definitions */
#define NAKED_FUNC			__attribute__((naked))

/** Periphery Address Base */
#define SRAM_START_BASE		0x20000000u
#define SYST_CSR_BASE		0xE000E010u
#define SYST_RVR_BASE		0xE000E014u
#define SHCRS_BASE			0xE000ED24u
#define ICSR_BASE			0xE000ED04u

#define SHCRS_MEMFAULTENA 	16u
#define SHCRS_BUSFAULTENA 	17u
#define SHCRS_USGFAULTENA 	18u
#define	ICSR_PENDSV			28u

/** Stack Memory calculation */
#define BYTES             	1u              //!< size of a byte
#define WORDS             	(4u * BYTES)    //!< size of an (32-bit) word
#define DWORDS            	(8u * BYTES)    //!< size of an (64-bit) double word
#define KILO_BYTES        	(1024u * BYTES) //!< size of 1024 bytes (1 kByte)
#define STACK_SIZE_TASK		(KILO_BYTES)
#define STACK_SIZE_SCHED	(KILO_BYTES)
#define SRAM_END_BASE		(SRAM_START_BASE + SRAM_SIZE)
#define SRAM_SIZE			(128u * KILO_BYTES)
#define STACK_START_T1		SRAM_END_BASE
#define STACK_START_T2		(SRAM_END_BASE - (1u * STACK_SIZE_TASK))
#define STACK_START_T3		(SRAM_END_BASE - (2u * STACK_SIZE_TASK))
#define STACK_START_T4		(SRAM_END_BASE - (3u * STACK_SIZE_TASK))
#define IDLE_STACK_START	(SRAM_END_BASE - (4u * STACK_SIZE_TASK))
#define STACK_START_SCHED	(SRAM_END_BASE - (5u * STACK_SIZE_TASK))

/** Kernel Constants */
#define CONTEXT_PARAMS_MAX		16u	// XPSR, PC, LR, R12, R3, R2, R1, R0, R11, R10, R9, R8, R7, R6, R5, R4
#define CONTEXT_RX_PARAMS_MAX	13u // The number of the rest of the Rx parameters: R12...R4
#define TASKS_MAX				5u
#define TASK_XPSR_DEF			0x01000000u // Programs Status Register. T bit shall always be 1 (0x01000000)!
#define TASK_RX_DEF				0u

/** Clock and tick constants */
#define TICK_HZ				1000u
#define HSI_CLOCK			16000000u // 16 MHz
#define SYSTICK_TIMER_CLK	HSI_CLOCK

/** Exception Return Behavior */
#define EXC_RET_HANDLER_MODE_NO_FP		0xFFFFFFF1u
#define EXC_RET_THREAD_MODE_MSP_NO_FP	0xFFFFFFF9u
#define EXC_RET_THREAD_MODE_PSP_NO_FP	0xFFFFFFFDu
#define EXC_RET_HANDLER_MODE_FP			0xFFFFFFE1u
#define EXC_RET_THREAD_MODE_MSP_FP		0xFFFFFFE9u
#define EXC_RET_THREAD_MODE_PSP_FP		0xFFFFFFEDu

/** Task States */
typedef enum {
	e_tst_block = 0u,
	e_tst_ready = 1u,
	e_tst_max   = 2u
} t_task_state;

/** Task Control Block */
typedef struct {
	uint32_t psp_val;
	uint32_t block_count;
	t_task_state state;
	void (* task_hlr)(void); // Function pointer to task handler address
} t_task_ctrl_block;

/** Task Register Data */
typedef struct {
	t_task_ctrl_block task_cb[TASKS_MAX]; // Task Control Block
	uint8_t task_idx; // Index of current running task
	uint32_t g_tick_count; // Global tick count
} t_task_register;

/** CPU Stack Frame Context
 * Reverse order of: XPSR, PC, LR, R12, R3, R2, R1, R0, R11, R10, R9, R8, R7, R6, R5, R4
 **/
typedef struct {
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;	// Link register - Special value (EXC_RETURN) which controls the exception exit.
	uint32_t pc;	// Program Counter - Address of the current task handler.
	uint32_t xpsr; 	// Programs Status Register. T bit shall always be 1 (0x01000000)!
} t_stack_frame;


#endif /* MAIN_H_ */
