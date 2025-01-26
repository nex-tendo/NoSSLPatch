#pragma once

#include "common.h"
#include "patches.h"
#include <kernel/kernel.h>
#include <vpad/input.h>
#include <mocha/mocha.h>
#include <coreinit/mcp.h>

bool is555Version(MCPSystemVersion version) {
    return version.major == 5 && version.minor == 5 && version.patch >= 5;
}

// credits @Gary#4139
static void write_string(uint32_t addr, const char* str)
{
    int len = strlen(str) + 1;
    int remaining = len % 4;
    int num = len - remaining;

    for (int i = 0; i < (num / 4); i++) {
        IOSUHAX_kern_write32(addr + i * 4, *(uint32_t*)(str + i * 4));
    }

    if (remaining > 0) {
        uint8_t buf[4];
        IOSUHAX_kern_read32(addr + num, (uint32_t*)&buf, 1);

        for (int i = 0; i < remaining; i++) {
            buf[i] = *(str + num + i);
        }

        IOSUHAX_kern_write32(addr + num, *(uint32_t*)&buf);
    }
}

int main(int argc, char** argv) {
    VPADStatus vpad_data;
    int vpadError;

    while (1) {
        VPADRead(0, &vpad_data, 1, &vpadError);
        if (vpadError == 0 && (vpad_data.hold & VPAD_BUTTON_A)) {
            MCPSystemVersion version;
            int mcp_handle = MCP_Open();
            MCP_GetSystemVersion(mcp_handle, &version);
            if (is555Version(version)) {
                Mocha_IOSUKernelWrite32(0xE1019F78, 0xE3A00001);
                printf("NoSSL Patch Patched Successfully! (Version 5.5.5 or more).\n");
            } else {
                Mocha_IOSUKernelWrite32(0xE1019E84, 0xE3A00001);
                printf("NoSSL Patch Patched Successfully! (Version under 5.5.5).\n");
            }
            for (int i = 0; i < sizeof(patches) / sizeof(Patch); i++) {
                write_string(patches[i].address, patches[i].url);
            }
            MCP_Close(mcp_handle);
        }
    }

    OSSleepTicks(OSSecondsToTicks(3));

    return RETURN_TO_HBL;
}
