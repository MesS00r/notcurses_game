#ifndef DEBUG_PLANE_H_INCLUDED
#define DEBUG_PLANE_H_INCLUDED

#include <notcurses/notcurses.h>

typedef struct DebugPlane DebugPlane;

typedef struct DebugPacket {
    uint32_t key;
    bool is_ctrl;
} DebugPacket;

typedef struct DebugOptions {
    uint16_t rows, cols;
    uint16_t x, y;
    char *name;
} DebugOptions;

DebugPlane* debug_panel_init(struct DebugOptions *opts, struct ncplane *stdplane);

#endif //DEBUG_PLANE_H_INCLUDED