#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "ConfectioneryFactory.h"
#include "FormatUtils.h"

// ===================== Тесты модели Date =====================

TEST(DateTests, Date_StoresComponents) {
    const Date d(2026, 9, 22);
    EXPECT_EQ(2026, d.GetYear());
    EXPECT_EQ(9, d.GetMonth());
    EXPECT_EQ(22, d.GetDay());
    EXPECT_EQ("2026-09-22", d.ToString());
}

TEST(DateTests, Date_ParseValidAndInvalid) {
    const Date d = Date::Parse("2026-09-22");
    EXPECT_EQ(2026, d.GetYear());
    EXPECT_EQ(9, d.GetMonth());
    EXPECT_EQ(22, d.GetDay());

    EXPECT_THROW(Date::Parse("invalid"), std::invalid_argument);
    EXPECT_THROW(Date::Parse("2026-13-01"), std::invalid_argument);
    EXPECT_THROW(Date(2026, 2, 30), std::invalid_argument);
}

TEST(DateTests, Date_Comparisons) {
    const Date d1(2026, 9, 10);
    const Date d2(2026, 9, 20);
    const Date d3(2026, 9, 10);

    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d2 > d1);
    EXPECT_TRUE(d1 == d3);
    EXPECT_TRUE(d1 != d2);
}

// ===================== Тесты моделей товаров =====================

TEST(ProductTests, Product_StoresData) {
    Product p("Какао", 300.0, "Бакалея");
    EXPECT_EQ("Какао", p.GetName());
    EXPECT_DOUBLE_EQ(300.0, p.GetPricePerKg());
    EXPECT_EQ("Бакалея", p.GetCategory());
    EXPECT_EQ("Товар", p.GetKindName());

    p.SetPricePerKg(320.0);
    EXPECT_DOUBLE_EQ(320.0, p.GetPricePerKg());
}

TEST(ProductTests, RawMaterial_StoresSupplierAndOrder) {
    RawMaterial rm("Мука", 50.0, "Мучное", "Мельница №1", 100.0);
    EXPECT_EQ("Мука", rm.GetName());
    EXPECT_DOUBLE_EQ(50.0, rm.GetPricePerKg());
    EXPECT_EQ("Мельница №1", rm.GetSupplierName());
    EXPECT_DOUBLE_EQ(100.0, rm.GetOrderedKg());
    EXPECT_EQ("Сырьё", rm.GetKindName());

    rm.AddOrder(50.0);
    EXPECT_DOUBLE_EQ(150.0, rm.GetOrderedKg());
    EXPECT_TRUE(rm.GetInfo().find("Мельница №1") != std::string::npos);
}

TEST(ProductTests, Confectionery_StoresKindAndShops) {
    Confectionery c("Торт 'Прага'", 600.0, "Торты", "Торт", 80.0);
    EXPECT_EQ("Торт 'Прага'", c.GetName());
    EXPECT_EQ("Торт", c.GetKind());
    EXPECT_DOUBLE_EQ(80.0, c.GetProducedKg());
    EXPECT_EQ("Готовое изделие", c.GetKindName());

    c.AddShop("Сладкоежка");
    c.AddShop("сладкоежка");
    c.AddShop("Лакомка");
    EXPECT_EQ(2u, c.GetShops().size());

    c.AddProduction(20.0);
    EXPECT_DOUBLE_EQ(100.0, c.GetProducedKg());
}

// ===================== Тесты Shop и Sale =====================

TEST(ShopAndSaleTests, Shop_StoresData) {
    const Shop shop("Сладкоежка", "ул. Ленина, д. 10");
    EXPECT_EQ("Сладкоежка", shop.GetName());
    EXPECT_EQ("ул. Ленина, д. 10", shop.GetAddress());
}

TEST(ShopAndSaleTests, Sale_CalculatesTotalCost) {
    const Sale sale("Торт 'Прага'", "Сладкоежка", 10.0, 600.0, Date(2026, 9, 15));
    EXPECT_EQ("Торт 'Прага'", sale.GetProductName());
    EXPECT_EQ("Сладкоежка", sale.GetShopName());
    EXPECT_DOUBLE_EQ(10.0, sale.GetKg());
    EXPECT_DOUBLE_EQ(600.0, sale.GetPricePerKg());
    EXPECT_DOUBLE_EQ(6000.0, sale.GetTotalCost());
    EXPECT_EQ(Date(2026, 9, 15), sale.GetDate());
}

// ===================== Тесты ConfectioneryFactory =====================

TEST(FactoryTests, Factory_StoresCollections) {
    ConfectioneryFactory factory("Сладкие Традиции");
    EXPECT_EQ("Сладкие Традиции", factory.GetName());
    EXPECT_TRUE(factory.GetAllProducts().empty());
    EXPECT_TRUE(factory.GetRawMaterials().empty());
    EXPECT_TRUE(factory.GetConfectioneries().empty());

    factory.AddProduct(RawMaterial("Мука", 40.0, "Мучное", "Поставщик1", 500.0));
    factory.AddProduct(Confectionery("Торт", 500.0, "Торты", "Торт", 50.0));

    EXPECT_EQ(2u, factory.GetAllProducts().size());
    EXPECT_EQ(1u, factory.GetRawMaterials().size());
    EXPECT_EQ(1u, factory.GetConfectioneries().size());
}

