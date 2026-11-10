#pragma once

#include <string>

/**
 * @brief Магазин, заказывающий продукцию фабрики.
 */
class Shop {
public:
    /**
     * @brief Создаёт магазин.
     * @param name Название магазина.
     * @param address Адрес магазина.
     */
    Shop(const std::string& name, const std::string& address);

    /**
     * @return Название магазина.
     */
    const std::string& GetName() const noexcept;

    /**
     * @return Адрес магазина.
     */
    const std::string& GetAddress() const noexcept;

private:
    std::string name_;
    std::string address_;
};
