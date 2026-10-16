#pragma once
//
// Date.h
// Простой самодостаточный тип "дата" (без потоков ввода-вывода).
//
#include <string>

/**
 * @brief Неизменяемая календарная дата (год/месяц/день).
 */
class Date {
public:
    /**
     * @brief Создаёт дату по числовым компонентам.
     */
    Date(int year, int month, int day);

    /**
     * @brief Разбирает дату из строки "ГГГГ-ММ-ДД".
     */
    static Date Parse(const std::string& isoDate);

    /**
     * @brief Возвращает календарный год.
     */
    int GetYear() const;

    /**
     * @brief Возвращает номер месяца (1-12).
     */
    int GetMonth() const;

    /**
     * @brief Возвращает день месяца.
     */
    int GetDay() const;

    /**
     * @brief Форматирует дату как "ГГГГ-ММ-ДД".
     */
    std::string ToString() const;

    /**
     * @brief Преобразует дату в номер дня относительно эпохи.
     */
    long ToDayNumber() const;

    /**
     * @brief Вычисляет, сколько дней отделяет текущую дату от other.
     */
    long DaysUntil(const Date& other) const;

    /**
     * @brief Сравнение на равенство.
     */
    bool operator==(const Date& other) const;

    /**
     * @brief Сравнение на неравенство.
     */
    bool operator!=(const Date& other) const;

    /**
     * @brief Строгое сравнение "раньше чем".
     */
    bool operator<(const Date& other) const;

    /**
     * @brief Сравнение "раньше или совпадает".
     */
    bool operator<=(const Date& other) const;

    /**
     * @brief Строгое сравнение "позже чем".
     */
    bool operator>(const Date& other) const;

    /**
     * @brief Сравнение "позже или совпадает".
     */
    bool operator>=(const Date& other) const;

private:
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;

    /**
     * @brief Проверяет корректность календарной даты.
     */
    static void Validate(int year, int month, int day);
};
