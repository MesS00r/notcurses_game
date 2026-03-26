#include "world.h"

struct World {
    struct ncplane *stdplane;
    struct notcurses *nc;
};

World* world_init(notcurses_options *opts) {
    World *world = (World*)malloc(sizeof(World));
    if (world) {
        world->nc = notcurses_init(opts, NULL);
        world->stdplane = notcurses_stdplane(world->nc);
    }
    return world;
}

void debug_plane_render(struct World *world) {
    
}