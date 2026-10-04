#pragma once
#include "Matrix.h"

namespace miit::algebra {

    /**
     * @brief Базовый класс для заданий над матрицей
     */
    class Exercise {
    protected:
        Matrix<int>& matrix;

    public:
        /**
         * @brief Конструктор
         * @param matrix Ссылка на матрицу
         */
        explicit Exercise(Matrix<int>& matrix);

        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Exercise() = default;

        /**
         * @brief Решить задание
         */
        virtual void solve() = 0;
    };

} // namespace miit::algebra
