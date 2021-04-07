# CppStringBuilder
A poor StringBuilder (C#)  clone for C++. Includes a testing playground (see Main.cpp and FunnyStrings.hpp)

**NOTE**: This has no performance gain compared to standard library tools, if you'd like to optimize further (good luck), then submit a PR!

## Implementation

### `StringBuilder (constructor)`
The StringBuilder initially reserves 1025 bytes (or `yourCapacity + 1` bytes) to do its operations in.

### `Append`
The way Append works is, it first checks if we've got enough space to work with, if not, allocate some more. After we did that, we just append the string that we provided to the pointer at `m_memory + m_stringSize` and increase the size.

### `GetString`
`GetString` makes use of a constructor for `std::string` that takes in a `const char*` and a length.

### `SetCapacity`
Resizes the allocated memory. First of all, we check to make sure that we don't size it small enough that our string no longer fits into the memory. If that happens, we just don't do anything. (**And this *can* be problematic.**) Otherwise, we carry on as normal. This function is used by `Append`.

### `~StringBuilder`
Frees up all the memory allocated by the `m_memory` array. 
