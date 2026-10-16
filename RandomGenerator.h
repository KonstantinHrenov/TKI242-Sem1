#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra {

    /**
     * @brief Генератор случайных чисел в диапазоне [min, max]
     */
    class RandomGenerator : public Generator {
    private:
        mutable std::uniform_int_distribution<int> distribution;
        mutable std::mt19937 generator;

    public:
        /**
         * @brief Конструктор
         * @param min Минимальное значение
         * @param max Максимальное значение
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Сгенерировать случайное число
         * @return Случайное число
         */
        int generate() const override;
    };

} // namespace miit::algebra
