# Virtual File System

Mellow does not follow the Linux Filesystem Hierarchy Standard (FHS). Instead, Mellow implements its own filesystem hierarchy designed around clear principles: *Each directory has one responsibility. Responsibilities do not overlap.*

This design avoids the historical baggage of FHS while maintaining the elegance and clarity of Unix-like systems.

## Design Principles

* **Clear Responsibility** — Each directory serves a single, well-defined purpose
* **Predictability** — Users and programs can reliably predict where things belong
* **Scalability** — New needs are accommodated by adding subdirectories, not mixing concerns
* **Power and Accessibility** — Power users have low-level access; normal users get high-level abstractions; both coexist without confusion

## Filesystem Hierarchy

### `/System`

Contains all Mellow-provided system components. This directory is protected and typically only modifiable by the system administrator.

* `/System/Kernel` — Kernel binary and essential kernel modules
* `/System/Libraries` — Core system libraries (libc, libm, etc.)
* `/System/Utilities` — Essential system tools (mount, fsck, dd, etc.)
* `/System/Boot` — Bootloader and boot-related files
* `/System/Devices` — Device files and device interfaces (for power users and system administration)
  * `/System/Devices/block/` — Block devices (disks, partitions, etc.)
  * `/System/Devices/char/` — Character devices (terminals, random, etc.)
* `/System/Info` — System information and kernel state
  * `/System/Info/processes` — Running processes and process information
  * `/System/Info/cpuinfo` — CPU information
  * `/System/Info/meminfo` — Memory and system information

### `/Apps`

Contains all installed software. This includes system applications, user-installed applications, and drivers.

* `/Apps/System/` — Mellow-provided applications (file manager, terminal, settings, etc.)
* `/Apps/Installed/` — Third-party and user-installed applications
  * `/Apps/Installed/Firefox/`
  * `/Apps/Installed/Zed/`
  * `/Apps/Installed/Blender/`
  * `/Apps/Installed/Whatever`
* `/Apps/Drivers/` — Non-essential kernel drivers as loadable modules

### `/Config`

Contains all configuration files for the system and applications. Users may edit these files directly, or through GUI settings applications.

* `/Config/System/` — System-level configuration
  * `hostname` — System hostname
  * `network/` — Network configuration
  * `boot/` — Boot-time configuration
  * `users/` — User account information
* `/Config/Applications/` — Application-specific configurations
  * `/Config/Applications/Firefox/`
  * `/Config/Applications/Zed/`

Configuration file formats are determined by the application or system component that creates them. This may include `.conf`, `.ini`, `.json`, `.xml`, or other formats as appropriate.

### `/Users`

Contains user data and user-specific settings.

* `/Users/<username>/` — Individual user home directory
  * `Desktop/` — User's desktop files
  * `Documents/` — User's documents
  * `Downloads/` — User's downloads
  * `Pictures/` — User's pictures
  * `Videos/` — User's videos
  * `Music/` — User's music
  * `Config/` — User-specific application configuration and settings
* `/Users/root/` — Root user home directory

### `/Storage`

Contains mounted external storage devices and removable media. This directory is designed to be user-friendly.

Removable devices (USB drives, external hard drives, SD cards, etc.) are automatically detected and mounted here with human-readable names.

* `/Storage/USB Drive` — Auto-discovered removable storage
* `/Storage/External SSD` — Auto-discovered removable storage

Users can customize mount point names for more meaningful identification (e.g., `/Storage/My Photos`, `/Storage/Archive`).

### `/State`

Contains runtime data, temporary files, logs, and volatile information that can be safely cleared.

* `/State/Logs/` — System and application logs
  * `/State/Logs/System/` — System-level logs
  * `/State/Logs/Applications/` — Application-specific logs
* `/State/Temp/` — Temporary files
* `/State/Cache/` — Application and system caches
* `/State/Run/` — Runtime data (PID files, sockets, locks)

### `/Packages`

Contains package manager metadata and version tracking. Users typically do not interact with this directory.

* `/Packages/Registry/` — Installed package registry
* `/Packages/Versions/` — Version tracking and dependency information

## Device Access

Devices are accessible at two levels:

**Low-level access** (for power users, system administration, and development):
* `/System/Devices/block/sda`
* `/System/Devices/block/sda1`
* `/System/Devices/char/tty0`
* `/System/Devices/char/random`

**High-level access** (for normal users):
* `/Storage/USB Drive`
* `/Storage/External SSD`
*

Normal users interact with devices through the high-level interface. Power users and administrators can access devices directly through `/System/Devices` when needed.

## File Naming and Case Sensitivity

Filenames are **case-sensitive**. This aligns with Unix conventions and is necessary for compatibility with POSIX software and standards.

The filesystem preserves the case of filenames exactly as created. `file.txt` and `FILE.TXT` are different files.

## Configuration Philosophy

Configuration files may use any format appropriate to the application or system component:

* System configurations typically use plain `.conf` format (human-readable, text-editable)
* Applications may use `.ini`, `.json`, `.xml`, or other structured formats as appropriate
* Users can inspect and edit configuration files directly if desired
* GUI settings applications read and write configuration files on behalf of users

There is no single enforced configuration format or location beyond the organizational structure of `/Config`.

## Future Considerations

Additional root directories may be added as Mellow develops if new needs require them. Any addition would follow the same principle: *Each directory has one responsibility. Responsibilities do not overlap.*
