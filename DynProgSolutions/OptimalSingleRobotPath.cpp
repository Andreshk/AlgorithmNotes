#include "DynProgProblems.h"

// T(n,m) = O(nm), M(n,m) = O(nm) <- can be reduced to M(n,m) = O(min{n,m})
void optimalSingleRobotPath(const Matrix<int>& field) {
    const int n = field.rows(), m = field.cols();
    const int minusInf = std::numeric_limits<int>::min();
    Matrix<int> M(n, m, minusInf);
    M[n - 1][m - 1] = field[n - 1][m - 1];
    for (int i = n - 2; i >= 0; --i)
        M[i][m - 1] = M[i + 1][m - 1] + field[i][m - 1];
    for (int j = m - 2; j >= 0; --j)
        M[n - 1][j] = M[n - 1][j + 1] + field[n - 1][j];

    for (int i = n - 2; i >= 0; --i)
        for (int j = m - 2; j >= 0; --j) {
            M[i][j] = std::max(M[i][j], M[i + 1][j] + field[i][j]);
            M[i][j] = std::max(M[i][j], M[i][j + 1] + field[i][j]);
        }
    //return M[0][0];

    std::cout << field;
    std::cout << "Maximum profit path: ";
    int i = 0, j = 0;
    while (true) {
        if (i + 1 < n && M[i][j] == M[i + 1][j] + field[i][j]) {
            std::cout << 'D'; ++i;
        } else if (j + 1 < m && M[i][j] == M[i][j + 1] + field[i][j]) {
            std::cout << 'R'; ++j;
        } else {
            break; // we have reached the bottom
        }
    }
    std::cout << "\nMaximum profit: " << M[0][0] << "\n\n";
}
