#pragma once

#include <string>

/**
 * @brief Абстрактный базовый класс "Товар" кондитерской фабрики.
 */
class Product {
public:
    /**
     * @brief Создаёт товар с базовыми атрибутами.
     * @param name Название товара.
     * @param pricePerKg Цена за килограмм.
     * @param category Категория товара.
     */
    Product(const std::string& name, double pricePerKg, const std::string& category);

    virtual ~Product() = default;

    /**
     * @return Название товара.
     */
    const std::string& GetName() const noexcept;

    /**
     * @return Цена за килограмм.
     */
    double GetPricePerKg() const noexcept;

    /**
     * @return Категория товара.
     */
    const std::string& GetCategory() const noexcept;

    /**
     * @param price Новая цена за килограмм.
     */
    void SetPricePerKg(double price) noexcept;

    /**
     * @return Название вида товара.
     */
    virtual std::string GetKindName() const = 0;

    /**
     * @return Строковое описание товара.
     */
    virtual std::string GetInfo() const;

protected:
    /**
     * @return Специфичная для наследника информация.
     */
    virtual std::string GetSpecificInfo() const = 0;

private:
    std::string name_;
    double pricePerKg_;
    std::string category_;
};
