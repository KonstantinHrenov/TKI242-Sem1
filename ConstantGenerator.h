#pragma once
#include "Generator.h"

namespace miit::algebra {

    /**
     * @brief Генератор, возвращающий константное значение
     */
    class ConstantGenerator : public Generator {
    private:
        int value;

    public:
        /**
         * @brief Конструктор
         * @param value Константное значение
         */
        explicit ConstantGenerator(const int value);

        /**
         * @brief Вернуть константное значение
         * @return Константное значение
         */
        int generate() override;
    };

} // namespace miit::algebra
