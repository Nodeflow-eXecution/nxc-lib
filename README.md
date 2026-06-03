# nxc-lib — nodeflow-execution c-library

nxc-lib is a lightweight utility and foundation library for C, built around explicit data control, predictable behavior, and clear ownership semantics.

The library aims to provide practical building blocks for modern C development without hiding complexity behind opaque abstractions. Rather than introducing frameworks, magic behavior, or unnecessary layers of indirection, nxc-lib focuses on exposing data and operations in a way that remains easy to reason about and debug.

Every type, structure, and utility is designed with a simple principle in mind:

> What the code does should be visible from what the code says.

---

## Philosophy

nxc-lib is grounded in data-oriented principles and favors explicitness over convenience.

### Explicit Data

Data is the primary concern.

Types are intentionally named, portable where possible, and designed to communicate their purpose clearly. Memory ownership, mutability, and size should be understandable without requiring hidden assumptions.

### Predictable Behavior

Operations should behave exactly as they appear.

The library avoids hidden allocations, implicit state changes, automatic resource management, and other behaviors that make code difficult to reason about.

If memory is allocated, it should be obvious.

If data changes, it should be obvious.

If a function performs an expensive operation, it should be obvious.

### Transparency

nxc-lib does not attempt to hide the realities of C.

Instead, it embraces them while providing cleaner abstractions around common patterns such as spans, string views, ranges, containers, and utility functionality.

The goal is not to make C behave like another language, but to make C easier to work with while preserving its strengths.

### Small, Composable Building Blocks

Large monolithic systems are intentionally avoided.

Modules should remain independent wherever possible and compose naturally with existing codebases.

Developers should be able to adopt only the parts they need without pulling in unnecessary dependencies.

---

## Current State

nxc-lib is currently in the early stages of development.

The project foundation is being established, including:

* Core type definitions
* Platform-aware utility types
* Fixed-width integer and floating-point aliases
* Memory span abstractions
* String view types
* Range utilities
* Documentation and project structure

At this stage the API should be considered experimental and subject to change as the library's design evolves.

Meaning: Interfaces may change, functionality may expand, and some components may be redesigned as practical experience with the library grows.

---

## Roadmap

The long-term goal is to build a collection of practical, reusable utilities that remain lightweight and predictable.

Planned areas of development include:

* Error and result handling
* Memory and allocator utilities
* Dynamic arrays and containers
* String manipulation utilities
* Hashing and lookup structures
* File and I/O helpers
* Parsing utilities
* Platform abstraction helpers
* Testing infrastructure
* Additional documentation and examples

Future additions will continue to follow the project's core philosophy of explicit behavior, visible mutation, and minimal hidden state.

---

## Documentation

Detailed technical documentation for each header and module can be found in the [`docs/technical_documentations`](docs/technical_documentations) folder.

For import and usage guidance, see [`docs/Import_Guide.md`](docs/Import_Guide.md).

---

## Contact

Feedback, suggestions, and discussion are always welcome.

For any inquiry, contact info.nxsoftware@gmail.com
