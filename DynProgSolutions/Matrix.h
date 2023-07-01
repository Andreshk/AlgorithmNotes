#pragma once
#include <print>
#include <vector>
#include <initializer_list>
#include <cassert>

template<class T>
class Matrix {
    // Avoid dealing with vector<bool> by using a vector of some other 1-byte type.
    static constexpr bool isBool = std::is_same_v<std::remove_cv_t<T>, bool>;
    using U = std::conditional_t<isBool, std::uint8_t, T>;
    std::vector<U> values;
    int n, m; // row & column count, respectively

    using MatrixInitializerList = std::initializer_list<std::initializer_list<T>>;
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
    Matrix(int _n, int _m, const T& _val = T{}) : values(_n*_m, _val), n(_n), m(_m) {}
    /* allows for the following:
     * Matrix<int> m1{ {1,2,3}, {4,5,6} };
     * Matrix<int> m2 = { {1,2,3}, {4,5,6} };
     * void f(Matrix<int>);
     * f({ {1,2,3}, {4,5,6} });
     */
    Matrix(MatrixInitializerList il) { init(il); }
    Matrix& operator=(MatrixInitializerList il) { init(il); return *this; }
    // Warning: no bounds checking for the second dimension, even in debug mode!
    // We are waiting for multi-dimensional operator[] (P2128)
    T* operator[](int row) {
        assert(row >= 0 && row < n);
        return reinterpret_cast<T*>(values.data()) + m*row;
    }
    const T* operator[](int row) const {
        assert(row >= 0 && row < n);
        return reinterpret_cast<const T*>(values.data()) + m*row;
    }
    // Bounds-safe alternative to operator[], returning a zero value on invalid input.
    T at(int i, int j) const {
        return ((i < 0 || j < 0 || i >= n || j >= m) ? T{} : (*this)[i][j]);
    }
    int rows() const { return n; }
    int cols() const { return m; }
    // Pointers are the poor man's iterators, but they work just fine here
          T* begin()       { return (*this)[0]; }
    const T* begin() const { return (*this)[0]; }
          T* end()       { return (*this)[n-1]+m; }
    const T* end() const { return (*this)[n-1]+m; }
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
                std::formatter<T>::format(m[row][col], ctx);
            }
        }
        return ctx.out();
    }
};
