#pragma once
//
// ProductionPeriod.h
// Период, за который запрашивается отчёт о производстве.
//
#include <string>

/**
 * @brief Временное окно для отчёта о производстве.
 */
enum class ProductionPeriod {
    Day,
    Week,
    Month,
    Quarter,
    Year
};

/**
 * @brief Возвращает русское название периода.
 */
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
