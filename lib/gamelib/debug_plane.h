#ifndef DEBUG_PLANE_H_INCLUDED
#define DEBUG_PLANE_H_INCLUDED

#include <notcurses/notcurses.h>

// -----------------------------------------------------------------------
// СТРУКТУРА DEBUG PLANE
// -----------------------------------------------------------------------

#define DEBUG_OPTS_DEFAULT (DebugOptions){  \
    .cols = 1, .rows = 1,                   \
    .x = 0, .y = 0,                         \
    .name = "debug",                        \
                                            \
    .bg_rgb = 0xffffff, .fg_rgb = 0x000000, \
    .style = 0, .bg_char = " "              \
}

typedef struct DebugPlane DebugPlane;

typedef struct DebugOptions {
    uint16_t   cols, rows;
    uint16_t   x, y;
    const char *name;

    uint32_t   bg_rgb;
    uint32_t   fg_rgb;
    uint32_t   style;
    const char *bg_char;
} DebugOptions;

// -----------------------------------------------------------------------
// ИНИЦИЛИЗАТОР DEBUG PLANE
// -----------------------------------------------------------------------

/**
 * @brief Инициализация структуры DebugPlane.
 * @param opts Настройки DebugPlane (DebugOptions).
 * @param parent_plane Родительская плоскость.
 * @return Указатель на структуру DebugPlane с заданными параметрами.
 * @note При ошибке возвращает NULL.
 * @warning Если в opts передать NULL, то настройки будут стандартными (DEBUG_OPTS_DEFAULT).
 * @warning Если opts будут не инициализированы, то поведенние не определено.
 */
DebugPlane* debug_plane_init(DebugOptions *opts, struct ncplane *parent_plane);

// -----------------------------------------------------------------------
// ГЕТТЕР DEBUG PLANE
// -----------------------------------------------------------------------

/**
 * @brief Получение доступа к полю plane (ncplane).
 * @param debug_p Указатель на структуру DebugPlane.
 * @return Указатель на поле plane (ncplane).
 * @note При ошибке возвращает NULL.
 */
struct ncplane* debug_plane_get_plane(DebugPlane* debug_p);

// -----------------------------------------------------------------------
// ДЕКОНСТРУКТОР DEBUG PLANE
// -----------------------------------------------------------------------

/**
 * @brief Удаление структуры DebugPlane и очистка памяти.
 * @param debug_p Указатель на структуру DebugPlane.
 * @warning Этот метод не нужно вызывать отдельно, он вызывается автоматически в world_destroy.
 */
void debug_plane_destroy(DebugPlane* debug_p);

#endif //DEBUG_PLANE_H_INCLUDED