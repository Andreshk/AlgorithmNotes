#include "DynProgProblems.h"
#include <fmt/core.h>

// T(n,m) = O(nm), M(n,m) = O(nm) <- can be reduced to M(n,m) = O(min{n,m})
void optimalSingleRobotPath(const Matrix<int>& field) {
    const int n = field.rows(), m = field.cols();
    const int minusInf = std::numeric_limits<int>::min();
    Matrix<int> M(n, m, minusInf);
    M[n - 1][m - 1] = field[n - 1][m - 1];
    for (int i = n - 2; i >= 0; --i) {
        M[i][m - 1] = M[i + 1][m - 1] + field[i][m - 1];
    }
    for (int j = m - 2; j >= 0; --j) {
        M[n - 1][j] = M[n - 1][j + 1] + field[n - 1][j];
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = m - 2; j >= 0; --j) {
            M[i][j] = field[i][j] + std::max(M[i + 1][j], M[i][j + 1]);
        }
    }
    //return M[0][0];

    fmt::print("{}\n", field);
    fmt::print("Maximum profit path: ");
    int i = 0, j = 0;
    while (true) {
        if (i + 1 < n && M[i][j] == M[i + 1][j] + field[i][j]) {
            fmt::print("D"); ++i;
        } else if (j + 1 < m && M[i][j] == M[i][j + 1] + field[i][j]) {
            fmt::print("R"); ++j;
        } else {
            break; // we have reached the bottom
        }
    }
    fmt::print("\nMaximum profit: {}\n\n", M[0][0]);
}
