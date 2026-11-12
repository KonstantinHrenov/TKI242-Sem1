#pragma once

#include "Product.h"
#include <string>

/**
 * @brief Сырьё (мука, сахар и т.д.).
 */
class RawMaterial : public Product {
private:
    std::string supplierName_;
    double orderedKg_;

protected:
    /**
     * @brief Описание поставщика и заказа.
     *
     * @return Строка с информацией.
     */
    std::string GetSpecificInfo() const override;

public:
    /**
     * @brief Создаёт партию сырья.
     *
     * @param name Название сырья.
     * @param pricePerKg Цена за килограмм.
     * @param category Категория.
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
     * @return Заказанное количество (кг).
     */
    double GetOrderedKg() const noexcept;

    /**
     * @brief Добавляет килограммы к заказу.
     *
     * @param kg Количество для добавления.
     */
    void AddOrder(double kg) noexcept;

    /**
     * @return Название вида: "Сырьё".
     */
    std::string GetKindName() const override;
};
