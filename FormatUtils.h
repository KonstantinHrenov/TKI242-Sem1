#pragma once
//
// FormatUtils.h
// Вспомогательные функции форматирования строк.
//
#include <string>

namespace FormatUtils {

    /**
     * @brief Форматирует дробное число как денежную сумму.
     */
    std::string FormatMoney(double value);

    /**
     * @brief Форматирует дробное число с двумя знаками после точки.
     */
    std::string FormatDecimal(double value);

    /**
     * @brief Регистронезависимое сравнение двух строк в UTF-8.
     */
    bool EqualsIgnoreCase(const std::string& a, const std::string& b);

}
