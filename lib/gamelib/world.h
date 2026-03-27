#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <notcurses/notcurses.h>
#include <gamelib/debug_plane.h>

typedef struct World World;

World* world_init(notcurses_options *opts);

void world_set_debug_plane(World *world, struct ncplane *debug_p);
void world_set_timeout(World *world, uint32_t msec);

uint32_t world_getch(World *world);
uint32_t world_getch_block(World *world);
uint32_t world_getch_nblock(World *world);
struct ncplane* world_get_stdplane(World *world);

// void world_debug_plane_prerender(World *world);
void world_debug_plane_prerender(World *world, uint32_t key, bool is_ctrl);
void world_render(World *world);

void world_read_term_size(World *world, uint32_t *rows, uint32_t *cols);
bool world_what_mod(World *world, uint8_t mod);

void world_destroy(World *world);

#endif  //WORLD_H_INCLUDED