// файлът от същото repo
#include "Matrix.h"

void minimumCoinCount(const std::vector<size_t>& coins, const size_t S) // T(n,S) = O(nS), M(n,S) = O(S)
{
	std::vector<size_t> M(S + 1, std::numeric_limits<size_t>::max());
	M[0] = 0;
	for (size_t x = 1; x <= S; x++)
		for (auto c : coins)
			if (c <= x) M[x] = std::min(M[x], M[x - c] + 1);
	// return M[S];

	if (M[S] == std::numeric_limits<size_t>::max())
	{
		std::cout << "It's impossible to gather the selected sum with these coins!\n";
		return;
	}
	std::cout << "S = " << S << " with coins:";
	for (auto c : coins) std::cout << " " << c;
	std::cout << "\nMinimum coin count is " << M[S] << ":";
	size_t sum = S;
	while (sum)
	{
		for (size_t i = 0; i < coins.size(); i++) if (M[sum] == M[sum - coins[i]] + 1)
		{
			std::cout << " " << coins[i];
			sum -= coins[i];
			break;
		}
	}
	std::cout << "\n\n";
}
