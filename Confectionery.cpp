#include "Confectionery.h"
#include "FormatUtils.h"

Confectionery::Confectionery(const std::string name, const double pricePerKg, const std::string category,
                             const std::string kind, const double producedKg)
    : Product(name, pricePerKg, category),
      kind_(kind), producedKg_(producedKg) {
}

const std::string& Confectionery::GetKind() const { return kind_; }
double Confectionery::GetProducedKg() const { return producedKg_; }
const std::vector<std::string>& Confectionery::GetShops() const { return shops_; }
void Confectionery::AddShop(const std::string& shop) { shops_.push_back(shop); }
void Confectionery::AddProduction(const double kg) { producedKg_ += kg; }

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
