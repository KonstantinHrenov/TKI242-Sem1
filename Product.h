#pragma once
#include <string>

class Product {
public:
    Product(std::string name, double pricePerKg, std::string category);
    virtual ~Product() = default;

    const std::string& GetName() const;
    double GetPricePerKg() const;
    const std::string& GetCategory() const;
    void SetPricePerKg(double price);

    virtual std::string GetKindName() const = 0;
    virtual std::string GetInfo() const;

protected:
    virtual std::string GetSpecificInfo() const = 0;

private:
    std::string name_;
    double pricePerKg_ = 0.0;
    std::string category_;
};
