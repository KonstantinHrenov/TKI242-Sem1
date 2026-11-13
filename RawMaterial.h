#pragma once

#include "Product.h"
#include <string>

/**
 * @brief Класс RawMaterial (сырьё, заказываемое у поставщика) - наследник класса Product
 */
class RawMaterial : public Product {
private:
    /**
     * @brief Название поставщика
     */
    std::string supplierName_;

    /**
     * @brief Заказанное количество (кг)
     */
    double orderedKg_;

protected:
    /**
     * @brief Получить информацию о поставщике и объёме заказа
     * @return строка вида "поставщик: ..., заказ: ... кг"
     */
    std::string GetSpecificInfo() const override;

public:
    /**
     * @brief Конструктор
     * @param name - название сырья
     * @param pricePerKg - цена за килограмм (руб.)
     * @param category - категория сырья
     * @param supplierName - название поставщика
     * @param orderedKg - заказанное количество (кг)
     */
    RawMaterial(const std::string& name, const double pricePerKg, const std::string& category,
        const std::string& supplierName, const double orderedKg);

    /**
     * @brief Получить название поставщика
     * @return название поставщика
     */
    const std::string& GetSupplierName() const noexcept;

    /**
     * @brief Получить заказанное количество
     * @return заказанное количество (кг)
     */
    double GetOrderedKg() const noexcept;

    /**
     * @brief Увеличить объём заказа
     * @param kg - добавляемое количество (кг)
     */
    void AddOrder(const double kg) noexcept;

    /**
     * @brief Получить название типа товара
     * @return строка "Сырьё"
     */
    std::string GetKindName() const override;
};
