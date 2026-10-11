#include "FormatUtils.h"
#include <cctype>
#include <cmath>

namespace {

    const std::pair<std::string, std::string> kCyrillicUpperToLower[] = {
        {"А", "а"}, {"Б", "б"}, {"В", "в"}, {"Г", "г"}, {"Д", "д"},
        {"Е", "е"}, {"Ж", "ж"}, {"З", "з"}, {"И", "и"}, {"Й", "й"},
        {"К", "к"}, {"Л", "л"}, {"М", "м"}, {"Н", "н"}, {"О", "о"},
        {"П", "п"}, {"Р", "р"}, {"С", "с"}, {"Т", "т"}, {"У", "у"},
        {"Ф", "ф"}, {"Х", "х"}, {"Ц", "ц"}, {"Ч", "ч"}, {"Ш", "ш"},
        {"Щ", "щ"}, {"Ъ", "ъ"}, {"Ы", "ы"}, {"Ь", "ь"}, {"Э", "э"},
        {"Ю", "ю"}, {"Я", "я"}, {"Ё", "ё"},
    };

    const std::string* FindCyrillicLowerCase(const std::string& s, size_t pos) {
        for (const auto& pair : kCyrillicUpperToLower) {
            const std::string& upper = pair.first;
            if (s.compare(pos, upper.size(), upper) == 0) return &pair.second;
        }
        return nullptr;
    }

    std::string ToLower(const std::string& s) {
        std::string result;
        result.reserve(s.size());
        size_t pos = 0;
        while (pos < s.size()) {
            const unsigned char byte = static_cast<unsigned char>(s[pos]);
            if (byte < 0x80) {
                result += static_cast<char>(std::tolower(byte));
                ++pos;
                continue;
            }
            if (const std::string* const lower = FindCyrillicLowerCase(s, pos)) {
                result += *lower;
                pos += lower->size();
            }
            else {
                result += static_cast<char>(byte);
                ++pos;
            }
        }
        return result;
    }

}

namespace FormatUtils {

    std::string FormatDecimal(double value) {
        const bool negative = value < 0.0;
        const double absValue = negative ? -value : value;
        const long long hundredths = static_cast<long long>(std::floor(absValue * 100.0 + 0.5));
        const long long whole = hundredths / 100;
        const long long frac = hundredths % 100;
        const std::string sign = (negative && hundredths != 0) ? "-" : "";
        return sign + std::to_string(whole) + "." +
            (frac < 10 ? "0" : "") + std::to_string(frac);
    }

    std::string FormatMoney(double value) {
        return FormatDecimal(value);
    }

    bool EqualsIgnoreCase(const std::string& a, const std::string& b) {
        return ToLower(a) == ToLower(b);
    }

}