#include "DynProgProblems.h"
#include <print>
#include <algorithm> // std::ranges::{max,max_element}

// T(n) = O(n^2), M(n) = O(n)
void longestIncreasingSubsequence(std::span<const int> values) {
    /* Note:
     * building a graph leads to T(n) = O(n^2), but M(n) = O(n+m),
     * since the process is always slow and we need additional memory
     * Without a graph (using the implicit one) we have T(n) = O(n^2)
     * still, but M(n) = O(n) only.
     */
    const int count = int(values.size());
    std::vector<int> M(count), successors(count);
    for (int i = count - 1; i >= 0; --i) {
        M[i] = 1;
        successors[i] = count;
        for (int j = i + 1; j < count; j++) {
            if (values[i] < values[j] && M[i] < M[j] + 1) {
                M[i] = M[j] + 1;
                successors[i] = j;
            }
        }
    }
    //return std::ranges::max(M);

    // Find the maximum value
    const int maxIdx = int(std::distance(M.begin(), std::ranges::max_element(M)));
    // (!) std::print("Longest increasing subsequence of {}\nis:", values);
    int nextIdx = maxIdx;
    while (nextIdx != count) {
        std::print(" {}", values[nextIdx]);
        nextIdx = successors[nextIdx];
    }
    std::print("\nLength = {} \n\n", M[maxIdx]);
}
