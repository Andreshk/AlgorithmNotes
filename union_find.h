#pragma once
#include <vector>
#include <type_traits>

template <class Idx>
class union_find
{
    static_assert(std::is_unsigned_v<Idx>);
    struct pair { Idx p, r; };
    std::vector<pair> values;
    
    Idx& parent(Idx x) { return values[x].p; }
    Idx&   rank(Idx x) { return values[x].r; }

    Idx Find(Idx x) { // path halving
        while (parent(x) != x) {
            parent(x) = parent(parent(x));
            x = parent(x);
        }
        return x;
    }
public:
    union_find(const Idx n) : values{ n } {
        for (Idx i = 0; i < n; ++i) {
            parent(i) = i;
            rank(i) = 0;
        }
    }
    void Union(Idx x, Idx y) { // union by rank
        Idx xroot = Find(x), yroot = Find(y);
        if (xroot == yroot)
            return;
        if (rank(xroot) < rank(yroot))
            std::swap(xroot, yroot);
        parent(yroot) = xroot;
        Idx& xrank = rank(xroot);
        if (xrank == rank(yroot))
            ++xrank;
    }
};
