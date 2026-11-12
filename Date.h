#pragma once

#include <string>

/**
 * @brief Класс Date (календарная дата)
 */
class Date {
private:
    /**
     * @brief Год
     */
    int year_;

    /**
     * @brief Номер месяца (1..12)
     */
    int month_;

    /**
     * @brief День месяца (1..31)
     */
    int day_;

    /**
     * @brief Проверить корректность календарной даты
     * @param year - год
     * @param month - номер месяца (1..12)
     * @param day - день месяца
     * @throw std::invalid_argument - если месяц или день выходят за допустимые границы
     */
    static void Validate(const int year, const int month, const int day);

public:
    /**
     * @brief Конструктор
     * @param year - год
     * @param month - номер месяца (1..12)
     * @param day - день месяца
     * @throw std::invalid_argument - если такой даты не существует
     */
    Date(const int year, const int month, const int day);

    /**
     * @brief Создать дату из строки формата "ГГГГ-ММ-ДД"
     * @param isoDate - строка с датой
     * @return объект даты
     * @throw std::invalid_argument - если строка не соответствует формату
     * или такой даты не существует
     */
    static Date Parse(const std::string& isoDate);

    /**
     * @brief Получить год
     * @return год
     */
    int GetYear() const noexcept;

    /**
     * @brief Получить номер месяца
     * @return номер месяца (1..12)
     */
    int GetMonth() const noexcept;

    /**
     * @brief Получить день месяца
     * @return день месяца
     */
    int GetDay() const noexcept;

    /**
     * @brief Получить строку с датой
     * @return строка формата "ГГГГ-ММ-ДД"
     */
    std::string ToString() const;

    /**
     * @brief Получить порядковый номер дня
     * @return количество дней, прошедших с 1 января 1970 года
     */
    long ToDayNumber() const noexcept;

    /**
     * @brief Вычислить количество дней до другой даты
     * @param other - дата, до которой считается разница
     * @return количество дней (отрицательное, если other раньше текущей даты)
     */
    long DaysUntil(const Date& other) const noexcept;

    /**
     * @brief Оператор сравнения на равенство
     * @param other - дата для сравнения
     * @return true - если даты совпадают, иначе false
     */
    bool operator==(const Date& other) const noexcept;

    /**
     * @brief Оператор сравнения на неравенство
     * @param other - дата для сравнения
     * @return true - если даты различаются, иначе false
     */
    bool operator!=(const Date& other) const noexcept;

    /**
     * @brief Оператор "меньше"
     * @param other - дата для сравнения
     * @return true - если текущая дата раньше other, иначе false
     */
    bool operator<(const Date& other) const noexcept;

    /**
     * @brief Оператор "меньше или равно"
     * @param other - дата для сравнения
     * @return true - если текущая дата не позже other, иначе false
     */
    bool operator<=(const Date& other) const noexcept;

    /**
     * @brief Оператор "больше"
     * @param other - дата для сравнения
     * @return true - если текущая дата позже other, иначе false
     */
    bool operator>(const Date& other) const noexcept;

    /**
     * @brief Оператор "больше или равно"
     * @param other - дата для сравнения
     * @return true - если текущая дата не раньше other, иначе false
     */
    bool operator>=(const Date& other) const noexcept;
};
