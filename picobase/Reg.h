#pragma once

#include "Types.h"

/*
 * RP2040 register base structures.
 *
 * Main reference:
 * https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
 *
 * Register addresses:
 * https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2040/hardware_regs/include/hardware/regs/addressmap.h
 */

struct Reg;

struct Slice {
    Reg& reg;
    u8 hi;  // MSB position, exclusive
    u8 lo;  // LSB position, inclusive

    void operator=(u32 x);
    void operator&=(u32 x);
    void operator|=(u32 x);
    void operator^=(u32 x);
    operator u32() const;
};

struct Reg {
    u32* const addr;

    Slice operator[](u8 bit) { return (*this)[bit + 1, bit]; }
    Slice operator[](u8 hi, u8 lo);

    u32 operator*() const;
};

inline Slice Reg::operator[](u8 hi, u8 lo) { return Slice {*this, hi, lo}; }

inline Slice::operator u32() const {
    if (hi <= lo) { throw hi; }
    return ((*reg) >> lo) & ((1 << (hi - lo)) - 1);
}

inline u32 Reg::operator*() const { return *addr; }

template <u32 REGBASE, u8 COUNT>
struct Regs {
    constexpr u32* regs() const { return (u32*)(void*)(REGBASE); }
};
