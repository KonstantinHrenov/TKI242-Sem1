#pragma once

#include "Date.h"
#include <string>

/**
 * @brief Запись о продаже партии товара магазину.
 */
class Sale {
public:
    /**
     * @brief Создаёт запись о продаже.
     * @param productName Название товара.
     * @param shopName Название магазина.
     * @param kg Количество в килограммах.
     * @param pricePerKg Цена за килограмм.
     * @param saleDate Дата продажи.
     */
    Sale(const std::string& productName, const std::string& shopName,
         double kg, double pricePerKg, const Date& saleDate);

    /**
     * @return Название проданного товара.
     */
    const std::string& GetProductName() const noexcept;

    /**
     * @return Название магазина-покупателя.
     */
    const std::string& GetShopName() const noexcept;

    /**
     * @return Объем партии в килограммах.
     */
    double GetKg() const noexcept;

    /**
     * @return Цена за килограмм.
     */
    double GetPricePerKg() const noexcept;

    /**
     * @return Общая стоимость партии.
     */
    double GetTotalCost() const noexcept;

    /**
     * @return Дата продажи.
     */
    const Date& GetDate() const noexcept;

private:
    std::string productName_;
    std::string shopName_;
    double kg_;
    double pricePerKg_;
    Date saleDate_;
};
