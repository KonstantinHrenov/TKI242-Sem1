#include "RawMaterial.h"
#include "FormatUtils.h"

RawMaterial::RawMaterial(const std::string& name, double pricePerKg, const std::string& category,
                         const std::string& supplierName, double orderedKg)
    : Product(name, pricePerKg, category),
      supplierName_(supplierName), orderedKg_(orderedKg) {}

const std::string& RawMaterial::GetSupplierName() const noexcept { return supplierName_; }
double RawMaterial::GetOrderedKg() const noexcept { return orderedKg_; }
void RawMaterial::AddOrder(double kg) noexcept { orderedKg_ += kg; }
std::string RawMaterial::GetKindName() const { return "Сырьё"; }

std::string RawMaterial::GetSpecificInfo() const {
    return "поставщик: " + supplierName_ + ", заказ: " + FormatUtils::FormatDecimal(orderedKg_) + " кг";
}
