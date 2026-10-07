/*
 * Mellow Operating System
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "filesystem.h"

/* Open the UEFI filesystem Mellow was booted from */
EFI_FILE_PROTOCOL *open_filesystem(
    EFI_HANDLE image_handle,
    EFI_SYSTEM_TABLE *system_table
) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE *loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *filesystem;
    EFI_FILE_PROTOCOL *root;

    /* Get information about the currently running image */
    status = uefi_call_wrapper(system_table->BootServices->HandleProtocol,
        3,
        image_handle,
        &LoadedImageProtocol,
        (void **)&loaded_image
    );

    if (status != EFI_SUCCESS) return NULL;

    /* Get the filesystem protcol from the device we were loaded from */
    status = uefi_call_wrapper(
        system_table->BootServices->HandleProtocol,
        3,
        loaded_image->DeviceHandle,
        &FileSystemProtocol,
        (void **)&filesystem
    );

    if (status != EFI_SUCCESS) return NULL;

    /* Open the root directory */
    status = uefi_call_wrapper(
        filesystem->OpenVolume,
        2,
        filesystem,
        &root
    );

    if (status != EFI_SUCCESS) return NULL;

    return root;
}

/* List contents of a directory */
EFI_STATUS list_directory(EFI_FILE_PROTOCOL *directory) {
    EFI_STATUS status;

    UINTN buffer_size = 4096;
    UINTN read_size;

    UINT8 *buffer;

    /* Allocate a buffer for directory entries */
    status = uefi_call_wrapper(
        gBS->AllocatePool,
        3,
        EfiLoaderData,
        buffer_size,
        (void **)&buffer
    );

    if (status != EFI_SUCCESS) return status;

    while (TRUE) {
        read_size = buffer_size;

        /* Read directory entries */
        status = uefi_call_wrapper(
            directory->Read,
            3,
            directory,
            &read_size,
            buffer
        );

        /* The buffer is too smol; resize it */
        if (status == EFI_BUFFER_TOO_SMALL) {
            uefi_call_wrapper(gBS->FreePool, 1, buffer);

            buffer_size = read_size;

            buffer_size = uefi_call_wrapper(
                gBS->AllocatePool,
                3,
                EfiLoaderData,
                buffer_size,
                (void **)&buffer
            );

            if (status != EFI_SUCCESS) return status;

            continue;
        }

        if (status != EFI_SUCCESS) {
            uefi_call_wrapper(gBS->FreePool, 1, buffer);
            return status;
        }

        /* No more entries */
        if (read_size == 0) {
            break;
        }

        /* Process every entry returned */
        UINTN offset = 0;

        while (offset < read_size) {
            EFI_FILE_INFO *info =
                (EFI_FILE_INFO *)(buffer + offset);

            if (info->Size == 0) {
                break;
            }

            if (info->Attribute & EFI_FILE_DIRECTORY) {
                Print(L"  [DIR]  %s\r\n", info->FileName);
            } else {
                Print(L"  [FILE] %s\r\n", info->FileName);
            }

            offset += info->Size;
        }
    }

    uefi_call_wrapper(gBS->FreePool, 1, buffer);

    return EFI_SUCCESS;
}
