#include "DynProgProblems.h"

// T(n,k) = O(nk), M(n,k) = O(nk) <- can be reduced to M(n,k) = O(k)
void binomialCoefficient(const int n, const int k) {
    vassert(n > 0 && k > 0);
    Matrix<int> M(n, k, 0);
    for (int i = 0; i < k; i++) M[i][i] = 1;
    for (int i = 0; i < n; i++) M[i][0] = i + 1;

    for (int i = 1; i < n; i++)
        for (int j = 1; j < k && j < i; j++)
            M[i][j] = M[i - 1][j - 1] + M[i - 1][j];
    //return M[n - 1][k - 1];
    std::cout << n << " over " << k << " = " << M[n - 1][k - 1] << "\n\n";
}
