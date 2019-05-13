#pragma once
#include <iostream>
#include <vector>
#include <algorithm> // std::{min,max}
#include <initializer_list>

#include <cassert>
#define vassert assert

template<class T>
class Matrix {
    using matrix_initializer_list = std::initializer_list<std::initializer_list<T>>;

    std::vector<T> values;
    int n, m; // row & column count, respectively

    /* allows for the following expressions:
     * Matrix<int> m1{ {1,2,3}, {4,5,6} };
     * Matrix<int> m2 = { {1,2,3}, {4,5,6} };
     * void f(Matrix<int>);
     * f({ {1,2,3}, {4,5,6} });
     */
    void init(matrix_initializer_list il) {
        values.clear();
        n = int(il.size());
        m = int(il.begin()->size());
        values.resize(n*m);
        size_t idx = 0;
        for (const auto& row : il) {
            vassert(row.size() == m);
            for (const auto& val : row)
                values[idx++] = val;
        }
    }
public:
    Matrix(int _n, int _m, const T& _val = T{}) : values(_n*_m, _val), n(_n), m(_m) {}
    Matrix(matrix_initializer_list il) { init(il); }
    Matrix& operator=(matrix_initializer_list il) { init(il); return *this; }

    T* operator[](int row) {
        vassert(row >= 0 && row < n);
        return values.data() + m * row;
    }
    const T* operator[](int row) const {
        vassert(row >= 0 && row < n);
        return values.data() + m*row;
    }
    T at(int i, int j) const {
        // exception-safe alternative to operator[],
        // returning a default value on invalid input
        return ((i < 0 || j < 0 || i >= n || j >= m) ? T{} : (*this)[i][j]);
    }
    int rows() const { return n; }
    int cols() const { return m; }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matr) {
    for (int i = 0; i < matr.rows(); i++) {
        for (int j = 0; j < matr.cols(); j++)
            os << matr[i][j] << ' ';
        os << '\n';
    }
    return os << '\n';
}

template<class T>
T min(const T& a, const T& b, const T& c) {
    return std::min(std::min(a, b), c);
}

template<class T>
T max(const T& a, const T& b, const T& c, const T& d) {
    return std::max(std::max(a, b), std::max(c, d));
}
