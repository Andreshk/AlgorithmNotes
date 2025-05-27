#include "DynProgProblems.h"
#include <algorithm> // std::ranges::reverse, visualization only

// T(n) = O(n^2); M(n) = O(n^2) -> can be optimized to O(n) if recovering the palindrome isn't required
void minimumDeletionsToPalindrome(std::string_view str) {
    const int n = int(str.length());
    // Invariant: M[i][j] contains the max length of a palindromic subsequence of str[i..j)
    Matrix<int> M(n, n, 0);
    for (int i = 0; i < n; ++i) {
        M[i, i] = 1;
    }
    // When the "unused" values in the matrix are zeroes, this is technically not needed
    for (int i = 0; i < n - 1; ++i) {
        M[i, i + 1] = (str[i] == str[i + 1] ? 2 : 1);
    }
    for (int diag = 2; diag < n; ++diag) {
        for (int i = 0; i < n - diag; ++i) {
            const int j = i + diag;
            if (str[i] == str[j]) {
                M[i, j] = 2 + M[i + 1, j - 1]; // Always the best choice
            } else {
                M[i, j] = std::max(M[i + 1, j], M[i, j - 1]); // M[i+1, j-1] covered by these two options
            }
        }
    }
    // return n - M[0, n - 1];
    // Recover the longest palindromic subsequence:
    std::string front, back;
    int i = 0, j = n - 1;
    while (i < j) {
        if (str[i] == str[j]) {
            front.push_back(str[i]);
            back.push_back(str[j]);
            ++i; --j;
        } else if (M[i, j] == M[i + 1, j]) {
            front.push_back(' ');
            ++i;
        } else { // M[i, j] == M[i, j - 1]
            back.push_back(' ');
            --j;
        }
    }
    if (i == j) { back.push_back(str[i]); }
    std::ranges::reverse(back);
    std::println("Longest palindromic subsequence\n for {}\n is: {}{}", str, front, back);
    std::println("Minimum deletions to palindrome: {}", n - M[0, n - 1]);
}