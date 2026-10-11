#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Product.h"
#include "RawMaterial.h"
#include "Confectionery.h"
#include "Shop.h"
#include "Sale.h"
#include "ProductionPeriod.h"
#include "Date.h"

enum class SalesPeriod {
    Week,
    Month,
    Year
};

inline std::string SalesPeriodName(SalesPeriod period) {
    switch (period) {
    case SalesPeriod::Week:  return "неделю";
    case SalesPeriod::Month: return "месяц";
    case SalesPeriod::Year:  return "год";
    }
    return "период";
}

class ConfectioneryFactory {
public:
    explicit ConfectioneryFactory(const std::string name);

    const std::string& GetName() const;

    void AddProduct(std::shared_ptr<Product> product);
    void AddShop(const Shop& shop);
    void RegisterSale(const Sale& sale);

    const std::vector<std::shared_ptr<Product>>& GetAllProducts() const;
    const std::vector<Shop>& GetAllShops() const;
    const std::vector<Sale>& GetAllSales() const;

    std::shared_ptr<Product> FindProductByName(const std::string& name) const;

    std::vector<std::string> GetShopsForProduct(const std::string& productName) const;
    std::vector<std::shared_ptr<RawMaterial>> GetProductsBySupplier(const std::string& supplierName) const;
    std::vector<std::shared_ptr<Product>> GetAssortmentByCategory(const std::string& category) const;
    std::string GetMostPopularKind() const;
    double GetTotalProductionCost(ProductionPeriod period) const;

    std::vector<Sale> GetSalesForPeriod(const std::string& productName,
        SalesPeriod period,
        const Date& asOf) const;
    int GetTotalQuantitySold(const std::string& productName,
        SalesPeriod period,
        const Date& asOf) const;
    double GetTotalRevenue(const std::string& productName,
        SalesPeriod period,
        const Date& asOf) const;

private:
    std::string name_;
    std::vector<std::shared_ptr<Product>> products_;
    std::vector<Shop> shops_;
    std::vector<Sale> sales_;

    static int PeriodLengthDays(SalesPeriod period);
    bool IsWithinPeriod(const Date& saleDate, const Date& asOf, SalesPeriod period) const;
};
