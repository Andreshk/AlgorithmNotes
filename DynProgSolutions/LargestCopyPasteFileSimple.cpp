#include "DynProgProblems.h"
#include <fmt/core.h>
#include <ranges> // std::views::reverse

// T(n) = O(n), M(n) = O(n)
void largestCopyPasteFileSimple(const int n) {
    assert(n <= 189); // n = 190 overflows uint64
    // Closed formula:
    // return ((3 + n%3) * (1ui64 << (n / 3 - 1)));
    // T(n) = O(1), M(n) = O(1), f(n) = Theta(2^(n/3))

    std::vector<uint64_t> M(n + 1, 0);
    M[1] = 1;
    M[2] = 2;
    for (int k = 3; k <= n; k++) {
        M[k] = std::max(std::max(M[k - 1] + 1, M[k - 1]),
                        std::max(M[k - 2], 2 * M[k - 3]));
    }
    //return M[n];

    fmt::print("The largest possible filesize with {} keystrokes is: {}\n", n, M[n]);

    std::vector<Key> keystrokes;
    size_t idx = n;
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

    for (const Key k : std::views::reverse(keystrokes)) {
        switch (k) {
        case Key::A:     { fmt::print("\'a\'\n"); break; }
        case Key::CtrlA: { fmt::print("Ctrl-A\n"); break; }
        case Key::CtrlC: { fmt::print("Ctrl-A Ctrl-C\n"); break; }
        case Key::CtrlV: { fmt::print("Ctrl-A Ctrl-C Ctrl-V\n"); break; }
        }
    }
    fmt::print("\n");
}
