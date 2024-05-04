/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022, Ivaylo Ivanov <ivo.ivanov.ivanov1@gmail.com>
 */

#include <stddef.h>

#ifndef MAIN_H_   /* Include guard */
#define MAIN_H_

extern unsigned long kernel_size;
extern void load_kernel(void* dtb, void* x1, void* x2, void* x3, void* kernel);
extern void soc_init(void);
extern void board_init(void);

extern void clean_fb(volatile char *fb, int width, int height, int stride);
extern void printk(char *text);
extern void printf(char *text);
extern void print(char *text);

extern void writel(unsigned int value, void* address);
extern unsigned int readl(void* address);

#endif // MAIN_H_
