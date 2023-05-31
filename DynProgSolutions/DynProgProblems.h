#pragma once
#include "Matrix.h"
#include <span>
#include <string_view>

void minimumCoinCount(std::span<const int> coins, const int S);

void minimumCoinCountLimited(std::span<const int> coins, const int S);

void binomialCoefficient(const int n, const int k);

void longestIncreasingSubsequence(std::span<const int> values);

void longestCommonSubsequence(std::span<const int> v1, std::span<const int> v2);

void optimalSingleRobotPath(const Matrix<int>& field);

void optimalTwoRobotPath(const Matrix<int>& field);

void singleRobotPathCount(const Matrix<int>& blocked);

void optimalMatrixMultiplication(std::span<const std::pair<int, int>> coords);

void minimumPalindromSubstrings(std::string_view str);

void minimumDeletionsToPalindrome(std::string_view str);

void nDigitIntegerCount(const int n, const int S);

struct Item { int weight, price; };
void Knapsack(std::span<const Item> items, const int W);

void KnapsackNoRepetitions(std::span<const Item> items, const int W);

void EqualSumSubsets(std::span<const int> values);

void Partition(std::span<const int> values);

void LevenshteinDistance(std::string_view str1, std::string_view str2);

void maximumSubarraySum(std::span<const int> values,
    int* result = nullptr, int* from = nullptr, int* to = nullptr);

void maximumSubmatrixSum(const Matrix<int>& values);

enum class Key { A, CtrlA, CtrlC, CtrlV };
void largestCopyPasteFileSimple(const int n);

void largestCopyPasteFile(const int n);

void pictureProfit(std::span<const int> values);

void minimumSquareCount(const int n);

// Generates all integer partitions via a coroutine, with or without dupicates (by default, without).
#include <cppcoro/generator.hpp> // Preferably from https://github.com/andreasbuhr/cppcoro
cppcoro::generator<std::span<const int>> integerPartitionsGen(const int n, const bool printAll = false);
/* Example usage:
 * for (auto part : integerPartitionsGen(n)) {
 *     fmt::print("{}\n", fmt::join(part, "+"));
 * }
 */
