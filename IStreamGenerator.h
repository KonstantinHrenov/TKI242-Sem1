#pragma once
#include "Generator.h"
#include <istream>

namespace miit::algebra {

    /**
     * @brief Генератор, считывающий значения из входного потока
     */
    class IStreamGenerator : public Generator {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор
         * @param in Поток ввода
         */
        explicit IStreamGenerator(std::istream& in);

        /**
         * @brief Считать значение из потока
         * @return Считанное значение
         */
        int generate() override;
    };

} // namespace miit::algebra
