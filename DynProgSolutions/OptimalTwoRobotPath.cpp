#include "DynProgProblems.h"
#include <string>
#include <fmt/core.h>

// T(n) = O(n^3), M(n) = O(n^3), where n^2 is the input size (!)
// Again, can be reduced to M(n) = O(n^2), but without reconstructing the paths
void optimalTwoRobotPath(const Matrix<int>& field) {
    const int n = field.rows(), m = field.cols();
    constexpr int minusInf = std::numeric_limits<int>::min();
    // three dimensions, corresponding to x1,x2 & y2 (y1=x2+y2-x1)
    std::vector<Matrix<int>> M(n, Matrix<int>(n, m, minusInf));
    // for safe (but slow) accessing
    auto get = [=, &M](int x1, int x2, int y2) {
        return (x1 < n && x2 < n && y2 < m) ? M[x1][x2][y2] : minusInf;
    };
    for (int x1 = n - 1; x1 >= 0; --x1) {
        for (int x2 = n - 1; x2 >= 0; --x2) {
            for (int y2 = m - 1; y2 >= 0; --y2) {
                const int y1 = x2 + y2 - x1;
                if (y1 < 0 || y1 >= m) { // Not all pairs of positions are possible (!)
                    continue;
                }
                int m = std::max(std::max(get(x1, x2, y2 + 1),
                                          get(x1, x2 + 1, y2)),
                                 std::max(get(x1 + 1, x2, y2 + 1),
                                          get(x1 + 1, x2 + 1, y2)));
                if (m == minusInf) {
                    m = 0;
                }
                M[x1][x2][y2] = field[x1][y1] + ((x1 == x2) ? 0 : field[x2][y2]) + m;
            }
        }
    }
    // return M[0][0][0];
    // Reconstruct both robots' paths:
    std::string r1, r2;
    r1.reserve(n + m - 2);
    r2.reserve(n + m - 2);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (x1 < n && x2 < n && y1 < m && y2 < m) {
        const int tmp = field[x1][y1] + ((x1 == x2) ? 0 : field[x2][y2]);
        if (y1 < m - 1 && y2 < m - 1 && M[x1][x2][y2] == tmp + M[x1][x2][y2 + 1]) {
            ++y1; ++y2; r1 += 'R'; r2 += 'R';
        } else if (y1 < m - 1 && x2 < n - 1 && M[x1][x2][y2] == tmp + M[x1][x2 + 1][y2]) {
            ++y1; ++x2; r1 += 'R'; r2 += 'D';
        } else if (x1 < n - 1 && y2 < m - 1 && M[x1][x2][y2] == tmp + M[x1 + 1][x2][y2 + 1]) {
            ++x1; ++y2; r1 += 'D'; r2 += 'R';
        } else if (x1 < n - 1 && x2 < n - 1 && M[x1][x2][y2] == tmp + M[x1 + 1][x2 + 1][y2]) {
            ++x1; ++x2; r1 += 'D'; r2 += 'D';
        } else {
            break;
        }
    }
    // Pretty-print the matrix better by padding each value
    size_t pad = 1;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            pad = std::max(pad, fmt::formatted_size("{}", field[row][col]));
        }
    }
    fmt::print("{:{}}\n", field, pad);
    fmt::print("Maximum profit paths:\n{}\n{}\n", r1, r2);
    fmt::print("Maximum profit for two robots: {}.\n\n", M[0][0][0]);
}