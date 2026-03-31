#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

// -----------------------------------------------------------------------
// COMMON
// -----------------------------------------------------------------------

#define CH_ERR_CODE (uint32_t)-1;

typedef uint32_t chtype_32;

// -----------------------------------------------------------------------
// СТРУКТУРА TVEC (TEXT VECTOR)
// -----------------------------------------------------------------------

typedef struct TVec {
    uint16_t x, y;
} TVec;

/**
 * @brief Создание вектора.
 * @param x Первая координата.
 * @param y Вторая координата.
 * @return Новый вектор с координатами {x, y}.
 */
static inline TVec v_create(uint16_t x, uint16_t y) {
    return (TVec){x, y};
}

/**
 * @brief Создание вектора с нулевыми координатами.
 * @return Новый вектор с координатами {0, 0}.
 */
static inline TVec v_zero() {
    return (TVec){0, 0};
}

// -----------------------------------------------------------------------
// ПРОСТЫЕ ОПЕРАТОРЫ
// -----------------------------------------------------------------------

/**
 * @brief Сложение двух векторов.
 * @param first Первый вектор.
 * @param second Второй вектор.
 * @return Результирующий вектор (first + second).
 */
static inline TVec v_addv(TVec first, TVec second) {
    TVec result = {
        first.x + second.x,
        first.y + second.y
    };
    return result;
}

/**
 * @brief Сложение вектора и числа.
 * @param first Вектор.
 * @param num Число.
 * @return Результирующий вектор (first + num).
 */
static inline TVec v_addn(TVec first, uint16_t num) {
    TVec result = {
        first.x + num,
        first.y + num
    };
    return result;
}

/**
 * @brief Вычитание двух векторов.
 * @param first Первый вектор.
 * @param second Второй вектор.
 * @return Результирующий вектор (first - second).
 */
static inline TVec v_subv(TVec first, TVec second) {
    TVec result = {
        first.x - second.x,
        first.y - second.y
    };
    return result;
}

/**
 * @brief Вычитание вектора и числа.
 * @param first Вектор.
 * @param num Число.
 * @return Результирующий вектор (first - num).
 */
static inline TVec v_subn(TVec first, uint16_t num) {
    TVec result = {
        first.x - num,
        first.y - num
    };
    return result;
}

/**
 * @brief Умножение двух векторов.
 * @param first Первый вектор.
 * @param second Второй вектор.
 * @return Результирующий вектор (first * second).
 */
static inline TVec v_mulv(TVec first, TVec second) {
    TVec result = {
        first.x * second.x,
        first.y * second.y
    };
    return result;
}

/**
 * @brief Умножение вектора на число.
 * @param first Вектор.
 * @param num Число.
 * @return Результирующий вектор (first * num).
 */
static inline TVec v_muln(TVec first, uint16_t num) {
    TVec result = {
        first.x * num,
        first.y * num
    };
    return result;
}

/**
 * @brief Деление двух векторов.
 * @param first Первый вектор.
 * @param second Второй вектор.
 * @return Результирующий вектор (first / second).
 * @warning Если одна из координат second равна 0 вернет нулевой вектор.
 */
static inline TVec v_divv(TVec first, TVec second) {
    if (second.x == 0) return v_create(0, 0);
    if (second.y == 0) return v_create(0, 0);

    TVec result = {
        first.x / second.x,
        first.y / second.y
    };
    return result;
}

/**
 * @brief Деление вектора на число.
 * @param first Вектор.
 * @param num Число.
 * @return Результирующий вектор (first / num).
 * @warning Если во второй аргумент передать 0 вернет нулевой вектор.
 */
static inline TVec v_divn(TVec first, uint16_t num) {
    if (num == 0) return v_create(0, 0);

    TVec result = {
        first.x / num,
        first.y / num
    };
    return result;
}

/**
 * @brief Вычисление остатка от деления двух векторов.
 * @param first Первый вектор.
 * @param second Второй вектор.
 * @return Результирующий вектор (first % second).
 * @warning Если одна из координат second равна 0 вернет нулевой вектор.
 */
static inline TVec v_modv(TVec first, TVec second) {
    if (second.x == 0) return v_create(0, 0);
    if (second.y == 0) return v_create(0, 0);

    TVec result = {
        first.x % second.x,
        first.y % second.y
    };
    return result;
}

/**
 * @brief Вычисление остатка от деления вектора на число.
 * @param first Вектор.
 * @param num Число.
 * @return Результирующий вектор (first % num).
 * @warning Если во второй аргумент передать 0 вернет нулевой вектор.
 */
static inline TVec v_modn(TVec first, uint16_t num) {
    if (num == 0) return v_create(0, 0);

    TVec result = {
        first.x % num,
        first.y % num
    };
    return result;
}

