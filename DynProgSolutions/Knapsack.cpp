#include "DynProgProblems.h"

// T(n,W) = O(nW), M(n,W) = O(W)
void Knapsack(const std::vector<Item>& items, const int W) {
    vassert(W >= 0);
    std::vector<int> M(W + 1, 0);
    for (int w = 1; w <= W; ++w)
        for (const Item& item : items)
            if (item.weight <= w)
                M[w] = std::max(M[w], M[w - item.weight] + item.price);
    //return M[W];

    std::cout << "The optimal profit for weight " << W << " is: " << M[W]
              << "\nThe following items are being used:\n";
    int w = W;
    while (M[w] != 0) {
        for (const Item& item : items)
            if (item.weight <= w && M[w] == M[w - item.weight] + item.price) {
                std::cout << "  W: " << item.weight << " C: " << item.price << '\n';
                w -= item.weight;
                break;
            }
    }
    std::cout << "The unused space in the knapsack is: " << w << ".\n\n";
}
