# Versioning

Mellow uses a versioning system designed to communicate both the development stage and the maturity of the operating system.

## Version Format

A Mellow version generally follows this format:

```text
MAJOR.MINOR[STAGE]
```

For example:

```text
0.1a
0.1b
0.1
0.2a
0.2b
0.2
```

The optional stage suffix indicates the development stage of the current milestone.

## Development Stages

### Alpha (`a`)

Alpha releases represent early development.

An alpha release may contain:

* Experimental features
* Incomplete features
* Significant changes
* Unstable functionality
* Features that are still being evaluated

Alpha releases are intended primarily for development, testing, and experimentation.

### Beta (`b`)

Beta releases represent later development and stabilization.

A beta release should generally contain the features intended for the milestone, but may still require:

* Bug fixing
* Stability improvements
* Testing
* Refinement
* Minor changes

Beta releases are more stable than alpha releases but are not yet considered ready for mainstream use.

### Stable

A version without a stage suffix represents a completed milestone.

For example:

```text
0.2
```

indicates that the 0.2 milestone has been completed and the resulting release is considered stable for its intended audience.

Stable does not necessarily mean that Mellow is production-ready as a whole. The maturity of the individual release depends on the overall development state of Mellow.

## Development Progression

A milestone may progress through alpha, beta, and stable stages:

```text
0.1a → 0.1b → 0.1
```

A milestone may also skip the beta stage when a separate beta phase is not useful:

```text
0.3a → 0.3
```

The alpha stage may also be skipped when a milestone consists only of small changes, such as a few bug fixes or other minor improvements:

```text
0.3 → 0.4b → 0.4
```

Skipping a development stage does not imply that the stage was forgotten. It means that the additional development phase was not necessary for that milestone.

## Releases

Mellow does not follow a fixed release schedule.

A release occurs when a meaningful development milestone has been completed and the resulting system is coherent enough to publish.

Features alone do not determine when a release occurs. A release should represent a meaningful state of Mellow rather than simply a collection of recently added features.

For example, a milestone might represent:

```text
0.1 — Initial boot
0.2 — Kernel foundations
0.3 — Userspace foundations
0.4 — Storage and filesystem foundations
```

The exact contents of each milestone are determined during development.

There is no requirement for every new feature to result in a release.

## Generation Increments

The major version represents a generation of Mellow.

A new generation should only be created when Mellow undergoes a significant architectural or compatibility-breaking change.

For example:

```text
1.x → 2.0
```

may be appropriate when Mellow introduces a fundamental change to:

* The kernel/userspace ABI
* The executable format
* The filesystem representation
* The process or security model
* Other fundamental system interfaces

Adding new features or improving existing functionality does not, by itself, require a new generation.

For example:

```text
1.2 → 1.3
```

may include:

* New filesystem support
* Additional POSIX functionality
* New hardware support
* Performance improvements
* New userspace functionality

without becoming Mellow 2.

The purpose of a generation increment is therefore to communicate a meaningful change in what Mellow is, rather than simply indicating that a large number of features have been added.

## Development and Stable Releases

Development versions allow users who want to test Mellow early to understand its current state.

For example:

```text
0.4a
```

communicates that 0.4 is currently in an early, experimental stage.

```text
0.4b
```

communicates that 0.4 is in a later, more stable development stage.

```text
0.4
```

communicates that the 0.4 milestone has been completed.

This distinction allows Mellow to provide testable development releases without requiring every change to be treated as a new stable release.

## Component Versioning

Mellow components may have their own version numbers when appropriate.

For example:

```text
Mellow 0.1
Mellow Boot Manager 0.1a
```

The version of a component does not need to match the version of the overall operating system.

Components may therefore progress independently while remaining part of the same Mellow release.

## Aliasing

Version numbers may be simplified or expanded for communication purposes.

**Simplified aliases** communicate the essence of a version without full precision:

```text
Mellow 1.3 -> Mellow
Mellow 2.4 -> Mellow 2
```

When Mellow reaches significant maturity or when a specific generation is well-established, referring to it simply by the major version (or without version at all) is appropriate.

**Expanded aliases** communicate the same version with additional context:

```text
Mellow 2.3 -> Mellow Generation 2 Version 3
```

Expanded aliases may be used in documentation, formal communication, or when maximum clarity is desired.

Aliases do not change the actual version of the software. They are alternative ways to refer to the same release.

## Summary

Mellow's versioning system follows these principles:

* **Alpha (`a`)** — early and experimental development
* **Beta (`b`)** — later development and stabilization
* **No suffix** — completed milestone
* **Minor versions** — meaningful compatible milestones
* **Major versions** — fundamental architectural or compatibility generations
* Development stages may be skipped when unnecessary
* Releases occur at meaningful milestones rather than on a fixed schedule
* Components may maintain independent versions
