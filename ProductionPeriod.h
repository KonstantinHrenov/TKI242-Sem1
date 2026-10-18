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
    /** @brief День. */
    Day = 1,
    /** @brief Неделя. */
    Week = 2,
    /** @brief Месяц. */
    Month = 3,
    /** @brief Квартал. */
    Quarter = 4,
    /** @brief Год. */
    Year = 5
};

/**
 * @brief Возвращает русское название периода.
 */
inline std::string ProductionPeriodName(const ProductionPeriod period) {
    switch (period) {
    case ProductionPeriod::Day:     return "день";
    case ProductionPeriod::Week:    return "неделю";
    case ProductionPeriod::Month:   return "месяц";
    case ProductionPeriod::Quarter: return "квартал";
    case ProductionPeriod::Year:    return "год";
    }
    return "период";
}
