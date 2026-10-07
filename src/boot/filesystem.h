/*
 * Mellow Operating System
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef FS_H
#define FS_H

#include <efi.h>
#include <efilib.h>

EFI_FILE_PROTOCOL *open_filesystem(
    EFI_HANDLE image_handle,
    EFI_SYSTEM_TABLE *system_table
);

EFI_STATUS list_directory(EFI_FILE_PROTOCOL *directory);

#endif
