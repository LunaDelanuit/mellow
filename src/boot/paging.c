/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "paging.h"

/* x86-64 page-table entry flags */
#define PAGE_PRESENT  (1ULL << 0)
#define PAGE_WRITE    (1ULL << 1)
#define PAGE_SIZE_BIT (1ULL << 7)

/* x86-64 page table contains 512 entries */
#define PAGE_TABLE_ENTRIES 512

/* Physical address mask for page-table entries */
#define PAGE_ADDRESS_MASK 0x000FFFFFFFFFF000ULL

void switch_page_table(EFI_PHYSICAL_ADDRESS pml4) {
    __asm__ volatile (
        "mov %0, %%cr3"
        :
        : "r"(pml4)
        : "memory"
        );
}

static EFI_PHYSICAL_ADDRESS allocate_page(void) {
    EFI_PHYSICAL_ADDRESS address = 0;

    EFI_STATUS status = uefi_call_wrapper(
        gBS->AllocatePages,
        4,
        AllocateAnyPages,
        EfiLoaderData,
        1,
        &address
    );

    if (status != EFI_SUCCESS) {
        return 0;
    }

    SetMem((void *)(UINTN)address, PAGE_SIZE, 0);

    return address;
}

EFI_STATUS setup_paging(MELLOW_BOOT_INFO *boot_info) {
    EFI_PHYSICAL_ADDRESS pml4 = allocate_page();
    EFI_PHYSICAL_ADDRESS pdpt = allocate_page();
    EFI_PHYSICAL_ADDRESS pd   = allocate_page();
    EFI_PHYSICAL_ADDRESS kernel_pdpt = allocate_page();
    EFI_PHYSICAL_ADDRESS kernel_pd   = allocate_page();
    EFI_PHYSICAL_ADDRESS kernel_pt   = allocate_page();

    if (pml4 == 0 ||
        pdpt == 0 ||
        pd   == 0 ||
        kernel_pdpt == 0 ||
        kernel_pd   == 0 ||
        kernel_pt   == 0
    ) return EFI_OUT_OF_RESOURCES;

    Print(L"PML4 allocated at 0x%016lx\r\n", pml4);
    Print(L"PDPT allocated at 0x%016lx\r\n", pdpt);
    Print(L"PD allocated at 0x%016lx\r\n", pd);
    Print(L"Kernel PDPT allocated at 0x%016lx\r\n", kernel_pdpt);
    Print(L"Kernel PD allocated at 0x%016lx\r\n", kernel_pd);
    Print(L"Kernel PT allocated at 0x%016lx\r\n", kernel_pt);

    UINT64 *pml4_table = (UINT64 *)(UINTN)pml4;
    UINT64 *pdpt_table = (UINT64 *)(UINTN)pdpt;
    UINT64 *pd_table   = (UINT64 *)(UINTN)pd;
    UINT64 *kernel_pdpt_table = (UINT64 *)(UINTN)kernel_pdpt;
    UINT64 *kernel_pd_table   = (UINT64 *)(UINTN)kernel_pd;
    UINT64 *kernel_pt_table   = (UINT64 *)(UINTN)kernel_pt;

    pml4_table[0] =
        (pdpt & PAGE_ADDRESS_MASK) |
        PAGE_PRESENT |
        PAGE_WRITE;

    pdpt_table[0] =
        (pd & PAGE_ADDRESS_MASK) |
        PAGE_PRESENT |
        PAGE_WRITE;

    for (UINTN i = 0; i < PAGE_TABLE_ENTRIES; i++) {
        EFI_PHYSICAL_ADDRESS address =
            i * PAGE_SIZE;

        pd_table[i] =
            address |
            PAGE_PRESENT |
            PAGE_WRITE |
            PAGE_SIZE_BIT;
    }

    pml4_table[511] =
        (kernel_pdpt & PAGE_ADDRESS_MASK) |
        PAGE_PRESENT |
        PAGE_WRITE;

    kernel_pdpt_table[510] =
        (kernel_pd & PAGE_ADDRESS_MASK) |
        PAGE_PRESENT |
        PAGE_WRITE;

    kernel_pd_table[0] =
        (kernel_pt & PAGE_ADDRESS_MASK) |
        PAGE_PRESENT |
        PAGE_WRITE;

    for (UINTN i = 0; i < boot_info->kernel_size; i += SMALL_PAGE_SIZE) {
        EFI_PHYSICAL_ADDRESS  physical =
            boot_info->kernel_phys_base + i;

        kernel_pt_table[i / SMALL_PAGE_SIZE] =
            (physical & PAGE_ADDRESS_MASK) |
            PAGE_PRESENT |
            PAGE_WRITE;
    }

    boot_info->page_table_root = pml4;

    Print(L"Paging set up successfully.\r\n");

    return EFI_SUCCESS;
}
