#include "DynProgProblems.h"
#include <print>

// T(n,W) = O(nW), M(n,W) = O(nW) <- can be reduced to M(n,W) = O(W)
void KnapsackNoRepetitions(std::span<const Item> items, const int W) {
    assert(W >= 0);
    const int n = int(items.size());
    Matrix<int> M(n + 1, W + 1, 0);
    for (int k = 1; k <= n; ++k) {
        for (int P = 1; P <= W; ++P) {
            const Item& item = items[k - 1];
            if (item.weight > P) {
                M[k, P] = M[k - 1, P];
            } else {
                M[k, P] = std::max(M[k - 1, P], M[k - 1, P - item.weight] + item.price);
            }
        }
    }
    //return M[n, W];

    std::println("The optimal profit for weight {} is: {}", W, M[n, W]);
    std::println("The following items are being used:");
    int P = W;
    for (int k = n; k > 0; --k) {
        if (M[k, P] != M[k - 1, P]) {
            const Item& item = items[k - 1];
            std::println("  W: {} C: {}", item.weight, item.price);
            P -= item.weight;
        }
    }
    std::println("The unused space in the knapsack is: {}.", P);
}