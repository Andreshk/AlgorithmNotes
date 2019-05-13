#include "DynProgProblems.h"

// T(n) = O(n), M(n) = O(n)
void largestCopyPasteFileSimple(const int n) {
    vassert(n <= 189); // n = 190 overflows uint64
    // Closed formula:
    // return ((3 + n%3) * (1ui64 << (n / 3 - 1)));
    // T(n) = O(1), M(n) = O(1), f(n) = Theta(2^(n/3))

    std::vector<uint64_t> M(n + 1, 0);
    M[1] = 1;
    M[2] = 2;
    for (int k = 3; k <= n; k++)
        M[k] = max(M[k - 1] + 1, M[k - 1], M[k - 2], 2 * M[k - 3]);
    //return M[n];

    std::cout << "The largest possible filesize with " << n << " keystrokes is: " << M[n] << "\n";

    std::vector<Key> keystrokes;
    int idx = n;
    while (idx > 0) {
        if (M[idx] == M[idx - 1] + 1) {
            keystrokes.push_back(Key::A); --idx;
        } else if (M[idx] == M[idx - 1]) {
            keystrokes.push_back(Key::CtrlA); --idx;
        } else if (M[idx] == M[idx - 2]) {
            keystrokes.push_back(Key::CtrlC); idx -= 2;
        } else /*(M[idx] == 2 * M[idx - 3])*/ {
            keystrokes.push_back(Key::CtrlV); idx -= 3;
        }
    }
    std::reverse(keystrokes.begin(), keystrokes.end());
    for (Key k : keystrokes)
        switch (k) {
        case Key::A:     std::cout << "\'a\'\n"; break;
        case Key::CtrlA: std::cout << "Ctrl-A\n"; break;
        case Key::CtrlC: std::cout << "Ctrl-A Ctrl-C\n"; break;
        case Key::CtrlV: std::cout << "Ctrl-A Ctrl-C Ctrl-V\n"; break;
        }
    std::cout << '\n';
}
