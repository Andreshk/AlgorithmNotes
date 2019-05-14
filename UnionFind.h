#pragma once
#include <vector>
#include <cstddef>     // size_t
#include <type_traits> // std::is_unsigned_v

template <class Idx = size_t>
class UnionFind {
    static_assert(std::is_unsigned_v<Idx>);
    struct pair { Idx p, r; };
    std::vector<pair> values;

    // Ease of access, will be inlined
    Idx& parent(Idx x) { return values[x].p; }
    Idx&   rank(Idx x) { return values[x].r; }

    // Find w/ path halving. May probably be optimized a little more.
    Idx Find(Idx x) {
        while (parent(x) != x) {
            parent(x) = parent(parent(x));
            x = parent(x);
        }
        return x;
    }
public:
    // Constructs a disjont-set with n values, each in its own set
    explicit UnionFind(const Idx n) : values{ n } {
        for (Idx i = 0; i < n; ++i) {
            parent(i) = i;
            rank(i) = 0;
        }
    }
    // Union by rank. Returns true on successful union,
    // false if x and y are already in the same component.
    bool Union(Idx x, Idx y) {
        Idx xroot = Find(x), yroot = Find(y);
        if (xroot == yroot)
            return false;
        if (rank(xroot) < rank(yroot))
            std::swap(xroot, yroot);
        parent(yroot) = xroot;
        Idx& xrank = rank(xroot);
        if (xrank == rank(yroot))
            ++xrank;
        return true;
    }
};
