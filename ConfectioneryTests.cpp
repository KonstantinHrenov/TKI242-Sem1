#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ConfectioneryLib.h"

// ===================== Date =====================

TEST(DateTests, Parse_ValidIsoString_ReturnsCorrectComponents) {
    Date d = Date::Parse("2026-09-22");
    EXPECT_EQ(2026, d.GetYear());
    EXPECT_EQ(9, d.GetMonth());
    EXPECT_EQ(22, d.GetDay());
}

TEST(DateTests, Parse_WrongFormat_ThrowsInvalidArgument) {
    EXPECT_THROW(Date::Parse("22-09-2026"), std::invalid_argument);
}

TEST(DateTests, Parse_MissingDashes_Throws) {
    EXPECT_THROW(Date::Parse("2026/09/22"), std::invalid_argument);
}

TEST(DateTests, Parse_EmptyString_Throws) {
    EXPECT_THROW(Date::Parse(""), std::invalid_argument);
}

TEST(DateTests, Parse_NonNumeric_Throws) {
    EXPECT_THROW(Date::Parse("20aa-09-22"), std::invalid_argument);
}

TEST(DateTests, Constructor_InvalidMonth_Throws) {
    EXPECT_THROW({ Date invalid(2026, 13, 1); (void)invalid; }, std::invalid_argument);
}

TEST(DateTests, Constructor_ZeroMonth_Throws) {
    EXPECT_THROW({ Date invalid(2026, 0, 1); (void)invalid; }, std::invalid_argument);
}

TEST(DateTests, Constructor_InvalidDayForMonth_Throws) {
    EXPECT_THROW({ Date invalid(2026, 2, 30); (void)invalid; }, std::invalid_argument);
}

TEST(DateTests, Constructor_DayZero_Throws) {
    EXPECT_THROW({ Date invalid(2026, 5, 0); (void)invalid; }, std::invalid_argument);
}

TEST(DateTests, Constructor_Day32_Throws) {
    EXPECT_THROW({ Date invalid(2026, 1, 32); (void)invalid; }, std::invalid_argument);
}

TEST(DateTests, DaysUntil_SameDate_ReturnsZero) {
    Date d(2026, 9, 22);
    EXPECT_EQ(0L, d.DaysUntil(d));
}

TEST(DateTests, DaysUntil_OneWeekLater_ReturnsSeven) {
    Date start(2026, 9, 15);
    Date end(2026, 9, 22);
    EXPECT_EQ(7L, start.DaysUntil(end));
}

TEST(DateTests, DaysUntil_OneMonthLater_Returns30) {
    Date start(2026, 8, 23);
    Date end(2026, 9, 22);
    EXPECT_EQ(30L, start.DaysUntil(end));
}

TEST(DateTests, DaysUntil_AcrossYearBoundary_IsCorrect) {
    Date start(2025, 12, 30);
    Date end(2026, 1, 2);
    EXPECT_EQ(3L, start.DaysUntil(end));
}

TEST(DateTests, DaysUntil_Reverse_ReturnsNegative) {
    Date start(2026, 9, 22);
    Date end(2026, 9, 15);
    EXPECT_EQ(-7L, start.DaysUntil(end));
}

TEST(DateTests, ComparisonOperators_WorkAsExpected) {
    Date a(2026, 1, 1);
    Date b(2026, 1, 2);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(DateTests, EqualityOperator_SameDate_True) {
    EXPECT_TRUE(Date(2026, 5, 15) == Date(2026, 5, 15));
}

TEST(DateTests, EqualityOperator_DifferentDay_False) {
    EXPECT_FALSE(Date(2026, 5, 15) == Date(2026, 5, 16));
}

TEST(DateTests, ToString_FormatsWithLeadingZeros) {
    Date d(2026, 3, 5);
    EXPECT_EQ(std::string("2026-03-05"), d.ToString());
}

TEST(DateTests, ToString_DoubleDigits_NoLeadingZero) {
    Date d(2026, 12, 31);
    EXPECT_EQ(std::string("2026-12-31"), d.ToString());
}

TEST(DateTests, LeapYear_February29_IsValid) {
    Date d(2028, 2, 29);
    EXPECT_EQ(29, d.GetDay());
}

TEST(DateTests, NonLeapYear_February29_Throws) {
    EXPECT_THROW({ Date invalid(2026, 2, 29); (void)invalid; }, std::invalid_argument);
}

// ===================== Product =====================

TEST(ProductTests, GetName_ReturnsConstructorValue) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_EQ(std::string("Мука"), r.GetName());
}

