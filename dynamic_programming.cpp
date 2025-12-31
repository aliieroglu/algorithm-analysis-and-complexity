/*
7. DİNAMİK PROGRAMLAMA 
- Bottom-Up DP 
- Minimum Maliyet Yol Problemi (Top-Down) 
- Sırt Çantası Problemi 
Her problem için dinamik programlama tablosu 
gösterilmelidir. 
 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;
// ------------------------------------------------------------

// Bottom-Up DP
vector<int> bottomUpDPTable(int n) {
    if (n < 0) {
        return {};
    }
    int size = max(2, n + 1);
    vector<int> dp(size, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    dp.resize(n + 1);
    return dp;
}

void printBottomUpDPTable(int n) {
    vector<int> dp = bottomUpDPTable(n);
    cout << "Bottom-Up DP (Fibonacci)" << endl;
    cout << "DP Tablosu (index): ";
    for (int i = 0; i <= n; i++) {
        cout << i << " ";
    }
    cout << endl;
    cout << "DP Tablosu (deger): ";
    for (int i = 0; i <= n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
    cout << "Sonuc: " << dp[n] << endl;
}

// ------------------------------------------------------------
// Minimum Maliyet Yol Problemi (Top-Down)
// ------------------------------------------------------------

static const int UNVISITED = INT_MIN;

int solve(int i, int j, const vector<vector<int>>& M, vector<vector<int>>& memo){
    int N = (int)M.size();

    // hedef hücre: maliyet dahil
    if (i == N - 1 && j == N - 1)
        return M[i][j];

    // memo varsa dön
    if (memo[i][j] != UNVISITED)
        return memo[i][j];

    int best = INT_MAX;

    // aşağı
    if (i + 1 < N) {
        best = min(best, solve(i + 1, j, M, memo));
    }
    // sağ
    if (j + 1 < N) {
        best = min(best, solve(i, j + 1, M, memo));
    }

    // (i,j) maliyetini ekle
    memo[i][j] = M[i][j] + best;
    return memo[i][j];
}

int minCostPath_TopDown(const vector<vector<int>>& M, vector<vector<int>>& memo)
{
    int N = (int)M.size();
    if (N == 0) return 0;

    memo.assign(N, vector<int>(N, UNVISITED));
    return solve(0, 0, M, memo);
}

void printMatrix(const vector<vector<int>>& matrix, const string& label) {
    cout << label << endl;
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << setw(4) << value << " ";
        }
        cout << endl;
    }
}

void printMinCostPathTable(const vector<vector<int>>& M) {
    cout << "Minimum Maliyet Yol Problemi (Top-Down)" << endl;
    printMatrix(M, "Girdi matrisi:");

    vector<vector<int>> memo;
    int result = minCostPath_TopDown(M, memo);
    printMatrix(memo, "DP Tablosu (min maliyet):");
    cout << "Minimum maliyet: " << result << endl;
}

// ------------------------------------------------------------
// Sirt Çantası Problemi
// ------------------------------------------------------------

struct Item {
    int weight;
    int value;
};

struct KnapsackResult {
    int maxValue;
    vector<int> chosenIndices; // 0-based
};

KnapsackResult knapsack01_dp(const vector<Item>& items, int W, vector<vector<int>>& dp) {
    int n = (int)items.size();
    dp.assign(n + 1, vector<int>(W + 1, 0));

    // dp[i][w] = ilk i item ile kapasite w'de alınabilecek max değer
    for (int i = 1; i <= n; i++) {
        int wi = items[i - 1].weight;
        int vi = items[i - 1].value;
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w]; // item alınmaz
            if (wi <= w) {
                dp[i][w] = max(dp[i][w], dp[i - 1][w - wi] + vi); // item alınır
            }
        }
    }

    // Seçilen eşyaları geri izleme (backtrack)
    vector<int> chosen;
    int w = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            chosen.push_back(i - 1);            // item i-1 alındı
            w -= items[i - 1].weight;
        }
    }
    reverse(chosen.begin(), chosen.end());

    return { dp[n][W], chosen };
}

KnapsackResult knapsack01_dp(const vector<Item>& items, int W) {
    vector<vector<int>> dp;
    return knapsack01_dp(items, W, dp);
}

void printKnapsackTable(const vector<Item>& items, int W) {
    cout << "Sirt Cantasi Problemi (0/1 Knapsack)" << endl;
    cout << "Itemler (agirlik, deger): ";
    for (const auto& item : items) {
        cout << "(" << item.weight << "," << item.value << ") ";
    }
    cout << endl;

    vector<vector<int>> dp;
    KnapsackResult result = knapsack01_dp(items, W, dp);

    cout << "DP Tablosu (satir: item sayisi, sutun: kapasite)" << endl;
    cout << "     ";
    for (int w = 0; w <= W; w++) {
        cout << setw(4) << w << " ";
    }
    cout << endl;
    for (int i = 0; i <= (int)items.size(); i++) {
        cout << setw(3) << i << " ";
        for (int w = 0; w <= W; w++) {
            cout << setw(4) << dp[i][w] << " ";
        }
        cout << endl;
    }

    cout << "Maksimum deger: " << result.maxValue << endl;
    cout << "Secilen item indeksleri: ";
    for (int idx : result.chosenIndices) {
        cout << idx << " ";
    }
    cout << endl;
}

int main() {
    cout << "Dinamik Programlama Ornek Cikti" << endl;
    cout << "--------------------------------" << endl;

    // Bottom-Up DP (Fibonacci)
    int n = 8;
    printBottomUpDPTable(n);
    cout << endl;

    // Minimum Maliyet Yol Problemi
    vector<vector<int>> costMatrix = {
        {1, 3, 1, 2},
        {2, 1, 8, 1},
        {4, 2, 1, 3},
        {5, 3, 2, 1}
    };
    printMinCostPathTable(costMatrix);
    cout << endl;

    // 0/1 Knapsack
    vector<Item> items = {
        {2, 12}, {1, 10}, {3, 20}, {2, 15}
    };
    int capacity = 5;
    printKnapsackTable(items, capacity);

    return 0;
}
