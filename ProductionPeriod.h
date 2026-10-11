#pragma once
#include <string>

enum class ProductionPeriod {
    Day,
    Week,
    Month,
    Quarter,
    Year
};

inline std::string ProductionPeriodName(ProductionPeriod period) {
    switch (period) {
    case ProductionPeriod::Day:     return "день";
    case ProductionPeriod::Week:    return "неделю";
    case ProductionPeriod::Month:   return "месяц";
    case ProductionPeriod::Quarter: return "квартал";
    case ProductionPeriod::Year:    return "год";
    }
    return "период";
}
