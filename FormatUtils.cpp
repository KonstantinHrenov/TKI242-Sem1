#include "FormatUtils.h"
#include <cstdio>

namespace {
    std::string ToLowerString(const std::string& s) {
        std::string res;
        res.reserve(s.size());
        for (size_t i = 0; i < s.size(); ++i) {
            const unsigned char b1 = static_cast<unsigned char>(s[i]);
            if (i + 1 < s.size()) {
                const unsigned char b2 = static_cast<unsigned char>(s[i + 1]);
                if (b1 == 0xD0 && b2 >= 0x90 && b2 <= 0x9F) {
                    res += static_cast<char>(0xD0);
                    res += static_cast<char>(b2 + 0x20);
                    ++i;
                    continue;
                }
                if (b1 == 0xD0 && b2 >= 0xA0 && b2 <= 0xAF) {
                    res += static_cast<char>(0xD1);
                    res += static_cast<char>(b2 - 0x20);
                    ++i;
                    continue;
                }
                if (b1 == 0xD0 && b2 == 0x81) {
                    res += static_cast<char>(0xD1);
                    res += static_cast<char>(0x91);
                    ++i;
                    continue;
                }
                if ((b1 == 0xD0 && b2 >= 0xB0 && b2 <= 0xBF) ||
                    (b1 == 0xD1 && ((b2 >= 0x80 && b2 <= 0x8F) || b2 == 0x91))) {
                    res += static_cast<char>(b1);
                    res += static_cast<char>(b2);
                    ++i;
                    continue;
                }
            }
            if (b1 >= 'A' && b1 <= 'Z') {
                res += static_cast<char>(b1 + ('a' - 'A'));
            } else if (b1 >= 0xC0 && b1 <= 0xDF) {
                res += static_cast<char>(b1 + 0x20);
            } else if (b1 == 0xA8) {
                res += static_cast<char>(0xB8);
            } else {
                res += static_cast<char>(b1);
            }
        }
        return res;
    }
}

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
        return ToLowerString(a) == ToLowerString(b);
    }
}
