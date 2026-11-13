#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <type_traits>
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
    EXPECT_THROW(Date::Parse("invalid"), std::invalid_argument);
    EXPECT_THROW(Date::Parse("2026-1x-05"), std::invalid_argument);
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

    // Даты до 1970 года тоже сравниваются корректно
    EXPECT_TRUE(Date(1960, 5, 1) < Date(1965, 1, 1));
    EXPECT_EQ(0, Date(1970, 1, 1).ToDayNumber());
    EXPECT_EQ(-1, Date(1969, 12, 31).ToDayNumber());
    EXPECT_EQ(30, Date(2026, 9, 1).DaysUntil(Date(2026, 10, 1)));
}

// ===================== Тесты моделей товаров =====================

TEST(ProductTests, Product_IsAbstractAndStoresBaseData) {
    EXPECT_TRUE(std::is_abstract<Product>::value);

    RawMaterial rm("Какао", 300.0, "Бакалея", "ИмпортТрейд", 50.0);
    Product& baseRef = rm;

    EXPECT_EQ("Какао", baseRef.GetName());
    EXPECT_DOUBLE_EQ(300.0, baseRef.GetPricePerKg());
    EXPECT_EQ("Сырьё", baseRef.GetKindName());
}

TEST(ProductTests, RawMaterial_StoresSupplierAndOrder) {
    RawMaterial rm("Мука", 50.0, "Мучное", "Мельница №1", 100.0);

    EXPECT_EQ("Мука", rm.GetName());
    EXPECT_EQ("Мельница №1", rm.GetSupplierName());
    EXPECT_DOUBLE_EQ(100.0, rm.GetOrderedKg());

    rm.AddOrder(50.0);
    EXPECT_DOUBLE_EQ(150.0, rm.GetOrderedKg());
}

TEST(ProductTests, Confectionery_StoresKindAndShops) {
    Confectionery c("Торт 'Прага'", 600.0, "Торты", "Торт", 80.0);

    EXPECT_EQ("Торт", c.GetKind());
    EXPECT_DOUBLE_EQ(80.0, c.GetProducedKg());

    c.AddShop("Сладкоежка");
    EXPECT_EQ(1u, c.GetShops().size());

    c.AddProduction(20.0);
    EXPECT_DOUBLE_EQ(100.0, c.GetProducedKg());
}

// ===================== Тесты вспомогательных классов =====================

TEST(ShopAndSaleTests, Shop_StoresData) {
    const Shop shop("Сладкоежка", "ул. Ленина, д. 10");
    EXPECT_EQ("Сладкоежка", shop.GetName());
    EXPECT_EQ("ул. Ленина, д. 10", shop.GetAddress());
}

TEST(ShopAndSaleTests, Sale_CalculatesTotalCost) {
    const Sale sale("Торт", "Сладкоежка", 10.0, 600.0, Date(2026, 9, 15));

    EXPECT_DOUBLE_EQ(10.0, sale.GetKg());
    EXPECT_DOUBLE_EQ(600.0, sale.GetPricePerKg());
    EXPECT_DOUBLE_EQ(6000.0, sale.GetTotalCost());
}

// ===================== Тесты Фабрики и Заданий =====================

TEST(FactoryTests, Factory_StoresCollections) {
    ConfectioneryFactory factory("Сладкие Традиции");
    EXPECT_TRUE(factory.GetPolymorphicProducts().empty());

    factory.AddProduct(RawMaterial("Мука", 40.0, "Мучное", "Поставщик1", 500.0));
    factory.AddProduct(Confectionery("Торт", 500.0, "Торты", "Торт", 50.0));

    EXPECT_EQ(2u, factory.GetPolymorphicProducts().size());
}

TEST(FactoryTests, Factory_PolymorphicTraversal) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Сахар", 60.0, "Сахар", "СахарПром", 300.0));
    factory.AddProduct(Confectionery("Печенье", 200.0, "Печенье", "Печенье", 100.0));

    const auto products = factory.GetPolymorphicProducts();
    ASSERT_EQ(2u, products.size());

    EXPECT_EQ("Сырьё", products[0].get().GetKindName());
    EXPECT_EQ("Готовое изделие", products[1].get().GetKindName());
}

