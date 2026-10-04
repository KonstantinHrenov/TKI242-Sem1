#include <iostream>
#include <memory>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

/**
 * @brief Способ заполнения матрицы
 */
enum class FillMethod {
    Random = 1,
    Manual = 2,
    Constant = 3
};

int main()
{
    setlocale(LC_ALL, "Russian");

    std::size_t n = 0, m = 0;
    std::cout << "Введите n и m: ";
    std::cin >> n >> m;

    std::cout << "Выберите способ заполнения:\n"
              << static_cast<int>(FillMethod::Random)   << " - случайными числами\n"
              << static_cast<int>(FillMethod::Manual)   << " - с клавиатуры\n"
              << static_cast<int>(FillMethod::Constant) << " - константой\n"
              << "Ваш выбор: ";

    int input = 0;
    std::cin >> input;
    const auto choice = static_cast<FillMethod>(input);

    std::unique_ptr<Generator> generator;

    switch (choice)
    {
    case FillMethod::Random:
        generator = std::make_unique<RandomGenerator>(-100, 100);
        break;
    case FillMethod::Manual:
        generator = std::make_unique<IStreamGenerator>(std::cin);
        break;
    case FillMethod::Constant:
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
