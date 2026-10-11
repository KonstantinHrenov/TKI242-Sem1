#include "Confectionery.h"
#include "FormatUtils.h"

Confectionery::Confectionery(std::string name, double pricePerKg, std::string category,
    std::string kind, double producedKg)
    : Product(std::move(name), pricePerKg, std::move(category)),
    kind_(std::move(kind)), producedKg_(producedKg) {
}

const std::string& Confectionery::GetKind() const { return kind_; }
double Confectionery::GetProducedKg() const { return producedKg_; }
const std::vector<std::string>& Confectionery::GetShops() const { return shops_; }
void Confectionery::AddShop(const std::string& shop) { shops_.push_back(shop); }
void Confectionery::AddProduction(double kg) { producedKg_ += kg; }

std::string Confectionery::GetKindName() const { return "Готовое изделие"; }

std::string Confectionery::GetSpecificInfo() const {
    std::string shopsList;
    for (size_t i = 0; i < shops_.size(); ++i) {
        if (i > 0) shopsList += ", ";
        shopsList += shops_[i];
    }
    if (shopsList.empty()) shopsList = "не указаны";
    return "вид: " + kind_ +
        ", произведено: " + FormatUtils::FormatDecimal(producedKg_) + " кг" +
        ", магазины: " + shopsList;
}
