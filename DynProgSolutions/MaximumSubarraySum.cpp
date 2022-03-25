#include "DynProgProblems.h"
#include <fmt/core.h>
#include <fmt/ranges.h>

// T(n) = O(n), M(n) = O(1). The last 3 are used by maximumSubmatrixSum only
void maximumSubarraySum(std::span<const int> values, int* result, int* from, int* to) {
    const int n = int(values.size());
    // Negative values in the beginning of the array can be discarded
    int first = 0;
    while (first < n && values[first] < 0) {
        ++first;
    }
    int bestFrom = first, bestTo = first, currFrom = first;
    int current = values[first], best = values[first];
    if (first == n) {
        // No positive numbers => maximum sum is 0, from the empty subarray
        if (result && from && to) {
            *result = *from = *to = 0;
        }
    } else for (int i = first + 1; i < n; i++) {
        current += values[i];
        if (current < 0) {
            current = 0;
            currFrom = i + 1;
        }
        if (current > best) {
            best = current;
            bestFrom = currFrom;
            bestTo = i;
        }
    }

    if (result && from && to) {
        *result = best;
        *from = bestFrom;
        *to = bestTo;
    } else {
        fmt::print("The maximum subarray sum for the array {} is: {}\n", values, best);
        fmt::print("The subarray starts at index: {} and ends at index: {}\n\n", bestFrom, bestTo);
    }
}
