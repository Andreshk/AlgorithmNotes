#include "DynProgProblems.h"
#include <print>

// T(n) = O(nS), M(n) = O(nS) <- can be reduced to M(n) = O(S)
void Partition(std::span<const int> values) {
    int S = 0;
    for (auto v : values) {
        S += v;
    }
    assert(S % 2 == 0);
    S /= 2;
    const int n = int(values.size());
    Matrix<bool> M(n, S + 1, 0);
    for (int P = 1; P <= S; P++) {
        M[0][P] = (P == values[0]);
    }
    for (int i = 1; i < n; i++) {
        for (int P = 0; P <= S; P++) {
            if (values[i] > P) {
                M[i][P] = M[i - 1][P];
            } else {
                M[i][P] = M[i - 1][P] || M[i - 1][P - values[i]];
            }
        }
    }
    // return M[n - 1][S];

    if (!M[n - 1][S]) {
        // (!) std::print("There is no possible partition for the multiset\n{}\n\n", values);
    } else {
        // (!) std::print("One possible partition for the multiset {}\nis:", values);
        int P = S;
        for (int k = n - 1; k >= 0; --k) {
            if ((k == 0 && M[0][P]) || (P >= values[k] && M[k - 1][P - values[k]])) {
                std::print(" {}", values[k]);
                P -= values[k];
            }
        }
        std::print("\n\n");
    }
}
