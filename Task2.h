#pragma once
#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Задание 2: удалить столбцы с нечётным положительным элементом
     */
    class Task2 : public Exercise {
    public:
        /**
         * @brief Конструктор
         * @param matrix Ссылка на матрицу
         */
        explicit Task2(Matrix<int>& matrix);

        /**
         * @brief Выполнить задание
         */
        void solve() override;
    };

} // namespace miit::algebra
