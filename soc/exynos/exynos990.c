/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022, halal-beef <78730004+halal-beef@users.noreply.github.com>
 */

#include <soc/exynos990.h>
#include <main.h>
#include <stdint.h>

uint32_t s5p_chip_id[2] = {};
uint32_t s5p_soc_id[1] = {};
char buffer[13] = {};
char str[21] = {};

uint64_t exynos_smc(uint64_t cmd, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
	register uint64_t reg0 __asm__ ("x0") = cmd;
	register uint64_t reg1 __asm__ ("x1") = arg1;
	register uint64_t reg2 __asm__ ("x2") = arg2;
	register uint64_t reg3 __asm__ ("x3") = arg3;

	__asm__ volatile (
                "smc\t0\n"
                : "+r"(reg0), "+r"(reg1), "+r"(reg2), "+r"(reg3)

        );

	return reg0;
}

uint32_t read_secure_chip(void)
{
	return exynos_smc(SMC_CMD_READ_SB_PARAM, 0, 0, 0);
}

int strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char nibble_to_hex(uint8_t nibble) {
    if (nibble < 10)
        return '0' + nibble;
    else
        return 'A' + (nibble - 10);
}

void uint_to_hex(uint32_t value, char* buffer) {
    for (int i = 7; i >= 0; --i) {
        uint8_t nibble = (value >> (i * 4)) & 0xF;
        *buffer++ = nibble_to_hex(nibble);
    }
    *buffer = '\0';
}

void write_two_strings(char* str1, char* str2) {
    char combined_str[strlen(str1) + strlen(str2) + 1];
    int i, j;

    for (i = 0; str1[i] != '\0'; ++i) combined_str[i] = str1[i];
    for (j = 0; str2[j] != '\0'; ++j) combined_str[i + j] = str2[j];

    combined_str[i + j] = '\0';
    printf(combined_str);
}

void soc_init(void) {
	*(int*) (DECON_F_BASE + HW_SW_TRIG_CONTROL) = 0x1281;

	s5p_chip_id[0] = readl(EXYNOS9830_PRO_ID + CHIPID0_OFFSET);
	s5p_chip_id[1] = readl(EXYNOS9830_PRO_ID + CHIPID1_OFFSET) & 0xFFFF;

	s5p_soc_id[0] = readl(EXYNOS9830_PRO_ID);

	print("----------Device Information----------");

	uint_to_hex(s5p_chip_id[0], buffer);
	write_two_strings("Chip ID 0: ", buffer);

	uint_to_hex(s5p_chip_id[1], buffer);
	write_two_strings("Chip ID 1: ", buffer);

	uint_to_hex(s5p_soc_id[0], buffer);
	write_two_strings("SOC ID: ", buffer);

	switch (read_secure_chip())
	{
	case 0:
		printf("Secure Boot: Disabled");
		break;
	case 1:
		printf("Secure Boot: Enabled (Test Key)");
		break;
	case 2:
		printf("Secure Boot: Enabled");
		break;
	default:
		printf("Unable to determine secure boot state!");
		break;
	}
}