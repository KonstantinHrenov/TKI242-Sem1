#pragma once

#include "Product.h"
#include "RawMaterial.h"
#include "Confectionery.h"
#include "Shop.h"
#include "Sale.h"
#include "Date.h"

#include <functional>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Главный класс - Кондитерская фабрика.
 */
class ConfectioneryFactory {
private:
    std::string name_;
    std::vector<RawMaterial> rawMaterials_;
    std::vector<Confectionery> confectioneries_;
    std::vector<std::pair<bool, std::size_t>> productOrder_;
    std::vector<Shop> shops_;
    std::vector<Sale> sales_;

public:
    /**
     * @brief Создаёт фабрику.
     *
     * @param name Название фабрики.
     */
    explicit ConfectioneryFactory(const std::string& name = "Сладкие Традиции");

    /**
     * @return Название фабрики.
     */
    const std::string& GetName() const noexcept;

    /**
     * @brief Добавляет сырьё на фабрику.
     *
     * @param material Объект сырья.
     */
    void AddProduct(const RawMaterial& material);

    /**
     * @brief Добавляет изделие на фабрику.
     *
     * @param confectionery Объект изделия.
     */
    void AddProduct(const Confectionery& confectionery);

    /**
     * @return Список всего сырья.
     */
    const std::vector<RawMaterial>& GetRawMaterials() const noexcept;

    /**
     * @return Список всех изделий.
     */
    const std::vector<Confectionery>& GetConfectioneries() const noexcept;

    /**
     * @brief Возвращает ссылки на базовый класс для полиморфного вывода.
     *
     * @return Коллекция ссылок на Product.
     */
    std::vector<std::reference_wrapper<const Product>> GetPolymorphicProducts() const;

    /**
     * @brief Ищет сырьё по названию.
     *
     * @param name Имя товара.
     * @param found Сюда запишется найденный объект.
     * @return true, если найдено.
     */
    bool FindProductByName(const std::string& name, RawMaterial& found) const;

    /**
     * @brief Ищет изделие по названию.
     *
     * @param name Имя товара.
     * @param found Сюда запишется найденный объект.
     * @return true, если найдено.
     */
    bool FindProductByName(const std::string& name, Confectionery& found) const;

    /**
     * @brief Проверяет наличие товара.
     *
     * @param name Имя товара.
     * @return true, если товар есть.
     */
    bool HasProduct(const std::string& name) const;

    /**
     * @brief Получает список сырья у поставщика.
     *
     * @param supplierName Имя поставщика.
     * @return Вектор найденного сырья.
     */
    std::vector<RawMaterial> GetProductsBySupplier(const std::string& supplierName) const;

    /**
     * @brief Получает ассортимент сырья по категории.
     *
     * @param category Категория.
     * @param outAssortment Сюда запишется результат.
     */
    void GetAssortmentByCategory(const std::string& category, std::vector<RawMaterial>& outAssortment) const;

    /**
     * @brief Получает ассортимент изделий по категории.
     *
     * @param category Категория.
     * @param outAssortment Сюда запишется результат.
     */
    void GetAssortmentByCategory(const std::string& category, std::vector<Confectionery>& outAssortment) const;

    /**
     * @brief Задание 1: магазины, заказывающие товар.
     *
     * @param productName Название товара.
     * @return Список названий магазинов.
     */
    std::vector<std::string> GetShopsForProduct(const std::string& productName) const;

    /**
     * @brief Задание 4: самый популярный вид.
     *
     * @return Название популярного вида.
     */
    std::string GetMostPopularKind() const;

    /**
     * @brief Задание 5: стоимость произведенного за период.
     *
     * @param from Начало периода.
     * @param to Конец периода.
     * @return Суммарная стоимость.
     */
    double GetProductionValueInPeriod(const Date& from, const Date& to) const;

    /**
     * @brief Добавляет магазин.
     *
     * @param shop Объект магазина.
     */
    void AddShop(const Shop& shop);

    /**
     * @return Список магазинов.
     */
    const std::vector<Shop>& GetShops() const noexcept;

    /**
     * @brief Добавляет запись о продаже.
     *
     * @param sale Объект продажи.
     */
    void AddSale(const Sale& sale);

    /**
     * @return Список продаж.
     */
    const std::vector<Sale>& GetSales() const noexcept;

    /**
     * @return Краткая сводка о фабрике.
     */
    std::string ToString() const;
};
