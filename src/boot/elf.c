/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "elf.h"
#include "bootinfo.h"
#include "paging.h"

EFI_STATUS load_kernel(
    EFI_HANDLE image_handle,
    EFI_FILE_PROTOCOL *root
) {
    EFI_STATUS status;
    EFI_FILE_PROTOCOL *kernel;
    MELLOW_BOOT_INFO boot_info = {0};

    /* Open the kernel */
    status = uefi_call_wrapper(
        root->Open,
        5,
        root,
        &kernel,
        L"kmel.elf",
        EFI_FILE_MODE_READ,
        0
    );

    if (status != EFI_SUCCESS) return status;

    ELF64_HEADER header;
    UINTN size = sizeof(header);

    /* Read the ELF header */
    status = uefi_call_wrapper(
        kernel->Read,
        3,
        kernel,
        &size,
        &header
    );

    if (status != EFI_SUCCESS || size != sizeof(header)) {
        uefi_call_wrapper(kernel->Close, 1, kernel);
        return EFI_LOAD_ERROR;
    }

    /* Check ELF magic */
    if (header.e_ident[0] != ELF_MAGIC_0 ||
        header.e_ident[1] != ELF_MAGIC_1 ||
        header.e_ident[2] != ELF_MAGIC_2 ||
        header.e_ident[3] != ELF_MAGIC_3
    ) {
        uefi_call_wrapper(kernel->Close, 1, kernel);
        return EFI_LOAD_ERROR;
    }

    Print(L"Kernel ELF header is valid.\r\n");
    Print(L"  Entry Point: 0x%X\r\n", header.e_entry);
    Print(L"  Program Headers: %u\r\n", header.e_phnum);

    /* Read the pogram-header table */
    UINTN prog_header_size =
        header.e_phentsize * header.e_phnum;

    ELF64_PROG_HEADER *prog_headers;

    status = uefi_call_wrapper(
        gBS->AllocatePool,
        3,
        EfiLoaderData,
        prog_header_size,
        (void **)&prog_headers
    );

    if (status != EFI_SUCCESS) {
        uefi_call_wrapper(kernel->Close, 1, kernel);
        return status;
    }

    /* Move to the program-header table */
    status = uefi_call_wrapper(
        kernel->SetPosition,
        2,
        kernel,
        header.e_phoff
    );

    if (status != EFI_SUCCESS) {
        uefi_call_wrapper(gBS->FreePool, 1, prog_headers);
        uefi_call_wrapper(kernel->Close, 1, kernel);
        return status;
    }

    UINTN read_size = prog_header_size;

    status = uefi_call_wrapper(
        kernel->Read,
        3,
        kernel,
        &read_size,
        prog_headers
    );

    if (status != EFI_SUCCESS || read_size != prog_header_size) {
        uefi_call_wrapper(gBS->FreePool, 1, prog_headers);
        uefi_call_wrapper(kernel->Close, 1, kernel);
        return EFI_LOAD_ERROR;
    }

    /* Display program headers */
    for (UINT16 i = 0; i < header.e_phnum; i++) {
        ELF64_PROG_HEADER *prog_header =
            &prog_headers[i];

        Print(L"Program header %u:\r\n", i);
        Print(L"  Type: 0x%x\r\n", prog_header->p_type);
        Print(L"  Address: 0x%016lx\r\n", prog_header->p_vaddr);
        Print(L"  File size: 0x%lx\r\n", prog_header->p_filesz);
        Print(L"  Memory size: 0x%lx\r\n", prog_header->p_memsz);

        if (prog_header->p_type == ELF_PT_LOAD) {
            Print(L"  LOAD segment\r\n");
        } else continue;

        Print(L"  Loading segment...\r\n");

        /* Calculate how many pages the segment requires */
        UINTN pages =
            (prog_header->p_memsz + ELF_PAGE_SIZE -1) /
            ELF_PAGE_SIZE;

        EFI_PHYSICAL_ADDRESS address =
            prog_header->p_paddr;

        if (boot_info.kernel_size == 0) {
            boot_info.kernel_phys_base = address;
            boot_info.kernel_virt_base = prog_header->p_vaddr;
        }

        boot_info.kernel_size += pages * ELF_PAGE_SIZE;

        /* Allocate memory at the address requested by ELF */
        status = uefi_call_wrapper(
            gBS->AllocatePages,
            4,
            AllocateAddress,
            EfiLoaderData,
            pages,
            &address
        );

        if (status != EFI_SUCCESS) {
            Print(L"  Failed to allocate kernel memory: %r\r\n", status);

            uefi_call_wrapper(gBS->FreePool, 1, prog_headers);
            uefi_call_wrapper(kernel->Close, 1, kernel);
            return status;
        }

        /* Clear the entire memory segment */
        SetMem(
            (void *)(UINTN)address,
            pages * ELF_PAGE_SIZE,
            0
        );

        /* Move the segment's data inside the ELF */
        status = uefi_call_wrapper(
            kernel->SetPosition,
            2,
            kernel,
            prog_header->p_offset
        );

        if (status != EFI_SUCCESS) {
            uefi_call_wrapper(
                gBS->FreePages,
                2,
                address,
                pages
            );

            uefi_call_wrapper(gBS->FreePool, 1, prog_headers);
            uefi_call_wrapper(kernel->Close, 1, kernel);
            return status;
        }

        /* Read the segment into its final memory location */
        UINTN read_size = prog_header->p_filesz;

        status = uefi_call_wrapper(
            kernel->Read,
            3,
            kernel,
            &read_size,
            (void *)(UINTN)address
        );

        if (status != EFI_SUCCESS ||
            read_size != prog_header->p_filesz) {

            uefi_call_wrapper(
                gBS->FreePages,
                2,
                address,
                pages
            );

            uefi_call_wrapper(gBS->FreePool, 1, prog_headers);
            uefi_call_wrapper(kernel->Close, 1, kernel);
            return EFI_LOAD_ERROR;
        }

        Print(L"  Segment loaded at 0x%016lx\r\n", address);
    }

    Print(L"ELF loading complete.\r\n");

    status = setup_paging(&boot_info);

    if (status != EFI_SUCCESS) {
        Print(L"Failed to setup paging: %r\r\n", status);
        return status;
    }

    status = get_mmmap(&boot_info);

    if (status != EFI_SUCCESS) {
        Print(L"Failed to get memory map: %r\r\n", status);
        return status;
    }

    Print(L"UEFI memory map acquired.\r\n");
    Print(L"Memory map size: %lu bytes\r\n", boot_info.mmmap_size);
    Print(L"Descriptor size: %lu bytes\r\n",
          boot_info.mmmap_desc_size);

    UINT64 stack_pointer;

    __asm__ volatile (
        "mov %%rsp, %0"
        : "=r"(stack_pointer)
    );

    Print(L"Current RSP: 0x%016lx\r\n", stack_pointer);

    Print(L"Exiting boot services and handing control to kernel...\r\n");

    status = exit_boot_services(image_handle, &boot_info);

    if (status != EFI_SUCCESS) {
        Print(L"Failed to exit UEFI boot services: %r\r\n", status);
        return status;
    }

    /* From now on, UEFI services no longer work.*/

    switch_page_table(boot_info.page_table_root);

    /*
     * The kernel should never return.
     */

    void (*kernel_entry)(void) = (void (*)(void))(UINTN)header.e_entry;

    kernel_entry();

    /* In the event the kernel returns... welp, we tried. */
    return EFI_LOAD_ERROR;
    /*
     * The return might not even work since UEFI boot services no longer exist...
     * but who cares?
     */
}
