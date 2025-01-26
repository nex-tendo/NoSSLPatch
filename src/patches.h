#pragma once

typedef struct Patch {
    int addr;
    char url;
} Patch;

const Patch patches[] = {
    {0xE31930D4, "https://%s%saccount.nintendo.net/v%u/api/"}
}
