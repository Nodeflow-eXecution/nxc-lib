# nxc_types.h — Technical Documentation

# Overview

`nxc_types.h` defines the fundamental types used throughout nxc-lib.

The header provides:

* Fixed-width integer aliases
* Floating-point aliases
* Platform-aware utility types
* Memory view abstractions
* Range types
* Character types
* String view types

The goal is to establish a consistent type system across the entire library while remaining compatible with standard C types and conventions.

All types in this header are lightweight wrappers around standard C types or simple data structures. No type in this file performs allocation, ownership tracking, or automatic memory management.

---

## Dependencies

`nxc_types.h` depends only on standard library headers:

```c
#include <wchar.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
```

No platform-specific dependencies are required.

---

# Integer Types

## Overview

The integer types provide explicit size guarantees using the fixed-width types defined by `<stdint.h>`.

| Type      | Wrapped Type | Size   |
| --------- | ------------ | ------ |
| `nxc_i8`  | `int8_t`     | 8-bit  |
| `nxc_i16` | `int16_t`    | 16-bit |
| `nxc_i32` | `int32_t`    | 32-bit |
| `nxc_i64` | `int64_t`    | 64-bit |
| `nxc_u8`  | `uint8_t`    | 8-bit  |
| `nxc_u16` | `uint16_t`   | 16-bit |
| `nxc_u32` | `uint32_t`   | 32-bit |
| `nxc_u64` | `uint64_t`   | 64-bit |

Compile-time assertions verify the expected size of every type.

---

## When to Use

Use fixed-width integer types whenever:

* Binary file formats are involved
* Network protocols are involved
* Serialization/deserialization is required
* Data structures require predictable memory layout
* Portability across architectures matters

Example:

```c
typedef struct {
    nxc_u32 id;
    nxc_u16 flags;
    nxc_u16 version;
} packet_header;
```

---

## When Not to Use

Avoid fixed-width integers when the value represents:

* Array sizes
* Container lengths
* Memory sizes
* Object counts

For those cases, prefer `nxc_size`.

Example:

```c
nxc_size element_count;
```

instead of

```c
nxc_u32 element_count;
```

---

# Float Types

## Overview

| Type      | Wrapped Type |
| --------- | ------------ |
| `nxc_f32` | `float`      |
| `nxc_f64` | `double`     |

The library verifies only the storage size.

No guarantees are made regarding IEEE-754 compliance beyond what the compiler and platform provide.

---

## When to Use

Use:

* `nxc_f32` when memory footprint matters
* `nxc_f64` when numerical precision matters

Example:

```c
nxc_f32 temperature;
nxc_f64 simulation_time;
```

---

# Utility Types

## nxc_size

Wraps:

```c
size_t
```

Represents object sizes, array lengths, capacities, and indices.

Example:

```c
nxc_size length = 128;
```

Preferred over fixed-width integers when working with memory or container sizes.

---

## nxc_bool

Wraps:

```c
bool
```

Represents logical true/false values.

Example:

```c
nxc_bool is_valid = true;
```

---

## nxc_byte

Wraps:

```c
uint8_t
```

Represents raw byte-oriented data.

Example:

```c
nxc_byte buffer[256];
```

---

## nxc_uptr

Wraps:

```c
uintptr_t
```

An unsigned integer capable of storing a pointer value.

Useful when a pointer must be converted to an integer.

Example:

```c
nxc_uptr address = (nxc_uptr)ptr;
```

### Typical Use Cases

* Hashing pointers
* Address calculations
* Low-level memory systems
* Allocator implementations

### Not Intended For

General memory access.

This:

```c
ptr[5];
```

is usually preferable to:

```c
((nxc_uptr)ptr) + 5;
```

---

## nxc_iptr

Wraps:

```c
intptr_t
```

Signed counterpart to `nxc_uptr`.

Useful when signed pointer offsets are required.

Example:

```c
nxc_iptr offset;
```

---

## nxc_ptrdiff

Wraps:

```c
ptrdiff_t
```

Represents the difference between two pointers that refer to elements of the same array.

Example:

```c
nxc_ptrdiff diff = end - begin;
```

---

# Memory View Types

## nxc_span

Represents a mutable view over contiguous memory.

```c
typedef struct {
    nxc_byte* data;
    nxc_size len;
} nxc_span;
```

The span does **not** own the memory.

