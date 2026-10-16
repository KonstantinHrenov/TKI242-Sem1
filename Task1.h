/*
 * @file Task1.h
 * @brief Задание 1: замена минимального элемента каждой строки нулем
 * @author Student
 * @version 1.0
 * @date 2024
 */

#pragma once
#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Задание 1: заменить минимальный элемент каждой строки нулем
     */
    class Task1 : public Exercise {
    public:
        /**
         * @brief Конструктор
         * @param matrix Ссылка на матрицу
         */
        explicit Task1(Matrix<int>& matrix);

        /**
         * @brief Выполнить задание
         */
        void solve() override;
    };

} // namespace miit::algebra
