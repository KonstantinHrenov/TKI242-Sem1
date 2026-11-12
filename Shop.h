#pragma once

#include <string>

/**
 * @brief Магазин.
 */
class Shop {
private:
    std::string name_;
    std::string address_;

public:
    /**
     * @brief Создаёт магазин.
     *
     * @param name Название магазина.
     * @param address Адрес магазина.
     */
    Shop(const std::string& name, const std::string& address);

    /**
     * @return Название.
     */
    const std::string& GetName() const noexcept;

    /**
     * @return Адрес.
     */
    const std::string& GetAddress() const noexcept;
};
