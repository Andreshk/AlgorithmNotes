#include "DynProgProblems.h"

cppcoro::generator<std::span<const int>> integerPartitionsGen(const int n, const bool printAll) {
    std::vector<int> xs(n, 0); // At most n numbers add up to n (all ones)
    // Initialize with the first, trivial partition [n]
    xs[0] = n;
    int pos = 1; // Index of the next number in xs to be filled
    int rest = 0; // Invariant: rest == n - Sum(xs[0..pos))
    // Each iteration advances from one partition to the next
    while (true) {
        co_yield { xs.begin(), xs.begin() + pos }; // This is xs[0..pos)
        if (pos == n) { // This was the last partition: 1+...+1
            break;
        }
        while (xs[--pos] == 1) { // Unroll until we reach a number that can be decreased
            ++rest; // same as rest += xs[idx]
        }
        // Decrease one number to "switch" to the next partition
        --xs[pos];
        ++rest;
        ++pos;
        // Fill the rest of it
        while (rest > 0) {
            xs[pos] = (printAll ? rest : std::min(rest, xs[pos - 1]));
            rest -= xs[pos];
            ++pos;
        }
    }
}

// Naive, recursive solution:
#include <cppcoro/recursive_generator.hpp>

cppcoro::recursive_generator<std::span<const int>>
    partitionsHelper(const std::span<int> xs, const int rest, const int pos, const bool printAll)
{
    if (rest == 0) {
        co_yield xs.subspan(0, pos);
    } else {
        int first = (printAll || pos == 0 ? rest : std::min(rest, xs[pos - 1]));
        for (; first >= 1; --first) {
            xs[pos] = first;
            co_yield partitionsHelper(xs, rest - first, pos + 1, printAll);
        }
    }
}

cppcoro::recursive_generator<std::span<const int>>
    integerPartitionsGenR(const int n, const bool printAll = false)
{
    if (n > 1) {
        std::vector<int> xs(n); // At most n numbers add to n (all ones)
        co_yield partitionsHelper(xs, n, 0, printAll);
    }
}
