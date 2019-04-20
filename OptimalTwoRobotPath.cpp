#include "DynProgProblems.h"
#include <string>

// T(n) = O(n^3), M(n) = O(n^2), където n^2 е фголемината на входа (!)
void optimalTwoRobotPath(const Matrix<int>& field) {
    std::cout << field;
    const int n = field.rows(), m = field.cols();
    const int minusInf = std::numeric_limits<int>::min();
    // тримерна матрица с измерения, отговарящи на x1,x2 и y2 (y1=x2+y2-x1)
    std::vector<Matrix<int>> M(n, Matrix<int>(n, m, minusInf));
    // за "сигурен" достъп в матрицата (но доста бавен...)
    auto get = [=, &M](int x1, int x2, int y2) {
        return (x1 < n && x2 < n && y2 < m) ? M[x1][x2][y2] : minusInf;
    };
    for (int x1 = n - 1; x1 >= 0; --x1)
        for (int x2 = n - 1; x2 >= 0; --x2)
            for (int y2 = m - 1; y2 >= 0; --y2) {
                const int y1 = x2 + y2 - x1;
                if (y1 < 0 || y1 >= m) // Не всички двойки позиции са възможни (!)
                    continue;
                int m = max(get(x1, x2, y2 + 1),
                    get(x1, x2 + 1, y2),
                    get(x1 + 1, x2, y2 + 1),
                    get(x1 + 1, x2 + 1, y2));
                if (m == minusInf)
                    m = 0;
                M[x1][x2][y2] = field[x1][y1] + ((x1 == x2) ? 0 : field[x2][y2]) + m;
            }

    std::string r1, r2;
    r1.reserve(n + m - 2);
    r2.reserve(n + m - 2);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (x1 < n && x2 < n && y1 < m && y2 < m) {
        int tmp = field[x1][y1] + ((x1 == x2) ? 0 : field[x2][y2]);
        if (y1 < m - 1 && y2 < m - 1 && M[x1][x2][y2] == tmp + M[x1][x2][y2 + 1]) {
            ++y1; ++y2; r1 += 'R'; r2 += 'R';
        } else if (y1 < m - 1 && x2 < n - 1 && M[x1][x2][y2] == tmp + M[x1][x2 + 1][y2]) {
            ++y1; ++x2; r1 += 'R'; r2 += 'D';
        } else if (x1 < n - 1 && y2 < m - 1 && M[x1][x2][y2] == tmp + M[x1 + 1][x2][y2 + 1]) {
            ++x1; ++y2; r1 += 'D'; r2 += 'R';
        } else if (x1 < n - 1 && x2 < n - 1 && M[x1][x2][y2] == tmp + M[x1 + 1][x2 + 1][y2]) {
            ++x1; ++x2; r1 += 'D'; r2 += 'D';
        } else {
            break;
        }
    }
    std::cout << "Maximum profit paths:\n" << r1 << "\n" << r2 << "\n";
    std::cout << "Maximum profit for two robots: " << M[0][0][0] << "\n\n";
}