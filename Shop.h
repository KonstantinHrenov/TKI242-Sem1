#pragma once

#include <string>

/**
 * @brief Класс Shop (магазин, заказывающий изделия фабрики)
 */
class Shop {
private:
    /**
     * @brief Название магазина
     */
    std::string name_;

    /**
     * @brief Адрес магазина
     */
    std::string address_;

public:
    /**
     * @brief Конструктор
     * @param name - название магазина
     * @param address - адрес магазина
     */
    Shop(const std::string& name, const std::string& address);

    /**
     * @brief Получить название магазина
     * @return название магазина
     */
    const std::string& GetName() const noexcept;

    /**
     * @brief Получить адрес магазина
     * @return адрес магазина
     */
    const std::string& GetAddress() const noexcept;
};
