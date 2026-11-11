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
 * @brief Кондитерская фабрика: управляет товарами, поставками и продажами.
 */
class ConfectioneryFactory {
public:
    /**
     * @brief Создаёт фабрику с указанным названием.
     * @param name Название фабрики.
     */
    explicit ConfectioneryFactory(const std::string& name = "Сладкие Традиции");

    /**
     * @return Название фабрики.
     */
    const std::string& GetName() const noexcept;

    /**
     * @brief Добавляет партию сырья на фабрику.
     * @param material Объект сырья.
     */
    void AddProduct(const RawMaterial& material);

    /**
     * @brief Добавляет кондитерское изделие на фабрику.
     * @param confectionery Объект кондитерского изделия.
     */
    void AddProduct(const Confectionery& confectionery);

    /**
     * @return Вектор зарегистрированного сырья.
     */
    const std::vector<RawMaterial>& GetRawMaterials() const noexcept;

    /**
     * @return Вектор зарегистрированных кондитерских изделий.
     */
    const std::vector<Confectionery>& GetConfectioneries() const noexcept;

    /**
     * @return Коллекция ссылок на продукты как на базовый класс Product.
     */
    std::vector<std::reference_wrapper<const Product>> GetPolymorphicProducts() const;

    /**
     * @brief Поиск сырья по названию.
     * @param name Имя товара.
     * @param found Выходной объект сырья.
     * @return true при успешном поиске, иначе false.
     */
    bool FindProductByName(const std::string& name, RawMaterial& found) const;

    /**
     * @brief Поиск кондитерского изделия по названию.
     * @param name Имя товара.
     * @param found Выходной объект изделия.
     * @return true при успешном поиске, иначе false.
     */
    bool FindProductByName(const std::string& name, Confectionery& found) const;

    /**
     * @brief Проверяет наличие товара на фабрике.
     * @param name Имя товара.
     * @return true если товар присутствует, иначе false.
     */
    bool HasProduct(const std::string& name) const;

    /**
     * @brief Получить список сырья указанного поставщика.
     * @param supplierName Имя поставщика.
     * @return Вектор сырья от данного поставщика.
     */
    std::vector<RawMaterial> GetProductsBySupplier(const std::string& supplierName) const;

    /**
     * @brief Получить ассортимент сырья по категории.
     * @param category Категория.
     * @param outAssortment Выходной вектор сырья.
     */
    void GetAssortmentByCategory(const std::string& category, std::vector<RawMaterial>& outAssortment) const;

    /**
     * @brief Получить ассортимент изделий по категории.
     * @param category Категория.
     * @param outAssortment Выходной вектор изделий.
     */
    void GetAssortmentByCategory(const std::string& category, std::vector<Confectionery>& outAssortment) const;

    std::vector<RawMaterial> GetRawMaterialsByCategory(const std::string& category) const;
    std::vector<Confectionery> GetConfectioneryByCategory(const std::string& category) const;

    /**
     * @brief Задание 1: список магазинов, заказывающих данный товар.
     * @param productName Название изделия.
     * @return Список названий магазинов.
     */
    std::vector<std::string> GetShopsForProduct(const std::string& productName) const;

    /**
     * @brief Задание 4: наиболее популярный вид кондитерского изделия.
     * @return Название популярного вида.
     */
    std::string GetMostPopularKind() const;

    /**
     * @brief Задание 5: стоимость произведенного товара за период.
     * @param from Начало периода.
     * @param to Конец периода.
     * @return Суммарная стоимость.
     */
    double GetProductionValueInPeriod(const Date& from, const Date& to) const;

    void AddShop(const Shop& shop);
    const std::vector<Shop>& GetShops() const noexcept;

    void AddSale(const Sale& sale);
    const std::vector<Sale>& GetSales() const noexcept;

    /**
     * @return Сводная информация о фабрике.
     */
    std::string ToString() const;

private:
    std::string name_;
    std::vector<RawMaterial> rawMaterials_;
    std::vector<Confectionery> confectioneries_;
    std::vector<std::pair<bool, std::size_t>> productOrder_;
    std::vector<Shop> shops_;
    std::vector<Sale> sales_;
};
