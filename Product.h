#pragma once

#include <string>

/**
 * @brief Базовый класс "Товар".
 */
class Product {
private:
    std::string name_;
    double pricePerKg_;
    std::string category_;

protected:
    /**
     * @brief Возвращает специфичную информацию для наследника.
     *
     * @return Строка с дополнительной информацией.
     */
    virtual std::string GetSpecificInfo() const = 0;

public:
    /**
     * @brief Создаёт товар с базовыми атрибутами.
     *
     * @param name Название товара.
     * @param pricePerKg Цена за килограмм.
     * @param category Категория товара.
     */
    Product(const std::string& name, double pricePerKg, const std::string& category);

    /**
     * @brief Виртуальный деструктор.
     */
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
     * @brief Устанавливает новую цену.
     *
     * @param price Новая цена.
     */
    void SetPricePerKg(double price) noexcept;

    /**
     * @brief Возвращает название вида (Сырьё/Готовое изделие).
     *
     * @return Название вида.
     */
    virtual std::string GetKindName() const = 0;

    /**
     * @brief Возвращает полную строку с информацией о товаре.
     *
     * @return Описание товара.
     */
    virtual std::string GetInfo() const;
};
