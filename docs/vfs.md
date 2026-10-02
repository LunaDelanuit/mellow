# Virtual File System

Forget the Linux Filesystem Hierarchy Standard (HFS), forget DOS-like legacy drive letters.  
The VFS will take concepts of both environments:

 * The `/` delimeter will be used. (HFS)
 * A root `/` directory will exist. (HFS)
 * Folders are separated into VFS-coded root directories. (Semi-DOS) (See Root Directories)
 * Folders and files are case-insensitive. (DOS)

 ## Root Directories

 `/System` - Contains all Mellow-related binaries and drivers. Protected by the root/Administrator user. Will also hold `/System/Boot` for boot-related files.  
 `/Apps` - System-wide installed apps will fall here. Mellow's version of `/bin` or `C:\Program Files`  
 `/Users` - Holds all user directories, similar to Window's `C:\Users`. (See User Directories)  
 `/Config` - Replaces Linux's messy `/etc` folder. Holds all system-configs and system-wide app configs.  
 `/Storage` - Instead of Linux's `/mnt` or Window's `D:\`; holds all extra storage devices.  

 ## User Directories

 User directories will look similar to Window's user directories (without OneDrive (ew)).

 (In context of `/Users/<username>/`)  
`Apps` - User-installed applications.  
`Config` - User-specific config files.  
And all the standard stuff like `Documents`, `Pictures`, `Videos`, `Desktop`, etc., will exist!~

More will be written once I actually implement the VFS.
