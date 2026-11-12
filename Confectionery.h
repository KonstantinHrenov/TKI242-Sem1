#pragma once

#include "Product.h"
#include "Date.h"
#include <string>
#include <vector>

/**
 * @brief Класс Confectionery (готовое кондитерское изделие) - наследник класса Product
 */
class Confectionery : public Product {
private:
    /**
     * @brief Вид изделия
     */
    std::string kind_;

    /**
     * @brief Названия магазинов, заказывающих изделие
     */
    std::vector<std::string> shops_;

    /**
     * @brief Произведённое количество (кг)
     */
    double producedKg_;

    /**
     * @brief Дата производства
     */
    Date productionDate_;

protected:
    /**
     * @brief Получить информацию о виде, объёме производства, дате и магазинах
     * @return строка вида "вид: ..., произведено: ... кг, дата: ..., магазины: ..."
     */
    std::string GetSpecificInfo() const override;

public:
    /**
     * @brief Конструктор
     * @param name - название изделия
     * @param pricePerKg - цена за килограмм (руб.)
     * @param category - категория изделия (товар), например "Торты"
     * @param kind - вид изделия, например "Шоколадный"
     * @param producedKg - произведённое количество (кг)
     * @param productionDate - дата производства (по умолчанию 1 сентября 2026 года)
     */
    Confectionery(const std::string& name, const double pricePerKg, const std::string& category,
        const std::string& kind, const double producedKg, const Date& productionDate = Date(2026, 9, 1));

    /**
     * @brief Получить вид изделия
     * @return вид изделия
     */
    const std::string& GetKind() const noexcept;

    /**
     * @brief Получить произведённое количество
     * @return произведённое количество (кг)
     */
    double GetProducedKg() const noexcept;

    /**
     * @brief Получить дату производства
     * @return ссылку на дату производства
     */
    const Date& GetProductionDate() const noexcept;

    /**
     * @brief Получить список магазинов, заказывающих изделие
     * @return ссылку на массив названий магазинов
     */
    const std::vector<std::string>& GetShops() const noexcept;

    /**
     * @brief Добавить магазин, заказывающий изделие (повторно магазин не добавляется)
     * @param shop - название магазина
     */
    void AddShop(const std::string& shop);

    /**
     * @brief Увеличить произведённое количество
     * @param kg - добавляемое количество (кг)
     */
    void AddProduction(const double kg) noexcept;

    /**
     * @brief Получить название типа товара
     * @return строка "Готовое изделие"
     */
    std::string GetKindName() const override;
};
