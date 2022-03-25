#pragma once
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>
#include <span>
#include <algorithm> // std::{min,max}
#include <initializer_list>

#include <cassert>

template<class T>
class Matrix {
    using MatrixInitializerList = std::initializer_list<std::initializer_list<T>>;

    std::vector<T> values;
    int n, m; // row & column count, respectively

    void init(MatrixInitializerList il) {
        values.clear();
        n = int(il.size());
        m = int(il.begin()->size());
        values.resize(n*m);
        size_t idx = 0;
        for (const auto& row : il) {
            assert(row.size() == m);
            for (const auto& val : row) {
                values[idx++] = val;
            }
        }
    }
public:
    Matrix(int _n, int _m, const T& _val = T{}) : values(_n* _m, _val), n(_n), m(_m) {}
    /* allows for the following:
     * Matrix<int> m1{ {1,2,3}, {4,5,6} };
     * Matrix<int> m2 = { {1,2,3}, {4,5,6} };
     * void f(Matrix<int>);
     * f({ {1,2,3}, {4,5,6} });
     */
    Matrix(MatrixInitializerList il) { init(il); }
    Matrix& operator=(MatrixInitializerList il) { init(il); return *this; }

    T* operator[](int row) {
        assert(row >= 0 && row < n);
        return values.data() + m*row;
    }
    const T* operator[](int row) const {
        assert(row >= 0 && row < n);
        return values.data() + m*row;
    }
    T at(int i, int j) const {
        // bounds-safe alternative to operator[],
        // returning a default value on invalid input
        return ((i < 0 || j < 0 || i >= n || j >= m) ? T{} : (*this)[i][j]);
    }
    int rows() const { return n; }
    int cols() const { return m; }
};

// Matrices can be formatted, even supporting the same formatting attributes as ranges
template<class T>
struct fmt::formatter<Matrix<T>> : formatter<std::span<const T>> {
    template <typename FormatContext>
    auto format(const Matrix<T>& m, FormatContext& ctx) {
        fmt::format_to(ctx.out(), "[");
        for (int row = 0; row < m.rows(); ++row) {
            if (row > 0) {
                fmt::format_to(ctx.out(), "\n ");
            }
            formatter<std::span<const T>>::format({ m[row], size_t(m.cols()) }, ctx);
        }
        fmt::format_to(ctx.out(), "]");
        return ctx.out();
    }
};

// Other useful stuff
template<class T>
T min(const T& a, const T& b, const T& c) {
    return std::min(std::min(a, b), c);
}

template<class T>
T max(const T& a, const T& b, const T& c, const T& d) {
    return std::max(std::max(a, b), std::max(c, d));
}
