> [!NOTE]
> Recommended to read through `vfs.md` first.

# Hardware Abstraction

Mellow's hardware abstraction layer is currently under design. This document outlines the general approach.

## Devices as Modules

Hardware drivers in Mellow are implemented as independent kernel modules. Drivers are not inherently tied to the kernel and can be developed, tested, and updated independently.

## Device Interfaces

Devices are presented to the system through well-defined interfaces:

**Block Devices** — Persistent storage (disks, partitions, USB drives)
* Accessible through `/System/Devices/block/`
* Mounted through `/Storage/` for user access
* Used by filesystems and storage applications

**Character Devices** — Sequential I/O devices (terminals, random number generators, etc.)
* Accessible through `/System/Devices/char/`
* Used directly by applications or through abstractions

**Network Devices** — Network interfaces
* Accessible through `/System/Devices/net/` or equivalent
* Configured through `/Config/System/network/`

## Driver Architecture

Drivers communicate with the kernel through a stable, well-defined interface. This isolation ensures:

* A faulty driver does not necessarily crash the kernel
* Drivers can be developed and tested independently
* Multiple drivers can coexist without interference
* The kernel remains small and focused

The specifics of driver loading, privilege levels, and communication mechanisms are still under design.

## Future Hardware Support

Mellow is currently targeted at x86_64 architecture. Support for additional architectures (ARM, RISC-V, etc.) may be considered in the future as the core system matures.
