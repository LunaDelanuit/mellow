### 1. Overview

Mellow is an elegant, easy-to-use, powerful, modern, general-purpose, modular operating system.

Mellow is intended to provide a familiar computing environment that combines ideas and qualities traditionally associated with both Windows and Unix-like operating systems.

The primary goal of Mellow is to remove the perceived divide between the accessibility and familiarity of Windows and the power and flexibility of Unix/Linux.

### 2. Intended Users

Mellow is designed for everyone alike.

It is not intended to be restricted to a particular class of user such as developers, power users, servers, or hobbyists. Its design should therefore accommodate users who have little technical knowledge while still providing the power and control expected by experienced users.

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

### 4. Windows and Unix

Mellow intentionally draws from both Windows and Unix-like operating systems.

Rather than attempting to reproduce either environment exactly, Mellow aims to combine useful characteristics of both into a single coherent system.

The goal is not simply to make one operating system resemble another. The goal is to provide an environment where familiarity, accessibility, power, and flexibility can coexist.

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

Compatibility with existing operating systems and software ecosystems is not currently a primary design goal.

However, compatibility should remain a consideration for the future.

Mellow's own architecture and philosophy should be established first rather than allowing compatibility requirements to dictate the fundamental design.

### 8. Hardware

Mellow's hardware model has not yet been defined.

The design of hardware abstractions, device representation, and related mechanisms remains an open design area.

Also, please read `vfs.md` after this.

### 9. Current Motivation

Mellow is primarily being developed as an exploration of how the traditional divide between Windows and Linux/Unix-like environments could be removed.

The intended result is an operating system that combines:

* The familiarity and accessibility commonly associated with Windows
* The power and flexibility commonly associated with Unix/Linux
* A consistent and elegant design
* Transparent system behavior
* A modular architecture

Mellow should feel like one operating system rather than a collection of incompatible philosophies.

### 10. Open Questions

The following areas have not yet been decided:

* What Mellow considers a process
* What Mellow considers a program
* What Mellow considers a file
* What Mellow considers a device
* What Mellow considers a user
* How modules work
* How hardware is represented
* How inter-process communication works
* How memory is managed
* How storage is represented
* How the filesystem works
* How executable programs are represented
* How the user interacts with the system
* What compatibility mechanisms Mellow may eventually provide

These should be designed after the fundamental philosophy and terminology of Mellow have been established.
