#include "DynProgProblems.h"

// T(n) = O(nS), M(n) = O(nS) <- can be reduced to M(n) = O(S)
void Partition(const std::vector<int>& values) {
    int S = 0;
    for (auto v : values)
        S += v;
    vassert(S % 2 == 0);
    S /= 2;
    const int n = int(values.size());
    // we have to fake booleans with ints, because std::vector<bool> is s#!t
    Matrix<int> M(n, S + 1, 0);
    for (int P = 1; P <= S; P++)
        M[0][P] = (P == values[0]);
    for (int i = 1; i < n; i++)
        for (int P = 0; P <= S; P++)
            if (values[i] > P) {
                M[i][P] = M[i - 1][P];
            } else {
                M[i][P] = M[i - 1][P] || M[i - 1][P - values[i]];
            }
    // return bool(M[n - 1][S]);

    if (!M[n - 1][S]) {
        std::cout << "There is no possible partition for the multiset\n";
        for (auto v : values)
            std::cout << v << ' ';
        std::cout << "\n\n";
    } else {
        std::cout << "One possible partition for the multiset\n";
        for (auto v : values)
            std::cout << v << ' ';
        std::cout << "is:\n";
        int P = S;
        for (int k = n - 1; k >= 0; --k) {
            if ((k == 0 && M[0][P]) || (P >= values[k] && M[k - 1][P - values[k]])) {
                std::cout << values[k] << ' ';
                P -= values[k];
            }
        }
        std::cout << "\n\n";
    }
}
