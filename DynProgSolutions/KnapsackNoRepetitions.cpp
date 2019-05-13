#include "DynProgProblems.h"

// T(n,W) = O(nW), M(n,W) = O(nW) <- can be reduced to M(n,W) = O(W)
void KnapsackNoRepetitions(const std::vector<Item>& items, const int W) {
    vassert(W >= 0);
    const int n = int(items.size());
    Matrix<int> M(n + 1, W + 1, 0);
    for (int k = 1; k <= n; ++k)
        for (int P = 1; P <= W; ++P) {
            const Item& item = items[k - 1];
            if (item.weight > P) {
                M[k][P] = M[k - 1][P];
            } else {
                M[k][P] = std::max(M[k - 1][P], M[k - 1][P - item.weight] + item.price);
            }
        }
    //return M[n][W];

    std::cout << "The optimal profit for weight " << W << " is: " << M[n][W]
              << "\nThe following items are being used:\n";
    int P = W;
    for (int k = n; k > 0; --k)
        if (M[k][P] != M[k - 1][P]) {
            const Item& item = items[k - 1];
            std::cout << "  W: " << item.weight << " C: " << item.price << "\n";
            P -= item.weight;
        }
    std::cout << "The unused space in the knapsack is: " << P << ".\n\n";
}