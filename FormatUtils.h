#pragma once
#include <string>

namespace FormatUtils {
    std::string FormatMoney(double value);
    std::string FormatDecimal(double value);
    bool EqualsIgnoreCase(const std::string& a, const std::string& b);
}
