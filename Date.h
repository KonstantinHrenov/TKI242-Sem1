#pragma once

#include <string>

/**
 * @brief Календарная дата (год, месяц, день).
 */
class Date {
public:
    /**
     * @brief Создаёт дату по числовым компонентам.
     * @param year Календарный год.
     * @param month Номер месяца (1..12).
     * @param day День месяца (1..31).
     */
    Date(const int year, const int month, const int day);

    /**
     * @brief Разбирает дату из строки формата "ГГГГ-ММ-ДД".
     * @param isoDate Строка с датой.
     * @return Объект даты Date.
     */
    static Date Parse(const std::string& isoDate);

    int GetYear() const noexcept;
    int GetMonth() const noexcept;
    int GetDay() const noexcept;

    /**
     * @return Строка в формате "ГГГГ-ММ-ДД".
     */
    std::string ToString() const;

    long ToDayNumber() const noexcept;
    long DaysUntil(const Date& other) const noexcept;

    bool operator==(const Date& other) const noexcept;
    bool operator!=(const Date& other) const noexcept;
    bool operator<(const Date& other) const noexcept;
    bool operator<=(const Date& other) const noexcept;
    bool operator>(const Date& other) const noexcept;
    bool operator>=(const Date& other) const noexcept;

private:
    int year_;
    int month_;
    int day_;
    static void Validate(int year, int month, int day);
};
