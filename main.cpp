// 1. Maximum subsequence Problem
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

// brute-force approach O(n^3)
int maxSubsequenceBruteForce(const vector<int>& arr) {
    int maxSum = 0;
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int currentSum = 0;
            for (int k = i; k <= j; ++k) {
                currentSum += arr[k];
            }
            maxSum = max(maxSum, currentSum);
        }
    }
    return maxSum;
}