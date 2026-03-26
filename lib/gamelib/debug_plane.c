#include "debug_plane.h"

void read_input(struct DebugPlane *debug_p, ncinput *ni);
const DebugPacket* get_packet(struct DebugPlane *debug_p);

struct DebugPlane {
    struct ncplane *plane;
    uint16_t cols, rows;
    uint16_t x, y;
    char *name;
    DebugPacket packet;

    void (*read_input)(struct DebugPlane *debug_p, ncinput *ni);
    const DebugPacket* (*get_packet)(struct DebugPlane *debug_p);
};

DebugPlane* debug_panel_init(struct DebugOptions *opts, struct ncplane *stdplane) {
    DebugPlane *debug_p = (DebugPlane*)malloc(sizeof(DebugPlane));
    if (debug_p) {
        debug_p->cols = opts->cols;
        debug_p->rows = opts->rows;
        debug_p->x = opts->x;
        debug_p->y = opts->y;
        debug_p->name = opts->name;
        
        debug_p->packet.is_ctrl = false;
        debug_p->packet.key = (uint32_t)-1;

        debug_p->read_input = read_input;
        debug_p->get_packet = get_packet;


        struct ncplane_options p_opt = {
            .cols = debug_p->cols,
            .rows = debug_p->rows,
            .x = debug_p->x,
            .y = debug_p->y,
            .name = debug_p->name
        };
    
        debug_p->plane = ncplane_create(stdplane, &p_opt);
    }
    return debug_p;
}

void read_input(struct DebugPlane *debug_p, ncinput *ni) {
    debug_p->packet.key = ni->id;
    debug_p->packet.is_ctrl = ni->ctrl;
}

const DebugPacket* get_packet(struct DebugPlane *debug_p) {
    return &debug_p->packet;
}