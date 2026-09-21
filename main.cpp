#include <iostream>
#include <memory>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

int main()
{
    setlocale(LC_ALL, "Russian");

    std::size_t n = 0, m = 0;
    std::cout << "Введите n и m: ";
    std::cin >> n >> m;

    std::cout << "Выберите способ заполнения:\n"
        << "1 - случайными числами\n"
        << "2 - с клавиатуры\n"
        << "3 - константой\n"
        << "Ваш выбор: ";

    int choice = 0;
    std::cin >> choice;

    std::unique_ptr<Generator> generator;

    switch (choice)
    {
    case 1:
        generator = std::make_unique<RandomGenerator>(-100, 100);
        break;
    case 2:
        generator = std::make_unique<IStreamGenerator>(std::cin);
        break;
    case 3:
    {
        int value = 0;
        std::cout << "Введите константу: ";
        std::cin >> value;
        generator = std::make_unique<ConstantGenerator>(value);
        break;
    }
    default:
        std::cout << "Неверный выбор\n";
        return 1;
    }

    Matrix<int> matrix(n, m, *generator);

    std::cout << "\nИсходная матрица:\n" << matrix.toString();

    Task1 task1(matrix);
    task1.solve();
    std::cout << "\nПосле Задания 1 (мин. элемент каждой строки -> 0):\n"
        << matrix.toString();

    Task2 task2(matrix);
    task2.solve();
    std::cout << "\nПосле Задания 2 (удалены столбцы с нечётным положительным):\n"
        << matrix.toString();

    return 0;
}
