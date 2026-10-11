#include "ConfectioneryFactory.h"
#include "FormatUtils.h"
#include <map>

ConfectioneryFactory::ConfectioneryFactory(std::string name)
    : name_(std::move(name)) {
}

const std::string& ConfectioneryFactory::GetName() const { return name_; }

void ConfectioneryFactory::AddProduct(std::shared_ptr<Product> product) {
    products_.push_back(std::move(product));
}

void ConfectioneryFactory::AddShop(const Shop& shop) {
    shops_.push_back(shop);
}

std::vector<std::string> ConfectioneryFactory::GetShopsForProduct(
    const std::string& productName) const {
    std::vector<std::string> result;
    for (const auto& product : products_) {
        if (FormatUtils::EqualsIgnoreCase(product->GetName(), productName)) {
            const auto confectionery = std::dynamic_pointer_cast<Confectionery>(product);
            if (confectionery) {
                for (const auto& shop : confectionery->GetShops()) result.push_back(shop);
            }
        }
    }
    return result;
}

std::vector<std::shared_ptr<RawMaterial>> ConfectioneryFactory::GetProductsBySupplier(
    const std::string& supplierName) const {
    std::vector<std::shared_ptr<RawMaterial>> result;
    for (const auto& product : products_) {
        const auto raw = std::dynamic_pointer_cast<RawMaterial>(product);
        if (raw && FormatUtils::EqualsIgnoreCase(raw->GetSupplierName(), supplierName)) {
            result.push_back(raw);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Product>> ConfectioneryFactory::GetAssortmentByCategory(
    const std::string& category) const {
    std::vector<std::shared_ptr<Product>> result;
    for (const auto& product : products_) {
        if (FormatUtils::EqualsIgnoreCase(product->GetCategory(), category)) {
            result.push_back(product);
        }
    }
    return result;
}

std::string ConfectioneryFactory::GetMostPopularKind() const {
    std::map<std::string, double> totals;
    for (const auto& product : products_) {
        const auto confectionery = std::dynamic_pointer_cast<Confectionery>(product);
        if (confectionery) totals[confectionery->GetKind()] += confectionery->GetProducedKg();
    }

    std::string best;
    double bestWeight = -1.0;
    for (const auto& pair : totals) {
        if (pair.second > bestWeight) {
            bestWeight = pair.second;
            best = pair.first;
        }
    }
    return best;
}

double ConfectioneryFactory::GetTotalProductionCost(const std::string& /*period*/) const {
    double total = 0.0;
    for (const auto& product : products_) {
        const auto confectionery = std::dynamic_pointer_cast<Confectionery>(product);
        if (confectionery) total += confectionery->GetProducedKg() * confectionery->GetPricePerKg();
    }
    return total;
}

const std::vector<std::shared_ptr<Product>>& ConfectioneryFactory::GetAllProducts() const {
    return products_;
}

std::shared_ptr<Product> ConfectioneryFactory::FindProductByName(const std::string& name) const {
    for (const auto& product : products_) {
        if (FormatUtils::EqualsIgnoreCase(product->GetName(), name)) return product;
    }
    return nullptr;
}