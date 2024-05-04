/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022, Ivaylo Ivanov <ivo.ivanov.ivanov1@gmail.com>
 */

#include <main.h>
#include <string.h>

#define REBOOT_MODE_FASTBOOT				0xFA

#define EXYNOS9830_POWER_BASE				0x15860000
#define EXYNOS9830_PMU_PSHOLD_CONTROL		        0x030c
#define EXYNOS9830_PMU_PS_HOLD_HW_TRIP		        0x0820
#define EXYNOS9830_PMU_PS_HOLD_SW_TRIP		        0x0824
#define EXYNOS9830_POWER_SYSIP_DAT0			(EXYNOS9830_POWER_BASE + 0x0810)
#define EXYNOS9830_POWER_SYSTEM_CONFIGURATION		(EXYNOS9830_POWER_BASE + 0x3A00)


//	writel(REBOOT_MODE_FASTBOOT, EXYNOS9830_POWER_SYSIP_DAT0);
//	writel(readl(EXYNOS9830_POWER_SYSTEM_CONFIGURATION) | 0x2, EXYNOS9830_POWER_SYSTEM_CONFIGURATION);


void main(void* dt, void* kernel) {
	/* Initialize SoC and Board specific peripherals/quirks */

	/* TODO: Find a better way to make this more universal (since devices like arm64 Samsung Galaxies enable FB after soc_init) */
#ifdef CONFIG_SIMPLE_FB
	clean_fb((char*)CONFIG_FRAMEBUFFER_BASE, CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT, CONFIG_FRAMEBUFFER_STRIDE);
#endif
	soc_init();
	printk("soc_init() passed!");

	board_init();
	printk("board_init() passed!");

	/* Copy kernel to memory and boot  */
	printk("Booting linux...");

	//memcpy((void*)CONFIG_PAYLOAD_ENTRY, kernel, (unsigned long) &kernel_size);
	//load_kernel(dt, 0, 0, 0, (void*)CONFIG_PAYLOAD_ENTRY);
	/* We shouldn't get there */
	while(1) {}
}
