#include "DynProgProblems.h"
#include <print>

// T(n,m) = O(nm), M(n,m) = O(nm) <- can be reduced to M(n,m) = O(min{n,m})
void LevenshteinDistance(std::string_view str1, std::string_view str2) {
    // for details, see https://github.com/Andreshk/ApproximateStringMatching
    const int n = int(str1.size()), m = int(str2.size());
    Matrix<int> M(n + 1, m + 1);
    for (int i = 1; i <= n; i++) {
        M[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        M[0][j] = j;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            M[i][j] = std::min(std::min(M[i - 1][j] + 1, M[i][j - 1] + 1),
                               M[i - 1][j - 1] + ((str1[i - 1] == str2[j - 1]) ? 0 : 1));
        }
    }
    //return M[n][m];

    std::print("Minimum edit distance between strings \"{}\" and \"{}\" is {}.\n\n", str1, str2, M[n][m]);
}
