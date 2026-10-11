#include "RawMaterial.h"
#include "FormatUtils.h"

RawMaterial::RawMaterial(std::string name, double pricePerKg, std::string category,
    std::string supplierName, double orderedKg)
    : Product(std::move(name), pricePerKg, std::move(category)),
    supplierName_(std::move(supplierName)), orderedKg_(orderedKg) {
}

const std::string& RawMaterial::GetSupplierName() const { return supplierName_; }
double RawMaterial::GetOrderedKg() const { return orderedKg_; }
void RawMaterial::AddOrder(double kg) { orderedKg_ += kg; }

std::string RawMaterial::GetKindName() const { return "Сырьё"; }

std::string RawMaterial::GetSpecificInfo() const {
    return "поставщик: " + supplierName_ +
        ", заказано: " + FormatUtils::FormatDecimal(orderedKg_) + " кг";
}