// -----------------------------------------------------------------------
// ОПЕРАТОРЫ ПРИСВАИВАНИЯ
// -----------------------------------------------------------------------

/**
 * @brief Сложение двух векторов (с перезаписью).
 * @param first Первый вектор (изменяется).
 * @param second Второй вектор.
 * @return Результирующий вектор (first += second).
 * @note При ошибке возвращает NULL.
 */
static inline TVec* v_iaddv(TVec *first, TVec second) {
    if (first == NULL) return NULL;

    first->x += second.x;
    first->y += second.y;
    return first;
}

/**
 * @brief Сложение вектора и числа (с перезаписью).
 * @param first Вектор (изменяется).
 * @param num Число.
 * @return Результирующий вектор (first += num).
 * @note При ошибке возвращает NULL.
 */
static inline TVec* v_iaddn(TVec *first, uint16_t num) {
    if (first == NULL) return NULL;

    first->x += num;
    first->y += num;
    return first;
}

/**
 * @brief Вычитание двух векторов (с перезаписью).
 * @param first Первый вектор (изменяется).
 * @param second Второй вектор.
 * @return Результирующий вектор (first -= second).
 * @note При ошибке возвращает NULL.
 */
static inline TVec* v_isubv(TVec *first, TVec second) {
    if (first == NULL) return NULL;

    first->x -= second.x;
    first->y -= second.y;
    return first;
}

/**
 * @brief Вычитание вектора и числа (с перезаписью).
 * @param first Вектор (изменяется).
 * @param num Число.
 * @return Результирующий вектор (first -= num).
 * @note При ошибке возвращает NULL.
 */
static inline TVec* v_isubn(TVec *first, uint16_t num) {
    if (first == NULL) return NULL;

    first->x -= num;
    first->y -= num;
    return first;
}

/**
 * @brief Умножение двух векторов (с перезаписью).
 * @param first Первый вектор (изменяется).
 * @param second Второй вектор.
 * @return Результирующий вектор (first *= second).
 * @note При ошибке возвращает NULL.
 */
static inline TVec* v_imulv(TVec *first, TVec second) {
    if (first == NULL) return NULL;

    first->x *= second.x;
    first->y *= second.y;
    return first;
}

/**
 * @brief Умножение вектора на число (с перезаписью).
 * @param first Вектор (изменяется).
 * @param num Число.
 * @return Результирующий вектор (first *= num).
 * @note При ошибке возвращает NULL.
 */
static inline TVec* v_imuln(TVec *first, uint16_t num) {
    if (first == NULL) return NULL;

    first->x *= num;
    first->y *= num;
    return first;
}

/**
 * @brief Деление двух векторов (с перезаписью).
 * @param first Первый вектор (изменяется).
 * @param second Второй вектор.
 * @return Результирующий вектор (first /= second).
 * @note При ошибке возвращает NULL.
 * @warning Если одна из координат second равна 0 вернет NULL.
 */
static inline TVec* v_idivv(TVec *first, TVec second) {
    if (first == NULL) return NULL;
    if (second.x == 0) return NULL;
    if (second.y == 0) return NULL;

    first->x /= second.x;
    first->y /= second.y;
    return first;
}

/**
 * @brief Деление вектора на число (с перезаписью).
 * @param first Вектор (изменяется).
 * @param num Число.
 * @return Результирующий вектор (first /= num).
 * @note При ошибке возвращает NULL.
 * @warning Если во второй аргумент передать 0 вернет NULL.
 */
static inline TVec* v_idivn(TVec *first, uint16_t num) {
    if (first == NULL) return NULL;
    if (num == 0) return NULL;

    first->x /= num;
    first->y /= num;
    return first;
}

/**
 * @brief Вычисление остатка от деления двух векторов (с перезаписью).
 * @param first Первый вектор (изменяется).
 * @param second Второй вектор.
 * @return Результирующий вектор (first %= second).
 * @note При ошибке возвращает NULL.
 * @warning Если одна из координат second равна 0 вернет NULL.
 */
static inline TVec* v_imodv(TVec *first, TVec second) {
    if (first == NULL) return NULL;
    if (second.x == 0) return NULL;
    if (second.y == 0) return NULL;

    first->x %= second.x;
    first->y %= second.y;
    return first;
}

/**
 * @brief Вычисление остатка от деления вектора на число (с перезаписью).
 * @param first Вектор (изменяется).
 * @param num Число.
 * @return Результирующий вектор (first %= num).
 * @note При ошибке возвращает NULL.
 * @warning Если во второй аргумент передать 0 вернет NULL.
 */
static inline TVec* v_imodn(TVec *first, uint16_t num) {
    if (first == NULL) return NULL;
    if (num == 0) return NULL;

    first->x %= num;
    first->y %= num;
    return first;
}

#endif //COMMON_H_INCLUDED