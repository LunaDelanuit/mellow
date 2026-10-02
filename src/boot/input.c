/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "input.h"

/* Wait for a single key stroke */
EFI_INPUT_KEY wait_for_key(EFI_SYSTEM_TABLE* system_table) {
    EFI_STATUS status;
    UINTN event_index;
    EFI_INPUT_KEY key;

    /* Clear the input buffer */
    uefi_call_wrapper(system_table->ConIn->Reset, 2, system_table->ConIn, FALSE);

    /* Wait for the keyboard event to trigger */
    uefi_call_wrapper(system_table->BootServices->WaitForEvent, 3,
                        1, &system_table->ConIn->WaitForKey, &event_index);

    /* Read the key stroke */
    status = uefi_call_wrapper(system_table->ConIn->ReadKeyStroke, 2,
                                system_table->ConIn, &key);

    /* Confirm key stroke */
    if (status == EFI_SUCCESS) {
        return key;
    } else {
        return (EFI_INPUT_KEY){0, 0};
    }
}