TEST(ProductTests, GetPricePerKg_ReturnsConstructorValue) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_DOUBLE_EQ(45.0, r.GetPricePerKg());
}

TEST(ProductTests, GetCategory_ReturnsConstructorValue) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_EQ(std::string("Сыпучее"), r.GetCategory());
}

TEST(ProductTests, SetPricePerKg_ChangesPrice) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    r.SetPricePerKg(50.0);
    EXPECT_DOUBLE_EQ(50.0, r.GetPricePerKg());
}

TEST(ProductTests, SetPricePerKg_ZeroIsAllowed) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    r.SetPricePerKg(0.0);
    EXPECT_DOUBLE_EQ(0.0, r.GetPricePerKg());
}

TEST(ProductTests, GetInfo_IncludesNameAndKind) {
    std::shared_ptr<Product> p = std::make_shared<Confectionery>(
        "Торт «Прага»", 650.0, "Мучная", "Торт", 100.0);
    const std::string info = p->GetInfo();
    EXPECT_NE(std::string::npos, info.find("Торт «Прага»"));
    EXPECT_NE(std::string::npos, info.find("Готовое изделие"));
}

TEST(ProductTests, GetInfo_IncludesCategory) {
    std::shared_ptr<Product> p = std::make_shared<Confectionery>(
        "Торт", 650.0, "Мучная", "Торт", 100.0);
    EXPECT_NE(std::string::npos, p->GetInfo().find("Мучная"));
}

TEST(ProductTests, GetInfo_IncludesPrice) {
    std::shared_ptr<Product> p = std::make_shared<Confectionery>(
        "Торт", 650.0, "Мучная", "Торт", 100.0);
    EXPECT_NE(std::string::npos, p->GetInfo().find("650.00"));
}

// ===================== RawMaterial =====================

TEST(RawMaterialTests, GetKindName_ReturnsSyrye) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_EQ(std::string("Сырьё"), r.GetKindName());
}

TEST(RawMaterialTests, GetSupplierName_ReturnsConstructorValue) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_EQ(std::string("Мельница №1"), r.GetSupplierName());
}

TEST(RawMaterialTests, GetOrderedKg_ReturnsConstructorValue) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    EXPECT_DOUBLE_EQ(100.0, r.GetOrderedKg());
}

TEST(RawMaterialTests, AddOrder_IncreasesOrderedKg) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    r.AddOrder(50.0);
    EXPECT_DOUBLE_EQ(150.0, r.GetOrderedKg());
}

TEST(RawMaterialTests, AddOrder_Twice_Accumulates) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    r.AddOrder(50.0);
    r.AddOrder(25.0);
    EXPECT_DOUBLE_EQ(175.0, r.GetOrderedKg());
}

TEST(RawMaterialTests, AddOrder_Zero_NoChange) {
    RawMaterial r("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0);
    r.AddOrder(0.0);
    EXPECT_DOUBLE_EQ(100.0, r.GetOrderedKg());
}

// ===================== Confectionery =====================

TEST(ConfectioneryTests_, GetKindName_ReturnsGotovoe) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    EXPECT_EQ(std::string("Готовое изделие"), c.GetKindName());
}

TEST(ConfectioneryTests_, GetKind_ReturnsConstructorValue) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    EXPECT_EQ(std::string("Торт"), c.GetKind());
}

TEST(ConfectioneryTests_, GetProducedKg_ReturnsConstructorValue) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    EXPECT_DOUBLE_EQ(100.0, c.GetProducedKg());
}

TEST(ConfectioneryTests_, AddProduction_IncreasesProducedKg) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    c.AddProduction(50.0);
    EXPECT_DOUBLE_EQ(150.0, c.GetProducedKg());
}

