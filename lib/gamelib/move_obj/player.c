#include "player.h"

struct Player {
    struct ncplane *plane;

    uint16_t cols, rows;
    uint16_t x, y;
    const char *name;

    const char *playerstr;

    uint64_t channels;
    uint32_t style;

    PlayerPacket packet;
};

Player* player_init(PlayerOptions *opts, struct ncplane *parent_plane) {
    Player *player = (Player*)malloc(sizeof(Player));
    if (!player) return NULL;

    PlayerOptions default_opts = PLAYER_OPTS_DEFAULT;
    if (!opts) opts = &default_opts;
    
    if (opts->name == NULL) opts->name = "none";
    if (opts->bg_char == NULL) opts->bg_char = " ";

    player->cols = 3;
    player->rows = 3;
    player->x = opts->x;
    player->y = opts->y;
    player->name = opts->name;

    player->playerstr = (const char*){
        " 0 "
        "/|\\"
        "/ \\"
    };

    player->style = opts->style;

    struct ncplane_options p_opts = {
        .cols = player->cols,
        .rows = player->rows,
        .x = player->x,
        .y = player->y,
        .name = player->name
    };
    player->plane = ncplane_create(parent_plane, &p_opts);
    if (!player->plane) {
        free(player);
        return NULL;
    }

    player->channels = 0;
    ncchannels_set_bg_rgb(&player->channels, opts->bg_rgb);
    ncchannels_set_fg_rgb(&player->channels, opts->fg_rgb);
    ncplane_set_base(player->plane, opts->bg_char, 0, player->channels);
    ncplane_set_styles(player->plane, player->style);

    player->packet.plane = NULL;
    player->packet.playerstr = NULL;

    return player;
}

PlayerPacket* player_get_packet(Player* player) {
    if (!player) return NULL;

    player->packet.plane = player->plane;
    player->packet.playerstr = player->playerstr;
    return &player->packet;
}

// void player_move(World *world) {
//     switch (world->key) {
//     case 'w': case 'W': break;
//     case 's': case 'S': break;
//     case 'a': case 'A': break;
//     case 'd': case 'D': break;
//     }
// }

void player_destroy(Player* player) {
    if (!player) return;

    free(player);
}