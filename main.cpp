#ifdef _WIN32
#include <windows.h>
#endif

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "ConfectioneryFactory.h"
#include "FormatUtils.h"

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Объекты типов-наследников: сырьё (поставщики: Мельница, СахарПром)
    const RawMaterial flour("Мука", 45.0, "Мучное", "Мельница", 1000.0);
    const RawMaterial sugar("Сахар", 55.0, "Сахаристое", "СахарПром", 500.0);
    const RawMaterial cocoa("Какао", 350.0, "Шоколадное", "СахарПром", 200.0);

    Confectionery prague("Торт 'Прага'", 650.0, "Торты", "Шоколадный", 150.0, Date(2026, 9, 5));
    prague.AddShop("Сладкоежка");
    prague.AddShop("Лакомка");

    Confectionery honeyCake("Торт 'Медовик'", 520.0, "Торты", "Медовый", 100.0, Date(2026, 9, 10));
    honeyCake.AddShop("Лакомка");

    Confectionery cookies("Печенье 'Юбилейное'", 180.0, "Печенье", "Сахарное", 300.0, Date(2026, 9, 15));
    cookies.AddShop("Сладкоежка");

    const std::vector<std::reference_wrapper<const Product>> products = {
        std::cref(flour), std::cref(sugar), std::cref(cocoa),
        std::cref(prague), std::cref(honeyCake), std::cref(cookies)
    };

    std::cout << "=== Все товары (коллекция базового типа Product) ===\n";
    for (const Product& product : products) {
        std::cout << "  " << product.GetInfo() << '\n';
    }
    std::cout << "\n";

    // Создаём фабрику и заполняем её данными
    ConfectioneryFactory factory("Кондитерская фабрика 'Сладкие Традиции'");

    factory.AddShop(Shop("Сладкоежка", "ул. Ленина, 10"));
    factory.AddShop(Shop("Лакомка", "ул. Пушкина, 5"));

    factory.AddProduct(flour);
    factory.AddProduct(sugar);
    factory.AddProduct(cocoa);
    factory.AddProduct(prague);
    factory.AddProduct(honeyCake);
    factory.AddProduct(cookies);

    // Продажи изделий магазинам
    factory.AddSale(Sale("Торт 'Прага'", "Сладкоежка", 40.0, 650.0, Date(2026, 9, 7)));
    factory.AddSale(Sale("Торт 'Прага'", "Лакомка", 35.0, 650.0, Date(2026, 9, 9)));
    factory.AddSale(Sale("Торт 'Медовик'", "Лакомка", 50.0, 520.0, Date(2026, 9, 12)));
    factory.AddSale(Sale("Печенье 'Юбилейное'", "Сладкоежка", 120.0, 180.0, Date(2026, 9, 18)));

    std::cout << factory.ToString() << "\n\n";

    // Выполнение пяти заданий варианта
    std::cout << "=== Задание 1: Магазины, заказывающие товар 'Торт 'Прага'' ===\n";
    for (const std::string& shop : factory.GetShopsForProduct("Торт 'Прага'")) {
        std::cout << "  - " << shop << '\n';
    }

    std::cout << "\n=== Задание 2: Продукты, заказываемые у поставщика 'СахарПром' ===\n";
    for (const RawMaterial& material : factory.GetProductsBySupplier("СахарПром")) {
        std::cout << "  - " << material.GetName() << " (поставщик: " << material.GetSupplierName() << ")\n";
    }

    std::cout << "\n=== Задание 3: Ассортимент товара 'Торты' и цены ===\n";
    std::vector<Confectionery> cakes;
    factory.GetAssortmentByCategory("Торты", cakes);
    for (const Confectionery& cake : cakes) {
        std::cout << "  - " << cake.GetName() << " (вид: " << cake.GetKind() << "), цена: "
            << FormatUtils::FormatMoney(cake.GetPricePerKg()) << '\n';
    }

    std::cout << "\n=== Задание 4: Наиболее популярный вид товара 'Торты' ===\n";
    std::cout << "  Популярный вид: " << factory.GetMostPopularKind("Торты") << '\n';

    std::cout << "\n=== Задание 5: Стоимость произведенного товара за сентябрь ===\n";
    std::cout << "  Итого: "
        << FormatUtils::FormatMoney(factory.GetProductionValueInPeriod(Date(2026, 9, 1), Date(2026, 9, 30))) << "\n";

    return 0;
}