TEST(ConfectioneryTests_, AddProduction_Twice_Accumulates) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    c.AddProduction(50.0);
    c.AddProduction(25.0);
    EXPECT_DOUBLE_EQ(175.0, c.GetProducedKg());
}

TEST(ConfectioneryTests_, AddShop_IncreasesShopCount) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    c.AddShop("Пятёрочка");
    c.AddShop("Магнит");
    EXPECT_EQ(static_cast<size_t>(2), c.GetShops().size());
}

TEST(ConfectioneryTests_, AddShop_StoresCorrectNames) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    c.AddShop("Пятёрочка");
    EXPECT_EQ(std::string("Пятёрочка"), c.GetShops()[0]);
}

TEST(ConfectioneryTests_, AddShop_ThreeTimes) {
    Confectionery c("Торт", 650.0, "Мучная", "Торт", 100.0);
    c.AddShop("A");
    c.AddShop("B");
    c.AddShop("C");
    EXPECT_EQ(static_cast<size_t>(3), c.GetShops().size());
}

// ===================== Shop =====================

TEST(ShopTests, GetName_ReturnsConstructorValue) {
    Shop s("Пятёрочка", "ул. Ленина, 5");
    EXPECT_EQ(std::string("Пятёрочка"), s.GetName());
}

TEST(ShopTests, GetAddress_ReturnsConstructorValue) {
    Shop s("Пятёрочка", "ул. Ленина, 5");
    EXPECT_EQ(std::string("ул. Ленина, 5"), s.GetAddress());
}

TEST(ShopTests, GetInfo_ContainsNameAndAddress) {
    Shop s("Пятёрочка", "ул. Ленина, 5");
    const std::string info = s.GetInfo();
    EXPECT_NE(std::string::npos, info.find("Пятёрочка"));
    EXPECT_NE(std::string::npos, info.find("ул. Ленина, 5"));
}

TEST(ShopTests, DifferentShops_DifferentNames) {
    Shop a("A", "addr");
    Shop b("B", "addr");
    EXPECT_NE(a.GetName(), b.GetName());
}

// ===================== Sale =====================

TEST(SaleTests, GetProductName_ReturnsConstructorValue) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    EXPECT_EQ(std::string("Торт"), s.GetProductName());
}

TEST(SaleTests, GetSaleDate_ReturnsConstructorValue) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    EXPECT_EQ(Date(2026, 9, 20), s.GetSaleDate());
}

TEST(SaleTests, GetQuantity_ReturnsConstructorValue) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    EXPECT_EQ(3, s.GetQuantity());
}

TEST(SaleTests, GetTotalPrice_ReturnsConstructorValue) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    EXPECT_DOUBLE_EQ(1950.0, s.GetTotalPrice());
}

TEST(SaleTests, GetInfo_ContainsProductNameAndQuantity) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    const std::string info = s.GetInfo();
    EXPECT_NE(std::string::npos, info.find("Торт"));
    EXPECT_NE(std::string::npos, info.find("3"));
}

TEST(SaleTests, GetInfo_ContainsFormattedDate) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    EXPECT_NE(std::string::npos, s.GetInfo().find("2026-09-20"));
}

TEST(SaleTests, GetInfo_ContainsFormattedPrice) {
    Sale s("Торт", Date(2026, 9, 20), 3, 1950.0);
    EXPECT_NE(std::string::npos, s.GetInfo().find("1950.00"));
}

TEST(SaleTests, ZeroQuantity_Allowed) {
    Sale s("Торт", Date(2026, 9, 20), 0, 0.0);
    EXPECT_EQ(0, s.GetQuantity());
    EXPECT_DOUBLE_EQ(0.0, s.GetTotalPrice());
}

// ===================== ConfectioneryFactory =====================

