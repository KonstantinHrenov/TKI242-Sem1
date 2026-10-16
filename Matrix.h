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
        /**
         * @brief Данные матрицы — вектор строк
         */
        std::vector<std::vector<T>> data;

        /**
         * @brief Количество строк
         */
        std::size_t rows;

        /**
         * @brief Количество столбцов
         */
        std::size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию. Создаёт пустую матрицу 0x0
         */
        Matrix()
            : data{}, rows{ 0 }, cols{ 0 }
        {
        }

        /**
         * @brief Конструктор с заданным размером
         * @param rows Количество строк
         * @param cols Количество столбцов
         * @note Элементы инициализируются значением по умолчанию T()
         */
        Matrix(const std::size_t rows, const std::size_t cols)
            : data(rows, std::vector<T>(cols)), rows{ rows }, cols{ cols }
        {
        }

        /**
         * @brief Конструктор с размером и генератором
         * @param rows Количество строк
         * @param cols Количество столбцов
         * @param generator Генератор для заполнения матрицы
         */
        Matrix(const std::size_t rows, const std::size_t cols, const Generator& generator)
            : Matrix(rows, cols)
        {
            fill(generator);
        }

        /**
         * @brief Конструктор копирования
         * @param other Матрица для копирования
         */
        Matrix(const Matrix& other) = default;

        /**
         * @brief Конструктор перемещения
         * @param other Матрица для перемещения
         */
        Matrix(Matrix&& other) noexcept = default;

        /**
         * @brief Деструктор
         */
        ~Matrix() = default;

        /**
         * @brief Оператор копирующего присваивания
         * @param other Матрица для копирования
         * @return Ссылка на текущий объект
         */
        Matrix& operator=(const Matrix& other) = default;

        /**
         * @brief Оператор перемещающего присваивания
         * @param other Матрица для перемещения
         * @return Ссылка на текущий объект
         */
        Matrix& operator=(Matrix&& other) noexcept = default;

        /**
         * @brief Доступ к строке матрицы по индексу (неконстантный)
         * @param index Индекс строки
         * @return Ссылка на вектор строки
         * @throws std::out_of_range если индекс вне допустимого диапазона
         */
        std::vector<T>& operator[](const std::size_t index)
        {
            if (index >= data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            return data[index];
        }

        /**
         * @brief Доступ к строке матрицы по индексу (константный)
         * @param index Индекс строки
         * @return Константная ссылка на вектор строки
         * @throws std::out_of_range если индекс вне допустимого диапазона
         */
        const std::vector<T>& operator[](const std::size_t index) const
        {
            if (index >= data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            return data[index];
        }

        /**
         * @brief Циклический сдвиг каждой строки влево
         * @param shift Величина сдвига
         * @return Ссылка на текущий объект
         */
        Matrix& operator<<(const std::size_t shift)
        {
            if (cols == 0) return *this;
            const std::size_t s = shift % cols;
            for (auto& row : data)
            {
                std::rotate(row.begin(), row.begin() + s, row.end());
            }
            return *this;
        }

        /**
         * @brief Циклический сдвиг каждой строки вправо
         * @param shift Величина сдвига
         * @return Ссылка на текущий объект
         */
        Matrix& operator>>(const std::size_t shift)
        {
            if (cols == 0) return *this;
            const std::size_t s = shift % cols;
            for (auto& row : data)
            {
                std::rotate(row.begin(), row.end() - s, row.end());
            }
            return *this;
        }

        /**
         * @brief Получить количество строк в матрице
         * @return Количество строк
         */
        std::size_t getRows() const noexcept
        {
            return rows;
        }

        /**
         * @brief Получить количество столбцов в матрице
         * @return Количество столбцов
         */
        std::size_t getCols() const noexcept
        {
            return cols;
        }

        /**
         * @brief Заполнить матрицу с помощью генератора
         * @param generator Генератор значений
         */
        void fill(const Generator& generator)
        {
            for (auto& row : data)
            {
                for (auto& element : row)
                {
                    element = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Преобразовать матрицу в строку
         * @return Строковое представление матрицы
         */
        std::string toString() const
        {
            std::ostringstream out;
            for (const auto& row : data)
            {
                for (const auto& element : row)
                {
                    out << element << ' ';
                }
                out << '\n';
            }
            return out.str();
        }

        /**
         * @brief Вставить строку по указанному индексу
         * @param index Индекс, куда вставить строку
         * @param row Вставляемая строка
         * @throws std::invalid_argument если размер строки не совпадает с количеством столбцов
         * @throws std::out_of_range если индекс вне допустимого диапазона
         */
        void insertRow(const std::size_t index, const std::vector<T>& row)
        {
            if (row.size() != cols)
            {
                throw std::invalid_argument("Row size mismatch");
            }
            if (index > data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            data.insert(data.begin() + index, row);
            ++rows;
        }

        /**
         * @brief Удалить строку по указанному индексу
         * @param index Индекс строки
         * @throws std::out_of_range если индекс вне допустимого диапазона
         */
        void removeRow(const std::size_t index)
        {
            if (index >= data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            data.erase(data.begin() + index);
            --rows;
        }

        /**
         * @brief Вставить столбец по указанному индексу
         * @param index Индекс, куда вставить столбец
         * @param col Вставляемый столбец
         * @throws std::invalid_argument если размер столбца не совпадает с количеством строк
         * @throws std::out_of_range если индекс вне допустимого диапазона
         */
        void insertCol(const std::size_t index, const std::vector<T>& col)
        {
            if (col.size() != rows)
            {
                throw std::invalid_argument("Col size mismatch");
            }
            if (index > cols)
            {
                throw std::out_of_range("Col index out of range");
            }
            for (std::size_t i = 0; i < rows; ++i)
            {
                data[i].insert(data[i].begin() + index, col[i]);
            }
            ++cols;
        }

        /**
         * @brief Удалить столбец по указанному индексу
         * @param index Индекс столбца
         * @throws std::out_of_range если индекс вне допустимого диапазона
         */
        void removeCol(const std::size_t index)
        {
            if (index >= cols)
            {
                throw std::out_of_range("Col index out of range");
            }
            for (auto& row : data)
            {
                row.erase(row.begin() + index);
            }
            --cols;
        }
    };

} // namespace miit::algebra
