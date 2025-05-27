#pragma once
#include <print>
#include <initializer_list>
#include <memory>
#include <cassert>

template<class T>
class Matrix {
    std::unique_ptr<T[]> values;
    int n, m; // row & column count, respectively

    using MatrixInitializerList = std::initializer_list<std::initializer_list<T>>;
    void init(MatrixInitializerList il) {
        n = int(il.size());
        m = int(il.begin()->size());
        values = std::make_unique_for_overwrite<T[]>(n * m);
        for (int idx = 0; const auto& row : il) {
            assert(row.size() == m);
            for (const auto& val : row) {
                values[idx++] = val;
            }
        }
    }
public:
    Matrix(int _n, int _m, const T& _val = T{}) : values{std::make_unique_for_overwrite<T[]>(_n*_m)}, n(_n), m(_m) {
        std::uninitialized_fill_n(values.get(), n * m, _val);
    }
    /* allows for the following:
     * Matrix<int> m1{ {1,2,3}, {4,5,6} };
     * Matrix<int> m2 = { {1,2,3}, {4,5,6} };
     * void f(Matrix<int>);
     * f({ {1,2,3}, {4,5,6} });
     */
    Matrix(MatrixInitializerList il) { init(il); }
    Matrix& operator=(MatrixInitializerList il) { init(il); return *this; }
    T& operator[](int row, int col) {
        assert(row >= 0 && row < n && col >= 0 && col < m);
        return reinterpret_cast<T&>(values[row * m + col]);
    }
    const T& operator[](int row, int col) const {
        assert(row >= 0 && row < n && col >= 0 && col < m);
        return reinterpret_cast<const T&>(values[row * m + col]);
    }
    // "Safe" alternative to operator[], returning a zero value on invalid input.
    T at(int i, int j) const {
        return ((i < 0 || j < 0 || i >= n || j >= m) ? T{} : (*this)[i, j]);
    }
    int rows() const { return n; }
    int cols() const { return m; }
    // Pointers are the poor man's iterators, but they work just fine here
          T* begin()       { return values.get(); }
    const T* begin() const { return values.get(); }
          T* end()       { return values.get() + n*m; }
    const T* end() const { return values.get() + n*m; }
};

// Matrices can be formatted, too, even using the same attributes as the contained values,
// f.e. std::print("{:{}}", m, pad) for padding each individual value to some length.
template<class T>
struct std::formatter<Matrix<T>> : std::formatter<T> {
    template <typename FormatContext>
    auto format(const Matrix<T>& m, FormatContext& ctx) const {
        for (int row = 0; row < m.rows(); ++row) {
            if (row > 0) {
                *ctx.out()++ = '\n';
            }
            for (int col = 0; col < m.cols(); ++col) {
                if (col > 0) {
                    *ctx.out()++ = ' ';
                }
                std::formatter<T>::format(m[row, col], ctx);
            }
        }
        return ctx.out();
    }
};
