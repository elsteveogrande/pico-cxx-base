#pragma once

// Define very basic types (in lieu of e.g. `cstdint`)

using u8 = unsigned char;
static_assert(sizeof(u8) == 1);

using u16 = unsigned short;
static_assert(sizeof(u16) == 2);

using u32 = unsigned long;
static_assert(sizeof(u32) == 4);
