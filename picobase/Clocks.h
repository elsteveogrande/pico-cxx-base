#pragma once

#include "Reg.h"

template <u32 REGBASE>
struct PLL {
    void init();
};

struct SysPLL : PLL<0xbeef0000> {};

template <u32 REGBASE>
struct Clock {};

struct Clock0 {};
