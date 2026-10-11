#include "Sale.h"
#include "FormatUtils.h"

Sale::Sale(std::string productName, Date saleDate, int quantity, double totalPrice)
    : productName_(std::move(productName)), saleDate_(saleDate),
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
