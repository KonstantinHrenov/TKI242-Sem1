#include "Date.h"
#include <stdexcept>
#include <cstdlib>
#include <string>

namespace {
    // Простая проверка на високосный год
    bool IsLeap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    // Сколько дней в месяце
    int DaysInMonth(int m, int y) {
        if (m == 2) return IsLeap(y) ? 29 : 28;
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        return 31;
    }
}

void Date::Validate(int year, int month, int day) {
    if (month < 1 || month > 12)
        throw std::invalid_argument("Date: неверный месяц");
    if (day < 1 || day > DaysInMonth(month, year))
        throw std::invalid_argument("Date: неверный день");
}

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {
    Validate(year_, month_, day_);
}

Date Date::Parse(const std::string& iso) {
    if (iso.size() != 10 || iso[4] != '-' || iso[7] != '-')
        throw std::invalid_argument("Date::Parse: ожидается формат ГГГГ-ММ-ДД");
    for (size_t i = 0; i < iso.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (iso[i] < '0' || iso[i] > '9')
            throw std::invalid_argument("Date::Parse: нечисловые символы");
    }
    return Date(std::stoi(iso.substr(0, 4)), std::stoi(iso.substr(5, 2)), std::stoi(iso.substr(8, 2)));
}

int Date::GetYear() const noexcept { return year_; }
int Date::GetMonth() const noexcept { return month_; }
int Date::GetDay() const noexcept { return day_; }

std::string Date::ToString() const {
    std::string m = (month_ < 10 ? "0" : "") + std::to_string(month_);
    std::string d = (day_ < 10 ? "0" : "") + std::to_string(day_);
    return std::to_string(year_) + "-" + m + "-" + d;
}

long Date::ToDayNumber() const noexcept {
    long total = 0;
    // Считаем дни за прошедшие годы
    for (int y = 1970; y < year_; ++y) {
        total += IsLeap(y) ? 366 : 365;
    }
    // Считаем дни за прошедшие месяцы текущего года
    for (int m = 1; m < month_; ++m) {
        total += DaysInMonth(m, year_);
    }
    // Добавляем дни текущего месяца
    total += day_ - 1;
    return total;
}

long Date::DaysUntil(const Date& other) const noexcept {
    return other.ToDayNumber() - ToDayNumber();
}

bool Date::operator==(const Date& o) const noexcept { return year_ == o.year_ && month_ == o.month_ && day_ == o.day_; }
bool Date::operator!=(const Date& o) const noexcept { return !(*this == o); }
bool Date::operator<(const Date& o) const noexcept { return ToDayNumber() < o.ToDayNumber(); }
bool Date::operator<=(const Date& o) const noexcept { return ToDayNumber() <= o.ToDayNumber(); }
bool Date::operator>(const Date& o) const noexcept { return ToDayNumber() > o.ToDayNumber(); }
bool Date::operator>=(const Date& o) const noexcept { return ToDayNumber() >= o.ToDayNumber(); }
