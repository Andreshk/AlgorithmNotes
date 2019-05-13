#include "DynProgProblems.h"

// T(n) = O(n*sqrt(n)), M(n) = O(n)
void minimumSquareCount(const int n) {
    const int infinity = std::numeric_limits<int>::max();
    std::vector<int> M(n + 1, infinity);
    M[0] = 0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i*i <= k; i++)
            M[k] = std::min(M[k], M[k - i*i] + 1);
    // return M[n];

    std::cout << "The minimum square count with sum " << n << " is: " << M[n] << '\n';
    int idx = n;
    while (idx > 0) {
        for (int i = 0; i*i <= idx; i++)
            if (M[idx] == M[idx - i*i] + 1) {
                std::cout << i << "^2 ";
                idx -= i*i;
            }
    }
    std::cout << "\n\n";
}
