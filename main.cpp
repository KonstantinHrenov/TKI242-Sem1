#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

#include "ConfectioneryLib.h"

namespace {

    enum class MainMenuChoice {
        Exit = 0,
        ShowShopsForProduct = 1,
        ShowProductsBySupplier = 2,
        ShowAssortmentByCategory = 3,
        ShowMostPopularKind = 4,
        ShowProductionCost = 5,
        ShowSalesReport = 6,
        ShowShopsList = 7,
    };

#ifdef _WIN32
    void EnableUtf8Console() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    }
#endif

    void PrintDivider() {
        std::cout << "------------------------------------------------------------\n";
    }

    Date Today() { return Date(2026, 9, 22); }

    std::vector<std::shared_ptr<Product>> CreateDemoProducts() {
        std::vector<std::shared_ptr<Product>> products;

        products.push_back(std::make_shared<RawMaterial>(
            "Мука пшеничная", 45.0, "Сыпучее", "Мельница №1", 5000.0));
        products.push_back(std::make_shared<RawMaterial>(
            "Сахар-песок", 62.0, "Сыпучее", "СахарПром", 3000.0));
        products.push_back(std::make_shared<RawMaterial>(
            "Какао-порошок", 780.0, "Сыпучее", "СахарПром", 200.0));

        auto cake = std::make_shared<Confectionery>(
            "Торт «Прага»", 650.0, "Мучная", "Торт", 250.0);
        cake->AddShop("Пятёрочка");
        cake->AddShop("Магнит");
        products.push_back(cake);

        auto cookies = std::make_shared<Confectionery>(
            "Печенье «Юбилейное»", 320.0, "Мучная", "Печенье", 1800.0);
        cookies->AddShop("Ашан");
        cookies->AddShop("Пятёрочка");
        products.push_back(cookies);

        auto chocolate = std::make_shared<Confectionery>(
            "Шоколад «Горький»", 890.0, "Шоколадная", "Шоколад", 700.0);
        chocolate->AddShop("Ашан");
        products.push_back(chocolate);

        return products;
    }

    ConfectioneryFactory CreateDemoFactory(const std::vector<std::shared_ptr<Product>>& products) {
        ConfectioneryFactory factory("ОАО «Сладкий мир»");
        for (const auto& product : products) factory.AddProduct(product);

        factory.AddShop(Shop("Пятёрочка", "ул. Ленина, 5"));
        factory.AddShop(Shop("Магнит", "пр. Мира, 12"));
        factory.AddShop(Shop("Ашан", "ТЦ «Мега», 1 этаж"));

        factory.RegisterSale(Sale("Торт «Прага»", Date(2026, 9, 20), 3, 1950.0));
        factory.RegisterSale(Sale("Торт «Прага»", Date(2026, 8, 15), 5, 3250.0));
        factory.RegisterSale(Sale("Печенье «Юбилейное»", Date(2026, 9, 19), 20, 6400.0));
        factory.RegisterSale(Sale("Шоколад «Горький»", Date(2026, 9, 10), 10, 8900.0));
        factory.RegisterSale(Sale("Шоколад «Горький»", Date(2025, 12, 1), 8, 7120.0));

        return factory;
    }

    void PrintAllProducts(const std::vector<std::shared_ptr<Product>>& products) {
        PrintDivider();
        std::cout << "Задание 1. Данные о товарах (полиморфный обход):\n";
        PrintDivider();
        for (const auto& product : products) std::cout << product->GetInfo() << "\n";
    }

    void ShowShopsForProduct(const ConfectioneryFactory& factory) {
        std::cout << "Введите название товара: ";
        std::string name;
        std::getline(std::cin, name);
        const auto shops = factory.GetShopsForProduct(name);
        PrintDivider();
        std::cout << "Магазины, заказывающие \"" << name << "\":\n";
        if (shops.empty()) std::cout << "  Ничего не найдено.\n";
        else for (const auto& shop : shops) std::cout << "  • " << shop << "\n";
    }

    void ShowProductsBySupplier(const ConfectioneryFactory& factory) {
        std::cout << "Введите имя поставщика: ";
        std::string supplier;
        std::getline(std::cin, supplier);
        const auto found = factory.GetProductsBySupplier(supplier);
        PrintDivider();
        std::cout << "Продукты у поставщика \"" << supplier << "\":\n";
        if (found.empty()) std::cout << "  Ничего не найдено.\n";
        else for (const auto& p : found) std::cout << "  " << p->GetInfo() << "\n";
    }

    void ShowAssortmentByCategory(const ConfectioneryFactory& factory) {
        std::cout << "Введите категорию товара: ";
        std::string category;
        std::getline(std::cin, category);
        const auto found = factory.GetAssortmentByCategory(category);
        PrintDivider();
        std::cout << "Ассортимент категории \"" << category << "\":\n";
        if (found.empty()) std::cout << "  Ничего не найдено.\n";
        else for (const auto& p : found) std::cout << "  " << p->GetInfo() << "\n";
    }

    void ShowMostPopularKind(const ConfectioneryFactory& factory) {
        PrintDivider();
        std::cout << "Наиболее популярный вид товара: " << factory.GetMostPopularKind() << "\n";
    }

    ProductionPeriod AskProductionPeriod() {
        std::cout << "Выберите период (1 - день, 2 - неделя, 3 - месяц, 4 - квартал, 5 - год): ";
        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: return ProductionPeriod::Day;
        case 2: return ProductionPeriod::Week;
        case 3: return ProductionPeriod::Month;
        case 4: return ProductionPeriod::Quarter;
        case 5: return ProductionPeriod::Year;
        default: return ProductionPeriod::Month;
        }
    }

    void ShowProductionCost(const ConfectioneryFactory& factory) {
        const auto period = AskProductionPeriod();
        PrintDivider();
        std::cout << "Стоимость произведённого за " << ProductionPeriodName(period) << ": "
            << FormatUtils::FormatMoney(factory.GetTotalProductionCost(period))
            << " руб.\n";
    }

    void ShowSalesReport(const ConfectioneryFactory& factory) {
        std::cout << "Введите название товара: ";
        std::string name;
        std::getline(std::cin, name);
        if (!factory.FindProductByName(name)) {
            std::cout << "Товар \"" << name << "\" не найден.\n";
            return;
        }
        const Date today = Today();
        const auto sales = factory.GetSalesForPeriod(name, SalesPeriod::Month, today);
        PrintDivider();
        std::cout << "Продажи \"" << name << "\" за " << SalesPeriodName(SalesPeriod::Month)
            << " (по состоянию на " << today.ToString() << "):\n";
        if (sales.empty()) std::cout << "  Продаж нет.\n";
        else for (const auto& s : sales) std::cout << "  " << s.GetInfo() << "\n";
        std::cout << "Итого: " << factory.GetTotalQuantitySold(name, SalesPeriod::Month, today)
            << " шт. на сумму "
            << FormatUtils::FormatMoney(factory.GetTotalRevenue(name, SalesPeriod::Month, today))
            << " руб.\n";
    }

    void ShowShopsList(const ConfectioneryFactory& factory) {
        PrintDivider();
        std::cout << "Магазины фабрики:\n";
        for (const auto& s : factory.GetAllShops()) std::cout << "  " << s.GetInfo() << "\n";
    }

    void PrintMenu() {
        PrintDivider();
        std::cout << static_cast<int>(MainMenuChoice::ShowShopsForProduct) << " - Магазины, заказывающие товар (Задание 1)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowProductsBySupplier) << " - Продукты у поставщика (Задание 2)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowAssortmentByCategory) << " - Ассортимент по категории (Задание 3)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowMostPopularKind) << " - Самый популярный вид (Задание 4)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowProductionCost) << " - Стоимость произведённого (Задание 5)\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowSalesReport) << " - Продажи за месяц\n";
        std::cout << static_cast<int>(MainMenuChoice::ShowShopsList) << " - Список магазинов\n";
        std::cout << static_cast<int>(MainMenuChoice::Exit) << " - Выход\n";
        std::cout << "Ваш выбор: ";
    }
}

