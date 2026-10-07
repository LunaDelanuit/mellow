### 1. Overview

Mellow is an elegant, easy-to-use, powerful, modern, general-purpose, modular operating system.

Mellow is intended to provide a familiar computing environment that combines ideas and qualities traditionally associated with both Windows and Unix-like operating systems.

The primary goal of Mellow is to remove the perceived divide between the accessibility and familiarity of Windows and the power and flexibility of Unix/Linux.

### 2. Intended Users

Mellow is designed for everyone alike.

It is not intended to be restricted to a particular class of user such as developers, power users, servers, or hobbyists. Its design should therefore accommodate users who have little technical knowledge.

### 3. Design Philosophy

Mellow should be:

* **Elegant** — systems and interfaces should avoid unnecessary complexity and feel coherent.
* **Easy to use** — users should be able to accomplish common tasks without requiring extensive technical knowledge.
* **Powerful** — ease of use should not come at the cost of capability.
* **Predictable** — behavior should be understandable and consistent.
* **Consistent** — related concepts should behave in related ways throughout the system.
* **Modern** — Mellow should be designed as a contemporary operating system rather than being constrained by historical conventions.
* **Modular** — major system components should be capable of being developed and maintained independently where appropriate.
* **Transparent** — the operating system should not unnecessarily hide what it is doing from the user.
* **Open** — the system should be fully open so that users can inspect and understand how it works.

### 4. Architectural Approach

Mellow adopts a **Unix-like core** with **Windows-like accessibility**.

The kernel is designed around Unix principles: elegant abstractions, composable primitives, and transparent behavior. This provides power and flexibility.

The presentation layer (shell, file manager, GUI) is designed around Windows principles: familiar, accessible, and visual. This provides accessibility without sacrificing capability.

This separation of concerns means:
* Power users can drop to the CLI and use Unix tools
* Normal users can use the GUI and accomplish everything without touching a terminal
* Both are first-class ways to interact with the system
* Neither compromises the other

### 5. Kernel Philosophy

The Mellow kernel provides the underlying abstractions and fundamental functionality required by the operating system.

The kernel also provides the system-call interface through which programs and other system components interact with the underlying system.

Drivers should not be inherently tied to the kernel itself. Hardware drivers should instead exist as independent kernel modules.

This modular approach is intended to keep the kernel and its drivers separated while allowing the operating system to support hardware through independently developed components.

### 6. Software Philosophy

Mellow programs should aim to be:

* Easy to use
* Powerful
* Small
* Elegant
* Easy to understand and troubleshoot

When something goes wrong, the user should have enough information to understand what happened or seek help.

Mellow should favor transparent error reporting rather than obscuring failures behind vague messages.

Even when a user does not understand a technical error themselves, useful and explicit information should make it possible to search for the problem and find assistance.

### 7. Compatibility

**POSIX Compatibility** is a primary design goal for Mellow.

POSIX (Portable Operating System Interface) defines a set of standards for Unix-like operating systems. By targeting POSIX compatibility as a primary goal, Mellow ensures:

* Ability to run most Unix and Unix-like software
* Stability and predictability through adherence to a well-established standard
* Clear, achievable targets for development
* A coherent foundation built on proven abstractions

**Linux Compatibility** is not currently a design consideration.

Mellow will not attempt to replicate Linux-specific features or extensions. Linux compatibility may be considered in the future (several years into development), but only after Mellow's own architecture and philosophy are fully established.

**Other Operating System Compatibility** (Windows, macOS, etc.) is not a design goal at the kernel level.

However, compatibility may be provided through userspace layers, translation tools, or future design considerations.

### 8. Hardware

Mellow's hardware model is being defined alongside the filesystem hierarchy.

The design of hardware abstractions, device representation, and related mechanisms remains an active design area.

Please read `vfs.md` and `hardware.md` after this.

### 9. Current Motivation

Mellow is primarily being developed as an exploration of how the traditional divide between Windows and Linux/Unix-like environments could be removed.

The intended result is an operating system that combines:

* The familiarity and accessibility commonly associated with Windows (through GUI and userspace tools)
* The power and flexibility commonly associated with Unix/Linux (through the kernel and CLI)
* A consistent and elegant design at the architectural level
* Transparent system behavior
* A modular architecture where components can be developed independently

Mellow should feel like one operating system rather than a collection of incompatible philosophies.

### 10. Open Questions

The following areas have not yet been fully decided:

* What Mellow considers a process
* What Mellow considers a program
* What Mellow considers a file
* What Mellow considers a device
* What Mellow considers a user
* How modules work and interact with the kernel
* How privilege boundaries are enforced
* How inter-process communication works
* How memory is managed and protected
* How storage devices are represented and mounted
* How executable programs are represented and launched
* How the user interacts with the system (beyond basic CLI/GUI)
* What userspace compatibility mechanisms Mellow may eventually provide

These should be designed after the fundamental philosophy and terminology of Mellow have been established. Decisions made on these topics must align with the core principles outlined above.
