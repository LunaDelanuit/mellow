/*
 * Mellow Operating System
 * Copyright (C) 2026 Luna Delanuit and contributors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bootinfo.h"

EFI_STATUS get_mmmap(MELLOW_BOOT_INFO *boot_info)
{
    EFI_STATUS status;

    UINTN mmmap_size = 0;
    UINTN mmap_key;
    UINTN desc_size;
    UINT32 desc_ver;

    /* Find out how large the memory map is */
    Print(L"Getting UEFI memory map size...\r\n");

    status = uefi_call_wrapper(
        gBS->GetMemoryMap,
        5,
        &mmmap_size,
        NULL,
        &mmap_key,
        &desc_size,
        &desc_ver
    );

    if (status != EFI_BUFFER_TOO_SMALL) return status;

    /*
     * Leave extra room for descriptors created by allocations
     * made while the boot manager is running.
     */
    mmmap_size += desc_size * 64;

    status = uefi_call_wrapper(
        gBS->AllocatePool,
        3,
        EfiLoaderData,
        mmmap_size,
        (void **)&boot_info->mmmap
    );

    if (status != EFI_SUCCESS) return status;

    boot_info->mmmap_size = mmmap_size;
    boot_info->mmmap_capacity = mmmap_size;
    boot_info->mmmap_desc_size = desc_size;
    boot_info->mmmap_desc_ver = desc_ver;

    /*
     * Get the current map. This is not necessarily the final map;
     * ExitBootServices() will acquire the final one.
     */
    UINTN current_size = mmmap_size;

    status = uefi_call_wrapper(
        gBS->GetMemoryMap,
        5,
        &current_size,
        boot_info->mmmap,
        &mmap_key,
        &desc_size,
        &desc_ver
    );

    if (status != EFI_SUCCESS) {
        uefi_call_wrapper(
            gBS->FreePool,
            1,
            boot_info->mmmap
        );

        boot_info->mmmap = NULL;
        boot_info->mmmap_size = 0;

        return status;
    }

    boot_info->mmmap_size = current_size;
    boot_info->mmmap_desc_size = desc_size;
    boot_info->mmmap_desc_ver = desc_ver;
    boot_info->mmmap_key = mmap_key;

    Print(L"UEFI memory map acquired.\r\n");
    Print(L"Memory map size: %lu bytes\r\n", current_size);
    Print(L"Descriptor size: %lu bytes\r\n", desc_size);

    return EFI_SUCCESS;
}

EFI_STATUS exit_boot_services(
    EFI_HANDLE image_handle,
    MELLOW_BOOT_INFO *boot_info
)
{
    EFI_STATUS status;

    UINTN mmmap_size;
    UINTN mmap_key;
    UINTN desc_size;
    UINT32 desc_ver;

    for (;;) {
        mmmap_size = boot_info->mmmap_capacity;

        status = uefi_call_wrapper(
            gBS->GetMemoryMap,
            5,
            &mmmap_size,
            boot_info->mmmap,
            &mmap_key,
            &desc_size,
            &desc_ver
        );

        if (status != EFI_SUCCESS) {
            return status;
        }

        boot_info->mmmap_size = mmmap_size;
        boot_info->mmmap_desc_size = desc_size;
        boot_info->mmmap_desc_ver = desc_ver;
        boot_info->mmmap_key = mmap_key;

        status = uefi_call_wrapper(
            gBS->ExitBootServices,
            2,
            image_handle,
            mmap_key
        );

        if (status == EFI_SUCCESS) {
            return EFI_SUCCESS;
        }

        if (status != EFI_INVALID_PARAMETER) {
            return status;
        }
    }
}
