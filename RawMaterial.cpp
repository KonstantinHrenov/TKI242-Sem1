#include "RawMaterial.h"
#include "FormatUtils.h"

RawMaterial::RawMaterial(const std::string name, const double pricePerKg, const std::string category,
                         const std::string supplierName, const double orderedKg)
    : Product(name, pricePerKg, category),
      supplierName_(supplierName), orderedKg_(orderedKg) {
}

const std::string& RawMaterial::GetSupplierName() const { return supplierName_; }
double RawMaterial::GetOrderedKg() const { return orderedKg_; }
void RawMaterial::AddOrder(const double kg) { orderedKg_ += kg; }

std::string RawMaterial::GetKindName() const { return "Сырьё"; }

std::string RawMaterial::GetSpecificInfo() const {
    return "поставщик: " + supplierName_ +
        ", заказано: " + FormatUtils::FormatDecimal(orderedKg_) + " кг";
}
