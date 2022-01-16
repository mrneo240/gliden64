#include "PluginAPI.h"
#include "N64.h"
#include "RSP.h"
#include "Native.h"
#include "GLideNUI-wtl/GLideNUI.h"
#include "GLideN64.h"
#include "Config.h"
#include "DebugDump.h"
#include "Config.h"
#include "DisplayWindow.h"
#include <wchar.h>

#define START_WIDTH 1280
#define START_HEIGHT 720

static u64 g_width = START_WIDTH;
static u64 g_height = START_HEIGHT;

extern "C" {
    u64 gfx_width()
    {
        return g_width;
    }

    u64 gfx_height()
    {
        return g_height;
    }
}

#ifdef WTL_UI
void ConfigInit(void* hinst);
void ConfigCleanup(void);
#endif

N64Regs::N64Regs() {
MI_INTR = new u32;
DPC_START = new word;
DPC_END = new word;
DPC_CURRENT = new word;
DPC_STATUS = new word;
DPC_CLOCK = new u32;
DPC_BUFBUSY = new u32;
DPC_PIPEBUSY = new u32;
DPC_TMEM = new u32;
VI_STATUS = new u32;
VI_ORIGIN = new u32;
VI_WIDTH = new u32;
VI_INTR = new u32;
VI_V_CURRENT_LINE = new u32;
VI_TIMING = new u32;
VI_V_SYNC = new u32;
VI_H_SYNC = new u32;
VI_LEAP = new u32;
VI_H_START = new u32;
VI_V_START = new u32;
VI_V_BURST = new u32;
VI_X_SCALE = new u32;
VI_Y_SCALE = new u32;
SP_STATUS = new u32;

*MI_INTR = 0;
*DPC_START = 0;
*DPC_END = 0;
*DPC_CURRENT = 0;
*DPC_STATUS = 0;
*DPC_CLOCK = 0;
*DPC_BUFBUSY = 0;
*DPC_PIPEBUSY = 0;
*DPC_TMEM = 0;
*VI_STATUS = 0;
*VI_ORIGIN = 0;
*VI_WIDTH = 320;
*VI_INTR = 0;
*VI_V_CURRENT_LINE = 0;
*VI_TIMING = 0;
*VI_V_SYNC = 0;
*VI_H_SYNC = 0;
*VI_LEAP = 0;
*VI_H_START = 0;
*VI_V_START = 0;
*VI_V_BURST = 0;
*VI_X_SCALE = 1024;
*VI_Y_SCALE = 512;
*SP_STATUS = 0;
}

N64Regs::~N64Regs() {
}

extern "C"
{
    void gfx_resize(long width, long height)
    {
        g_width = width;
        g_height = height;
        config.video.windowedWidth = g_width;
        config.video.windowedHeight = g_height;
        dwnd().setWindowSize(g_width, g_height);
        (*REG.VI_ORIGIN)++;
    }
}

void _CheckInterrupts() {
}



extern "C" {
    void gfx_init(const char* romName, OSViMode* viMode) {
        REG.VI_STATUS = &viMode->comRegs.ctrl;
        REG.VI_WIDTH = &viMode->comRegs.width;
        REG.VI_TIMING = &viMode->comRegs.burst;
        REG.VI_V_SYNC = &viMode->comRegs.vSync;
        REG.VI_H_SYNC = &viMode->comRegs.hSync;
        REG.VI_LEAP = &viMode->comRegs.leap;
        REG.VI_H_START = &viMode->comRegs.hStart;
        REG.VI_X_SCALE = &viMode->comRegs.xScale;
        REG.VI_V_CURRENT_LINE = &viMode->comRegs.vCurrent;

        REG.VI_ORIGIN = &viMode->fldRegs->origin;
        REG.VI_Y_SCALE = &viMode->fldRegs->yScale;
        REG.VI_V_START = &viMode->fldRegs->vStart;
        REG.VI_V_BURST = &viMode->fldRegs->vBurst;
        REG.VI_INTR = &viMode->fldRegs->vIntr;

        CheckInterrupts = _CheckInterrupts;

        //StartDump(DEBUG_LOW | DEBUG_NORMAL | DEBUG_DETAIL | DEBUG_IGNORED | DEBUG_ERROR);

        REG.VI_STATUS;
        RDRAMSize = (word)-1;

        api().RomOpen(romName);

        config.frameBufferEmulation.enable = 0;
        config.frameBufferEmulation.aspect = Config::aAdjust;
        
    }

    void gfx_shutdown() {
        RDRAMSize = 0;
        api().RomClosed();
    }

    void gfx_run(OSTask_t* task, u32 sz) {
        if(sizeof(OSTask_t) != sz)
        {
            return;
        }
        RSP_ProcessDList(task->data_ptr, task->data_size, task->ucode_boot, task->ucode_data, task->ucode_size);
        api().UpdateScreen();
        //Sleep(30);
    }
}