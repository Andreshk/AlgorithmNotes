#include "DynProgProblems.h"

// T(n) = O(n^3), M(n) = O(n^2)
void maximumSubmatrixSum(const Matrix<int>& values) {
    const int n = values.rows(), m = values.cols();
    Matrix<int> prefixes(n, m + 1);
    for (int i = 0; i < n; ++i) {
        prefixes[i][0] = 0;
        prefixes[i][1] = values[i][0];
        for (int j = 2; j <= m; ++j)
            prefixes[i][j] = prefixes[i][j - 1] + values[i][j - 1];
    }

    std::vector<int> temp;
    int best = values[0][0];
    int bestTop = 0, bestBottom = 0, bestLeft = 0, bestRight = 0;
    for (int left = 0; left < m; ++left)
        for (int right = left; right < m; ++right) {
            temp.clear();
            temp.resize(n, 0);
            for (int row = 0; row < n; row++)
                temp[row] = prefixes[row][right + 1] - prefixes[row][left];

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
    // return best;

    std::cout << values;
    std::cout << "The maximum submatrix sum is: " << best
              << "\nwith top left corner at [" << bestTop << "][" << bestLeft
              << "] and bottom right corner at [" << bestBottom << "][" << bestRight << "].\n\n";

}
