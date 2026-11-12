#include "Sale.h"

Sale::Sale(const std::string& productName, const std::string& shopName,
    double kg, double pricePerKg, const Date& saleDate)
    : productName_(productName), shopName_(shopName),
    kg_(kg), pricePerKg_(pricePerKg), saleDate_(saleDate) {
}

const std::string& Sale::GetProductName() const noexcept { return productName_; }
const std::string& Sale::GetShopName() const noexcept { return shopName_; }
double Sale::GetKg() const noexcept { return kg_; }
double Sale::GetPricePerKg() const noexcept { return pricePerKg_; }
double Sale::GetTotalCost() const noexcept { return kg_ * pricePerKg_; }
const Date& Sale::GetDate() const noexcept { return saleDate_; }
