	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.bss
	.align	2
USER_TASK:
	.space	88
	.size	USER_TASK, 88
	.text
	.align	1
	.global	enable_processor_faults
	.syntax unified
	.thumb
	.thumb_func
	.type	enable_processor_faults, %function
enable_processor_faults:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	ldr	r3, .L2
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	orr	r2, r3, #458752
	ldr	r3, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L3:
	.align	2
.L2:
	.word	-536810204
	.size	enable_processor_faults, .-enable_processor_faults
	.align	1
	.global	init_scheduler_stack
	.syntax unified
	.thumb
	.thumb_func
	.type	init_scheduler_stack, %function
init_scheduler_stack:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	r3, r0
	.syntax unified
@ 114 "main.c" 1
	MSR MSP,r3
@ 0 "" 2
@ 116 "main.c" 1
	BX LR
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	init_scheduler_stack, .-init_scheduler_stack
	.align	1
	.global	init_task_register
	.syntax unified
	.thumb
	.thumb_func
	.type	init_task_register, %function
init_task_register:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #28
	add	r7, sp, #0
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	str	r2, [r7, #4]
	movs	r3, #0
	str	r3, [r7, #20]
	b	.L6
.L7:
	ldr	r3, [r7, #20]
	lsls	r3, r3, #2
	ldr	r2, [r7, #8]
	add	r3, r3, r2
	ldr	r2, [r3]
	ldr	r1, [r7, #12]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r1
	str	r2, [r3]
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #4
	movs	r2, #0
	str	r2, [r3]
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	movs	r2, #1
	strb	r2, [r3]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #2
	ldr	r2, [r7, #4]
	add	r3, r3, r2
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #12
	str	r1, [r3]
	ldr	r3, [r7, #20]
	adds	r3, r3, #1
	str	r3, [r7, #20]
.L6:
	ldr	r3, [r7, #20]
	cmp	r3, #4
	bls	.L7
	ldr	r3, [r7, #12]
	movs	r2, #1
	strb	r2, [r3, #80]
	ldr	r3, [r7, #12]
	movs	r2, #0
	str	r2, [r3, #84]
	nop
	adds	r7, r7, #28
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
	.size	init_task_register, .-init_task_register
	.align	1
	.global	init_task_stack
	.syntax unified
	.thumb
	.thumb_func
	.type	init_task_stack, %function
init_task_stack:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #28
	add	r7, sp, #0
	str	r0, [r7, #4]
	movs	r3, #0
	str	r3, [r7, #20]
	b	.L9
.L12:
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r2
	ldr	r3, [r3]
	str	r3, [r7, #16]
	ldr	r3, [r7, #16]
	subs	r3, r3, #4
	str	r3, [r7, #16]
	ldr	r3, [r7, #16]
	mov	r2, #16777216
	str	r2, [r3]
	ldr	r3, [r7, #16]
	subs	r3, r3, #4
	str	r3, [r7, #16]
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #12
	ldr	r3, [r3]
	mov	r2, r3
	ldr	r3, [r7, #16]
	str	r2, [r3]
	ldr	r3, [r7, #16]
	subs	r3, r3, #4
	str	r3, [r7, #16]
	ldr	r3, [r7, #16]
	mvn	r2, #2
	str	r2, [r3]
	movs	r3, #0
	str	r3, [r7, #12]
	b	.L10
.L11:
	ldr	r3, [r7, #16]
	subs	r3, r3, #4
	str	r3, [r7, #16]
	ldr	r3, [r7, #16]
	movs	r2, #0
	str	r2, [r3]
	ldr	r3, [r7, #12]
	adds	r3, r3, #1
	str	r3, [r7, #12]
.L10:
	ldr	r3, [r7, #12]
	cmp	r3, #12
	bls	.L11
	ldr	r2, [r7, #16]
	ldr	r1, [r7, #4]
	ldr	r3, [r7, #20]
	lsls	r3, r3, #4
	add	r3, r3, r1
	str	r2, [r3]
	ldr	r3, [r7, #20]
	adds	r3, r3, #1
	str	r3, [r7, #20]
.L9:
	ldr	r3, [r7, #20]
	cmp	r3, #4
	bls	.L12
	nop
	nop
	adds	r7, r7, #28
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
	.size	init_task_stack, .-init_task_stack
	.align	1
	.global	init_systick_timer
	.syntax unified
	.thumb
	.thumb_func
	.type	init_systick_timer, %function
init_systick_timer:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L14
	str	r3, [r7, #12]
	ldr	r2, .L14+4
	ldr	r3, [r7, #4]
	udiv	r3, r2, r3
	subs	r2, r3, #1
	ldr	r3, [r7, #12]
	str	r2, [r3]
	ldr	r3, .L14+8
	str	r3, [r7, #8]
	ldr	r3, [r7, #8]
	ldr	r3, [r3]
	orr	r2, r3, #6
	ldr	r3, [r7, #8]
	str	r2, [r3]
	ldr	r3, [r7, #8]
	ldr	r3, [r3]
	orr	r2, r3, #1
	ldr	r3, [r7, #8]
	str	r2, [r3]
	nop
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L15:
	.align	2
.L14:
	.word	-536813548
	.word	16000000
	.word	-536813552
	.size	init_systick_timer, .-init_systick_timer
	.align	1
	.global	switch_sp_to_psp
	.syntax unified
	.thumb
	.thumb_func
	.type	switch_sp_to_psp, %function
switch_sp_to_psp:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax unified
@ 174 "main.c" 1
	PUSH {LR}
@ 0 "" 2
@ 175 "main.c" 1
	BL get_psp_value
@ 0 "" 2
@ 176 "main.c" 1
	MSR PSP,R0
@ 0 "" 2
@ 177 "main.c" 1
	POP {LR}
@ 0 "" 2
@ 180 "main.c" 1
	MOV R0,#0x02
@ 0 "" 2
@ 181 "main.c" 1
	MSR CONTROL,R0
@ 0 "" 2
@ 182 "main.c" 1
	BX LR
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	switch_sp_to_psp, .-switch_sp_to_psp
	.align	1
	.global	get_psp_value
	.syntax unified
	.thumb
	.thumb_func
	.type	get_psp_value, %function
get_psp_value:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	ldr	r3, .L19
	ldrb	r3, [r3, #80]
	strb	r3, [r7, #7]
	ldrb	r3, [r7, #7]	@ zero_extendqisi2
	ldr	r2, .L19
	lsls	r3, r3, #4
	add	r3, r3, r2
	ldr	r3, [r3]
	mov	r0, r3
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L20:
	.align	2
.L19:
	.word	USER_TASK
	.size	get_psp_value, .-get_psp_value
	.align	1
	.global	set_psp_value
	.syntax unified
	.thumb
	.thumb_func
	.type	set_psp_value, %function
set_psp_value:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L22
	ldrb	r3, [r3, #80]
	strb	r3, [r7, #15]
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	ldr	r2, .L22
	lsls	r3, r3, #4
	add	r3, r3, r2
	ldr	r2, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L23:
	.align	2
.L22:
	.word	USER_TASK
	.size	set_psp_value, .-set_psp_value
	.align	1
	.global	update_next_task
	.syntax unified
	.thumb
	.thumb_func
	.type	update_next_task, %function
update_next_task:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	movs	r3, #0
	strb	r3, [r7, #7]
	movs	r3, #0
	str	r3, [r7]
	b	.L25
.L28:
	ldr	r3, .L32
	ldrb	r3, [r3, #80]	@ zero_extendqisi2
	adds	r3, r3, #1
	uxtb	r2, r3
	ldr	r3, .L32
	strb	r2, [r3, #80]
	ldr	r3, .L32
	ldrb	r2, [r3, #80]	@ zero_extendqisi2
	ldr	r3, .L32+4
	umull	r1, r3, r3, r2
	lsrs	r1, r3, #2
	mov	r3, r1
	lsls	r3, r3, #2
	add	r3, r3, r1
	subs	r3, r2, r3
	uxtb	r2, r3
	ldr	r3, .L32
	strb	r2, [r3, #80]
	ldr	r3, .L32
	ldrb	r3, [r3, #80]	@ zero_extendqisi2
	ldr	r2, .L32
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	ldrb	r3, [r3]
	strb	r3, [r7, #7]
	ldrb	r3, [r7, #7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L26
	ldr	r3, .L32
	ldrb	r3, [r3, #80]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L30
.L26:
	ldr	r3, [r7]
	adds	r3, r3, #1
	str	r3, [r7]
.L25:
	ldr	r3, [r7]
	cmp	r3, #4
	bls	.L28
	b	.L27
.L30:
	nop
.L27:
	ldrb	r3, [r7, #7]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L31
	ldr	r3, .L32
	movs	r2, #0
	strb	r2, [r3, #80]
.L31:
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L33:
	.align	2
.L32:
	.word	USER_TASK
	.word	-858993459
	.size	update_next_task, .-update_next_task
	.align	1
	.global	update_global_tick_count
	.syntax unified
	.thumb
	.thumb_func
	.type	update_global_tick_count, %function
update_global_tick_count:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	ldr	r3, .L35
	ldr	r3, [r3, #84]
	adds	r3, r3, #1
	ldr	r2, .L35
	str	r3, [r2, #84]
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L36:
	.align	2
.L35:
	.word	USER_TASK
	.size	update_global_tick_count, .-update_global_tick_count
	.align	1
	.global	unblock_tasks
	.syntax unified
	.thumb
	.thumb_func
	.type	unblock_tasks, %function
unblock_tasks:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	movs	r3, #1
	str	r3, [r7, #4]
	b	.L38
.L40:
	ldr	r2, .L41
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L39
	ldr	r2, .L41
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #4
	ldr	r2, [r3]
	ldr	r3, .L41
	ldr	r3, [r3, #84]
	cmp	r2, r3
	bne	.L39
	ldr	r2, .L41
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	movs	r2, #1
	strb	r2, [r3]
.L39:
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L38:
	ldr	r3, [r7, #4]
	cmp	r3, #4
	bls	.L40
	nop
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L42:
	.align	2
.L41:
	.word	USER_TASK
	.size	unblock_tasks, .-unblock_tasks
	.align	1
	.global	schedule
	.syntax unified
	.thumb
	.thumb_func
	.type	schedule, %function
schedule:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	ldr	r3, .L44
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	orr	r2, r3, #268435456
	ldr	r3, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L45:
	.align	2
.L44:
	.word	-536810236
	.size	schedule, .-schedule
	.align	1
	.global	task_delay
	.syntax unified
	.thumb
	.thumb_func
	.type	task_delay, %function
task_delay:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #0
	str	r0, [r7, #4]
	.syntax unified
@ 239 "main.c" 1
	MOV R0,#0x1
@ 0 "" 2
@ 239 "main.c" 1
	MSR PRIMASK,R0
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L48
	ldrb	r3, [r3, #80]
	strb	r3, [r7, #15]
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L47
	ldr	r3, .L48
	ldr	r1, [r3, #84]
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	ldr	r2, [r7, #4]
	add	r2, r2, r1
	ldr	r1, .L48
	lsls	r3, r3, #4
	add	r3, r3, r1
	adds	r3, r3, #4
	str	r2, [r3]
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	ldr	r2, .L48
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	movs	r2, #0
	strb	r2, [r3]
	bl	schedule
.L47:
	.syntax unified
@ 250 "main.c" 1
	MOV R0,#0x0
@ 0 "" 2
@ 250 "main.c" 1
	MSR PRIMASK,R0
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	adds	r7, r7, #16
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L49:
	.align	2
.L48:
	.word	USER_TASK
	.size	task_delay, .-task_delay
	.align	1
	.global	task_idle
	.syntax unified
	.thumb
	.thumb_func
	.type	task_idle, %function
task_idle:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
.L51:
	b	.L51
	.size	task_idle, .-task_idle
	.align	1
	.global	task1_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task1_handler, %function
task1_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L53:
	movs	r0, #5
	bl	LED_on
	mov	r0, #1000
	bl	task_delay
	movs	r0, #5
	bl	LED_off
	mov	r0, #1000
	bl	task_delay
	b	.L53
	.size	task1_handler, .-task1_handler
	.section	.rodata
	.align	2
.LC0:
	.ascii	"LED 2 ON\000"
	.align	2
.LC1:
	.ascii	"LED 2 OFF\000"
	.text
	.align	1
	.global	task2_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task2_handler, %function
task2_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L55:
	ldr	r0, .L56
	bl	puts
	mov	r0, #500
	bl	task_delay
	ldr	r0, .L56+4
	bl	puts
	mov	r0, #500
	bl	task_delay
	b	.L55
.L57:
	.align	2
.L56:
	.word	.LC0
	.word	.LC1
	.size	task2_handler, .-task2_handler
	.section	.rodata
	.align	2
.LC2:
	.ascii	"LED 3 ON\000"
	.align	2
.LC3:
	.ascii	"LED 3 OFF\000"
	.text
	.align	1
	.global	task3_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task3_handler, %function
task3_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L59:
	ldr	r0, .L60
	bl	puts
	movs	r0, #250
	bl	task_delay
	ldr	r0, .L60+4
	bl	puts
	movs	r0, #250
	bl	task_delay
	b	.L59
.L61:
	.align	2
.L60:
	.word	.LC2
	.word	.LC3
	.size	task3_handler, .-task3_handler
	.section	.rodata
	.align	2
.LC4:
	.ascii	"LED 4 ON\000"
	.align	2
.LC5:
	.ascii	"LED 4 OFF\000"
	.text
	.align	1
	.global	task4_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task4_handler, %function
task4_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L63:
	ldr	r0, .L64
	bl	puts
	movs	r0, #125
	bl	task_delay
	ldr	r0, .L64+4
	bl	puts
	movs	r0, #125
	bl	task_delay
	b	.L63
.L65:
	.align	2
.L64:
	.word	.LC4
	.word	.LC5
	.size	task4_handler, .-task4_handler
	.section	.rodata
	.align	2
.LC6:
	.ascii	" --- Round-robin Scheduler for STM32 ---\000"
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L68
	bl	puts
	bl	enable_processor_faults
	ldr	r0, .L68+4
	bl	init_scheduler_stack
	ldr	r2, .L68+8
	ldr	r1, .L68+12
	ldr	r0, .L68+16
	bl	init_task_register
	ldr	r0, .L68+16
	bl	init_task_stack
	bl	LED_init
	mov	r0, #1000
	bl	init_systick_timer
	bl	switch_sp_to_psp
	bl	task1_handler
.L67:
	b	.L67
.L69:
	.align	2
.L68:
	.word	.LC6
	.word	536996864
	.word	task_hlr.0
	.word	task_psp.1
	.word	USER_TASK
	.size	main, .-main
	.align	1
	.global	PendSV_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	PendSV_Handler, %function
PendSV_Handler:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax unified
@ 342 "main.c" 1
	MRS R0, PSP
@ 0 "" 2
@ 345 "main.c" 1
	STMDB R0!, {R4-R11}
@ 0 "" 2
@ 348 "main.c" 1
	PUSH {LR}
@ 0 "" 2
@ 349 "main.c" 1
	BL set_psp_value
@ 0 "" 2
@ 353 "main.c" 1
	BL update_next_task
@ 0 "" 2
@ 356 "main.c" 1
	BL get_psp_value
@ 0 "" 2
@ 359 "main.c" 1
	LDMIA R0!,{R4-R11}
@ 0 "" 2
@ 362 "main.c" 1
	MSR PSP, R0
@ 0 "" 2
@ 363 "main.c" 1
	POP {LR}
@ 0 "" 2
@ 364 "main.c" 1
	BX LR
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	PendSV_Handler, .-PendSV_Handler
	.align	1
	.global	SysTick_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Handler, %function
SysTick_Handler:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	bl	update_global_tick_count
	bl	unblock_tasks
	ldr	r3, .L72
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	orr	r2, r3, #268435456
	ldr	r3, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L73:
	.align	2
.L72:
	.word	-536810236
	.size	SysTick_Handler, .-SysTick_Handler
	.section	.rodata
	.align	2
.LC7:
	.ascii	"Exception: HardFault\000"
	.text
	.align	1
	.global	HardFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	HardFault_Handler, %function
HardFault_Handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L76
	bl	puts
.L75:
	b	.L75
.L77:
	.align	2
.L76:
	.word	.LC7
	.size	HardFault_Handler, .-HardFault_Handler
	.section	.rodata
	.align	2
.LC8:
	.ascii	"Exception: MemManage\000"
	.text
	.align	1
	.global	MemManage_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	MemManage_Handler, %function
MemManage_Handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L80
	bl	puts
.L79:
	b	.L79
.L81:
	.align	2
.L80:
	.word	.LC8
	.size	MemManage_Handler, .-MemManage_Handler
	.section	.rodata
	.align	2
.LC9:
	.ascii	"Exception: BusManage\000"
	.text
	.align	1
	.global	BusFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	BusFault_Handler, %function
BusFault_Handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L84
	bl	puts
.L83:
	b	.L83
.L85:
	.align	2
.L84:
	.word	.LC9
	.size	BusFault_Handler, .-BusFault_Handler
	.section	.rodata
	.align	2
	.type	task_psp.1, %object
	.size	task_psp.1, 20
task_psp.1:
	.word	536997888
	.word	537001984
	.word	537000960
	.word	536999936
	.word	536998912
	.align	2
	.type	task_hlr.0, %object
	.size	task_hlr.0, 20
task_hlr.0:
	.word	task_idle
	.word	task1_handler
	.word	task2_handler
	.word	task3_handler
	.word	task4_handler
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
