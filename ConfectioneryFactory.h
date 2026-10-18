#pragma once
//
// ConfectioneryFactory.h
// Класс "Кондитерская фабрика" - справочник товаров плюс журнал продаж.
//
// Реализует задания варианта "Кондитерская фабрика":
//   1) Список магазинов, заказывающих данный товар.
//   2) Список продуктов, заказываемых у данного поставщика.
//   3) Ассортимент данного товара и цену.
//   4) Наиболее популярный вид товара.
//   5) Стоимость произведённого за отчётный период.
//
#include <string>
#include <vector>
#include "Product.h"
#include "RawMaterial.h"
#include "Confectionery.h"
#include "Shop.h"
#include "Sale.h"
#include "ProductionPeriod.h"
#include "Date.h"

/**
 * @brief Период, за который запрашивается отчёт о продажах.
 */
enum class SalesPeriod {
    /** @brief Неделя. */
    Week = 1,
    /** @brief Месяц. */
    Month = 2,
    /** @brief Год. */
    Year = 3
};

/**
 * @brief Возвращает русское название периода продаж.
 */
inline std::string SalesPeriodName(const SalesPeriod period) {
    switch (period) {
    case SalesPeriod::Week:  return "неделю";
    case SalesPeriod::Month: return "месяц";
    case SalesPeriod::Year:  return "год";
    }
    return "период";
}

/**
 * @brief Объединяет справочник товаров, магазины и журнал продаж.
 */
class ConfectioneryFactory {
public:
    /**
     * @brief Создаёт пустую фабрику с заданным названием.
     */
    explicit ConfectioneryFactory(const std::string name);

    /**
     * @brief Возвращает название фабрики.
     */
    const std::string& GetName() const;

    /**
     * @brief Добавляет товар в справочник.
     */
    void AddProduct(Product* product);

    /**
     * @brief Добавляет магазин в список.
     */
    void AddShop(const Shop& shop);

    /**
     * @brief Регистрирует продажу.
     */
    void RegisterSale(const Sale& sale);

    /**
     * @brief Возвращает все товары.
     */
    const std::vector<Product*>& GetAllProducts() const;

    /**
     * @brief Возвращает все магазины.
     */
    const std::vector<Shop>& GetAllShops() const;

    /**
     * @brief Возвращает все продажи.
     */
    const std::vector<Sale>& GetAllSales() const;

    /**
     * @brief Ищет товар по названию (регистронезависимо).
     */
    Product* FindProductByName(const std::string& name) const;

    /**
     * @brief Задание 1: список магазинов, заказывающих данный товар.
     */
    std::vector<std::string> GetShopsForProduct(const std::string& productName) const;

    /**
     * @brief Задание 2: список продуктов у данного поставщика.
     */
    std::vector<RawMaterial*> GetProductsBySupplier(const std::string& supplierName) const;

    /**
     * @brief Задание 3: ассортимент по категории.
     */
    std::vector<Product*> GetAssortmentByCategory(const std::string& category) const;

    /**
     * @brief Задание 4: наиболее популярный вид товара.
     */
    std::string GetMostPopularKind() const;

    /**
     * @brief Задание 5: стоимость произведённого за период.
     */
    double GetTotalProductionCost(const ProductionPeriod period) const;

    /**
     * @brief Возвращает продажи товара за период.
     */
    std::vector<Sale> GetSalesForPeriod(const std::string& productName,
                                        const SalesPeriod period,
                                        const Date& asOf) const;

    /**
     * @brief Суммирует количество проданных единиц за период.
     */
    int GetTotalQuantitySold(const std::string& productName,
                             const SalesPeriod period,
                             const Date& asOf) const;

    /**
     * @brief Суммирует выручку по продажам за период.
     */
    double GetTotalRevenue(const std::string& productName,
                           const SalesPeriod period,
                           const Date& asOf) const;

private:
    /** @brief Название фабрики. */
    std::string name_;
    /** @brief Справочник товаров фабрики. */
    std::vector<Product*> products_;
    /** @brief Список магазинов-партнёров. */
    std::vector<Shop> shops_;
    /** @brief Журнал совершённых продаж. */
    std::vector<Sale> sales_;

    /**
     * @brief Возвращает длину периода в днях.
     */
    static int PeriodLengthDays(const SalesPeriod period);

    /**
     * @brief Проверяет, попадает ли дата в период.
     */
    bool IsWithinPeriod(const Date& saleDate, const Date& asOf, const SalesPeriod period) const;
};
