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
    Sale(const std::string productName, const Date saleDate, const int quantity, const double totalPrice);

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
    /** @brief Название товара. */
    std::string productName_;
    /** @brief Дата совершения продажи. */
    Date saleDate_;
    /** @brief Количество проданных единиц. */
    int quantity_;
    /** @brief Общая сумма продажи. */
    double totalPrice_;
};
