#include "Task2.h"

namespace miit::algebra {

    Task2::Task2(Matrix<int>& matrix)
        : Exercise{ matrix }
    {
    }

    void Task2::solve()
    {
        if (matrix.getCols() == 0)
        {
            return;
        }

        // идём с конца, чтобы индексы не съезжали при удалении
        for (std::size_t j = matrix.getCols(); j-- > 0;)
        {
            bool hasOddPositive = false;

            for (std::size_t i = 0; i < matrix.getRows(); ++i)
            {
                const int value = matrix[i][j];
                if (value > 0 && value % 2 != 0)
                {
                    hasOddPositive = true;
                    break;
                }
            }

            if (hasOddPositive)
            {
                matrix.removeCol(j);
            }
        }
    }

} // namespace miit::algebra
