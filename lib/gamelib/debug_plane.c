#include "debug_plane.h"

struct DebugPlane {
    struct ncplane *plane;

    uint16_t cols, rows;
    uint16_t x, y;
    const char *name;

    uint64_t channels;
    uint32_t style;
    const char *bg_char;
};

DebugPlane* debug_plane_init(DebugOptions *opts, struct ncplane *stdplane) {
    DebugPlane *debug_p = (DebugPlane*)malloc(sizeof(DebugPlane));
    if (!debug_p) return NULL;

    DebugOptions default_opts = DEBUG_OPTS_DEFAULT;
    if (!opts) opts = &default_opts;
    
    if (opts->cols == 0) opts->cols = 1;
    if (opts->rows == 0) opts->rows = 1;
    if (opts->name == NULL) opts->name = "none";
    if (opts->bg_char == NULL) opts->bg_char = " ";

    debug_p->cols = opts->cols;
    debug_p->rows = opts->rows;
    debug_p->x = opts->x;
    debug_p->y = opts->y;
    debug_p->name = opts->name;

    debug_p->style = opts->style;
    debug_p->bg_char = opts->bg_char;

    struct ncplane_options p_opts = {
        .cols = debug_p->cols,
        .rows = debug_p->rows,
        .x = debug_p->x,
        .y = debug_p->y,
        .name = debug_p->name
    };
    debug_p->plane = ncplane_create(stdplane, &p_opts);
    if (!debug_p->plane) {
        free(debug_p);
        return NULL;
    }

    debug_p->channels = 0;
    ncchannels_set_bg_rgb(&debug_p->channels, opts->bg_rgb);
    ncchannels_set_fg_rgb(&debug_p->channels, opts->fg_rgb);
    ncplane_set_base(debug_p->plane, debug_p->bg_char, 0, debug_p->channels);
    ncplane_set_styles(debug_p->plane, debug_p->style);

    return debug_p;
}

struct ncplane* debug_plane_get_plane(DebugPlane* debug_p) {
    if (!debug_p) return NULL;
    return debug_p->plane;
}

void debug_plane_destroy(DebugPlane* debug_p) {
    if (!debug_p) return;

    free(debug_p);
}