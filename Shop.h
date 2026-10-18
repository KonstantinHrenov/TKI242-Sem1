#pragma once
//
// Shop.h
// Класс "Магазин" - торговая точка, заказывающая изделия.
//
#include <string>

/**
 * @brief Магазин, получающий готовую продукцию.
 */
class Shop {
public:
    /**
     * @brief Создаёт магазин с именем и адресом.
     */
    Shop(const std::string name, const std::string address);

    /**
     * @brief Возвращает название магазина.
     */
    const std::string& GetName() const;

    /**
     * @brief Возвращает адрес магазина.
     */
    const std::string& GetAddress() const;

    /**
     * @brief Возвращает строковое описание магазина.
     */
    std::string GetInfo() const;

private:
    /** @brief Название магазина. */
    std::string name_;
    /** @brief Адрес магазина. */
    std::string address_;
};
