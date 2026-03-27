#include "world.h"

struct World {
    struct notcurses *nc;
    struct ncplane *stdplane;
    struct ncinput ni;
    struct timespec timeout;

    struct ncplane *debug_p;
};

World* world_init(notcurses_options *opts) {
    World *world = (World*)malloc(sizeof(World));
    if (!world) return NULL;

    world->nc = notcurses_init(opts, NULL);
    if (!world->nc) {
        free(world);
        return NULL;
    }
    world->stdplane = notcurses_stdplane(world->nc);
    world->ni = (struct ncinput){};
    world->timeout = (struct timespec){
        .tv_sec = 0,
        .tv_nsec = 0
    };

    world->debug_p = NULL;

    return world;
}

void world_set_debug_plane(World *world, struct ncplane *debug_p) {
    if (!world) return;
    if (!debug_p) return;

    world->debug_p = debug_p;
}

void world_set_timeout(World *world, uint32_t msec) {
    if (!world) return;
    
    uint32_t sec = 0;

    if (msec > 1000) {
        sec = msec / 1000;
        msec %= 1000;
    }

    world->timeout = (struct timespec){
        .tv_sec = sec,
        .tv_nsec = msec * 1000000
    };
}

uint32_t world_getch(World *world) {
    if (!world) return (uint32_t)-1;
    
    return notcurses_get(world->nc, &world->timeout, &world->ni);
}

uint32_t world_getch_block(World *world) {
    if (!world) return (uint32_t)-1;
    
    return notcurses_get_blocking(world->nc, &world->ni);
}

uint32_t world_getch_nblock(World *world) {
    if (!world) return (uint32_t)-1;
    
    return notcurses_get_nblock(world->nc, &world->ni);
}

struct ncplane* world_get_stdplane(World *world) {
    if (!world) return NULL;
    
    return world->stdplane;
}

// void world_debug_plane_prerender(World *world) {
//     if (!world) return;
//     if (!world->debug_p) return;
//     if (world->ni.id == (uint32_t)-1) return;

//     ncplane_printf_yx(world->debug_p, 0, 0, "Key ID: %u ", world->ni.id);
//     ncplane_printf_yx(world->debug_p, 1, 0, "Ctrl: %s ", (world->ni.modifiers & NCKEY_MOD_CTRL) ? "YES" : "NO");
// }

void world_debug_plane_prerender(World *world, uint32_t key, bool is_ctrl) {
    if (!world) return;
    if (!world->debug_p) return;
    if (key == (uint32_t)-1) return;

    ncplane_erase(world->debug_p);
    ncplane_printf_yx(world->debug_p, 0, 0, "Key ID: %u ", key);
    ncplane_printf_yx(world->debug_p, 1, 0, "Ctrl: %s ", is_ctrl ? "YES" : "NO");
}

void world_render(World *world) {
    if (!world) return;
    
    notcurses_render(world->nc);
}

void world_read_term_size(World *world, uint32_t *rows, uint32_t *cols) {
    if (!world) return;
    
    notcurses_term_dim_yx(world->nc, rows, cols);
}

bool world_what_mod(World *world, uint8_t mod) {
    if (!world) return false;
    
    return (world->ni.modifiers & mod);
}

void world_destroy(World *world) {
    if (!world) return;
    
    notcurses_stop(world->nc);
    free(world);
}