#include "Boot.h"

namespace sys {

[[gnu::section(".boot2")]]
void boot2() {
    // Adapted from Pico SDK code, specifically the boot2 for W25Q080 flash
    // (like on the Pico board).  Logic and comments taken from:
    // https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2040/boot_stage2/boot2_w25q080.S

    // Set pad configuration:
    // - SCLK 8mA drive, no slew limiting
    // - SDx disable input Schmitt to reduce delay
    qspiPads.clkControl().drive() = QSPIPads::PadControl::Drive::k8mA;
    qspiPads.clkControl().slewFast() = true;
    qspiPads.padControl0().schmitt() = false;
    qspiPads.padControl1().schmitt() = false;
    qspiPads.padControl2().schmitt() = false;
    qspiPads.padControl3().schmitt() = false;

    // Disable SSI to allow further config
    ssi.ssiEnable().enable() = false;

    // Set baud rate (PICO_FLASH_SPI_CLKDIV == 2)
    ssi.baudRate().ssiClockDivider() = 2;

    // Set 1-cycle sample delay (see original for full explanation)
    ssi.rxSampleDelay().delayCycles() = 1;

    // On QSPI parts we usually need a 01h SR-write command to enable QSPI mode
    // (i.e. turn WPn and HOLDn into IO2/IO3)
    ssi.control0().frameSize() = 7;  // 8 bits per data frame
    ssi.control0().xferMode() = SSI::Control0::XferMode::kTXRX;

    // Enable SSI (also says "and select slave 0" ... ?)
    ssi.ssiEnable().enable() = true;

    // Check whether SR needs updating

    start();
    __builtin_unreachable();  // `start` doesn't return
}

}  // namespace sys
