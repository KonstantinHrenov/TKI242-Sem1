#pragma once
//
// Confectionery.h
// Класс-наследник "Готовое кондитерское изделие".
//
#include "Product.h"
#include <string>
#include <vector>

/**
 * @brief Готовое кондитерское изделие (торт, печенье, конфеты).
 */
class Confectionery : public Product {
public:
    /**
     * @brief Создаёт готовое изделие.
     */
    Confectionery(const std::string name, const double pricePerKg, const std::string category,
                  const std::string kind, const double producedKg);

    /**
     * @brief Возвращает вид изделия ("Торт", "Печенье" и т.д.).
     */
    const std::string& GetKind() const;

    /**
     * @brief Возвращает произведённое количество (кг).
     */
    double GetProducedKg() const;

    /**
     * @brief Возвращает список магазинов-получателей.
     */
    const std::vector<std::string>& GetShops() const;

    /**
     * @brief Добавляет магазин в список получателей.
     */
    void AddShop(const std::string& shop);

    /**
     * @brief Увеличивает произведённое количество.
     */
    void AddProduction(const double kg);

    /**
     * @brief Возвращает название вида: "Готовое изделие".
     */
    std::string GetKindName() const override;

protected:
    /**
     * @brief Возвращает описание, специфичное для готового изделия.
     */
    std::string GetSpecificInfo() const override;

private:
    /** @brief Вид кондитерского изделия. */
    std::string kind_;
    /** @brief Список магазинов-получателей. */
    std::vector<std::string> shops_;
    /** @brief Произведённое количество (кг). */
    double producedKg_;
};
