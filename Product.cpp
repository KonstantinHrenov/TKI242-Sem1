#include "Product.h"
#include "FormatUtils.h"

Product::Product(std::string name, double pricePerKg, std::string category)
    : name_(std::move(name)),
    pricePerKg_(pricePerKg),
    category_(std::move(category)) {
}

const std::string& Product::GetName() const { return name_; }
double Product::GetPricePerKg() const { return pricePerKg_; }
const std::string& Product::GetCategory() const { return category_; }

void Product::SetPricePerKg(double price) { pricePerKg_ = price; }

std::string Product::GetInfo() const {
    return name_ +
        " [" + GetKindName() + "]" +
        " | категория: " + category_ +
        " | цена за кг: " + FormatUtils::FormatMoney(pricePerKg_) + " руб." +
        " | " + GetSpecificInfo();
}
