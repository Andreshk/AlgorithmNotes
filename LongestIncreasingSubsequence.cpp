#include "DynProgProblems.h"

// T(n) = O(n^2), M(n) = O(n)
void longestIncreasingSubsequence(const std::vector<int>& values) {
    /* забележка:
     * с изграждането на граф отново T(n) = O(n^2), но M(n) = O(n+m),
     * тъй като изграждането винаги е бавно и ни трябва допълн. памет
     * без построяване на граф T(n) = O(n^2), но M(n) = O(n)
     */
    const int count = int(values.size());
    std::vector<int> M(count), successors(count);
    for (int i = count - 1; i >= 0; --i) {
        M[i] = 1;
        successors[i] = count;
        for (int j = i + 1; j < count; j++)
            if (values[i] < values[j] && M[i] < M[j] + 1) {
                M[i] = M[j] + 1;
                successors[i] = j;
            }
    }
    // Find the maximum value
    int maxIdx = 0;
    for (int i = 1; i < count; i++)
        if (M[maxIdx] < M[i])
            maxIdx = i;
    //return M[maxIdx];

    std::cout << "Longest increasing subsequence of:\n";
    for (const int x : values)
        std::cout << x << ' ';
    std::cout << "is:\n";
    int nextIdx = maxIdx;
    while (nextIdx != count) {
        std::cout << values[nextIdx] << ' ';
        nextIdx = successors[nextIdx];
    }
    std::cout << "\nLength = " << M[maxIdx] << "\n\n";
}
