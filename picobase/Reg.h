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

template <typename Z = u32>
struct Slice {
    u32 volatile* const addr;
    u8 const hi;
    u8 const lo;
    u32 const hiMask = (1 << (hi + 1)) - 1;
    u32 const loMask = (1 << lo) - 1;
    u32 const mask = hiMask - loMask;

    void operator=(Z z) { (*addr) = ((*addr) & ~mask) | (u32(z) << lo); }
    operator u32() const { return ((*addr) & mask) >> lo; }
};

struct Reg {
    u32 volatile* const addr;

    template <typename T>
    Slice<T> bits(u8 hiInc, u8 loInc) {
        return Slice<T> {addr, hiInc, loInc};
    }

    template <typename T = bool>
    Slice<T> bit(u8 bit) {
        return Slice<T>(addr, bit, bit);
    }

    u32 volatile& operator*();
    u32 operator*() const;
};

template <>
inline void Slice<bool>::operator=(bool z) {
    *addr |= (u32(z) << lo);
}

inline u32 volatile& Reg::operator*() { return *addr; }
inline u32 Reg::operator*() const { return *addr; }

template <u32 REGBASE, u8 COUNT>
struct Regs {
    constexpr u32* regs() const { return (u32*)(void*)(REGBASE); }
};
