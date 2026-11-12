#include "ConfectioneryFactory.h"
#include "FormatUtils.h"
#include <map>

ConfectioneryFactory::ConfectioneryFactory(const std::string& name) : name_(name) {}

const std::string& ConfectioneryFactory::GetName() const noexcept { return name_; }

void ConfectioneryFactory::AddProduct(const RawMaterial& material) {
    rawMaterials_.push_back(material);
    productOrder_.emplace_back(true, rawMaterials_.size() - 1);
}

void ConfectioneryFactory::AddProduct(const Confectionery& confectionery) {
    confectioneries_.push_back(confectionery);
    productOrder_.emplace_back(false, confectioneries_.size() - 1);
}

const std::vector<RawMaterial>& ConfectioneryFactory::GetRawMaterials() const noexcept { return rawMaterials_; }
const std::vector<Confectionery>& ConfectioneryFactory::GetConfectioneries() const noexcept { return confectioneries_; }

std::vector<std::reference_wrapper<const Product>> ConfectioneryFactory::GetPolymorphicProducts() const {
    std::vector<std::reference_wrapper<const Product>> result;
    result.reserve(productOrder_.size());
    for (const auto& entry : productOrder_) {
        if (entry.first) result.emplace_back(rawMaterials_[entry.second]);
        else result.emplace_back(confectioneries_[entry.second]);
    }
    return result;
}

bool ConfectioneryFactory::FindProductByName(const std::string& name, RawMaterial& found) const {
    for (const auto& item : rawMaterials_) {
        if (FormatUtils::EqualsIgnoreCase(item.GetName(), name)) { found = item; return true; }
    }
    return false;
}

bool ConfectioneryFactory::FindProductByName(const std::string& name, Confectionery& found) const {
    for (const auto& item : confectioneries_) {
        if (FormatUtils::EqualsIgnoreCase(item.GetName(), name)) { found = item; return true; }
    }
    return false;
}

bool ConfectioneryFactory::HasProduct(const std::string& name) const {
    for (const auto& item : rawMaterials_) if (FormatUtils::EqualsIgnoreCase(item.GetName(), name)) return true;
    for (const auto& item : confectioneries_) if (FormatUtils::EqualsIgnoreCase(item.GetName(), name)) return true;
    return false;
}

std::vector<RawMaterial> ConfectioneryFactory::GetProductsBySupplier(const std::string& supplierName) const {
    std::vector<RawMaterial> result;
    for (const auto& item : rawMaterials_) {
        if (FormatUtils::EqualsIgnoreCase(item.GetSupplierName(), supplierName)) result.push_back(item);
    }
    return result;
}

void ConfectioneryFactory::GetAssortmentByCategory(const std::string& category, std::vector<RawMaterial>& outAssortment) const {
    outAssortment.clear();
    for (const auto& item : rawMaterials_) {
        if (FormatUtils::EqualsIgnoreCase(item.GetCategory(), category)) outAssortment.push_back(item);
    }
}

void ConfectioneryFactory::GetAssortmentByCategory(const std::string& category, std::vector<Confectionery>& outAssortment) const {
    outAssortment.clear();
    for (const auto& item : confectioneries_) {
        if (FormatUtils::EqualsIgnoreCase(item.GetCategory(), category)) outAssortment.push_back(item);
    }
}

std::vector<std::string> ConfectioneryFactory::GetShopsForProduct(const std::string& productName) const {
    for (const auto& item : confectioneries_) {
        if (FormatUtils::EqualsIgnoreCase(item.GetName(), productName)) return item.GetShops();
    }
    return {};
}

std::string ConfectioneryFactory::GetMostPopularKind() const {
    std::map<std::string, double> popularity;
    for (const auto& c : confectioneries_) popularity[c.GetKind()] += c.GetProducedKg();
    std::string bestKind; double maxKg = -1.0;
    for (const auto& pair : popularity) {
        if (pair.second > maxKg) { maxKg = pair.second; bestKind = pair.first; }
    }
    return bestKind;
}

double ConfectioneryFactory::GetProductionValueInPeriod(const Date& from, const Date& to) const {
    double total = 0.0;
    for (const auto& item : confectioneries_) {
        if (item.GetProductionDate() >= from && item.GetProductionDate() <= to)
            total += item.GetProducedKg() * item.GetPricePerKg();
    }
    return total;
}

void ConfectioneryFactory::AddShop(const Shop& shop) { shops_.push_back(shop); }
const std::vector<Shop>& ConfectioneryFactory::GetShops() const noexcept { return shops_; }

void ConfectioneryFactory::AddSale(const Sale& sale) { sales_.push_back(sale); }
const std::vector<Sale>& ConfectioneryFactory::GetSales() const noexcept { return sales_; }

std::string ConfectioneryFactory::ToString() const {
    return name_ + ", сырья: " + std::to_string(rawMaterials_.size()) +
        ", изделий: " + std::to_string(confectioneries_.size()) +
        ", магазинов: " + std::to_string(shops_.size());
}
