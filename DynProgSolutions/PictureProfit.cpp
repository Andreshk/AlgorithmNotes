#include "DynProgProblems.h"
#include <print>

// T(n) = O(n), M(n) = O(n)
void pictureProfit(std::span<const int> values) {
    const int n = int(values.size());
    std::vector<int> M(n + 1, 0);
    M[1] = values[0];
    for (int k = 2; k <= n; k++) {
        M[k] = std::max(values[k - 1] + M[k - 2], M[k - 1]);
    }
    // return M[n];

    std::print("The optimal profit is: {}.\n", M[n]);
    std::print("The following pictures are being taken:\n");
    int idx = n;
    while (idx > 0) {
        if (idx == 1 || M[idx] == values[idx - 1] + M[idx - 2]) {
            std::print("[{}]: {}\n", idx, values[idx - 1]);
            idx -= 2;
        } else {
            --idx;
        }
    }
}
