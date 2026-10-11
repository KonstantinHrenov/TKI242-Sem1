#pragma once
//
// FormatUtils.h
// Вспомогательные функции форматирования строк (без потоков ввода-вывода).
//
#include <string>

namespace FormatUtils {

    std::string FormatMoney(double value);
    std::string FormatDecimal(double value);
    bool EqualsIgnoreCase(const std::string& a, const std::string& b);

}