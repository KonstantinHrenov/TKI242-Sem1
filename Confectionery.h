#pragma once

#include "Product.h"
#include "Date.h"
#include <string>
#include <vector>

/**
 * @brief Готовое кондитерское изделие.
 */
class Confectionery : public Product {
private:
    std::string kind_;
    std::vector<std::string> shops_;
    double producedKg_;
    Date productionDate_;

protected:
    /**
     * @brief Описание вида, веса и магазинов.
     *
     * @return Строка с информацией.
     */
    std::string GetSpecificInfo() const override;

public:
    /**
     * @brief Создаёт готовое изделие.
     *
     * @param name Название изделия.
     * @param pricePerKg Цена за килограмм.
     * @param category Категория.
     * @param kind Вид изделия (Торт, Печенье).
     * @param producedKg Произведённый вес (кг).
     * @param productionDate Дата производства.
     */
    Confectionery(const std::string& name, double pricePerKg, const std::string& category,
        const std::string& kind, double producedKg, const Date& productionDate = Date(2026, 9, 1));

    /**
     * @return Вид изделия.
     */
    const std::string& GetKind() const noexcept;

    /**
     * @return Произведённый вес.
     */
    double GetProducedKg() const noexcept;

    /**
     * @return Дата производства.
     */
    const Date& GetProductionDate() const noexcept;

    /**
     * @return Список магазинов.
     */
    const std::vector<std::string>& GetShops() const noexcept;

    /**
     * @brief Добавляет магазин в список.
     *
     * @param shop Название магазина.
     */
    void AddShop(const std::string& shop);

    /**
     * @brief Увеличивает произведённый вес.
     *
     * @param kg Количество килограммов.
     */
    void AddProduction(double kg) noexcept;

    /**
     * @return Название вида: "Готовое изделие".
     */
    std::string GetKindName() const override;
};
