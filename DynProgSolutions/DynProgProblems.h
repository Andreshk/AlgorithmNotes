#pragma once
#include "Matrix.h"
#include <limits>

void minimumCoinCount(const std::vector<int>& coins, const int S);

void minimumCoinCountLimited(const std::vector<size_t>& coins, const size_t S);

void binomialCoefficient(const int n, const int k);

void longestIncreasingSubsequence(const std::vector<int>& values);

void longestCommonSubsequence(const std::vector<int>& v1, const std::vector<int>& v2);

void optimalSingleRobotPath(const Matrix<int>& field);

void optimalTwoRobotPath(const Matrix<int>& field);

void singleRobotPathCount(const Matrix<int>& blocked);

void optimalMatrixMultiplication(const std::vector<std::pair<int, int>>& coords);

void minimumPalindromSubstrings(const std::string& str);

void minimumDeletionsToPalindrom(const std::string& str);

void nDigitIntegerCount(const int n, const int S);

struct Item { int weight, price; };
void Knapsack(const std::vector<Item>& items, const int W);

void KnapsackNoRepetitions(const std::vector<Item>& items, const int W);

void EqualSumSubsets(const std::vector<int>& values);

void Partition(const std::vector<int>& values);

void LevenshteinDistance(const std::string& str1, const std::string& str2);

void maximumSubarraySum(const std::vector<int>& values,
    int* result = nullptr, int* from = nullptr, int* to = nullptr);

void maximumSubmatrixSum(const Matrix<int>& values);

enum class Key { A, CtrlA, CtrlC, CtrlV };
void largestCopyPasteFileSimple(const int n);

void largestCopyPasteFile(const int n);

void pictureProfit(const std::vector<int>& values);

void minimumSquareCount(const int n);
