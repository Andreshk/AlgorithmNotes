#include"Matrix.h"

void binomialCoefficient(const size_t n, const size_t k) // T(n,k) = O(nk), M(n,k) = O(nk) <- може да се оптимизира до M(n,k) = O(k)
{
	Matrix<size_t> M(n, k, 0);
	for (size_t i = 0; i < k; i++) M[i][i] = 1;
	for (size_t i = 0; i < n; i++) M[i][0] = i + 1;

	for (size_t i = 1; i < n; i++)
		for (size_t j = 1; j < k && j < i; j++)
			M[i][j] = M[i - 1][j - 1] + M[i - 1][j];
	//return M[n - 1][k - 1];
	std::cout << n << " over " << k << " = " << M[n - 1][k - 1] << "\n\n";
}
