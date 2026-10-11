#pragma once
#include <string>
#include "Date.h"

class Sale {
public:
    Sale(std::string productName, Date saleDate, int quantity, double totalPrice);

    const std::string& GetProductName() const;
    const Date& GetSaleDate() const;
    int GetQuantity() const;
    double GetTotalPrice() const;

    std::string GetInfo() const;

private:
    std::string productName_;
    Date saleDate_;
    int quantity_ = 0;
    double totalPrice_ = 0.0;
};
