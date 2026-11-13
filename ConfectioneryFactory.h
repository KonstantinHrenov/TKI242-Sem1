#pragma once

#include "Product.h"
#include "RawMaterial.h"
#include "Confectionery.h"
#include "Shop.h"
#include "Sale.h"
#include "Date.h"

#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Класс ConfectioneryFactory (кондитерская фабрика)
 */
class ConfectioneryFactory {
private:
    /**
     * @brief Название фабрики
     */
    std::string name_;

    /**
     * @brief Массив сырья, заказываемого у поставщиков
     */
    std::vector<RawMaterial> rawMaterials_;

    /**
     * @brief Массив готовых изделий
     */
    std::vector<Confectionery> confectioneries_;

    /**
     * @brief Порядок добавления товаров: признак "сырьё" (true) или "изделие" (false)
     * и индекс товара в соответствующем массиве
     */
    std::vector<std::pair<bool, std::size_t>> productOrder_;

    /**
     * @brief Массив магазинов
     */
    std::vector<Shop> shops_;

    /**
     * @brief Массив продаж
     */
    std::vector<Sale> sales_;

public:
    /**
     * @brief Конструктор
     * @param name - название фабрики (по умолчанию "Сладкие Традиции")
     */
    explicit ConfectioneryFactory(const std::string& name = "Сладкие Традиции");

    /**
     * @brief Получить название фабрики
     * @return название фабрики
     */
    const std::string& GetName() const noexcept;

    /**
     * @brief Добавить сырьё
     * @param material - ссылка на сырьё (в фабрике сохраняется копия)
     */
    void AddProduct(const RawMaterial& material);

    /**
     * @brief Добавить готовое изделие
     * @param confectionery - ссылка на изделие (в фабрике сохраняется копия)
     */
    void AddProduct(const Confectionery& confectionery);

    /**
     * @brief Получить список сырья
     * @return ссылку на массив сырья
     */
    const std::vector<RawMaterial>& GetRawMaterials() const noexcept;

    /**
     * @brief Получить список готовых изделий
     * @return ссылку на массив изделий
     */
    const std::vector<Confectionery>& GetConfectioneries() const noexcept;

    /**
     * @brief Получить все товары фабрики как коллекцию базового типа Product
     * @return массив ссылок на товары в порядке их добавления
     * (ссылки действительны, пока в фабрику не добавлены новые товары)
     */
    std::vector<std::reference_wrapper<const Product>> GetPolymorphicProducts() const;

    /**
     * @brief Найти сырьё по названию
     * @param name - название сырья
     * @param found - объект, в который записывается копия найденного сырья
     * @return true - если сырьё найдено, иначе false (found при этом не изменяется)
     */
    bool FindProductByName(const std::string& name, RawMaterial& found) const;

    /**
     * @brief Найти готовое изделие по названию
     * @param name - название изделия
     * @param found - объект, в который записывается копия найденного изделия
     * @return true - если изделие найдено, иначе false (found при этом не изменяется)
     */
    bool FindProductByName(const std::string& name, Confectionery& found) const;

    /**
     * @brief Проверить, есть ли на фабрике товар с данным названием
     * @param name - название товара (сырья или изделия)
     * @return true - если есть, иначе false
     */
    bool HasProduct(const std::string& name) const;

    /**
     * @brief Найти продукты (сырьё), заказываемые у данного поставщика
     * @param supplierName - название поставщика
     * @return массив найденного сырья (копии)
     */
    std::vector<RawMaterial> GetProductsBySupplier(const std::string& supplierName) const;

    /**
     * @brief Получить ассортимент сырья данной категории
     * @param category - категория сырья
     * @param outAssortment - массив, в который записывается результат (предварительно очищается)
     */
    void GetAssortmentByCategory(const std::string& category, std::vector<RawMaterial>& outAssortment) const;

    /**
     * @brief Получить ассортимент изделий данного товара (категории)
     * @param category - товар (категория изделий), например "Торты"
     * @param outAssortment - массив, в который записывается результат (предварительно очищается)
     */
    void GetAssortmentByCategory(const std::string& category, std::vector<Confectionery>& outAssortment) const;

    /**
     * @brief Найти магазины, заказывающие данное изделие
     * @param productName - название изделия
     * @return массив названий магазинов (пустой, если изделие не найдено)
     */
    std::vector<std::string> GetShopsForProduct(const std::string& productName) const;

    /**
     * @brief Выбрать наиболее популярный вид данного товара
     * (популярность определяется по суммарному весу продаж изделий этого вида)
     * @param category - товар (категория изделий), например "Торты"
     * @return название вида либо пустая строка, если продаж данного товара нет
     */
    std::string GetMostPopularKind(const std::string& category) const;

    /**
     * @brief Получить стоимость товара, произведённого за отчётный период
     * @param from - начало периода (включительно)
     * @param to - конец периода (включительно)
     * @return суммарная стоимость изделий, произведённых за период (руб.)
     */
    double GetProductionValueInPeriod(const Date& from, const Date& to) const;

    /**
     * @brief Добавить магазин
     * @param shop - ссылка на магазин (в фабрике сохраняется копия)
     */
    void AddShop(const Shop& shop);

    /**
     * @brief Получить список магазинов
     * @return ссылку на массив магазинов
     */
    const std::vector<Shop>& GetShops() const noexcept;

    /**
     * @brief Добавить продажу
     * @param sale - ссылка на продажу (в фабрике сохраняется копия)
     */
    void AddSale(const Sale& sale);

    /**
     * @brief Получить список продаж
     * @return ссылку на массив продаж
     */
    const std::vector<Sale>& GetSales() const noexcept;

    /**
     * @brief Получить краткую сводку о фабрике
     * @return строка с названием фабрики и количеством сырья, изделий и магазинов
     */
    std::string ToString() const;
};
