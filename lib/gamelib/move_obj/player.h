#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <notcurses/notcurses.h>

// -----------------------------------------------------------------------
// СТРУКТУРА PLAYER
// -----------------------------------------------------------------------

#define PLAYER_OPTS_DEFAULT (PlayerOptions){ \
    .x = 0, .y = 0,                          \
    .name = "player",                        \
                                             \
    .bg_rgb = 0x000000, .fg_rgb = 0xff7f00,  \
    .style = 0, .bg_char = " "               \
}

typedef struct Player Player;

typedef struct PlayerOptions {
    uint16_t   x, y;
    const char *name;

    uint32_t   bg_rgb;
    uint32_t   fg_rgb;
    uint32_t   style;
    const char *bg_char;
} PlayerOptions;

typedef struct PlayerPacket {
    struct ncplane *plane;
    const char     *playerstr;
} PlayerPacket;

// -----------------------------------------------------------------------
// ИНИЦИЛИЗАТОР PLAYER
// -----------------------------------------------------------------------

/**
 * @brief Инициализация структуры Player.
 * @param opts Настройки Player (PlayerOptions).
 * @param parent_plane Родительская плоскость.
 * @return Указатель на структуру Player с заданными параметрами.
 * @note При ошибке возвращает NULL.
 * @warning Если в opts передать NULL, то настройки будут стандартными (PLAYER_OPTS_DEFAULT).
 * @warning Если opts будут не инициализированы, то поведенние не определено.
 */
Player* player_init(PlayerOptions *opts, struct ncplane *parent_plane);

// -----------------------------------------------------------------------
// ГЕТТЕР PLAYER
// -----------------------------------------------------------------------

/**
 * @brief Получение доступа к полю packet (PlayerPacket).
 * @param player Указатель на структуру Player.
 * @return Указатель на поле packet (PlayerPacket).
 * @note При ошибке возвращает NULL.
 */
PlayerPacket* player_get_packet(Player* player);

// -----------------------------------------------------------------------
// ...
// -----------------------------------------------------------------------

// TODO: Player movement.
// void player_move(World *world);

// -----------------------------------------------------------------------
// ДЕКОНСТРУКТОР PLAYER
// -----------------------------------------------------------------------

/**
 * @brief Удаление структуры Player и очистка памяти.
 * @param player Указатель на структуру Player.
 * @warning Этот метод не нужно вызывать отдельно, он вызывается автоматически в world_destroy.
 */
void player_destroy(Player* player);

#endif  //PLAYER_H_INCLUDED