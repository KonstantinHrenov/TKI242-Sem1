#pragma once

#include "Product.h"
#include <string>

/**
 * @brief Сырьё (мука, сахар, какао), заказываемое у поставщиков.
 */
class RawMaterial : public Product {
public:
    /**
     * @brief Создаёт партию сырья.
     * @param name Название сырья.
     * @param pricePerKg Цена за килограмм.
     * @param category Категория сырья.
     * @param supplierName Имя поставщика.
     * @param orderedKg Заказанное количество (кг).
     */
    RawMaterial(const std::string& name, double pricePerKg, const std::string& category,
                const std::string& supplierName, double orderedKg);

    /**
     * @return Имя поставщика.
     */
    const std::string& GetSupplierName() const noexcept;

    /**
     * @return Заказанное количество сырья в килограммах.
     */
    double GetOrderedKg() const noexcept;

    /**
     * @param kg Дополнительное количество килограммов для заказа.
     */
    void AddOrder(double kg) noexcept;

    /**
     * @return Название вида: "Сырьё".
     */
    std::string GetKindName() const override;

protected:
    /**
     * @return Описание поставщика и объёма заказа.
     */
    std::string GetSpecificInfo() const override;

private:
    std::string supplierName_;
    double orderedKg_;
};
