#pragma once
//
// RawMaterial.h
// Класс-наследник "Сырьё" - продукт, заказываемый у поставщика.
//
#include "Product.h"
#include <string>

/**
 * @brief Сырьё (мука, сахар, какао), заказываемое у поставщиков.
 */
class RawMaterial : public Product {
public:
    RawMaterial(std::string name,
        double pricePerKg,
        std::string category,
        std::string supplierName,
        double orderedKg);

    const std::string& GetSupplierName() const;
    double GetOrderedKg() const;
    void AddOrder(double kg);

    std::string GetKindName() const override;

protected:
    std::string GetSpecificInfo() const override;

private:
    std::string supplierName_;
    double orderedKg_ = 0.0;
};