#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <vector>

#include "ConfectioneryFactory.h"
#include "FormatUtils.h"

/**
 * @brief Демонстрационная точка входа программы.
 * @return 0 при успешном завершении.
 */
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ConfectioneryFactory factory("Кондитерская фабрика 'Сладкие Традиции'");

    // 1. Создание и регистрация магазинов
    const Shop shop1("Сладкоежка", "ул. Ленина, д. 10");
    const Shop shop2("Кондитерский мир", "пр. Мира, д. 25");
    const Shop shop3("Лакомка", "ул. Пушкина, д. 5");
    factory.AddShop(shop1);
    factory.AddShop(shop2);
    factory.AddShop(shop3);

    // 2. Создание и добавление сырья с именованными параметрами
    const double flourPrice = 45.0;
    const double flourOrderKg = 1000.0;
    const RawMaterial rmFlour("Мука пшеничная в/с", flourPrice, "Мучное", "Мельница №1", flourOrderKg);

    const double sugarPrice = 55.0;
    const double sugarOrderKg = 800.0;
    const RawMaterial rmSugar("Сахар-песок", sugarPrice, "Сахаристое", "СахарПром", sugarOrderKg);

    const double cocoaPrice = 350.0;
    const double cocoaOrderKg = 200.0;
    const RawMaterial rmCocoa("Какао-порошок", cocoaPrice, "Шоколадное", "ИмпортТрейд", cocoaOrderKg);

    factory.AddProduct(rmFlour);
    factory.AddProduct(rmSugar);
    factory.AddProduct(rmCocoa);

    // 3. Создание и добавление готовых кондитерских изделий
    const double praguePrice = 650.0;
    const double pragueProducedKg = 150.0;
    Confectionery cakePrague("Торт 'Прага'", praguePrice, "Торты", "Торт", pragueProducedKg, Date(2026, 9, 5));
    cakePrague.AddShop(shop1.GetName());
    cakePrague.AddShop(shop2.GetName());

    const double jubileePrice = 180.0;
    const double jubileeProducedKg = 500.0;
    Confectionery cookiesJubilee("Печенье 'Юбилейное'", jubileePrice, "Печенье", "Печенье", jubileeProducedKg, Date(2026, 9, 12));
    cookiesJubilee.AddShop(shop2.GetName());
    cookiesJubilee.AddShop(shop3.GetName());

    const double alenkaPrice = 450.0;
    const double alenkaProducedKg = 300.0;
    Confectionery chocolateAlenka("Шоколад 'Алёнка'", alenkaPrice, "Шоколад", "Шоколад", alenkaProducedKg, Date(2026, 9, 18));
    chocolateAlenka.AddShop(shop1.GetName());
    chocolateAlenka.AddShop(shop3.GetName());

    factory.AddProduct(cakePrague);
    factory.AddProduct(cookiesJubilee);
    factory.AddProduct(chocolateAlenka);

    // 4. Фиксация продаж
    const double sale1Kg = 30.0;
    const double sale2Kg = 100.0;
    const double sale3Kg = 50.0;
    factory.AddSale(Sale("Торт 'Прага'", shop1.GetName(), sale1Kg, praguePrice, Date(2026, 9, 10)));
    factory.AddSale(Sale("Печенье 'Юбилейное'", shop2.GetName(), sale2Kg, jubileePrice, Date(2026, 9, 15)));
    factory.AddSale(Sale("Шоколад 'Алёнка'", shop3.GetName(), sale3Kg, alenkaPrice, Date(2026, 9, 20)));

    std::cout << factory.ToString() << "\n\n";

    // 5. Полиморфный вывод всех продуктов фабрики
    std::cout << "=== Все товары фабрики (полиморфный вывод) ===\n";
    for (const auto& item : factory.GetPolymorphicProducts()) {
        std::cout << "  " << item.get().GetInfo() << '\n';
    }

    // Задание 1: список магазинов, заказывающих данный товар
    std::cout << "\n=== Задание 1: Магазины, заказывающие Торт 'Прага' ===\n";
    for (const auto& s : factory.GetShopsForProduct("Торт 'Прага'")) {
        std::cout << "  - " << s << '\n';
    }

    // Задание 2: сырье, заказываемое у конкретного поставщика
    std::cout << "\n=== Задание 2: Сырье от поставщика 'Мельница №1' ===\n";
    for (const auto& m : factory.GetProductsBySupplier("Мельница №1")) {
        std::cout << "  - " << m.GetInfo() << '\n';
    }

    // Задание 3: ассортимент и цены по категории
    std::cout << "\n=== Задание 3: Ассортимент категории 'Торты' ===\n";
    std::vector<Confectionery> cakes;
    factory.GetAssortmentByCategory("Торты", cakes);
    for (const auto& cake : cakes) {
        std::cout << "  - " << cake.GetName() << ": " << FormatUtils::FormatMoney(cake.GetPricePerKg()) << '\n';
    }

    // Задание 4: наиболее популярный вид товара
    std::cout << "\n=== Задание 4: Наиболее популярный вид товара ===\n";
    std::cout << "  Популярный вид: " << factory.GetMostPopularKind() << '\n';

    // Задание 5: стоимость произведенного товара за отчетный период
    const Date periodFrom(2026, 9, 1);
    const Date periodTo(2026, 9, 30);
    const double periodTotal = factory.GetProductionValueInPeriod(periodFrom, periodTo);
    std::cout << "\n=== Задание 5: Стоимость за период 2026-09-01 .. 2026-09-30 ===\n";
    std::cout << "  Итого: " << FormatUtils::FormatMoney(periodTotal) << "\n\n";

    return 0;
}