namespace {
    ConfectioneryFactory BuildSampleFactory() {
        ConfectioneryFactory factory("Тестовая фабрика");
        factory.AddProduct(std::make_shared<RawMaterial>("Мука", 45.0, "Сыпучее", "Мельница №1", 100.0));
        factory.AddProduct(std::make_shared<RawMaterial>("Сахар", 62.0, "Сыпучее", "СахарПром", 50.0));
        factory.AddProduct(std::make_shared<RawMaterial>("Какао", 780.0, "Сыпучее", "СахарПром", 20.0));

        auto cake = std::make_shared<Confectionery>("Торт «Прага»", 650.0, "Мучная", "Торт", 100.0);
        cake->AddShop("Пятёрочка");
        cake->AddShop("Магнит");
        factory.AddProduct(cake);

        auto cookies = std::make_shared<Confectionery>("Печенье", 320.0, "Мучная", "Печенье", 200.0);
        cookies->AddShop("Ашан");
        factory.AddProduct(cookies);

        auto chocolate = std::make_shared<Confectionery>("Шоколад", 890.0, "Шоколадная", "Шоколад", 700.0);
        chocolate->AddShop("Ашан");
        factory.AddProduct(chocolate);

        factory.AddShop(Shop("Пятёрочка", "ул. Ленина, 5"));
        factory.AddShop(Shop("Магнит", "пр. Мира, 12"));
        factory.AddShop(Shop("Ашан", "ТЦ «Мега», 1 этаж"));
        return factory;
    }
}

TEST(ConfectioneryFactoryTests, GetName_ReturnsConstructorValue) {
    ConfectioneryFactory f("Фабрика");
    EXPECT_EQ(std::string("Фабрика"), f.GetName());
}

TEST(ConfectioneryFactoryTests, AddProduct_IncreasesCount) {
    ConfectioneryFactory f("Фабрика");
    f.AddProduct(std::make_shared<RawMaterial>("A", 1.0, "cat", "sup", 1.0));
    f.AddProduct(std::make_shared<RawMaterial>("B", 1.0, "cat", "sup", 1.0));
    EXPECT_EQ(static_cast<size_t>(2), f.GetAllProducts().size());
}

TEST(ConfectioneryFactoryTests, GetAllProducts_ReturnsAllAdded) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(6), f.GetAllProducts().size());
}

TEST(ConfectioneryFactoryTests, GetAllProducts_Empty_ReturnsZero) {
    ConfectioneryFactory f("Пустая");
    EXPECT_EQ(static_cast<size_t>(0), f.GetAllProducts().size());
}

TEST(ConfectioneryFactoryTests, AddShop_IncreasesCount) {
    ConfectioneryFactory f("Фабрика");
    f.AddShop(Shop("A", "addr"));
    f.AddShop(Shop("B", "addr"));
    EXPECT_EQ(static_cast<size_t>(2), f.GetAllShops().size());
}

TEST(ConfectioneryFactoryTests, GetAllShops_ReturnsAllAdded) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(3), f.GetAllShops().size());
}

TEST(ConfectioneryFactoryTests, GetAllShops_Empty_ReturnsZero) {
    ConfectioneryFactory f("Пустая");
    EXPECT_EQ(static_cast<size_t>(0), f.GetAllShops().size());
}

TEST(ConfectioneryFactoryTests, RegisterSale_IncreasesCount) {
    ConfectioneryFactory f("Фабрика");
    f.RegisterSale(Sale("Торт", Date(2026, 9, 20), 3, 1950.0));
    EXPECT_EQ(static_cast<size_t>(1), f.GetAllSales().size());
}

TEST(ConfectioneryFactoryTests, RegisterSale_Twice_IncreasesCount) {
    ConfectioneryFactory f("Фабрика");
    f.RegisterSale(Sale("Торт", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт", Date(2026, 9, 21), 2, 1300.0));
    EXPECT_EQ(static_cast<size_t>(2), f.GetAllSales().size());
}

TEST(ConfectioneryFactoryTests, GetAllSales_Empty_ReturnsZero) {
    ConfectioneryFactory f("Пустая");
    EXPECT_EQ(static_cast<size_t>(0), f.GetAllSales().size());
}

TEST(ConfectioneryFactoryTests, GetShopsForProduct_Existing_ReturnsShops) {
    ConfectioneryFactory f = BuildSampleFactory();
    auto shops = f.GetShopsForProduct("Торт «Прага»");
    ASSERT_EQ(static_cast<size_t>(2), shops.size());
    EXPECT_EQ(std::string("Пятёрочка"), shops[0]);
    EXPECT_EQ(std::string("Магнит"), shops[1]);
}

TEST(ConfectioneryFactoryTests, GetShopsForProduct_Unknown_ReturnsEmpty) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_TRUE(f.GetShopsForProduct("Несуществующий").empty());
}

TEST(ConfectioneryFactoryTests, GetShopsForProduct_CaseInsensitive) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(2), f.GetShopsForProduct("торт «прага»").size());
}

