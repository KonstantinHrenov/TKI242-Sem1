#pragma once

#include <string>

/**
 * @brief Вспомогательные функции для работы со строками.
 */
namespace FormatUtils {
    /**
     * @brief Добавляет к сумме слово "руб." и два знака после запятой.
     *
     * @param value Сумма в рублях.
     * @return Отформатированная строка.
     */
    std::string FormatMoney(double value);

    /**
     * @brief Оставляет у числа ровно два знака после запятой.
     *
     * @param value Числовое значение.
     * @return Отформатированная строка.
     */
    std::string FormatDecimal(double value);

    /**
     * @brief Сравнивает две строки.
     *
     * @param a Первая строка.
     * @param b Вторая строка.
     * @return true, если строки равны.
     */
    bool EqualsIgnoreCase(const std::string& a, const std::string& b);
}
