#pragma once

namespace miit::algebra {

    /**
     * @brief Абстрактный генератор целочисленных значений
     *
     * Базовый класс для всех способов заполнения матрицы: случайными
     * числами (RandomGenerator), значениями с клавиатуры/из потока
     * (IStreamGenerator) и константой (ConstantGenerator).
     */
    class Generator {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Generator() = default;

        /**
         * @brief Сгенерировать очередное значение
         * @return сгенерированное значение
         */
        virtual int generate() = 0;
    };

} // namespace miit::algebra