TEST(ConfectioneryFactoryTests, GetShopsForProduct_EmptyFactory_ReturnsEmpty) {
    ConfectioneryFactory f("Пустая");
    EXPECT_TRUE(f.GetShopsForProduct("Торт").empty());
}

TEST(ConfectioneryFactoryTests, GetShopsForProduct_RawMaterial_ReturnsEmpty) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_TRUE(f.GetShopsForProduct("Мука").empty());
}

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_Existing_ReturnsTwo) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(2), f.GetProductsBySupplier("СахарПром").size());
}

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_Unknown_ReturnsEmpty) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_TRUE(f.GetProductsBySupplier("Несуществующий").empty());
}

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_OnlyRawMaterial) {
    ConfectioneryFactory f = BuildSampleFactory();
    auto found = f.GetProductsBySupplier("Мельница №1");
    ASSERT_EQ(static_cast<size_t>(1), found.size());
    EXPECT_EQ(std::string("Мука"), found[0]->GetName());
}

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_CaseInsensitive) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(2), f.GetProductsBySupplier("сахарпром").size());
}

TEST(ConfectioneryFactoryTests, GetProductsBySupplier_EmptyFactory_ReturnsEmpty) {
    ConfectioneryFactory f("Пустая");
    EXPECT_TRUE(f.GetProductsBySupplier("СахарПром").empty());
}

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_Chocolate_ReturnsOne) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(1), f.GetAssortmentByCategory("Шоколадная").size());
}

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_Muchnaya_ReturnsTwo) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(2), f.GetAssortmentByCategory("Мучная").size());
}

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_Sypuchee_ReturnsThree) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(3), f.GetAssortmentByCategory("Сыпучее").size());
}

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_Unknown_ReturnsEmpty) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_TRUE(f.GetAssortmentByCategory("Несуществующая").empty());
}

TEST(ConfectioneryFactoryTests, GetAssortmentByCategory_CaseInsensitive) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(static_cast<size_t>(1), f.GetAssortmentByCategory("шоколадная").size());
}

TEST(ConfectioneryFactoryTests, GetMostPopularKind_ReturnsChocolate) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(std::string("Шоколад"), f.GetMostPopularKind());
}

TEST(ConfectioneryFactoryTests, GetMostPopularKind_Empty_ReturnsEmpty) {
    ConfectioneryFactory f("Пустая");
    EXPECT_EQ(std::string(""), f.GetMostPopularKind());
}

TEST(ConfectioneryFactoryTests, GetTotalProductionCost_MatchesExpectedSum) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_DOUBLE_EQ(752000.0, f.GetTotalProductionCost(ProductionPeriod::Month));
}

TEST(ConfectioneryFactoryTests, GetTotalProductionCost_DayAndYear_Same) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_DOUBLE_EQ(f.GetTotalProductionCost(ProductionPeriod::Day),
        f.GetTotalProductionCost(ProductionPeriod::Year));
}

TEST(ConfectioneryFactoryTests, GetTotalProductionCost_AllPeriodsSame) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_DOUBLE_EQ(f.GetTotalProductionCost(ProductionPeriod::Day),
        f.GetTotalProductionCost(ProductionPeriod::Quarter));
}

TEST(ConfectioneryFactoryTests, GetTotalProductionCost_Empty_ReturnsZero) {
    ConfectioneryFactory f("Пустая");
    EXPECT_DOUBLE_EQ(0.0, f.GetTotalProductionCost(ProductionPeriod::Year));
}

TEST(ConfectioneryFactoryTests, FindProductByName_Existing_ReturnsProduct) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_NE(nullptr, f.FindProductByName("торт «прага»").get());
}

TEST(ConfectioneryFactoryTests, FindProductByName_Missing_ReturnsNullptr) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(nullptr, f.FindProductByName("Несуществующий").get());
}

