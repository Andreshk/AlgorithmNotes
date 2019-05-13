#include "DynProgProblems.h"

// T(n,S) = O(nS), M(n,S) = O(nS) <- can be reduced to M(n,S) = O(S)
void nDigitIntegerCount(const int n, const int S) {
    vassert(n > 0 && S >= 0);
    Matrix<int> M(n, S + 1, 0);
    for (int i = 1; i < n; ++i)
        M[i][0] = 0;
    for (int j = 0; j < 10; ++j)
        M[0][j] = 1;
    for (int j = 10; j <= S; ++j)
        M[0][j] = 0;

    for (int k = 1; k < n; k++)
        for (int P = 1; P <= S; P++)
            for (int i = 0; i < 10; i++)
                M[k][P] += M.at(k - 1, P - i);
    // M[n-1][S] if leading zeroes are allowed, M[n-1][S] - M[n-2][S] otherwise
    std::cout << "The number of " << n << "-digit numbers with digit sum " << S << " is " << M[n - 1][S] - M.at(n - 2, S) << ".\n\n";
}
