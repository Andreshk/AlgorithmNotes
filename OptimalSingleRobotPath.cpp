#include"Matrix.h"
#include<limits>

void optimalSingleRobotPath(const Matrix<int>& field) // T(n,m) = O(nm), M(n,m) = O(nm) <- може да се оптимизира до M(n,m) = O(min{n,m})
{
	const size_t n = field.rows(), m = field.cols();
	Matrix<int> M(n, m, std::numeric_limits<int>::min());
	M[n - 1][m - 1] = field[n - 1][m - 1];
	for (size_t i = n - 2; i < n; i--) M[i][m - 1] = M[i + 1][m - 1] + field[i][m - 1];
	for (size_t j = m - 2; j < m; j--) M[n - 1][j] = M[n - 1][j + 1] + field[n - 1][j];
	
	for (size_t i = n - 2; i < n; i--)
		for (size_t j = m - 2; j < m; j--)
		{
			M[i][j] = std::max(M[i][j], M[i + 1][j] + field[i][j]);
			M[i][j] = std::max(M[i][j], M[i][j + 1] + field[i][j]);
		}
	//return M[0][0];
	
	std::cout << field;
	std::cout << "Maximum profit path:";
	size_t i = 0, j = 0;
	while (i < n - 1 || j < m - 1)
	{
		if (i < n - 1 && M[i][j] == M[i + 1][j] + field[i][j]) { std::cout << " D"; ++i; continue; }
		if (j < m - 1 && M[i][j] == M[i][j + 1] + field[i][j]) { std::cout << " R"; ++j; continue; }
	}
	std::cout << "\nMaximum profit: " << M[0][0] << "\n\n";
}
