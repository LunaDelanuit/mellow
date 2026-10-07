/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BOOTINFO_H
#define BOOTINFO_H

#include <efi.h>
#include <efilib.h>

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm */
typedef struct {
    /* UEFI Memory Map */
    EFI_MEMORY_DESCRIPTOR *mmmap;
    UINTN  mmmap_size;
    UINTN  mmmap_capacity;
    UINTN  mmmap_desc_size;
    UINT32 mmmap_desc_ver;
    UINTN  mmmap_key;

    /* Kernel Physical Memory */
    EFI_PHYSICAL_ADDRESS kernel_phys_base;
    UINTN kernel_size;

    /* Kernel Virtual Memory */
    EFI_VIRTUAL_ADDRESS kernel_virt_base;

    /* Page Tables */
    EFI_PHYSICAL_ADDRESS page_table_root;
} MELLOW_BOOT_INFO;

EFI_STATUS get_mmmap(MELLOW_BOOT_INFO *boot_info);
EFI_STATUS exit_boot_services(
    EFI_HANDLE image_handle,
    MELLOW_BOOT_INFO *boot_info
);

#endif
