/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022, halal-beef <78730004+halal-beef@users.noreply.github.com>
 */

#ifndef EXYNOS990_H_	/* Include guard */
#define EXYNOS990_H_

#define DECON_F_BASE		0x19050000
#define HW_SW_TRIG_CONTROL	0x70

#define SMC_CMD_READ_SB_PARAM			(-0x3FE)

#define EXYNOS9830_PRO_ID	0x10000000

#define CHIPID0_OFFSET		0x4
#define CHIPID1_OFFSET		0x8

#define IRAM_BASE			(0x02020000)
#define DRAM_INFO			(IRAM_BASE + 0x2C000)
#define DRAM_SIZE_INFO		(IRAM_BASE + 0x18848)

#endif // EXYNOS990_H_