int main() {
#ifdef _WIN32
    EnableUtf8Console();
#endif
    const std::vector<std::shared_ptr<Product>> products = CreateDemoProducts();
    const ConfectioneryFactory factory = CreateDemoFactory(products);

    std::cout << "=== " << factory.GetName() << " ===\n";
    PrintAllProducts(products);

    bool running = true;
    while (running) {
        PrintMenu();
        int choice = -1;
        if (!(std::cin >> choice)) break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (static_cast<MainMenuChoice>(choice)) {
        case MainMenuChoice::ShowShopsForProduct:      ShowShopsForProduct(factory);     break;
        case MainMenuChoice::ShowProductsBySupplier:   ShowProductsBySupplier(factory);  break;
        case MainMenuChoice::ShowAssortmentByCategory: ShowAssortmentByCategory(factory); break;
        case MainMenuChoice::ShowMostPopularKind:      ShowMostPopularKind(factory);     break;
        case MainMenuChoice::ShowProductionCost:       ShowProductionCost(factory);      break;
        case MainMenuChoice::ShowSalesReport:          ShowSalesReport(factory);         break;
        case MainMenuChoice::ShowShopsList:            ShowShopsList(factory);           break;
        case MainMenuChoice::Exit:                     running = false;                  break;
        default: std::cout << "Неизвестный пункт меню.\n"; break;
        }
    }
    std::cout << "Работа программы завершена.\n";
    return 0;
}
