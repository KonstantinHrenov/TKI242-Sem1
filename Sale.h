#pragma once

#include "Date.h"
#include <string>

/**
 * @brief Запись о продаже.
 */
class Sale {
private:
    std::string productName_;
    std::string shopName_;
    double kg_;
    double pricePerKg_;
    Date saleDate_;

public:
    /**
     * @brief Создаёт запись о продаже.
     *
     * @param productName Название товара.
     * @param shopName Название магазина.
     * @param kg Вес партии (кг).
     * @param pricePerKg Цена за килограмм.
     * @param saleDate Дата продажи.
     */
    Sale(const std::string& productName, const std::string& shopName,
        double kg, double pricePerKg, const Date& saleDate);

    /**
     * @return Название товара.
     */
    const std::string& GetProductName() const noexcept;

    /**
     * @return Название магазина.
     */
    const std::string& GetShopName() const noexcept;

    /**
     * @return Вес партии.
     */
    double GetKg() const noexcept;

    /**
     * @return Цена за килограмм.
     */
    double GetPricePerKg() const noexcept;

    /**
     * @return Общая стоимость (вес * цену).
     */
    double GetTotalCost() const noexcept;

    /**
     * @return Дата продажи.
     */
    const Date& GetDate() const noexcept;
};
