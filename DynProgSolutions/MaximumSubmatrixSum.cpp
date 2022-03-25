#include "DynProgProblems.h"
#include <fmt/core.h>

// T(n) = O(n^3), M(n) = O(n^2)
void maximumSubmatrixSum(const Matrix<int>& values) {
    const int n = values.rows(), m = values.cols();
    Matrix<int> prefixSums(n, m + 1);
    for (int i = 0; i < n; ++i) {
        prefixSums[i][0] = 0;
        prefixSums[i][1] = values[i][0];
        for (int j = 2; j <= m; ++j) {
            prefixSums[i][j] = prefixSums[i][j - 1] + values[i][j - 1];
        }
    }

    std::vector<int> temp(n);
    int best = values[0][0]; // Note: assumes it's nonnegative
    int bestTop = 0, bestBottom = 0, bestLeft = 0, bestRight = 0;
    for (int left = 0; left < m; ++left) {
        for (int right = left; right < m; ++right) {
            for (int row = 0; row < n; row++) {
                temp[row] = prefixSums[row][right + 1] - prefixSums[row][left];
            }
            int current;
            int currTop, currBottom;
            maximumSubarraySum(temp, &current, &currTop, &currBottom);
            if (current > best) {
                best = current;
                bestTop = currTop;
                bestBottom = currBottom;
                bestLeft = left;
                bestRight = right;
            }
        }
    }
    // return best;

    fmt::print("{}\n", values);
    fmt::print("The maximum submatrix sum is: {}\n", best);
    fmt::print("with top left corner at [{}][{}] and bottom right corner at [{}][{}].\n\n",
        bestTop, bestLeft, bestBottom, bestRight);
}
