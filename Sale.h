#pragma once

#include "Date.h"
#include <string>

/**
 * @brief Класс Sale (продажа партии изделия магазину)
 */
class Sale {
private:
    /**
     * @brief Название проданного изделия
     */
    std::string productName_;

    /**
     * @brief Название магазина-покупателя
     */
    std::string shopName_;

    /**
     * @brief Вес партии (кг)
     */
    double kg_;

    /**
     * @brief Цена за килограмм (руб.)
     */
    double pricePerKg_;

    /**
     * @brief Дата продажи
     */
    Date saleDate_;

public:
    /**
     * @brief Конструктор
     * @param productName - название изделия
     * @param shopName - название магазина
     * @param kg - вес партии (кг)
     * @param pricePerKg - цена за килограмм (руб.)
     * @param saleDate - дата продажи
     */
    Sale(const std::string& productName, const std::string& shopName,
        const double kg, const double pricePerKg, const Date& saleDate);

    /**
     * @brief Получить название проданного изделия
     * @return название изделия
     */
    const std::string& GetProductName() const noexcept;

    /**
     * @brief Получить название магазина
     * @return название магазина
     */
    const std::string& GetShopName() const noexcept;

    /**
     * @brief Получить вес партии
     * @return вес партии (кг)
     */
    double GetKg() const noexcept;

    /**
     * @brief Получить цену за килограмм
     * @return цена за килограмм (руб.)
     */
    double GetPricePerKg() const noexcept;

    /**
     * @brief Получить общую стоимость партии
     * @return произведение веса партии на цену за килограмм (руб.)
     */
    double GetTotalCost() const noexcept;

    /**
     * @brief Получить дату продажи
     * @return ссылку на дату продажи
     */
    const Date& GetDate() const noexcept;
};
