#include<iostream>
#include<vector>
#include<initializer_list>


template<class T>
class Matrix
{
	using matrix_initializer_list = std::initializer_list<std::initializer_list<T>>;

	std::vector<T> values;
	size_t n, m;

	/* позволява следните извиквания:
	 * Matrix<int> m1{ {1,2,3}, {4,5,6} };
	 * Matrix<int> m2 = { {1,2,3}, {4,5,6} };
	 * void f(Matrix<int>);
	 * f({ {1,2,3}, {4,5,6} });
	 */
	void init(const matrix_initializer_list& il)
	{
		clear();
		n = il.size();
		m = il.begin()->size();
		for (const auto& row : il) if (row.size() != m)
		{
			std::cout << "Invalid matrix dimensions (jagged matrix)!\n";
			clear();
			return;
		}
		values.resize(n*m);
		size_t idx = 0;
		for (const auto& row : il)
			for (const auto& val : row)
				values[idx++] = val;
	}
	void clear() noexcept
	{
		values.clear();
		n = m = 0;
	}
public:
	Matrix(size_t _n, size_t _m, const T& _val = T()) : values(_n*_m, _val), n(_n), m(_m) {}
	Matrix(const matrix_initializer_list& il) { init(il); }
	Matrix& operator=(const matrix_initializer_list& il) { init(il); return *this; }

	T* operator[](size_t row) noexcept { return values.data() + m*row; }
	const T* operator[](size_t row) const noexcept { return values.data() + m*row; }
	T at(size_t i, size_t j) const noexcept(noexcept(T()))
	{
		// exception-safe версия на оператора [], която връща
		// стойност по подразбиране при невалидни индекси
		if (i >= n || j >= m) return T();
		return (*this)[i][j];
	}
	size_t rows() const noexcept { return n; }
	size_t cols() const noexcept { return m; }
};

/* // трябва да е в .cpp файл (!)
template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matr)
{
	for (size_t i = 0; i < matr.rows(); i++)
	{
		for (size_t j = 0; j < matr.cols(); j++) os << matr[i][j] << " ";
		os << "\n";
	}
	return os << "\n";
}*/
