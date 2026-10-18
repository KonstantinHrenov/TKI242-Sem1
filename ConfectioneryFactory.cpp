#include "ConfectioneryFactory.h"
#include "FormatUtils.h"
#include <map>

ConfectioneryFactory::ConfectioneryFactory(const std::string name)
    : name_(name) {
}

const std::string& ConfectioneryFactory::GetName() const { return name_; }

void ConfectioneryFactory::AddProduct(Product* product) {
    if (product) {
        products_.push_back(product);
    }
}

void ConfectioneryFactory::AddShop(const Shop& shop) { shops_.push_back(shop); }
void ConfectioneryFactory::RegisterSale(const Sale& sale) { sales_.push_back(sale); }

const std::vector<Product*>& ConfectioneryFactory::GetAllProducts() const { return products_; }
const std::vector<Shop>& ConfectioneryFactory::GetAllShops() const { return shops_; }
const std::vector<Sale>& ConfectioneryFactory::GetAllSales() const { return sales_; }

Product* ConfectioneryFactory::FindProductByName(const std::string& name) const {
    for (const auto& product : products_) {
        if (FormatUtils::EqualsIgnoreCase(product->GetName(), name)) return product;
    }
    return nullptr;
}

std::vector<std::string> ConfectioneryFactory::GetShopsForProduct(const std::string& productName) const {
    std::vector<std::string> result;
    for (const auto& product : products_) {
        if (!FormatUtils::EqualsIgnoreCase(product->GetName(), productName)) continue;
        const auto c = dynamic_cast<Confectionery*>(product);
        if (c) for (const auto& s : c->GetShops()) result.push_back(s);
    }
    return result;
}

std::vector<RawMaterial*> ConfectioneryFactory::GetProductsBySupplier(const std::string& supplierName) const {
    std::vector<RawMaterial*> result;
    for (const auto& product : products_) {
        const auto raw = dynamic_cast<RawMaterial*>(product);
        if (raw && FormatUtils::EqualsIgnoreCase(raw->GetSupplierName(), supplierName)) {
            result.push_back(raw);
        }
    }
    return result;
}

std::vector<Product*> ConfectioneryFactory::GetAssortmentByCategory(const std::string& category) const {
    std::vector<Product*> result;
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
        const auto c = dynamic_cast<Confectionery*>(product);
        if (c) totals[c->GetKind()] += c->GetProducedKg();
    }
    std::string best;
    double bestWeight = -1.0;
    for (const auto& pair : totals) {
        if (pair.second > bestWeight) { bestWeight = pair.second; best = pair.first; }
    }
    return best;
}

double ConfectioneryFactory::GetTotalProductionCost(const ProductionPeriod /*period*/) const {
    double total = 0.0;
    for (const auto& product : products_) {
        const auto c = dynamic_cast<Confectionery*>(product);
        if (c) total += c->GetProducedKg() * c->GetPricePerKg();
    }
    return total;
}

int ConfectioneryFactory::PeriodLengthDays(const SalesPeriod period) {
    switch (period) {
    case SalesPeriod::Week:  return 7;
    case SalesPeriod::Month: return 30;
    case SalesPeriod::Year:  return 365;
    }
    return 0;
}

bool ConfectioneryFactory::IsWithinPeriod(const Date& saleDate, const Date& asOf, const SalesPeriod period) const {
    const long daysAgo = saleDate.DaysUntil(asOf);
    return daysAgo >= 0 && daysAgo <= PeriodLengthDays(period);
}

std::vector<Sale> ConfectioneryFactory::GetSalesForPeriod(const std::string& productName,
                                                         const SalesPeriod period,
                                                         const Date& asOf) const {
    std::vector<Sale> result;
    for (const auto& sale : sales_) {
        if (FormatUtils::EqualsIgnoreCase(sale.GetProductName(), productName) &&
            IsWithinPeriod(sale.GetSaleDate(), asOf, period)) {
            result.push_back(sale);
        }
    }
    return result;
}

int ConfectioneryFactory::GetTotalQuantitySold(const std::string& productName,
                                               const SalesPeriod period,
                                               const Date& asOf) const {
    int total = 0;
    for (const auto& sale : GetSalesForPeriod(productName, period, asOf)) total += sale.GetQuantity();
    return total;
}

double ConfectioneryFactory::GetTotalRevenue(const std::string& productName,
                                             const SalesPeriod period,
                                             const Date& asOf) const {
    double total = 0.0;
    for (const auto& sale : GetSalesForPeriod(productName, period, asOf)) total += sale.GetTotalPrice();
    return total;
}
