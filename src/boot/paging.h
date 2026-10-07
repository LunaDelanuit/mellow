/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef PAGING_H
#define PAGING_H

#include <efi.h>
#include "bootinfo.h"

/* x86-64 page size */
#define PAGE_SIZE       0x200000ULL /* 2MiB */
#define SMALL_PAGE_SIZE 0x1000ULL /* 4KiB */

void switch_page_table(EFI_PHYSICAL_ADDRESS pml4);
EFI_STATUS setup_paging(MELLOW_BOOT_INFO *boot_info);

#endif
