#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <vector>

#include "ConfectioneryFactory.h"
#include "FormatUtils.h"

/**
 * @brief Точка входа в программу.
 *
 * @return 0 при успешном завершении.
 */
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Создаём фабрику
    ConfectioneryFactory factory("Кондитерская фабрика 'Сладкие Традиции'");

    // Добавляем магазины
    factory.AddShop(Shop("Сладкоежка", "ул. Ленина, 10"));
    factory.AddShop(Shop("Лакомка", "ул. Пушкина, 5"));

    // Добавляем сырьё (поставщики: Мельница, СахарПром)
    factory.AddProduct(RawMaterial("Мука", 45.0, "Мучное", "Мельница", 1000.0));
    factory.AddProduct(RawMaterial("Сахар", 55.0, "Сахаристое", "СахарПром", 500.0));
    factory.AddProduct(RawMaterial("Какао", 350.0, "Шоколадное", "СахарПром", 200.0));

    // Добавляем готовые изделия
    Confectionery cake("Торт 'Прага'", 650.0, "Торты", "Торт", 150.0, Date(2026, 9, 5));
    cake.AddShop("Сладкоежка");
    cake.AddShop("Лакомка");
    factory.AddProduct(cake);

    Confectionery cookies("Печенье 'Юбилейное'", 180.0, "Печенье", "Печенье", 300.0, Date(2026, 9, 15));
    cookies.AddShop("Сладкоежка");
    factory.AddProduct(cookies);

    // 1. Демонстрация полиморфизма (вывод всех товаров)
    std::cout << "=== Демонстрация полиморфизма (Все товары) ===\n";
    for (const auto& item : factory.GetPolymorphicProducts()) {
        std::cout << "  " << item.get().GetInfo() << '\n';
    }
    std::cout << "\n";

    // 2. Выполнение 5 заданий варианта
    std::cout << "=== Задание 1: Магазины для товара 'Торт 'Прага'' ===\n";
    for (const auto& s : factory.GetShopsForProduct("Торт 'Прага'")) {
        std::cout << "  - " << s << '\n';
    }

    std::cout << "\n=== Задание 2: Продукты у поставщика 'СахарПром' ===\n";
    for (const auto& p : factory.GetProductsBySupplier("СахарПром")) {
        std::cout << "  - " << p.GetName() << " (поставщик: " << p.GetSupplierName() << ")\n";
    }

    std::cout << "\n=== Задание 3: Ассортимент категории 'Печенье' ===\n";
    std::vector<Confectionery> cookiesList;
    factory.GetAssortmentByCategory("Печенье", cookiesList);
    for (const auto& c : cookiesList) {
        std::cout << "  - " << c.GetName() << ", цена: " << FormatUtils::FormatMoney(c.GetPricePerKg()) << '\n';
    }

    std::cout << "\n=== Задание 4: Наиболее популярный вид ===\n";
    std::cout << "  Популярный вид: " << factory.GetMostPopularKind() << '\n';

    std::cout << "\n=== Задание 5: Стоимость произведенного товара за сентябрь ===\n";
    std::cout << "  Итого: " << FormatUtils::FormatMoney(factory.GetProductionValueInPeriod(Date(2026, 9, 1), Date(2026, 9, 30))) << "\n";

    return 0;
}
