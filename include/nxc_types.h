/*  nxc_types.h - nxc-lib foundation types
    Part of nxc-lib (Nodeflow-eXecution C-library)
    
    This header defines all base types used across nxc-lib.
    Include this header directly or via 'nxc.h'.
    See: "Import_Guide.md" inside the github repository.  */

#ifndef NXC_TYPES_H
#define NXC_TYPES_H

#include <wchar.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*  Integer-type size guarantees
    stdint.h provides fixed-size types per the C99 standard.
    Static assertions are added as an explicit compile-time safety net —
    they document the size contract directly in code and catch any
    non-compliant or misconfigured toolchain before it causes silent
    runtime errors. */

// signed integers
typedef int8_t nxc_i8;
_Static_assert(sizeof(nxc_i8) == 1, "nxc_i8 must be 1 byte");

typedef int16_t nxc_i16;
_Static_assert(sizeof(nxc_i16) == 2, "nxc_i16 must be 2 bytes");

typedef int32_t nxc_i32;
_Static_assert(sizeof(nxc_i32) == 4, "nxc_i32 must be 4 bytes");

typedef int64_t nxc_i64;
_Static_assert(sizeof(nxc_i64) == 8, "nxc_i64 must be 8 bytes");

// unsigned integers
typedef uint8_t nxc_u8;
_Static_assert(sizeof(nxc_u8) == 1, "nxc_u8 must be 1 byte");

typedef uint16_t nxc_u16;
_Static_assert(sizeof(nxc_u16) == 2, "nxc_u16 must be 2 bytes");

typedef uint32_t nxc_u32;
_Static_assert(sizeof(nxc_u32) == 4, "nxc_u32 must be 4 bytes");

typedef uint64_t nxc_u64;
_Static_assert(sizeof(nxc_u64) == 8, "nxc_u64 must be 8 bytes");

/*  Float-type size guarantees
    Float types are expected to be 32-bit and 64-bit respectively.
    No stdint.h equivalent exists for floats,
    size is verified via Static_assert.*/

typedef float nxc_f32;
_Static_assert(sizeof(nxc_f32) == 4, "nxc_f32 must be 4 bytes");

typedef double nxc_f64;
_Static_assert(sizeof(nxc_f64) == 8, "nxc_f64 must be 8 bytes");

/* Utility types
   Unlike fixed-size integer types, utility types are
   platform-aware by design. They wrap standard C types
   that adapt to the target platform intentionally. */

// unsigned type for object sizes and array indices, platform-dependent width
typedef size_t nxc_size;

// bool datatype
typedef bool nxc_bool;

// byte data-type
typedef uint8_t nxc_byte;

// unsigned integer type capable of storing a data pointer, similar to void*
typedef uintptr_t nxc_uptr;

// signed counterpart to nxc_uptr
typedef intptr_t nxc_iptr;

// pointer difference for pointer arithmetic to elements of the same array
typedef ptrdiff_t nxc_ptrdiff;

// span of data for handing eg. array to functions
typedef struct {
    nxc_byte* data;
    nxc_size len;
} nxc_span;

// read only counterpart to nxc_span
typedef struct {
    const nxc_byte* data;
    nxc_size len;
} nxc_cspan;

/* nxc_range represents a half-open index range [begin, end).
   begin is inclusive, end is exclusive.
   The number of elements in the range is always (end - begin).
   Example: begin=2, end=5 covers indices 2, 3, 4. */
typedef struct {
    nxc_size begin;
    nxc_size end;
} nxc_range;

/* Character types
   nxc_char wraps char and is intended for UTF-8 or ASCII text.
   nxc_wchar wraps wchar_t for wide characters (platform-dependent size).
   nxc_str and nxc_str_mut provide simple string views
   over immutable and mutable character data respectively. */

typedef char nxc_char;
_Static_assert(sizeof(nxc_char) == 1, "nxc_char must be 1 byte");

typedef wchar_t nxc_wchar;
// no Static_assert, size is platform-dependent

/* nxc_str is an immutable string view over existing character data.
   The underlying data is read-only and must outlive the view.
   Use for string literals, read-only access, and function parameters
   where modification is not intended. */
typedef struct {
    const nxc_char* data;
    nxc_size len;
} nxc_str;

/* nxc_str_mut is a mutable string view over existing character data.
   The underlying data is writable but must outlive the view.
   Use when in-place modification of string contents is required.
   Prefer nxc_str where mutation is not needed. */
typedef struct {
    nxc_char* data;
    nxc_size len;
} nxc_str_mut;

#endif