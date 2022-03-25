#include "DynProgProblems.h"
#include <fmt/core.h>

// T(n) = O(n), M(n) = O(n)
void pictureProfit(std::span<const int> values) {
    const int n = int(values.size());
    std::vector<int> M(n + 1, 0);
    M[1] = values[0];
    for (int k = 2; k <= n; k++) {
        M[k] = std::max(values[k - 1] + M[k - 2], M[k - 1]);
    }
    // return M[n];

    fmt::print("The optimal profit is: {}.\n", M[n]);
    fmt::print("The following pictures are being taken:\n");
    int idx = n;
    while (idx > 0) {
        if (idx == 1 || M[idx] == values[idx - 1] + M[idx - 2]) {
            fmt::print("[{}]: {}\n", idx, values[idx - 1]);
            idx -= 2;
        } else {
            --idx;
        }
    }
}
