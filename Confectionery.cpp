#include "Confectionery.h"
#include "FormatUtils.h"

Confectionery::Confectionery(const std::string& name, double pricePerKg, const std::string& category,
                             const std::string& kind, double producedKg, const Date& productionDate)
    : Product(name, pricePerKg, category),
      kind_(kind), producedKg_(producedKg), productionDate_(productionDate) {}

const std::string& Confectionery::GetKind() const noexcept { return kind_; }
double Confectionery::GetProducedKg() const noexcept { return producedKg_; }
const Date& Confectionery::GetProductionDate() const noexcept { return productionDate_; }
const std::vector<std::string>& Confectionery::GetShops() const noexcept { return shops_; }

void Confectionery::AddShop(const std::string& shop) {
    for (const auto& s : shops_) {
        if (FormatUtils::EqualsIgnoreCase(s, shop)) return;
    }
    shops_.push_back(shop);
}

void Confectionery::AddProduction(const double kg) noexcept { producedKg_ += kg; }
std::string Confectionery::GetKindName() const { return "Готовое изделие"; }

std::string Confectionery::GetSpecificInfo() const {
    std::string s = "вид: " + kind_ + ", произведено: " + FormatUtils::FormatDecimal(producedKg_) + " кг";
    s += ", дата: " + productionDate_.ToString();
    if (!shops_.empty()) {
        s += ", магазины: ";
        for (size_t i = 0; i < shops_.size(); ++i) {
            if (i > 0) s += ", ";
            s += shops_[i];
        }
    }
    return s;
}
