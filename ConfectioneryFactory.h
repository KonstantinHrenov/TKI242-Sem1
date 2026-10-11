#pragma once
//
// ConfectioneryFactory.h
// Класс "Кондитерская фабрика" - справочник товаров плюс магазины.
// Реализует пять заданий варианта "Кондитерская фабрика":
//   1) Список магазинов, заказывающих данный товар.
//   2) Список продуктов у данного поставщика.
//   3) Ассортимент по категории и цены.
//   4) Наиболее популярный вид товара.
//   5) Стоимость произведённого за отчётный период.
//
#include <memory>
#include <string>
#include <vector>
#include "Product.h"
#include "RawMaterial.h"
#include "Confectionery.h"
#include "Shop.h"
#include "Date.h"

/**
 * @brief Объединяет справочник товаров и магазины кондитерской фабрики.
 */
class ConfectioneryFactory {
public:
    explicit ConfectioneryFactory(const std::string name);

    const std::string& GetName() const;

    void AddProduct(std::shared_ptr<Product> product);
    void AddShop(const Shop& shop);

    std::vector<std::string> GetShopsForProduct(const std::string& productName) const;
    std::vector<std::shared_ptr<RawMaterial>> GetProductsBySupplier(const std::string& supplierName) const;
    std::vector<std::shared_ptr<Product>> GetAssortmentByCategory(const std::string& category) const;
    std::string GetMostPopularKind() const;
    double GetTotalProductionCost(const std::string& period) const;

    const std::vector<std::shared_ptr<Product>>& GetAllProducts() const;
    std::shared_ptr<Product> FindProductByName(const std::string& name) const;

private:
    std::string name_;
    std::vector<std::shared_ptr<Product>> products_;
    std::vector<Shop> shops_;
};