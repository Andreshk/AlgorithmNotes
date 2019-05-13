#include "DynProgProblems.h"

// T(n,m) = O(nm), M(n,m) = O(nm) <- can be reduced to M(n,m) = O(min{n,m})
void singleRobotPathCount(const Matrix<int>& blocked) {
    const int n = blocked.rows(), m = blocked.cols();
    Matrix<int> M(n, m, 0);
    M[n - 1][m - 1] = blocked[n - 1][m - 1] ? 0 : 1;
    for (int i = n - 2; i >= 0; --i)
        M[i][m - 1] = (!blocked[i][m - 1] && !blocked[i + 1][m - 1]) ? M[i + 1][m - 1] : 0;
    for (int j = m - 2; j >= 0; --j)
        M[n - 1][j] = (!blocked[n - 1][j] && !blocked[n - 1][j + 1]) ? M[n - 1][j + 1] : 0;

    for (int i = n - 2; i >= 0; --i)
        for (int j = m - 2; j >= 0; --j) {
            if (!blocked[i][j] && !blocked[i + 1][j])
                M[i][j] += M[i + 1][j];
            if (!blocked[i][j] && !blocked[i][j + 1])
                M[i][j] += M[i][j + 1];
        }
    //return M[0][0];
    std::cout << blocked;
    std::cout << "The number of paths is " << M[0][0] << ".\n\n";
}
