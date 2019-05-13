#include "DynProgProblems.h"

// T(n) = O(n), M(n) = O(1). The last 3 should inly be used by MaximumSubmatrixSum
void maximumSubarraySum(const std::vector<int>& values, int* result, int* from, int* to) {
    const int n = int(values.size());
    int first = 0;
    while (first < n && values[first] < 0)
        ++first;

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
        std::cout << "The maximum subarray sum for the array";
        for (int v : values)
            std::cout << ' ' << v;
        std::cout << " is: " << best << "\nThe subarray starts at index: " << bestFrom << " and ends at index: " << bestTo << "\n\n";
    }
}
