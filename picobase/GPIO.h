#pragma once
#include "Reg.h"
#include "Types.h"

/*
 * Reference: section 2.19.6 in:
 * https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
 */

constexpr u32 const kIOBank0Base = 0x40014000;

struct IOBank0 : Regs<kIOBank0Base, 100> {
    // Offsets: 0x000, 0x008, …, 0x0e0, 0x0e8
    // -> indexes 0, 2, 4, ... 58 -> GPIOs 0..29
    struct GPIOStatus : Reg {
        auto gpioToProc() { return bit(26); }
        auto irqFromPad() { return bit(24); }
        auto inToPeriph() { return bit(19); }
        auto inFromPad() { return bit(17); }
        auto outEnableToPad() { return bit(13); }
        auto outEnableFromPeriph() { return bit(12); }
        auto outToPad() { return bit(9); }
        auto outFromPeriph() { return bit(8); }
    };
    auto gpioStatus(u8 g) { return GPIOStatus {regs() + (g * 2)}; }

    // Offsets: 0x004, 0x00c, …, 0x0e4, 0x0ec
    // -> indexes 1, 3, 5, ..., 59 -> GPIOs 0..29
    struct GPIOControl : Reg {
        enum class IRQOverride : u32 {
            kNoInvert = 0,
            kInvert = 1,
            kDriveLo = 2,
            kDriveHi = 3
        };
    };
    auto gpioControl(u8 g) { return GPIOControl {regs() + (g * 2) + 1}; }

    // TODO: INTR0 Register
    // TODO: INTR1 Register
    // TODO: INTR2 Register
    // TODO: INTR3 Register

    // TODO: PROC0_INTE0 Register
    // TODO: PROC0_INTE1 Register
    // TODO: PROC0_INTE2 Register
    // TODO: PROC0_INTE3 Register

    // TODO: PROC0_INTF0 Register
    // TODO: PROC0_INTF1 Register
    // TODO: PROC0_INTF2 Register
    // TODO: PROC0_INTF3 Register

    // TODO: PROC0_INTS0 Register
    // TODO: PROC0_INTS1 Register
    // TODO: PROC0_INTS2 Register
    // TODO: PROC0_INTS3 Register

    // TODO: PROC1_INTE0 Register
    // TODO: PROC1_INTE1 Register
    // TODO: PROC1_INTE2 Register
    // TODO: PROC1_INTE3 Register

    // TODO: PROC1_INTF0 Register
    // TODO: PROC1_INTF1 Register
    // TODO: PROC1_INTF2 Register
    // TODO: PROC1_INTF3 Register

    // TODO: PROC1_INTS0 Register
    // TODO: PROC1_INTS1 Register
    // TODO: PROC1_INTS2 Register
    // TODO: PROC1_INTS3 Register

    // TODO: DORMANT_WAKE_INTE0 Register
    // TODO: DORMANT_WAKE_INTE1 Register
    // TODO: DORMANT_WAKE_INTE2 Register
    // TODO: DORMANT_WAKE_INTE3 Register

    // TODO: DORMANT_WAKE_INTF0 Register
    // TODO: DORMANT_WAKE_INTF1 Register
    // TODO: DORMANT_WAKE_INTF2 Register
    // TODO: DORMANT_WAKE_INTF3 Register

    // TODO: DORMANT_WAKE_INTS0 Register
    // TODO: DORMANT_WAKE_INTS1 Register
    // TODO: DORMANT_WAKE_INTS2 Register
    // TODO: DORMANT_WAKE_INTS3 Register
};
extern IOBank0 ioBank0;
