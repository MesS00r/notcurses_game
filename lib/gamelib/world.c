#include "world.h"

// -----------------------------------------------------------------------
// СТРУКТУРА WORLD
// -----------------------------------------------------------------------

struct World {
    struct notcurses *nc;
    struct ncplane   *stdplane;
    struct ncinput   ni;
    struct timespec  timeout;

    chtype_32 key;
    uint32_t  modifiers;

    DebugPlane     *debug_p;
    struct ncplane *debug_true_plane;

    Player       *player;
    PlayerPacket *player_packet;
};

// -----------------------------------------------------------------------
// ИНИЦИЛИЗАТОР WORLD
// -----------------------------------------------------------------------

World* world_init(notcurses_options *opts) {
    World *world = calloc(
        1, 
        sizeof(World)
    );
    if (!world) return NULL;

    world->nc = notcurses_init(
        opts, 
        NULL
    );
    if (!world->nc) {
        free(world);
        return NULL;
    }
    world->stdplane = notcurses_stdplane(world->nc);
    world->ni       = (struct ncinput){};
    world->timeout  = (struct timespec){
        .tv_sec = 0,
        .tv_nsec = 0
    };

    world->key       = 0;
    world->modifiers = 0;

    world->debug_p          = NULL;
    world->debug_true_plane = NULL;

    return world;
}

// -----------------------------------------------------------------------
// СЕТТЕРЫ WORLD
// -----------------------------------------------------------------------

void world_set_debug_plane(World *world, DebugPlane *debug_p) {
    if (!world) return;
    if (!debug_p) return;

    world->debug_p = debug_p;
    world->debug_true_plane = debug_plane_get_plane(debug_p);
}

void world_set_player(World *world, Player* player) {
    if (!world) return;
    if (!player) return;

    world->player = player;
    world->player_packet = player_get_packet(player);
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

// -----------------------------------------------------------------------
// ГЕТТЕРЫ WORLD
// -----------------------------------------------------------------------

chtype_32 world_getch(World *world) {
    if (!world) return CH_ERR_CODE;
    
    world->key = notcurses_get(
        world->nc, 
        &world->timeout, 
        &world->ni
    );
    world->modifiers = world->ni.modifiers;
    return world->key;
}

chtype_32 world_getch_block(World *world) {
    if (!world) return CH_ERR_CODE;
    
    world->key = notcurses_get_blocking(
        world->nc, 
        &world->ni
    );
    world->modifiers = world->ni.modifiers;
    return world->key;
}

chtype_32 world_getch_nblock(World *world) {
    if (!world) return CH_ERR_CODE;
    
    world->key = notcurses_get_nblock(
        world->nc, 
        &world->ni
    );
    world->modifiers = world->ni.modifiers;
    return world->key;
}

struct ncplane* world_get_stdplane(World *world) {
    if (!world) return NULL;
    
    return world->stdplane;
}

// -----------------------------------------------------------------------
// МЕТОДЫ ОТРИСОВКИ WORLD
// -----------------------------------------------------------------------

void world_debug_plane_prerender(World *world) {
    if (!world) return;
    if (!world->debug_p) return;

    struct ncplane *plane = world->debug_true_plane;

    chtype_32 key = 0;

    bool is_ctrl      = false;
    bool is_alt       = false;
    bool is_shift     = false;
    bool is_super     = false;
    bool is_caps_lock = false;
    bool is_num_lock  = false;

    if (world->key > 0) {
        key = world->key;

        is_ctrl      = world->modifiers & NCKEY_MOD_CTRL;
        is_alt       = world->modifiers & NCKEY_MOD_ALT;
        is_shift     = world->modifiers & NCKEY_MOD_SHIFT;
        is_super     = world->modifiers & NCKEY_MOD_SUPER;
        is_caps_lock = world->modifiers & NCKEY_MOD_CAPSLOCK;
        is_num_lock  = world->modifiers & NCKEY_MOD_NUMLOCK;
    }

    if (key == 0) return;
    ncplane_erase(plane);

    ncplane_printf_yx(plane, 0, 0, "Key ID: %c:%u ", key, key);

    ncplane_printf_yx(plane, 1, 0, "Ctrl:  %s ", is_ctrl  ? "YES" : "NO");
    ncplane_printf_yx(plane, 2, 0, "Alt:   %s ", is_alt   ? "YES" : "NO");
    ncplane_printf_yx(plane, 3, 0, "Shift: %s ", is_shift ? "YES" : "NO");
    ncplane_printf_yx(plane, 4, 0, "Super: %s ", is_super ? "YES" : "NO");

    ncplane_printf_yx(plane, 5, 0, "CapsLock: %s ", is_caps_lock ? "YES" : "NO");
    ncplane_printf_yx(plane, 6, 0, "NumLock:  %s ", is_num_lock  ? "YES" : "NO");
}

void world_player_prerender(World *world) {
    if (!world) return;
    if (!world->player) return;

    struct ncplane *plane = world->player_packet->plane;
    const char *playerstr = world->player_packet->playerstr;

    uint8_t cols = 3;

    for (uint8_t i = 0; i < 9; i++) {
        uint8_t y = i / cols;
        uint8_t x = i % cols;

        if (playerstr[i] == ' ') continue;
        ncplane_putchar_yx(
            plane, 
            y, x, 
            playerstr[i]
        );
    }
}

void world_render(World *world) {
    if (!world) return;
    
    notcurses_render(world->nc);
}

// -----------------------------------------------------------------------
// ДРУГИЕ МЕТОДЫ WORLD
// -----------------------------------------------------------------------

void world_read_term_size(World *world, uint32_t *rows, uint32_t *cols) {
    if (!world) return;
    
    notcurses_term_dim_yx(
        world->nc, 
        rows, cols
    );
}

bool world_what_mod(World *world, uint8_t mod) {
    if (!world) return false;
    
    bool spec_key = false;

    spec_key = world->modifiers & mod;
    return spec_key;
}

// -----------------------------------------------------------------------
// ДЕКОНСТРУКТОР WORLD
// -----------------------------------------------------------------------

void world_destroy(World *world) {
    if (!world) return;
    
    notcurses_stop(world->nc);
    debug_plane_destroy(world->debug_p);
    player_destroy(world->player);
    free(world);
}