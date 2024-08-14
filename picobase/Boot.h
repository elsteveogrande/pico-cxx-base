#pragma once
#include "QSPI.h"

extern QSPIPads qspiPads;
extern SSI ssi;

namespace sys {
void start();
void boot2();
}  // namespace sys
