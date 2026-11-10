#pragma once

#include "Product.h"
#include "Date.h"
#include <string>
#include <vector>

/**
 * @brief Готовое кондитерское изделие (торт, печенье, шоколад).
 */
class Confectionery : public Product {
public:
    /**
     * @brief Создаёт готовое изделие.
     * @param name Название изделия.
     * @param pricePerKg Цена за килограмм.
     * @param category Категория изделия.
     * @param kind Вид изделия ("Торт", "Печенье", "Шоколад").
     * @param producedKg Произведённое количество (кг).
     * @param productionDate Дата производства партии.
     */
    Confectionery(const std::string& name, double pricePerKg, const std::string& category,
                  const std::string& kind, double producedKg, const Date& productionDate = Date(2026, 9, 1));

    /**
     * @return Вид изделия.
     */
    const std::string& GetKind() const noexcept;

    /**
     * @return Произведённое количество в килограммах.
     */
    double GetProducedKg() const noexcept;

    /**
     * @return Дата производства партии.
     */
    const Date& GetProductionDate() const noexcept;

    /**
     * @return Список магазинов-получателей.
     */
    const std::vector<std::string>& GetShops() const noexcept;

    /**
     * @param shop Название магазина для добавления.
     */
    void AddShop(const std::string& shop);

    /**
     * @param kg Количество килограммов для добавления к производству.
     */
    void AddProduction(double kg) noexcept;

    /**
     * @return Название вида: "Готовое изделие".
     */
    std::string GetKindName() const override;

protected:
    /**
     * @return Описание вида, объёма и магазинов.
     */
    std::string GetSpecificInfo() const override;

private:
    std::string kind_;
    std::vector<std::string> shops_;
    double producedKg_;
    Date productionDate_;
};