Example:

```c
nxc_byte buffer[128];

nxc_span span = {
    .data = buffer,
    .len  = 128
};
```

---

## nxc_cspan

Read-only counterpart to `nxc_span`.

```c
typedef struct {
    const nxc_byte* data;
    nxc_size len;
} nxc_cspan;
```

Use when modification is not intended.

Example:

```c
void process(nxc_cspan data);
```

---

## Ownership Rules

Neither `nxc_span` nor `nxc_cspan` owns memory.

The referenced memory must remain valid for the entire lifetime of the span.

Valid:

```c
nxc_byte buffer[32];

nxc_span span = {
    .data = buffer,
    .len = 32
};
```

Invalid:

```c
nxc_span make_span(void)
{
    nxc_byte buffer[32];

    return (nxc_span){
        .data = buffer,
        .len = 32
    };
}
```

The returned span points to memory that no longer exists.

---

# Range Types

## nxc_range

Represents a half-open interval:

```text
[begin, end)
```

Meaning:

* begin is included
* end is excluded

Example:

```c
nxc_range range = {
    .begin = 2,
    .end = 5
};
```

This range covers:

```text
2, 3, 4
```

but not:

```text
5
```

---

## Why Half-Open Ranges?

Half-open ranges have several useful properties:

```text
element_count = end - begin
```

An empty range is naturally represented as:

```text
begin == end
```

Example:

```c
for (nxc_size i = range.begin; i < range.end; ++i)
{
    /* ... */
}
```

---

# Character Types

## nxc_char

Wraps:

```c
char
```

Intended for UTF-8 and ASCII text.

Example:

```c
nxc_char letter = 'A';
```

---

## nxc_wchar

Wraps:

```c
wchar_t
```

Represents wide characters.

The size of `wchar_t` is platform-dependent:

| Platform | Typical Size |
| -------- | ------------ |
| Windows  | 2 bytes      |
| Linux    | 4 bytes      |

Code should never assume a specific size.

---

# String View Types

## Overview

`nxc_str` and `nxc_str_mut` are non-owning string views.

They store:

* Pointer to character data
* Length of the view

They do **not** allocate memory.

They do **not** free memory.

They do **not** require null-termination.

---

## nxc_str

Immutable string view.

```c
typedef struct {
    const nxc_char* data;
    nxc_size len;
} nxc_str;
```

Example:

```c
nxc_str hello = {
    .data = "Hello",
    .len = 5
};
```

---

## nxc_str_mut

Mutable string view.

```c
typedef struct {
    nxc_char* data;
    nxc_size len;
} nxc_str_mut;
```

Example:

```c
nxc_char buffer[] = "Hello";

nxc_str_mut str = {
    .data = buffer,
    .len = 5
};
```

---

## Lifetime Requirements

String views do not own memory.

The referenced character data must outlive the view.

Valid:

```c
static const char text[] = "Hello";

nxc_str str = {
    .data = text,
    .len = 5
};
```

Invalid:

```c
nxc_str create(void)
{
    char buffer[32] = "Hello";

    return (nxc_str){
        .data = buffer,
        .len = 5
    };
}
```

The returned view references destroyed stack memory.

---

## Null-Termination

A string view is not required to be null-terminated.

Example:

```c
nxc_str str = {
    .data = "Hello World",
    .len = 5
};
```

This view represents:

```text
Hello
```

even though the source string contains additional characters.

Code should always respect `len` instead of relying on a terminating `'\0'`.

---

# Notes & Caveats

## Fixed-Width Types

The integer aliases rely on the availability of the corresponding `<stdint.h>` types.

Most modern platforms provide them.

---

## Floating-Point Guarantees

The library verifies size, not floating-point representation.

Applications requiring strict IEEE-754 guarantees should perform additional platform validation.

---

## Views Are Non-Owning

The following types never own memory:

* `nxc_span`
* `nxc_cspan`
* `nxc_str`
* `nxc_str_mut`

Destroying the underlying storage invalidates the view.

Always ensure the referenced memory outlives the view.

---

## Prefer Intent-Revealing Types

Use the type that best communicates purpose:

```c
nxc_size     count;
nxc_u32      network_id;
nxc_span     payload;
nxc_str      name;
nxc_range    indices;
```

Even when the underlying storage is identical, the semantic meaning becomes clearer to both readers and maintainers.