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
    /**
     * @brief Создаёт партию сырья у конкретного поставщика.
     */
    RawMaterial(std::string name, double pricePerKg, std::string category,
                std::string supplierName, double orderedKg);

    /**
     * @brief Возвращает имя поставщика.
     */
    const std::string& GetSupplierName() const;

    /**
     * @brief Возвращает заказанное количество (кг).
     */
    double GetOrderedKg() const;

    /**
     * @brief Увеличивает заказ на указанное количество кг.
     */
    void AddOrder(double kg);

    /**
     * @brief Возвращает название вида: "Сырьё".
     */
    std::string GetKindName() const override;

protected:
    /**
     * @brief Возвращает описание, специфичное для сырья.
     */
    std::string GetSpecificInfo() const override;

private:
    std::string supplierName_;
    double orderedKg_ = 0.0;
};
