#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <notcurses/notcurses.h>

#define PLAYER_OPTS_DEFAULT (PlayerOptions){ \
    .x = 0, .y = 0,                          \
    .name = "player",                        \
                                             \
    .bg_rgb = 0x000000, .fg_rgb = 0xff7f00,  \
    .style = 0, .bg_char = " "               \
}

typedef struct Player Player;

typedef struct PlayerOptions {
    uint16_t x, y;
    const char *name;

    uint32_t bg_rgb;
    uint32_t fg_rgb;
    uint32_t style;
    const char *bg_char;
} PlayerOptions;

typedef struct PlayerPacket {
    struct ncplane *plane;
    const char *playerstr;
} PlayerPacket;

Player* player_init(PlayerOptions *opts, struct ncplane *parent_plane);

PlayerPacket* player_get_packet(Player* player);

void player_destroy(Player* player);

#endif  //PLAYER_H_INCLUDED