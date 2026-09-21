/**
 * @file Task1.cpp
 * @brief Реализация класса Task1
 * @author Student
 * @version 1.0
 * @date 2024
 */

#include "Task1.h"

namespace miit::algebra {

    Task1::Task1(Matrix<int>& matrix)
        : Exercise{ matrix }
    {
    }

    void Task1::solve()
    {
        for (std::size_t i = 0; i < matrix.getRows(); ++i)
        {
            if (matrix.getCols() == 0)
            {
                continue;
            }

            std::size_t minIndex = 0;
            int minValue = matrix[i][0];

            for (std::size_t j = 1; j < matrix.getCols(); ++j)
            {
                if (matrix[i][j] < minValue)
                {
                    minValue = matrix[i][j];
                    minIndex = j;
                }
            }
            matrix[i][minIndex] = 0;
        }
    }

} // namespace miit::algebra
