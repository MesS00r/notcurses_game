#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <notcurses/notcurses.h>
#include <gamelib/debug_plane.h>
#include <gamelib/move_obj/player.h>
#include <gamelib/common.h>

// -----------------------------------------------------------------------
// СТРУКТУРА WORLD
// -----------------------------------------------------------------------

typedef struct World World;

// -----------------------------------------------------------------------
// ИНИЦИЛИЗАТОР WORLD
// -----------------------------------------------------------------------

/**
 * @brief Инициализация структуры World.
 * @param opts Настройки World и notcurses (notcurses_options).
 * @return Указатель на структуру World с заданными параметрами.
 * @note При ошибке возвращает NULL.
 * @warning Если в opts передать NULL, то настройки будут стандартными для notcurses.
 * @warning Если opts будут не инициализированы, то поведенние не определено.
 */
World* world_init(notcurses_options *opts);

// -----------------------------------------------------------------------
// СЕТТЕРЫ WORLD
// -----------------------------------------------------------------------

// Machina Mori

/**
 * @name Сеттеры World.
 * @brief Устанавливают значение определенному полю или полям.
 * @{
 */

/** 
 * @brief Устанавливает значение полям debug_p (DebugPlane) и debug_true_plane (ncplane).
 * @param world Указатель на структуру World.
 * @param debug_p Указатель на структуру DebugPlane.
 */
void world_set_debug_plane(World *world, DebugPlane *debug_p);

/** 
 * @brief Устанавливает значение полям player (Player) и player_packet (PlayerPacket).
 * @param world Указатель на структуру World.
 * @param player Указатель на структуру Player.
 */
void world_set_player(World *world, Player* player);

/** 
 * @brief Устанавливает значение полю timeout (struct timespec).
 * @param world Указатель на структуру World.
 * @param msec Время в миллисекундах.
 */
void world_set_timeout(World *world, uint32_t msec);
/** @} */

// -----------------------------------------------------------------------
// GETCH WORLD
// -----------------------------------------------------------------------

/** 
 * @name Методы получения ввода (getch).
 * @brief Улавливают пользовательский ввод.
 * @note При ошибке возвращают CH_ERR_CODE ((uint32_t)-1).
 * @note При отсутствии нажатия возвращают 0 (Это допустимое значение).
 * @{
 */

 /** 
 * @brief Улавливает ввод с timeout, если timeout выйдет вернет 0 (зависит от настроек).
 * @param world Указатель на структуру World.
 * @return Индекс нажатой клавиши (chtype_32 -> uint32_t).
 */
chtype_32 world_getch(World *world);

 /** 
 * @brief Улавливает ввод с блокировкой (ждет пока не произойдет нажатие).
 * @param world Указатель на структуру World.
 * @return Индекс нажатой клавиши (chtype_32 -> uint32_t).
 */
chtype_32 world_getch_block(World *world);

 /** 
 * @brief Улавливает ввод без блокировки (если нажатие не произошло вернет 0).
 * @param world Указатель на структуру World.
 * @return Индекс нажатой клавиши (chtype_32 -> uint32_t).
 */
chtype_32 world_getch_nblock(World *world);
/** @} */

// -----------------------------------------------------------------------
// ГЕТТЕР WORLD
// -----------------------------------------------------------------------

/**
 * @brief Получение доступа к полю stdplane (ncplane).
 * @param world Указатель на структуру World.
 * @return Указатель на поле stdplane (ncplane).
 * @note При ошибке возвращает NULL.
 */
struct ncplane* world_get_stdplane(World *world);

// -----------------------------------------------------------------------
// МЕТОДЫ ОТРИСОВКИ WORLD
// -----------------------------------------------------------------------

/**
 * @name Методы отрисовки.
 * @brief Отрисовывают объекты в терминале.
 * @{
 */

/**
 * @brief Отрисовывание debug plane в плоскости debug_true_plane (ncplane).
 * @param world Указатель на структуру World.
 */
void world_debug_plane_prerender(World *world);

/**
 * @brief Отрисовывание player в плоскости player_packet -> plane (ncplane).
 * @param world Указатель на структуру World.
 */
void world_player_prerender(World *world);

/**
 * @brief Проявление отрисованных объектов.
 * @param world Указатель на структуру World.
 */
void world_render(World *world);
/** @} */

// -----------------------------------------------------------------------
// ДРУГИЕ МЕТОДЫ WORLD
// -----------------------------------------------------------------------

/**
 * @brief Получение размеров терминала.
 * @param world Указатель на структуру World.
 * @param rows Ряды (высота) терминала (изменяется).
 * @param cols Столбцы (ширина) терминала (изменяется).
 */
void world_read_term_size(World *world, uint32_t *rows, uint32_t *cols);

/**
 * @brief Получение состояний специальных клавиш.
 * @param world Указатель на структуру World.
 * @param mod Bitmask Специальных клавиш.
 * @return Состояние специальной клавиши (true - активна false - не активна).
 */
bool world_what_mod(World *world, uint8_t mod);

// -----------------------------------------------------------------------
// ДЕКОНСТРУКТОР WORLD
// -----------------------------------------------------------------------

/**
 * @brief Удаление структуры World (и всех дочерних структур) и очистка памяти.
 * @param world Указатель на структуру World.
 */
void world_destroy(World *world);

#endif  //WORLD_H_INCLUDED