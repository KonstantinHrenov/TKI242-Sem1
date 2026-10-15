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
        Matrix()
            : data{}, rows{ 0 }, cols{ 0 }
        {
        }

        Matrix(const std::size_t rows, const std::size_t cols)
            : data(rows, std::vector<T>(cols)), rows{ rows }, cols{ cols }
        {
        }

        Matrix(const std::size_t rows, const std::size_t cols, const Generator& generator)
            : Matrix(rows, cols)
        {
            fill(generator);
        }

        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;
        ~Matrix() = default;

        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;

        std::vector<T>& operator[](const std::size_t index)
        {
            if (index >= data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            return data[index];
        }

        const std::vector<T>& operator[](const std::size_t index) const
        {
            if (index >= data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            return data[index];
        }

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

        std::size_t getRows() const noexcept { return rows; }
        std::size_t getCols() const noexcept { return cols; }

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

        void removeRow(const std::size_t index)
        {
            if (index >= data.size())
            {
                throw std::out_of_range("Row index out of range");
            }
            data.erase(data.begin() + index);
            --rows;
        }

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
