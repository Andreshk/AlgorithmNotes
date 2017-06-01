#include"Matrix.h"

void longestIncreasingSubsequence(const std::vector<int>& values) // T(n) = O(n^2), M(n) = O(n)
{
	/* забележка:
	 * с изграждането на граф отново T(n) = O(n^2), но M(n) = O(n+m) - изграждането винаги е бавно и ни трябва допълн. памет
	 * без построяване на граф T(n) = O(n^2), но M(n) = O(n)
	 */
	const size_t count = values.size();
	std::vector<size_t> M(count), successors(count);
	for (size_t i = count - 1; i < count; i--) // i < count вместо i>=0
	{
		M[i] = 1;
		successors[i] = count;
		for (size_t j = i + 1; j < count; j++)
			if (values[i] < values[j] && M[i] < M[j] + 1)
			{
				M[i] = M[j] + 1;
				successors[i] = j;
			}
	}
	size_t maxIdx = 0;
	for (size_t i = 1; i < M.size(); i++) if (M[maxIdx] < M[i]) maxIdx = i;
	//return M[maxIdx];

	std::cout << "Longest increasing subsequence:";
	size_t nextIdx = maxIdx;
	while (nextIdx != count)
	{
		std::cout << " " << values[nextIdx];
		nextIdx = successors[nextIdx];
	}
	std::cout << "\nLength = " << M[maxIdx] << "\n\n";
}
