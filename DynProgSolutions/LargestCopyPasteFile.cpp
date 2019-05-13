#include "DynProgProblems.h"

// T(n) = O(n^2), M(n) = O(n) <- can be reduced to T(n) = O(n)
void largestCopyPasteFile(const int n) {
    vassert(n < 158); // n > 158 can lead to overflow !
    // clsoed formula - unknown :/
    std::vector<uint64_t> M(n + 1, 0);
    M[1] = 1;
    M[2] = 2;
    for (int k = 3; k <= n; ++k){
        M[k] = std::max(M[k - 1] + 1, M[k - 1]);
        for (int i = 0; i <= k - 3; i++) // number of Ctrl-V actions after a Ctrl-C
            M[k] = std::max(M[k], (i + 1)*M[k - 2 - i]);
        // It can be shown that i < 6 is enough for optimal strategy => T(n) = O(n)
    }
    // return M[n];

    std::cout << "The largest possible filesize with " << n << " keystrokes is: " << M[n] << "\n";

    std::vector<int> keystrokes;
    size_t idx = n;
    while (idx > 0) {
        if (M[idx] == M[idx - 1] + 1) {
            keystrokes.push_back(int(Key::A)); --idx;
        } else if (M[idx] == M[idx - 1]) {
            keystrokes.push_back(int(Key::CtrlA)); --idx;
        } else for (int i = 2; i < idx; ++i)
            if (M[idx] == (i - 1)*M[idx - i]) {
                keystrokes.push_back(i);
                idx -= i;
                break;
            }
    }
    std::reverse(keystrokes.begin(), keystrokes.end());
    for (int k : keystrokes)
        switch (k) {
        case int(Key::A):     std::cout << "\'a\'\n"; break;
        case int(Key::CtrlA): std::cout << "Ctrl-A\n"; break;
        default: {
            std::cout << "Ctrl-A Ctrl-C";
            for (int i = 2; i < k; i++)
                std::cout << " Ctrl-V";
            std::cout << '\n';
        }
        }
    std::cout << '\n';
}
