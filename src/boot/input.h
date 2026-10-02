/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INPUT_H
#define INPUT_H

#include <efi.h>
#include <efilib.h>

EFI_INPUT_KEY wait_for_key(EFI_SYSTEM_TABLE* system_table);

#endif
