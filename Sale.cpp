#include "Sale.h"
#include "FormatUtils.h"

Sale::Sale(const std::string productName, const Date saleDate, const int quantity, const double totalPrice)
    : productName_(productName), saleDate_(saleDate),
      quantity_(quantity), totalPrice_(totalPrice) {
}

const std::string& Sale::GetProductName() const { return productName_; }
const Date& Sale::GetSaleDate() const { return saleDate_; }
int Sale::GetQuantity() const { return quantity_; }
double Sale::GetTotalPrice() const { return totalPrice_; }

std::string Sale::GetInfo() const {
    return saleDate_.ToString() + ": " + productName_ +
        " x" + std::to_string(quantity_) +
        " = " + FormatUtils::FormatMoney(totalPrice_) + " руб.";
}
