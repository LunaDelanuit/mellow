# Mellow

Mellow is an elegant, easy-to-use, modern operating system intended to provide a familiar computing environment combining ideas of Window and Unix philosophies.

The primary goal of Mellow is to remove the perceived divide between the accessibility and familiarity of Windows and the power and flexibility of Unix/Linux.

Mellow also acts as a spiritual successer to my other operating system - Miyabi. The reason can be found [here](https://github.com/LunaDelanuit/miyabi#readme).

More information about Mellow can be found at `docs` in the project's root directory.

## License

Copyright (c) 2026 Luna Delanuit and contributers.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the [GNU General Public License](https://www.gnu.org/licenses/gpl-3.0) for more details.

## Building

### Source

Required build tools:
* Any GNU/Linux system.
* GNU C Compiler (GCC)
* GNU Binutils
* GNU-EFI
* GNU mtools
* dosfstools
* Xorriso

Optionally:
* QEMU if you want to emulate Mellow

In the project root, simply run `make`; an ISO file will be generated in `/build`.

Alternatively, type `./run-qemu.sh` to automatically build and launch QEMU with recommended arguments.

### Binary-provided

Currently, no binary-provided builds of Mellow are available *yet*.

## Features

*This section is a work in progress~*

## Third-Party Acknowledgements

### GNU-EFI

GNU-EFI is a lightweight developing environment to create UEFI applications

Licensed under the GNU General Public License version 2 or later, **AND** BSD-3-Clause.
Specific license information can be found [here](https://github.com/ncroxon/gnu-efi?tab=License-1-ov-file#readme).

The repository can be found [here](https://github.com/ncroxon/gnu-efi).

Created by Nigel Croxon.
