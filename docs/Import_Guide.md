# nxc-lib — Import Guide

This document covers how to include and use nxc-lib headers in your project.

---

## Installation

nxc-lib is header-only where possible.
Clone the repository and add the `include/` folder to your project's include path.

```sh
git clone https://github.com/nxsoftware/nxc-lib
```

Then include headers as needed:

```c
#include "nxc_types.h"
```

## Current Headers

### nxc_types.h

Provides all foundation types used across nxc-lib.
Include this header in any file that uses nxc-lib types.

```c
#include "nxc_types.h"
```

This header provides:
- Fixed-width integer types (nxc_i8 through nxc_i64, nxc_u8 through nxc_u64)
- Floating-point aliases (nxc_f32, nxc_f64)
- Platform-aware utility types (nxc_size, nxc_bool, nxc_byte, nxc_uptr, nxc_iptr, nxc_ptrdiff)
- Memory abstractions (nxc_span, nxc_cspan, nxc_range)
- Character and string view types (nxc_char, nxc_wchar, nxc_str, nxc_str_mut)

No source file is required. nxc_types.h is header-only.
(Unfinished) See: [nxc_types.md](technical_documentations/nxc_types.md) for detailed technical documentation.

---

## Notes

Further headers will be documented here as the library grows.
