#include "DynProgProblems.h"
#include "Matrix.h"
#include <print>

// T(n,S) = O(nS), M(n,S) = O(nS), can be reduced to M(n,S) = O(S)
void minimumCoinCountLimited(std::span<const int> coins, const int S) {
    assert(S >= 0);
    const int n = int(coins.size());
    constexpr int infinity = std::numeric_limits<int>::max() - 1; // -1 to avoid overflow later
    Matrix<int> M(n + 1, S + 1, infinity);
    M[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int x = 1; x <= S; ++x) {
            if (coins[i - 1] <= x) {
                M[i][x] = std::min(1 + M[i - 1][x - coins[i - 1]], M[i - 1][x]);
            } else {
                M[i][x] = M[i - 1][x];
            }
        }
    }
    //return M[n][S];

    // (!) std::print("S = {} with coins: {}\n", S, coins);
    if (M[n][S] == infinity) {
        std::print("It's impossible to gather the selected sum with these coins!\n");
    } else {
        std::print("Minimum coin count is {}:", M[n][S]);
        for (int i = n, sum = S; sum != 0; --i) {
            for (const int c : coins) {
                if (M[i][sum] == M[i - 1][sum - c] + 1) {
                    std::print(" {}", c);
                    sum -= c;
                    break;
                }
            }
        }
        std::print("\n\n");
    }
}
