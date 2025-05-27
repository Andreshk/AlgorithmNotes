#include "DynProgProblems.h"
#include <print>

// T(n,W) = O(nW), M(n,W) = O(W)
void Knapsack(std::span<const Item> items, const int W) {
    assert(W >= 0);
    std::vector<int> M(W + 1, 0);
    for (int w = 1; w <= W; ++w) {
        for (const Item& item : items) {
            if (item.weight <= w) {
                M[w] = std::max(M[w], M[w - item.weight] + item.price);
            }
        }
    }
    //return M[W];

    std::println("The optimal profit for weight {} is: {}", W, M[W]);
    std::println("The following items are being used:");
    int w = W;
    while (M[w] != 0) {
        for (const Item& item : items)
            if (item.weight <= w && M[w] == M[w - item.weight] + item.price) {
                std::println("  W: {} C: {}", item.weight, item.price);
                w -= item.weight;
                break;
            }
    }
    std::println("The unused space in the knapsack is: {}.", w);
}
