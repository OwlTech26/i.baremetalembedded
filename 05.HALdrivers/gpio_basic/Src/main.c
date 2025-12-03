#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "clock.h"
#include "gpio.h"
#include "fw_debug.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

static void hw_init(void);

static void hw_init(void)
{
	// 1. Enable the HSE clock using HSEON bit (RCC_CR)
	// 2. Enable the HSE bypass bit (bypass the oscillator with an ext clock)
	const t_clock_source clk_src = e_clk_hse;
	CLOCK_enable_source(clk_src, TRUE);

	// 3. Wait until HSE clock enabled
	uint32_t timeout = 100u;
	while ((CLOCK_get_source_stat(clk_src) == FALSE) && (timeout > 0u)) {
		timeout--;
	}
	DEBUG_PRINT((timeout > 0u) ? "HSE clock READY.\n" : "HSE clock FAIL.\n");

	// 3. Switch the system clock to HSE
	const t_clock_cfgr clk_cfg = {
		.clk_sw = e_clk_sys_hse,
		.clk_mco1 = e_clk_mco_hse,
		.clk_mco1_pre = e_clk_mco_pre_4
	};
	const t_error_code clk_set_stat = CLOCK_set_config(&clk_cfg);

	t_clock_cfgr clk_cfg_stat = {0};
	CLOCK_get_config(&clk_cfg_stat);
	DEBUG_PRINT((clk_set_stat == e_ec_no_error) ? "Clock configuration PASS\n" : "Clock configuration FAIL\n");
	DEBUG_PRINT(" - SW:			%u\n", clk_cfg_stat.clk_sw);
	DEBUG_PRINT(" - SWS: 		%u\n", clk_cfg_stat.clk_sws);
	DEBUG_PRINT(" - HPRE: 		%u\n", clk_cfg_stat.clk_hpre);
	DEBUG_PRINT(" - PPRE1: 		%u\n", clk_cfg_stat.clk_ppre1);
	DEBUG_PRINT(" - PPRE2: 		%u\n", clk_cfg_stat.clk_ppre2);
	DEBUG_PRINT(" - RTCPRE:		%u\n", clk_cfg_stat.clk_rtcpre);
	DEBUG_PRINT(" - MCO1: 		%u\n", clk_cfg_stat.clk_mco1);
	DEBUG_PRINT(" - MCO1_PRE:	%u\n", clk_cfg_stat.clk_mco1_pre);
	DEBUG_PRINT(" - MCO2: 		%u\n", clk_cfg_stat.clk_mco2);
	DEBUG_PRINT(" - MCO2_PRE:	%u\n", clk_cfg_stat.clk_mco2_pre);

	// 4. Do MCO1 settings and measure it
	//2. Configure PA8 to AF0 mode to behave as MCO1 signal
	/*
	 * You are not expected to understand the below codes for the time being
	 * because these codes are related to GPIO configurations,
	 * which will be covered in later sections of this course.
	 */

	// a) Enable the peripheral clock for GPIOA peripheral
	CLOCK_enable(e_peri_ahb1, SYSTEM_CLK_EN_MASK, FALSE);

	// b) Configure the mode of GPIOA pin 8 as alternate function mode
	// c ) Configure the alternation function register to set the mode 0 for PA8
	const t_gpio_port_cfg gpio_cfg = {
		.port_sel = GPIO_PORT_PA,
		.pin_sel = GPIO_PIN_P8,
		.mode_sel = GPIO_PA8_MODE,
		.alt_func_sel = GPIO_PA8_ALT_FUNC_MCO1
	};
	GPIO_configure_port(&gpio_cfg, TRUE);
}

int main(void)
{
#ifdef OPEN_OCD_EN
	initialise_monitor_handles();
#endif /* OPEN_OCD_EN */

	DEBUG_PRINT("--- Nucleo System Active: HSE Measurement ---\n");

	hw_init();

    /* Loop forever */
	for(;;);


}
