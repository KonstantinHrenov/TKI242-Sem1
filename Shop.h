#pragma once
//
// Shop.h
// Класс "Магазин" - торговая точка, заказывающая готовые изделия.
//
#include <string>

/**
 * @brief Магазин, получающий готовую продукцию кондитерской фабрики.
 */
class Shop {
public:
    Shop(std::string name, std::string address);

    const std::string& GetName() const;
    const std::string& GetAddress() const;
    std::string GetInfo() const;

private:
    std::string name_;
    std::string address_;
};