TEST(FactoryTests, Factory_FindProductByName) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Мука", 45.0, "Мучное", "Мельница", 500.0));
    factory.AddProduct(Confectionery("Торт", 650.0, "Торты", "Торт", 40.0));

    EXPECT_TRUE(factory.HasProduct("Мука"));
    EXPECT_TRUE(factory.HasProduct("Торт"));
    EXPECT_FALSE(factory.HasProduct("Несуществующий"));

    RawMaterial foundMaterial("", 0.0, "", "", 0.0);
    EXPECT_TRUE(factory.FindProductByName("Мука", foundMaterial));
    EXPECT_EQ("Мельница", foundMaterial.GetSupplierName());
    EXPECT_FALSE(factory.FindProductByName("Торт", foundMaterial));

    Confectionery foundConfectionery("", 0.0, "", "", 0.0);
    EXPECT_TRUE(factory.FindProductByName("Торт", foundConfectionery));
    EXPECT_DOUBLE_EQ(650.0, foundConfectionery.GetPricePerKg());
    EXPECT_FALSE(factory.FindProductByName("Мука", foundConfectionery));
}


TEST(TaskTests, Task1_GetShopsForProduct) {
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


TEST(TaskTests, Task2_GetProductsBySupplier) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Мука 1", 40.0, "Мучное", "Мельница", 500.0));
    factory.AddProduct(RawMaterial("Мука 2", 50.0, "Мучное", "Мельница", 300.0));
    factory.AddProduct(RawMaterial("Сахар", 60.0, "Сахар", "СахарПром", 200.0));

    const std::vector<RawMaterial> result = factory.GetProductsBySupplier("Мельница");
    EXPECT_EQ(2u, result.size());
    EXPECT_EQ("Мука 1", result[0].GetName());
    EXPECT_EQ("Мука 2", result[1].GetName());
}


TEST(TaskTests, Task3_GetAssortmentByCategory) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(RawMaterial("Мука", 45.0, "Мучное", "Мельница", 500.0));
    factory.AddProduct(Confectionery("Торт", 650.0, "Десерты", "Торт", 30.0));
    factory.AddProduct(Confectionery("Печенье", 550.0, "Десерты", "Печенье", 25.0));

    std::vector<RawMaterial> rmAssort;
    factory.GetAssortmentByCategory("Мучное", rmAssort);
    EXPECT_EQ(1u, rmAssort.size());

    std::vector<Confectionery> cfAssort;
    factory.GetAssortmentByCategory("Десерты", cfAssort);
    EXPECT_EQ(2u, cfAssort.size());
}


TEST(TaskTests, Task4_GetMostPopularKind) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(Confectionery("Прага", 650.0, "Торты", "Шоколадный", 50.0));
    factory.AddProduct(Confectionery("Медовик", 520.0, "Торты", "Медовый", 70.0));
    factory.AddProduct(Confectionery("Юбилейное", 180.0, "Печенье", "Сахарное", 300.0));

    // Пока продаж нет, популярный вид не определён
    EXPECT_EQ("", factory.GetMostPopularKind("Торты"));

    factory.AddSale(Sale("Прага", "Сладкоежка", 20.0, 650.0, Date(2026, 9, 5)));
    factory.AddSale(Sale("Прага", "Лакомка", 15.0, 650.0, Date(2026, 9, 6)));
    factory.AddSale(Sale("Медовик", "Лакомка", 30.0, 520.0, Date(2026, 9, 7)));
    factory.AddSale(Sale("Юбилейное", "Сладкоежка", 200.0, 180.0, Date(2026, 9, 8)));

    EXPECT_EQ(4u, factory.GetSales().size());
    EXPECT_EQ("Шоколадный", factory.GetMostPopularKind("Торты"));
    EXPECT_EQ("Сахарное", factory.GetMostPopularKind("Печенье"));
    EXPECT_EQ("", factory.GetMostPopularKind("Конфеты"));
}


TEST(TaskTests, Task5_GetProductionValueInPeriod) {
    ConfectioneryFactory factory("Фабрика");
    factory.AddProduct(Confectionery("Торт", 500.0, "Торты", "Торт", 10.0, Date(2026, 9, 5)));
    factory.AddProduct(Confectionery("Печенье", 200.0, "Печенье", "Печенье", 20.0, Date(2026, 9, 15)));
    factory.AddProduct(Confectionery("Шоколад", 300.0, "Шоколад", "Шоколад", 10.0, Date(2026, 10, 1)));

    const double value = factory.GetProductionValueInPeriod(Date(2026, 9, 1), Date(2026, 9, 30));
    EXPECT_DOUBLE_EQ(9000.0, value);
}
