#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Generator.h"

namespace miit::algebra {

    /**
     * @brief Двумерный массив (матрица) размера rows x cols
     * @tparam T Тип элементов матрицы
     */
    template <typename T>
    class Matrix {
    private:
        std::vector<std::vector<T>> data;
        std::size_t rows;
        std::size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию
         */
        Matrix();

        /**
         * @brief Конструктор с размером
         * @param rows Количество строк
         * @param cols Количество столбцов
         */
        Matrix(const std::size_t rows, const std::size_t cols);

        /**
         * @brief Конструктор с размером и генератором
         * @param rows Количество строк
         * @param cols Количество столбцов
         * @param generator Генератор
         */
        Matrix(const std::size_t rows, const std::size_t cols, Generator& generator);

        /**
         * @brief Конструктор копирования
         */
        Matrix(const Matrix& other);

        /**
         * @brief Конструктор перемещения
         */
        Matrix(Matrix&& other) noexcept;

        /**
         * @brief Деструктор
         */
        ~Matrix();

        /**
         * @brief Оператор копирующего присваивания
         */
        Matrix& operator=(const Matrix& other);

        /**
         * @brief Оператор перемещающего присваивания
         */
        Matrix& operator=(Matrix&& other) noexcept;

        /**
         * @brief Доступ к строке по индексу
         * @param index Индекс строки
         * @return Ссылка на вектор строки
         */
        std::vector<T>& operator[](const std::size_t index);

        /**
         * @brief Доступ к строке по индексу (константный)
         * @param index Индекс строки
         * @return Константная ссылка на вектор строки
         */
        const std::vector<T>& operator[](const std::size_t index) const;

        /**
         * @brief Циклический сдвиг строк влево
         * @param shift Величина сдвига
         */
        Matrix& operator<<(const std::size_t shift);

        /**
         * @brief Циклический сдвиг строк вправо
         * @param shift Величина сдвига
         */
        Matrix& operator>>(const std::size_t shift);

        /**
         * @brief Количество строк
         */
        std::size_t getRows() const noexcept;

        /**
         * @brief Количество столбцов
         */
        std::size_t getCols() const noexcept;

        /**
         * @brief Заполнить матрицу с помощью генератора
         * @param generator Генератор
         */
        void fill(Generator& generator);

        /**
         * @brief Строковое представление матрицы
         */
        std::string toString() const;

        /**
         * @brief Вставить строку
         * @param index Индекс
         * @param row Строка
         */
        void insertRow(const std::size_t index, const std::vector<T>& row);

        /**
         * @brief Удалить строку
         * @param index Индекс
         */
        void removeRow(const std::size_t index);

        /**
         * @brief Вставить столбец
         * @param index Индекс
         * @param col Столбец
         */
        void insertCol(const std::size_t index, const std::vector<T>& col);

        /**
         * @brief Удалить столбец
         * @param index Индекс
         */
        void removeCol(const std::size_t index);
    };

} // namespace miit::algebra
