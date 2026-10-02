/*
 * Mellow Boot Manager
 * Copyright (C) 2026 Luna Delanuit and contributers
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <efi.h>
#include <efilib.h>
#include "input.h"

EFI_STATUS
efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE* system_table)
{
    /* Initialize and display copyright */
    InitializeLib(image_handle, system_table);
    Print(L"\r\nMellow Boot Manager v0.1a\r\n");
    Print(L"GNU General Public License Version 3 or any later version.\r\n");
    Print(L"Copyright (c) 2026 Luna Delanuit and contributers.\r\n\r\n");

    Print(L"Firmware Vendor: %s\r\n\n", system_table->FirmwareVendor);

    Print(L"Press 'q' to exit back to firmware.\r\n");
    EFI_INPUT_KEY key;

    /* Check key inputs */
    check_key:
        key = wait_for_key(system_table);

        if (key.UnicodeChar == 0 && key.ScanCode == 0) {
            /* An error occured during key reading */
            Print(L"An error occured trying to read a key input.\r\n");
        } else if (key.UnicodeChar == L'q') {
            return EFI_SUCCESS; /* Exit back to firmware. */
        } else if (key.UnicodeChar != 0) {
            Print(L"%c", key.UnicodeChar);
        } else {
            Print(L"Scan Code: 0x%X\r\n", key.ScanCode);
        }

    goto check_key;

    /* Should not run */
    return EFI_SUCCESS;
}
