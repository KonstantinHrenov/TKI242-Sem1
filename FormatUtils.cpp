#include "FormatUtils.h"
#include <cstdio>
#include <string>

namespace FormatUtils {
    std::string FormatDecimal(double value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%.2f", value);
        return std::string(buffer);
    }

    std::string FormatMoney(double value) {
        return FormatDecimal(value) + " руб.";
    }

    bool EqualsIgnoreCase(const std::string& a, const std::string& b) {
        return a == b; 
    }
}
