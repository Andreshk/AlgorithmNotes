#include "DynProgProblems.h"
#include <print>
#include <vector>

// T(n,S) = O(nS), M(n,S) = O(S)
void minimumCoinCount(std::span<const int> coins, const int S) {
    assert(S >= 0);
    constexpr int infinity = std::numeric_limits<int>::max();
    std::vector<int> M(S + 1, infinity);
    M[0] = 0;
    for (int x = 1; x <= S; x++) {
        for (const int c : coins) {
            if (c <= x && M[x - c] != infinity) {
                M[x] = std::min(M[x], M[x - c] + 1);
            }
        }
    }
    // return M[S];

    // (!) std::print("S = {} with coins: {}\n", S, coins);
    if (M[S] == infinity) {
        std::println("It's impossible to gather the selected sum with these coins!");
        return;
    } else {
        std::print("Minimum coin count is {}:", M[S]);
        int sum = S;
        while (sum) {
            for (const int c : coins)
                if (M[sum] == M[sum - c] + 1) {
                    std::print(" {}", c);
                    sum -= c;
                    break;
                }
        }
        std::println();
    }
}
