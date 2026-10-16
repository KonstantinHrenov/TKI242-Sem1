#pragma once
//
// Sale.h
// Запись о продаже товара магазину.
//
#include <string>
#include "Date.h"

/**
 * @brief Неизменяемая запись об одной продаже.
 */
class Sale {
public:
    /**
     * @brief Создаёт запись о продаже.
     */
    Sale(std::string productName, Date saleDate, int quantity, double totalPrice);

    /**
     * @brief Возвращает название проданного товара.
     */
    const std::string& GetProductName() const;

    /**
     * @brief Возвращает дату продажи.
     */
    const Date& GetSaleDate() const;

    /**
     * @brief Возвращает количество проданных единиц.
     */
    int GetQuantity() const;

    /**
     * @brief Возвращает общую сумму продажи.
     */
    double GetTotalPrice() const;

    /**
     * @brief Формирует однострочное описание продажи.
     */
    std::string GetInfo() const;

private:
    std::string productName_;
    Date saleDate_;
    int quantity_ = 0;
    double totalPrice_ = 0.0;
};
