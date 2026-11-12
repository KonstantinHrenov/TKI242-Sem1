#pragma once

#include <string>

/**
 * @brief Календарная дата (год, месяц, день).
 */
class Date {
private:
    int year_;
    int month_;
    int day_;

    /**
     * @brief Проверяет корректность календарной даты.
     *
     * @param year Календарный год.
     * @param month Номер месяца (1..12).
     * @param day День месяца (1..31).
     */
    static void Validate(int year, int month, int day);

public:
    /**
     * @brief Создаёт дату по числовым компонентам.
     *
     * @param year Календарный год.
     * @param month Номер месяца (1..12).
     * @param day День месяца (1..31).
     */
    Date(int year, int month, int day);

    /**
     * @brief Разбирает дату из строки формата "ГГГГ-ММ-ДД".
     *
     * @param isoDate Строка с датой.
     * @return Объект даты.
     */
    static Date Parse(const std::string& isoDate);

    /**
     * @return Календарный год.
     */
    int GetYear() const noexcept;

    /**
     * @return Номер месяца (1..12).
     */
    int GetMonth() const noexcept;

    /**
     * @return День месяца (1..31).
     */
    int GetDay() const noexcept;

    /**
     * @return Строка в формате "ГГГГ-ММ-ДД".
     */
    std::string ToString() const;

    /**
     * @return Количество дней с 1970 года.
     */
    long ToDayNumber() const noexcept;

    /**
     * @brief Вычисляет разницу в днях до другой даты.
     *
     * @param other Дата для сравнения.
     * @return Количество дней.
     */
    long DaysUntil(const Date& other) const noexcept;

    bool operator==(const Date& other) const noexcept;
    bool operator!=(const Date& other) const noexcept;
    bool operator<(const Date& other) const noexcept;
    bool operator<=(const Date& other) const noexcept;
    bool operator>(const Date& other) const noexcept;
    bool operator>=(const Date& other) const noexcept;
};
