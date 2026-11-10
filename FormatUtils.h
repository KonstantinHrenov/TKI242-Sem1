#pragma once

#include <string>

/**
 * @brief Вспомогательные функции форматирования значений.
 */
namespace FormatUtils {
    /**
     * @brief Форматирует сумму в рублях с копейками.
     * @param[in] value Сумма в рублях.
     * @return Отформатированная строка.
     */
    std::string FormatMoney(double value);

    /**
     * @brief Форматирует число с двумя знаками после точки.
     * @param[in] value Числовое значение.
     * @return Отформатированная строка.
     */
    std::string FormatDecimal(double value);

    /**
     * @brief Регистронезависимое сравнение строк.
     * @param[in] a Первая строка.
     * @param[in] b Вторая строка.
     * @return true, если строки равны без учёта регистра.
     */
    bool EqualsIgnoreCase(const std::string& a, const std::string& b);
}
