#include "N64.h"

#ifndef NATIVE
u8* HEADER;
u8 *DMEM;
u8 *IMEM;
#endif
u64 TMEM[512];
#ifndef NATIVE
u8 *RDRAM;
#endif

//word RDRAMSize = 0;
word RDRAMSize = 0x7FFFFF; //@Note: mrneo240

N64Regs REG;

bool ConfigOpen = false;
