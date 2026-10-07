/*
 * Mellow Kernel
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

typedef unsigned short int uint16_t;

static void cpu_halt(void) {
    for (;;) __asm__ volatile("hlt");
}

static void dputc(char character) {
    __asm__ volatile(
        "outb %0, %1"
        :
        : "a"(character), "Nd"((uint16_t)0xE9) /* 0xE9 is QEMU's debug console */
    );
}

static void dputs(const char *string) {
    while (*string) {
        dputc(*string++);
    }
}

void kmain(void) {
    dputs("Mellow Kernel (kmel) is here!");

    cpu_halt();
}
