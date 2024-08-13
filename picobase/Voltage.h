#pragma once
#include "Reg.h"
#include "Types.h"

/*
 * Reference: sections 2.10 and 2.11 in:
 * https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf
 */

constexpr u32 const kVRegAndChipResetBase = 0x40064000;

/** Section 2.10.6, "List of Registers" */
struct VRegAndReset : Regs<kVRegAndChipResetBase, 3> {
    struct VReg : Reg {
        auto regOK() { return bit(12); }

        enum class VoltageSel : u8 {
            k0v80 = 0b0000,
            k0v85 = 0b0110,
            k0v90 = 0b0111,
            k0v95 = 0b1000,
            k1v00 = 0b1001,
            k1v05 = 0b1010,
            k1v10 = 0b1011,  // default
            k1v15 = 0b1100,
            k1v20 = 0b1101,
            k1v25 = 0b1110,
            k1v30 = 0b1111,
        };
        auto voltageSel() { return bits<VoltageSel>(7, 4); }

        auto hiZMode() { return bit(1); }

        auto enable() { return bit(0); }
    };

    struct BOD : Reg {
        enum class ThresholdSel : u8 {
            k0v473 = 0b0000,
            k0v516 = 0b0001,
            k0v559 = 0b0010,
            k0v602 = 0b0011,
            k0v645 = 0b0100,
            k0v688 = 0b0101,
            k0v731 = 0b0110,
            k0v774 = 0b0111,
            k0v817 = 0b1000,
            k0v860 = 0b1001,  // default
            k0v903 = 0b1010,
            k0v946 = 0b1011,
            k0v989 = 0b1100,
            k1v032 = 0b1101,
            k1v075 = 0b1110,
            k1v118 = 0b1111,
        };
        auto thresholdSel() { return bits<ThresholdSel>(7, 4); }
        auto enable() { return bit(0); }
    };

    struct ChipReset : Reg {
        auto psmRestart() { return bit(24); }
        auto hadPSMRestart() { return bit(20); }
        auto hadRun() { return bit(16); }
        auto hadPowerOn() { return bit(8); }
    };

    auto vreg() { return VReg {regs() + 0}; }
    auto bod() { return BOD {regs() + 1}; }
    auto chipReset() { return ChipReset {regs() + 2}; }
};
extern VRegAndReset vregAndReset;
