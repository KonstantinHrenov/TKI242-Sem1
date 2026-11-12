#pragma once

#include <string>

/**
 * @brief Пространство имён FormatUtils (вспомогательные функции для работы со строками)
 */
namespace FormatUtils {
    /**
     * @brief Получить строку с денежной суммой
     * @param value - сумма в рублях
     * @return строка вида "123.45 руб."
     */
    std::string FormatMoney(const double value);

    /**
     * @brief Получить строку с числом, округлённым до двух знаков после запятой
     * @param value - числовое значение
     * @return строка вида "123.45"
     */
    std::string FormatDecimal(const double value);

    /**
     * @brief Сравнить две строки (сравнение чувствительно к регистру)
     * @param a - первая строка
     * @param b - вторая строка
     * @return true - если строки полностью совпадают, иначе false
     */
    bool Equals(const std::string& a, const std::string& b);
}
