#pragma once

#include <string>

/**
 * @brief Базовый класс Product (товар кондитерской фабрики)
 */
class Product {
private:
    /**
     * @brief Название товара
     */
    std::string name_;

    /**
     * @brief Цена за килограмм (руб.)
     */
    double pricePerKg_;

    /**
     * @brief Категория товара
     */
    std::string category_;

protected:
    /**
     * @brief Получить информацию, специфичную для типа-наследника
     * @return строка с дополнительной информацией (может быть пустой)
     */
    virtual std::string GetSpecificInfo() const = 0;

public:
    /**
     * @brief Конструктор
     * @param name - название товара
     * @param pricePerKg - цена за килограмм (руб.)
     * @param category - категория товара
     */
    Product(const std::string& name, const double pricePerKg, const std::string& category);

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Product() = default;

    /**
     * @brief Получить название товара
     * @return название товара
     */
    const std::string& GetName() const noexcept;

    /**
     * @brief Получить цену за килограмм
     * @return цена за килограмм (руб.)
     */
    double GetPricePerKg() const noexcept;

    /**
     * @brief Получить категорию товара
     * @return категория товара
     */
    const std::string& GetCategory() const noexcept;

    /**
     * @brief Установить новую цену за килограмм
     * @param price - новая цена (руб.)
     */
    void SetPricePerKg(const double price) noexcept;

    /**
     * @brief Получить название типа товара
     * @return строка "Сырьё" либо "Готовое изделие"
     */
    virtual std::string GetKindName() const = 0;

    /**
     * @brief Виртуальный метод получения информации о товаре
     * @return строка вида "[тип] название (категория), цена: ..., дополнительная информация"
     */
    virtual std::string GetInfo() const;
};
