#include "DynProgProblems.h"
#include <fmt/core.h>

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

    fmt::print("The optimal profit for weight {} is: {}\n", W, M[W]);
    fmt::print("The following items are being used:\n");
    int w = W;
    while (M[w] != 0) {
        for (const Item& item : items)
            if (item.weight <= w && M[w] == M[w - item.weight] + item.price) {
                fmt::print("  W: {} C: {} \n", item.weight, item.price);
                w -= item.weight;
                break;
            }
    }
    fmt::print("The unused space in the knapsack is: {}.\n\n", w);
}
