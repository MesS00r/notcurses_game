#ifndef DEBUG_PLANE_H_INCLUDED
#define DEBUG_PLANE_H_INCLUDED

#include <notcurses/notcurses.h>

#define DEBUG_OPTS_DEFAULT (DebugOptions){  \
    .cols = 1, .rows = 1,                   \
    .x = 0, .y = 0,                         \
    .name = "debug",                        \
                                            \
    .bg_rgb = 0xffffff, .fg_rgb = 0x000000, \
    .style = 0, .bg_char = " "              \
}

typedef struct DebugPlane DebugPlane;

typedef struct DebugOptions {
    uint16_t cols, rows;
    uint16_t x, y;
    const char *name;

    uint32_t bg_rgb;
    uint32_t fg_rgb;
    uint32_t style;
    const char *bg_char;
} DebugOptions;

DebugPlane* debug_plane_init(DebugOptions *opts, struct ncplane *parent_plane);

struct ncplane* debug_plane_get_plane(DebugPlane* debug_p);

void debug_plane_destroy(DebugPlane* debug_p);

#endif //DEBUG_PLANE_H_INCLUDED