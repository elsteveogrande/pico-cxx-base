#pragma once

#include "Reg.h"
#include "Types.h"

// Section 2.19.6.4, "Pad Control, QSPI Bank"
struct QSPIPads : Regs<0x40020000, 7> {
    constexpr QSPIPads() = default;

    struct VoltageSelect : Reg {
        enum class Voltage : bool {
            k3v3 = 0,
            k1v8 = 1,
        };
        auto voltage() { return bit<Voltage>(0); }
    };
    auto voltage() { return VoltageSelect {regs() + 0}; }

    struct PadControl : Reg {
        auto outEnable() { return bit(7); }
        auto inEnable() { return bit(6); }
        enum class Drive : u8 {
            k2mA = 0,
            k4mA = 1,
            k8mA = 2,
            k12mA = 3,
        };
        auto drive() { return bits<Drive>(5, 4); }
        auto pullUp() { return bit(3); }
        auto pullDown() { return bit(2); }
        auto schmitt() { return bit(1); }
        auto slewFast() { return bit(0); }
    };
    auto clkControl() { return PadControl {regs() + 1}; }
    auto padControl0() { return PadControl {regs() + 2}; }
    auto padControl1() { return PadControl {regs() + 3}; }
    auto padControl2() { return PadControl {regs() + 4}; }
    auto padControl3() { return PadControl {regs() + 5}; }
    auto ssControl() { return PadControl {regs() + 6}; }
};

struct SSI : Regs<0x18000000, 63> {
    constexpr SSI() = default;

    struct Control0 : Reg {
        auto periphEnable() { return bit(24); }

        enum class SPIFrameFormat {
            kStandardFullDuplex = 0,
            kDualHalfDuplex = 1,
            kQuadHalfDuplex = 2,
        };
        auto spiFrameFormat() { return bits<SPIFrameFormat>(22, 21); }

        auto frameSize32() { return bits<u8>(20, 16); }
        auto controlFrameSize() { return bits<u8>(15, 12); }
        auto shiftRegLoop() { return bit(11); }
        auto periphOutEnable() { return bit(10); }

        enum class XferMode {
            kTXRX = 0,
            kTXOnly = 1,
            kRXOnly = 2,
            kEEPROMTXThenRX = 3,
        };
        auto xferMode() { return bits<XferMode>(9, 8); }
        auto polarity() { return bit(7); }
        auto phase() { return bit(6); }

        // TODO: not explained in docs, is this simply SPIFrameFormat?
        enum class FrameFormat {
            kFF0 = 0,
            kFF1 = 1,
            kFF2 = 2,
            kFF3 = 3,
        };
        auto frameFormat() { return bits<FrameFormat>(5, 4); }
        auto frameSize() { return bits<u8>(3, 0); }
    };
    auto control0() { return Control0 {regs() + 0}; }

    struct Control1 : Reg {
        auto numDataFrames() { return bits<u16>(15, 0); }
    };
    auto control1() { return Control1 {regs() + 1}; }

    struct SSIEnable : Reg {
        auto enable() { return bit(0); }
    };
    auto ssiEnable() { return SSIEnable {regs() + 2}; }

    struct MicrowireControl : Reg {
        auto mwHandshaking() { return bit(2); }
        auto mwControl() { return bit(1); }
        auto mwMode() { return bit(0); }
    };
    auto microwireControl() { return MicrowireControl {regs() + 3}; }

    struct PeriphEnable : Reg {
        auto selected() { return bit(0); }
    };
    auto periphEnable() { return PeriphEnable {regs() + 4}; }

    struct BaudRate : Reg {
        auto ssiClockDivider() { return bits<u16>(15, 0); }
    };
    auto baudRate() { return BaudRate {regs() + 5}; }

    struct FIFOThreshold : Reg {
        auto thresh() { return bits<u8>(7, 0); }
    };
    auto txFIFOThresh() { return FIFOThreshold {regs() + 6}; }
    auto rxFIFOThresh() { return FIFOThreshold {regs() + 7}; }

    struct FIFOLevel : Reg {
        auto level() { return bits<u8>(7, 0); }
    };
    auto txFIFOLevel() { return FIFOLevel {regs() + 8}; }
    auto rxFIFOLevel() { return FIFOLevel {regs() + 9}; }

