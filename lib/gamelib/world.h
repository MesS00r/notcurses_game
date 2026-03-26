#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <notcurses/notcurses.h>
#include <gamelib/debug_plane.h>

typedef struct World World;

World* world_init(notcurses_options *opts);

#endif  //WORLD_H_INCLUDED