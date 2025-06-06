#include "DynProgProblems.h"
#include <mdspan>
// Debugging & visualization only
#include <string>     
#include <print>
#include <algorithm>
#include <ranges>

// T(n) = O(n^3), M(n) = O(n^3), where n^2 is the input size (!)
// Again, can be reduced to M(n) = O(n^2), but without reconstructing the paths
void optimalTwoRobotPath(const Matrix<int>& field) {
    const int n = field.rows(), m = field.cols();
    constexpr int minusInf = std::numeric_limits<int>::min();
    // three dimensions, corresponding to x1,x2 & y2 (y1=x2+y2-x1)
    std::vector<int> arr((n + 1) * (n + 1) * (m + 1), minusInf);
    auto M = std::mdspan{arr.data(), n + 1, n + 1, m + 1};
    for (int x1 = n - 1; x1 >= 0; --x1) {
        for (int x2 = n - 1; x2 >= 0; --x2) {
            for (int y2 = m - 1; y2 >= 0; --y2) {
                const int y1 = x2 + y2 - x1;
                if (y1 < 0 || y1 >= m) { // Not all pairs of positions are possible (!)
                    continue;
                }
                int m = std::max({ M[x1, x2, y2 + 1],
                                   M[x1, x2 + 1, y2],
                                   M[x1 + 1, x2, y2 + 1],
                                   M[x1 + 1, x2 + 1, y2] });
                if (m == minusInf) {
                    m = 0;
                }
                M[x1, x2, y2] = field[x1, y1] + ((x1 == x2) ? 0 : field[x2, y2]) + m;
            }
        }
    }
    // return M[0, 0, 0];
    // Reconstruct both robots' paths:
    std::string r1, r2;
    r1.reserve(n + m - 2);
    r2.reserve(n + m - 2);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (x1 < n && x2 < n && y1 < m && y2 < m) {
        const int tmp = field[x1, y1] + ((x1 == x2) ? 0 : field[x2, y2]);
        if (y1 < m - 1 && y2 < m - 1 && M[x1, x2, y2] == tmp + M[x1, x2, y2 + 1]) {
            ++y1; ++y2; r1 += 'R'; r2 += 'R';
        } else if (y1 < m - 1 && x2 < n - 1 && M[x1, x2, y2] == tmp + M[x1, x2 + 1, y2]) {
            ++y1; ++x2; r1 += 'R'; r2 += 'D';
        } else if (x1 < n - 1 && y2 < m - 1 && M[x1, x2, y2] == tmp + M[x1 + 1, x2, y2 + 1]) {
            ++x1; ++y2; r1 += 'D'; r2 += 'R';
        } else if (x1 < n - 1 && x2 < n - 1 && M[x1, x2, y2] == tmp + M[x1 + 1, x2 + 1, y2]) {
            ++x1; ++x2; r1 += 'D'; r2 += 'D';
        } else {
            break;
        }
    }
    // Pretty-print the matrix better by padding each value
    const size_t pad = std::ranges::max(field | std::views::transform([](const int x) { return std::formatted_size("{}", x); }));
    std::println("{:{}}", field, pad);
    std::println("Maximum profit paths:\n{}\n{}", r1, r2);
    std::println("Maximum profit for two robots: {}.", M[0, 0, 0]);
}