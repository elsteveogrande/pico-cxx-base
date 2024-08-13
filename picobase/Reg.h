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

template <typename Z = u32>
struct Slice {
    Reg& reg;
    u8 hi;  // MSB position, exclusive
    u8 lo;  // LSB position, inclusive

    void operator=(Z x);
    void operator&=(Z x);
    void operator|=(Z x);
    void operator^=(Z x);
    operator Z() const;
};

struct Reg {
    u32* const addr;

    template <typename T>
    Slice<T> bits(int hiInc, int loInc) {
        return Slice<T> {*this, hiInc + 1, loInc};
    }

    template <typename T = bool>
    Slice<T> bit(int bit) {
        return Slice<T>(*this, bit + 1, bit);
    }

    u32& operator*();
    u32 operator*() const;
};

template <typename Z>
inline void Slice<Z>::operator=(Z z) {
    u32 val = *reg;
    u32 mask = ((1 << hi) - 1) - ((1 << lo) - 1);
    val &= ~mask;
    val |= (u32(z) << lo);
    *reg = val;
}

template <>
inline void Slice<bool>::operator=(bool z) {
    *reg |= (u32(z) << lo);
}

template <>
inline Slice<>::operator u32() const {
    if (hi <= lo) { throw hi; }
    return ((*reg) >> lo) & ((1 << (hi - lo)) - 1);
}

inline u32& Reg::operator*() { return *addr; }
inline u32 Reg::operator*() const { return *addr; }

template <u32 REGBASE, u8 COUNT>
struct Regs {
    constexpr u32* regs() const { return (u32*)(void*)(REGBASE); }
};
