#pragma once

#include "Reg.h"

template <u32 tBase>
struct PLL : Regs<tBase, 42> {};

struct SysPLL : PLL<0xbeef0000> {
    constexpr SysPLL() = default;
};

template <u32 tBase>
struct Clock : Regs<tBase, 42> {};

struct Clock0 : Clock<0xf00df00d> {
    constexpr Clock0() = default;
};

extern SysPLL gSysPLL;
extern Clock0 gClock0;
