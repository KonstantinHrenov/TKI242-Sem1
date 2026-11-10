#include "Date.h"
#include <cstdlib>
#include <stdexcept>

namespace {
    bool IsLeapYear(int y) noexcept {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int DaysInMonth(int y, int m) noexcept {
        static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (m == 2 && IsLeapYear(y)) return 29;
        return days[m - 1];
    }

    long DaysFromCivil(int y, unsigned m, unsigned d) noexcept {
        y -= m <= 2;
        const long era = (y >= 0 ? y : y - 399) / 400;
        const unsigned yoe = static_cast<unsigned>(y - era * 400);
        const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
        return era * 146097 + static_cast<long>(doe) - 719468;
    }
}

void Date::Validate(int year, int month, int day) {
    if (month < 1 || month > 12)
        throw std::invalid_argument("Date: месяц должен быть в диапазоне 1..12");
    if (day < 1 || day > DaysInMonth(year, month))
        throw std::invalid_argument("Date: некорректный день месяца");
}

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {
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
    return Date(std::atoi(iso.substr(0, 4).c_str()),
                std::atoi(iso.substr(5, 2).c_str()),
                std::atoi(iso.substr(8, 2).c_str()));
}

int Date::GetYear() const noexcept { return year_; }
int Date::GetMonth() const noexcept { return month_; }
int Date::GetDay() const noexcept { return day_; }

std::string Date::ToString() const {
    auto pad2 = [](int v) { return (v < 10 ? "0" : "") + std::to_string(v); };
    return std::to_string(year_) + "-" + pad2(month_) + "-" + pad2(day_);
}

long Date::ToDayNumber() const noexcept {
    return DaysFromCivil(year_, static_cast<unsigned>(month_), static_cast<unsigned>(day_));
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
