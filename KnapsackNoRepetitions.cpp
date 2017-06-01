#include"Matrix.h"

// всеки "предмет" за задачата за раницата е наредена двойка, в която
// първият елемент е теглото, а вторият елемент е цената му
using Item = std::pair<size_t, size_t>;
void KnapsackNoRepetitions(const std::vector<Item>& items, const size_t W) // T(n,W) = O(nW), M(n,W) = O(nW) <- може да се оптимизира до M(n,W) = O(W)
{
	const size_t n = items.size();
	Matrix<size_t> M(n + 1, W + 1, 0);
	for (size_t k = 1; k <= n; k++)
		for (size_t P = 1; P <= W; P++)
		{
			const auto& item = items[k - 1];
			if (item.first > P)
				M[k][P] = M[k - 1][P];
			else
				M[k][P] = std::max(M[k - 1][P], M[k - 1][P - item.first] + item.second);
		}
	//return M[n][W]

	std::cout << "The optimal profit for weight " << W << " is: " << M[n][W] << "\nThe following items are being used:\n";
	size_t P = W;
	for (size_t k = n; k != 0;k--) if (M[k][P] != M[k - 1][P])
	{
		const auto& item = items[k - 1];
		std::cout << "  W: " << item.first << " C: " << item.second << "\n";
		P -= item.first;
	}
	std::cout << "The unused space in the knapsack is: " << P << ".\n\n";
}
