//
// ConfectioneryTests.cpp
// Модульные тесты для варианта "Кондитерская фабрика" (Google Test).
//
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ConfectioneryLib.h"

// ===================== Тесты класса Date =====================

TEST(DateTests, Parse_ValidIsoString_ReturnsCorrectComponents)
{
    Date d = Date::Parse("2026-09-22");
    EXPECT_EQ(2026, d.GetYear());
    EXPECT_EQ(9, d.GetMonth());
    EXPECT_EQ(22, d.GetDay());
}

TEST(DateTests, Parse_WrongFormat_ThrowsInvalidArgument)
{
    EXPECT_THROW(Date::Parse("22-09-2026"), std::invalid_argument);
}

TEST(DateTests, Constructor_InvalidMonth_Throws)
{
    EXPECT_THROW({ Date invalid(2026, 13, 1); (void)invalid; },
        std::invalid_argument);
}

TEST(DateTests, Constructor_InvalidDayForMonth_Throws)
{
    EXPECT_THROW({ Date invalid(2026, 2, 30); (void)invalid; },
        std::invalid_argument);
}

TEST(DateTests, DaysUntil_SameDate_ReturnsZero)
{
    Date d(2026, 9, 22);
    EXPECT_EQ(0L, d.DaysUntil(d));
}

TEST(DateTests, DaysUntil_OneWeekLater_ReturnsSeven)
{
    Date start(2026, 9, 15);
    Date end(2026, 9, 22);
    EXPECT_EQ(7L, start.DaysUntil(end));
}

TEST(DateTests, ComparisonOperators_WorkAsExpected)
{
    Date a(2026, 1, 1);
    Date b(2026, 1, 2);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(DateTests, ToString_FormatsWithLeadingZeros)
{
    Date d(2026, 3, 5);
    EXPECT_EQ(std::string("2026-03-05"), d.ToString());
}

// ============ Тесты Product / RawMaterial / Confectionery ============

TEST(ProductTests, RawMaterial_GetKindName_ReturnsSyrye)
{
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_EQ(std::string("Сырьё"), r.GetKindName());
}

TEST(ProductTests, RawMaterial_Getters_ReturnConstructorValues)
{
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_EQ(std::string("Мельница №1"), r.GetSupplierName());
    EXPECT_DOUBLE_EQ(100.0, r.GetOrderedKg());
}

TEST(ProductTests, RawMaterial_AddOrder_IncreasesOrderedKg)
{
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    r.AddOrder(50.0);
    EXPECT_DOUBLE_EQ(150.0, r.GetOrderedKg());
}

TEST(ProductTests, Confectionery_GetKindName_ReturnsGotovoe)
{
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    EXPECT_EQ(std::string("Готовое изделие"), c.GetKindName());
}

TEST(ProductTests, Confectionery_AddShop_IncreasesShopCount)
{
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    c.AddShop("Пятёрочка");
    c.AddShop("Магнит");
    EXPECT_EQ(static_cast<size_t>(2), c.GetShops().size());
}

TEST(ProductTests, Product_GetInfo_PolymorphicCallIncludesNameAndKind)
{
    std::shared_ptr<Product> p = std::make_shared<Confectionery>(
        "Торт «Прага»", 650.0, "Мучная", "Торт", 100.0);
    const std::string info = p->GetInfo();
    EXPECT_NE(std::string::npos, info.find("Торт «Прага»"));
    EXPECT_NE(std::string::npos, info.find("Готовое изделие"));
}

// ============ Тесты ConfectioneryFactory ============

namespace {

    ConfectioneryFactory BuildSampleFactory()
    {
        ConfectioneryFactory factory("Тестовая фабрика");

        factory.AddProduct(std::make_shared<RawMaterial>(
            "Мука", 45.0, "Сыпучее", "Мельница №1", 100.0));
        factory.AddProduct(std::make_shared<RawMaterial>(
            "Сахар", 62.0, "Сыпучее", "СахарПром", 50.0));
        factory.AddProduct(std::make_shared<RawMaterial>(
            "Какао", 780.0, "Сыпучее", "СахарПром", 20.0));

        auto cake = std::make_shared<Confectionery>(
            "Торт «Прага»", 650.0, "Мучная", "Торт", 100.0);
        cake->AddShop("Пятёрочка");
        cake->AddShop("Магнит");
        factory.AddProduct(cake);

        auto cookies = std::make_shared<Confectionery>(
            "Печенье", 320.0, "Мучная", "Печенье", 200.0);
        cookies->AddShop("Ашан");
        factory.AddProduct(cookies);

        auto chocolate = std::make_shared<Confectionery>(
            "Шоколад", 890.0, "Шоколадная", "Шоколад", 700.0);
        chocolate->AddShop("Ашан");
        factory.AddProduct(chocolate);

        return factory;
    }

}

// ---- Задание 1 ----

TEST(ConfectioneryFactoryTests, GetShopsForProduct_ExistingProduct_ReturnsShops)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto shops = f.GetShopsForProduct("Торт «Прага»");
    ASSERT_EQ(static_cast<size_t>(2), shops.size());
    EXPECT_EQ(std::string("Пятёрочка"), shops[0]);
    EXPECT_EQ(std::string("Магнит"), shops[1]);
}

TEST(ConfectioneryFactoryTests, GetShopsForProduct_UnknownProduct_ReturnsEmpty)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto shops = f.GetShopsForProduct("Несуществующий");
    EXPECT_TRUE(shops.empty());
}

// ---- Задание 2 ----

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_ExistingSupplier_ReturnsTwo)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.GetProductsBySupplier("СахарПром");
    EXPECT_EQ(static_cast<size_t>(2), found.size());
}

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_UnknownSupplier_ReturnsEmpty)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.GetProductsBySupplier("Несуществующий");
    EXPECT_TRUE(found.empty());
}

// ---- Задание 3 ----

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_Chocolate_ReturnsOne)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.GetAssortmentByCategory("Шоколадная");
    EXPECT_EQ(static_cast<size_t>(1), found.size());
}

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_Muchnaya_ReturnsTwo)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.GetAssortmentByCategory("Мучная");
    EXPECT_EQ(static_cast<size_t>(2), found.size());
}

// ---- Задание 4 ----

TEST(ConfectioneryFactoryTests, GetMostPopularKind_ReturnsChocolate)
{
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(std::string("Шоколад"), f.GetMostPopularKind());
}

// ---- Задание 5 ----

TEST(ConfectioneryFactoryTests, GetTotalProductionCost_MatchesExpectedSum)
{
    ConfectioneryFactory f = BuildSampleFactory();
    // Торт:     100 * 650 = 65 000
    // Печенье:  200 * 320 = 64 000
    // Шоколад:  700 * 890 = 623 000
    // Сумма:               = 752 000
    EXPECT_DOUBLE_EQ(752000.0, f.GetTotalProductionCost("month"));
}

// ---- Общие ----

TEST(ConfectioneryFactoryTests, GetAllProducts_ReturnsAllAdded)
{
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(6), f.GetAllProducts().size());
}

TEST(ConfectioneryFactoryTests, FindProductByName_Existing_ReturnsProduct)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.FindProductByName("торт «прага»");
    EXPECT_NE(nullptr, found.get());
}

TEST(ConfectioneryFactoryTests, FindProductByName_Missing_ReturnsNullptr)
{
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.FindProductByName("Несуществующий");
    EXPECT_EQ(nullptr, found.get());
}