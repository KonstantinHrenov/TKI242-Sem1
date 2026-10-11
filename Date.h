#pragma once
#include <string>

class Date {
public:
    Date(int year, int month, int day);
    static Date Parse(const std::string& isoDate);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    std::string ToString() const;
    long ToDayNumber() const;
    long DaysUntil(const Date& other) const;

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;

private:
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;
    static void Validate(int year, int month, int day);
};