TEST(ConfectioneryFactoryTests, FindProductByName_CaseInsensitive) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_NE(nullptr, f.FindProductByName("ТОРТ «ПРАГА»").get());
}

TEST(ConfectioneryFactoryTests, FindProductByName_EmptyFactory_ReturnsNullptr) {
    ConfectioneryFactory f("Пустая");
    EXPECT_EQ(nullptr, f.FindProductByName("Торт").get());
}

TEST(ConfectioneryFactoryTests, GetSalesForPeriod_Week_ReturnsRecent) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 8, 15), 5, 3250.0));
    EXPECT_EQ(static_cast<size_t>(1),
        f.GetSalesForPeriod("Торт «Прага»", SalesPeriod::Week, Date(2026, 9, 22)).size());
}

TEST(ConfectioneryFactoryTests, GetSalesForPeriod_Month_IncludesBoth) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 5), 5, 3250.0));
    EXPECT_EQ(static_cast<size_t>(2),
        f.GetSalesForPeriod("Торт «Прага»", SalesPeriod::Month, Date(2026, 9, 22)).size());
}

TEST(ConfectioneryFactoryTests, GetSalesForPeriod_Unknown_ReturnsEmpty) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_TRUE(f.GetSalesForPeriod("Несуществующий", SalesPeriod::Year, Date(2026, 9, 22)).empty());
}

TEST(ConfectioneryFactoryTests, GetSalesForPeriod_CaseInsensitive) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    EXPECT_EQ(static_cast<size_t>(1),
        f.GetSalesForPeriod("торт «прага»", SalesPeriod::Week, Date(2026, 9, 22)).size());
}

TEST(ConfectioneryFactoryTests, GetSalesForPeriod_NoSales_ReturnsEmpty) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_TRUE(f.GetSalesForPeriod("Торт «Прага»", SalesPeriod::Year, Date(2026, 9, 22)).empty());
}

TEST(ConfectioneryFactoryTests, GetTotalQuantitySold_Year_ExcludesOld) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт «Прага»", Date(2024, 5, 1), 1, 650.0));
    EXPECT_EQ(3, f.GetTotalQuantitySold("Торт «Прага»", SalesPeriod::Year, Date(2026, 9, 22)));
}

TEST(ConfectioneryFactoryTests, GetTotalQuantitySold_EmptySales_Zero) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_EQ(0, f.GetTotalQuantitySold("Торт «Прага»", SalesPeriod::Year, Date(2026, 9, 22)));
}

TEST(ConfectioneryFactoryTests, GetTotalQuantitySold_Month_SumAll) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 5), 5, 3250.0));
    EXPECT_EQ(8, f.GetTotalQuantitySold("Торт «Прага»", SalesPeriod::Month, Date(2026, 9, 22)));
}

TEST(ConfectioneryFactoryTests, GetTotalRevenue_Month_MatchesExpected) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 5), 5, 3250.0));
    EXPECT_DOUBLE_EQ(5200.0,
        f.GetTotalRevenue("Торт «Прага»", SalesPeriod::Month, Date(2026, 9, 22)));
}

TEST(ConfectioneryFactoryTests, GetTotalRevenue_EmptySales_Zero) {
    ConfectioneryFactory f = BuildSampleFactory();
    EXPECT_DOUBLE_EQ(0.0,
        f.GetTotalRevenue("Торт «Прага»", SalesPeriod::Year, Date(2026, 9, 22)));
}

TEST(ConfectioneryFactoryTests, GetTotalRevenue_Week_OnlyRecent) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 5), 5, 3250.0));
    EXPECT_DOUBLE_EQ(1950.0,
        f.GetTotalRevenue("Торт «Прага»", SalesPeriod::Week, Date(2026, 9, 22)));
}

TEST(ConfectioneryFactoryTests, GetTotalRevenue_MultipleProducts_OnlyMatching) {
    ConfectioneryFactory f = BuildSampleFactory();
    f.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
    f.RegisterSale(Sale("Печенье", Date(2026, 9, 20), 5, 1600.0));
    EXPECT_DOUBLE_EQ(1950.0,
        f.GetTotalRevenue("Торт «Прага»", SalesPeriod::Week, Date(2026, 9, 22)));
}