TEST(FactoryTests, Factory_PolymorphicTraversal) {
    ConfectioneryFactory factory("Фабрика");

    const RawMaterial rm("Сахар", 60.0, "Сахар", "СахарПром", 300.0);
    const Confectionery cf("Печенье", 200.0, "Печенье", "Печенье", 100.0);
    factory.AddProduct(rm);
    factory.AddProduct(cf);

    const auto products = factory.GetPolymorphicProducts();
    ASSERT_EQ(2u, products.size());

    EXPECT_EQ("Сырьё", products[0].get().GetKindName());
    EXPECT_EQ("Готовое изделие", products[1].get().GetKindName());
    EXPECT_TRUE(products[0].get().GetInfo().find("СахарПром") != std::string::npos);
    EXPECT_TRUE(products[1].get().GetInfo().find("Печенье") != std::string::npos);
}

TEST(FactoryTests, Factory_FindProductByName_Overloads) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Мука", 45.0, "Мучное", "Мельница", 500.0));
    factory.AddProduct(Confectionery("Торт 'Прага'", 650.0, "Торты", "Торт", 40.0));

    RawMaterial rmFound("x", 0, "x", "x", 0);
    EXPECT_TRUE(factory.FindProductByName("Мука", rmFound));
    EXPECT_EQ("Мельница", rmFound.GetSupplierName());

    Confectionery cfFound("x", 0, "x", "x", 0);
    EXPECT_TRUE(factory.FindProductByName("Торт 'Прага'", cfFound));
    EXPECT_EQ("Торт", cfFound.GetKind());

    Product prodFound("x", 0, "x");
    EXPECT_TRUE(factory.FindProductByName("Мука", prodFound));
    EXPECT_EQ("Мука", prodFound.GetName());

    EXPECT_TRUE(factory.HasProduct("Мука"));
    EXPECT_FALSE(factory.HasProduct("Несуществующий"));
}

TEST(FactoryTests, Factory_GetProductsBySupplier) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Мука 1 сорт", 40.0, "Мучное", "Мельница", 500.0));
    factory.AddProduct(RawMaterial("Мука в/с", 50.0, "Мучное", "Мельница", 300.0));
    factory.AddProduct(RawMaterial("Сахар", 60.0, "Сахар", "СахарПром", 200.0));

    const std::vector<RawMaterial> result = factory.GetProductsBySupplier("Мельница");
    EXPECT_EQ(2u, result.size());
    EXPECT_EQ("Мука 1 сорт", result[0].GetName());
    EXPECT_EQ("Мука в/с", result[1].GetName());
}

TEST(FactoryTests, Factory_GetAssortmentByCategory_Overloads) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Мука", 45.0, "Мучное", "Мельница", 500.0));
    factory.AddProduct(Confectionery("Торт 'Прага'", 650.0, "Десерты", "Торт", 30.0));
    factory.AddProduct(Confectionery("Торт 'Сказка'", 550.0, "Десерты", "Торт", 25.0));

    std::vector<RawMaterial> rmAssort;
    factory.GetAssortmentByCategory("Мучное", rmAssort);
    EXPECT_EQ(1u, rmAssort.size());

    std::vector<Confectionery> cfAssort;
    factory.GetAssortmentByCategory("Десерты", cfAssort);
    EXPECT_EQ(2u, cfAssort.size());
}

TEST(FactoryTests, Factory_Task1_GetShopsForProduct) {
    ConfectioneryFactory factory("Фабрика");
    Confectionery c("Торт 'Прага'", 650.0, "Торты", "Торт", 50.0);
    c.AddShop("Сладкоежка");
    c.AddShop("Лакомка");
    factory.AddProduct(c);

    const auto shops = factory.GetShopsForProduct("Торт 'Прага'");
    EXPECT_EQ(2u, shops.size());
    EXPECT_EQ("Сладкоежка", shops[0]);
    EXPECT_EQ("Лакомка", shops[1]);
}

TEST(FactoryTests, Factory_Task4_GetMostPopularKind) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(Confectionery("Торт 'Прага'", 650.0, "Торты", "Торт", 50.0));
    factory.AddProduct(Confectionery("Печенье 'Юбилейное'", 180.0, "Печенье", "Печенье", 100.0));

    EXPECT_EQ("Печенье", factory.GetMostPopularKind());
}

TEST(FactoryTests, Factory_Task5_GetProductionValueInPeriod) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(Confectionery("Торт", 500.0, "Торты", "Торт", 10.0, Date(2026, 9, 5)));
    factory.AddProduct(Confectionery("Печенье", 200.0, "Печенье", "Печенье", 20.0, Date(2026, 9, 15)));
    factory.AddProduct(Confectionery("Шоколад", 300.0, "Шоколад", "Шоколад", 10.0, Date(2026, 10, 1)));

    const double value = factory.GetProductionValueInPeriod(Date(2026, 9, 1), Date(2026, 9, 30));
    EXPECT_DOUBLE_EQ(9000.0, value);
}
