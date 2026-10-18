#pragma once
//
// Product.h
// Базовый класс "Товар" кондитерской фабрики.
//
#include <string>

/**
 * @brief Базовый класс, представляющий один товар.
 */
class Product {
public:
    /**
     * @brief Создаёт товар с его общими атрибутами.
     */
    Product(const std::string name, const double pricePerKg, const std::string category);

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~Product() = default;

    /**
     * @brief Возвращает название товара.
     */
    const std::string& GetName() const;

    /**
     * @brief Возвращает цену за килограмм.
     */
    double GetPricePerKg() const;

    /**
     * @brief Возвращает категорию товара.
     */
    const std::string& GetCategory() const;

    /**
     * @brief Устанавливает новую цену за килограмм.
     */
    void SetPricePerKg(const double price);

    /**
     * @brief Возвращает название вида товара.
     */
    virtual std::string GetKindName() const = 0;

    /**
     * @brief Формирует однострочное описание товара.
     */
    virtual std::string GetInfo() const;

protected:
    /**
     * @brief Возвращает описание, специфичное для вида товара.
     */
    virtual std::string GetSpecificInfo() const = 0;

private:
    /** @brief Название товара. */
    std::string name_;
    /** @brief Цена за килограмм. */
    double pricePerKg_;
    /** @brief Категория товара. */
    std::string category_;
};
