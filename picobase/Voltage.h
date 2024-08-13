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
        auto regOK() { return (*this)[12]; }

        constexpr static auto k0v80 = 0b0000;
        constexpr static auto k0v85 = 0b0110;
        constexpr static auto k0v90 = 0b0111;
        constexpr static auto k0v95 = 0b1000;
        constexpr static auto k1v00 = 0b1001;
        constexpr static auto k1v05 = 0b1010;
        constexpr static auto k1v10 = 0b1011;
        constexpr static auto k1v15 = 0b1100;
        constexpr static auto k1v20 = 0b1101;
        constexpr static auto k1v25 = 0b1110;
        constexpr static auto k1v30 = 0b1111;
        auto voltageSel() { return (*this)[8, 4]; }

        auto hiZMode() { return (*this)[1]; }

        auto enable() { return (*this)[0]; }
    };

    struct BOD : Reg {
        auto thresholdSel() { return (*this)[8, 4]; }
        auto enable() { return (*this)[0]; }
    };

    struct ChipReset : Reg {
        auto psmRestart() { return (*this)[24]; }
        auto hadPSMRestart() { return (*this)[20]; }
        auto hadRun() { return (*this)[16]; }
        auto hadPowerOn() { return (*this)[8]; }
    };

    auto vreg() { return VReg {regs() + 0}; }
    auto bod() { return BOD {regs() + 1}; }
    auto chipReset() { return ChipReset {regs() + 2}; }
};