    struct Status : Reg {
        auto dataColl() { return bit(6); }
        auto txError() { return bit(5); }
        auto rxFIFOFull() { return bit(4); }
        auto rxFIFONotEmpty() { return bit(3); }
        auto txFIFOEmpty() { return bit(2); }
        auto txFIFONotFull() { return bit(1); }
        auto busy() { return bit(0); }
    };
    auto status() { return Status {regs() + 10}; }

    struct IRQMask : Reg {
        auto contention() { return bit(5); }
        auto rxFIFOFull() { return bit(4); }
        auto rxFIFOOverflow() { return bit(3); }
        auto rxFIFOUnderflow() { return bit(2); }
        auto txFIFOOverflow() { return bit(1); }
        auto txFIFOEmpty() { return bit(0); }
    };
    auto irqMask() { return IRQMask {regs() + 11}; }

    struct IRQStatus : Reg {
        auto contention() { return bit(5); }
        auto rxFIFOFull() { return bit(4); }
        auto rxFIFOOverflow() { return bit(3); }
        auto rxFIFOUnderflow() { return bit(2); }
        auto txFIFOOverflow() { return bit(1); }
        auto txFIFOEmpty() { return bit(0); }
    };
    auto irqStatus() { return IRQStatus {regs() + 12}; }

    struct RawIRQStatus : Reg {
        auto contention() { return bit(5); }
        auto rxFIFOFull() { return bit(4); }
        auto rxFIFOOverflow() { return bit(3); }
        auto rxFIFOUnderflow() { return bit(2); }
        auto txFIFOOverflow() { return bit(1); }
        auto txFIFOEmpty() { return bit(0); }
    };
    auto rawIRQStatus() { return RawIRQStatus {regs() + 13}; }

    struct FIFOIRQClear : Reg {
        auto readToClear() { return bit(0); }
    };
    auto txFIFOOverflowIRQClear() { return FIFOIRQClear {regs() + 14}; }
    auto rxFIFOOverflowIRQClear() { return FIFOIRQClear {regs() + 15}; }
    auto rxFIFOUnderflowIRQClear() { return FIFOIRQClear {regs() + 16}; }
    auto controllerIRQClear() { return FIFOIRQClear {regs() + 17}; }
    auto irqClear() { return FIFOIRQClear {regs() + 18}; }

    struct DMAControl : Reg {
        auto dmaTXEnable() { return bit(1); }
        auto dmaRXEnable() { return bit(0); }
    };
    auto dmaControl() { return DMAControl {regs() + 19}; }

    struct DMADataLevel : Reg {
        auto watermark() { return bits<u8>(7, 0); }
    };
    auto dmaTXDataLevel() { return DMADataLevel {regs() + 20}; }
    auto dmaRXDataLevel() { return DMADataLevel {regs() + 21}; }

    auto ident() { return Reg {regs() + 22}; }
    auto versionID() { return Reg {regs() + 23}; }
    auto data(int d) { return Reg {regs() + 24 + d}; }

    struct RXSampleDelay : Reg {
        auto delayCycles() { return bits<u8>(7, 0); }
    };
    auto rxSampleDelay() { return RXSampleDelay {regs() + 60}; }

    struct SPIControl : Reg {
        auto xipCommand() { return bits<u8>(31, 24); }
        auto spiRXStrobeEnable() { return bit(18); }
        auto insnDDREnable() { return bit(17); }
        auto spiDDREnable() { return bit(16); }
        auto waitCycles() { return bits<u8>(15, 11); }

        enum class InsnLength {
            kNone = 0,
            k4Bit = 1,
            k8Bit = 2,
            k16Bit = 3,
        };
        auto insnLength() { return bits<u8>(9, 8); }

        auto addrLength() { return bits<u8>(5, 2); }

        enum class XferType {
            kStandard = 0,
            kAddrFRF = 1,
            kCmdAddrFRF = 2,
        };
        auto xferType() { return bits<u8>(1, 0); }
    };
    auto spiControl() { return SPIControl {regs() + 61}; }

    struct TXDriveEdge : Reg {
        auto driveEdge() { return bits<u8>(7, 0); }
    };
    auto txDriveEdge() { return TXDriveEdge {regs() + 62}; }
};

extern QSPIPads gQSPIPads;
extern SSI gSSI;
