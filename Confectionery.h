#pragma once
#include "Product.h"
#include <string>
#include <vector>

class Confectionery : public Product {
public:
    Confectionery(std::string name, double pricePerKg, std::string category,
        std::string kind, double producedKg);

    const std::string& GetKind() const;
    double GetProducedKg() const;
    const std::vector<std::string>& GetShops() const;
    void AddShop(const std::string& shop);
    void AddProduction(double kg);

    std::string GetKindName() const override;

protected:
    std::string GetSpecificInfo() const override;

private:
    std::string kind_;
    std::vector<std::string> shops_;
    double producedKg_ = 0.0;
};
