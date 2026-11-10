#include "Product.h"
#include "FormatUtils.h"

Product::Product(const std::string& name, double pricePerKg, const std::string& category)
    : name_(name), pricePerKg_(pricePerKg), category_(category) {}

const std::string& Product::GetName() const noexcept { return name_; }
double Product::GetPricePerKg() const noexcept { return pricePerKg_; }
const std::string& Product::GetCategory() const noexcept { return category_; }
void Product::SetPricePerKg(double price) noexcept { pricePerKg_ = price; }

std::string Product::GetKindName() const { return "Товар"; }
std::string Product::GetSpecificInfo() const { return ""; }

std::string Product::GetInfo() const {
    std::string info = "[" + GetKindName() + "] " + name_ + " (" + category_ + "), цена: " +
                       FormatUtils::FormatMoney(pricePerKg_);
    const std::string spec = GetSpecificInfo();
    if (!spec.empty()) {
        info += ", " + spec;
    }
    return info;
}
