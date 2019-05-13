#include "DynProgProblems.h"

// T(n,S) = O(nS), M(n,S) = O(S)
void minimumCoinCount(const std::vector<int>& coins, const int S) {
    vassert(S >= 0);
    const int infinity = std::numeric_limits<int>::max();
    std::vector<int> M(S + 1, infinity);
    M[0] = 0;
    for (int x = 1; x <= S; x++)
        for (const int c : coins)
            if (c <= x)
                M[x] = std::min(M[x], M[x - c] + 1);
    // return M[S];

    std::cout << "S = " << S << " with coins:";
    for (const int c : coins)
        std::cout << ' ' << c;
    if (M[S] == infinity) {
        std::cout << "\nIt's impossible to gather the selected sum with these coins!\n";
        return;
    } else {
        std::cout << "\nMinimum coin count is " << M[S] << ':';
        int sum = S;
        while (sum) {
            for (const int c : coins)
                if (M[sum] == M[sum - c] + 1) {
                    std::cout << ' ' << c;
                    sum -= c;
                    break;
                }
        }
        std::cout << "\n\n";
    }
}
