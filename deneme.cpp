#include <bits/stdc++.h>
using namespace std;

struct Result {
    long long bestSum;
    int left, right; // inclusive
};

// ------------------------------------------------------------
// O(n^3) Brute Force
// ------------------------------------------------------------
Result maxSubarray_O3(const vector<int>& A) {
    int n = (int)A.size();
    long long best = LLONG_MIN;
    int bestL = 0, bestR = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            long long sum = 0;
            for (int k = i; k <= j; k++) sum += A[k];
            if (sum > best) {
                best = sum; bestL = i; bestR = j;
            }
        }
    }
    return {best, bestL, bestR};
}

// ------------------------------------------------------------
// O(n^2) Improved Brute Force (prefix/rolling sum)
// ------------------------------------------------------------
Result maxSubarray_O2(const vector<int>& A) {
    int n = (int)A.size();
    long long best = LLONG_MIN;
    int bestL = 0, bestR = 0;

    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += A[j];
            if (sum > best) {
                best = sum; bestL = i; bestR = j;
            }
        }
    }
    return {best, bestL, bestR};
}

// ------------------------------------------------------------
// O(n log n) Divide and Conquer
// ------------------------------------------------------------
struct DCResult {
    long long sum;
    int l, r;
};

DCResult maxCrossing(const vector<int>& A, int lo, int mid, int hi) {
    // best suffix on left
    long long leftBest = LLONG_MIN, s = 0;
    int bestL = mid;
    for (int i = mid; i >= lo; --i) {
        s += A[i];
        if (s > leftBest) {
            leftBest = s; bestL = i;
        }
    }

    // best prefix on right
    long long rightBest = LLONG_MIN;
    s = 0;
    int bestR = mid + 1;
    for (int j = mid + 1; j <= hi; ++j) {
        s += A[j];
        if (s > rightBest) {
            rightBest = s; bestR = j;
        }
    }

    return {leftBest + rightBest, bestL, bestR};
}

DCResult dcSolve(const vector<int>& A, int lo, int hi) {
    if (lo == hi) return {(long long)A[lo], lo, hi};
    int mid = lo + (hi - lo) / 2;

    auto left = dcSolve(A, lo, mid);
    auto right = dcSolve(A, mid + 1, hi);
    auto cross = maxCrossing(A, lo, mid, hi);

    if (left.sum >= right.sum && left.sum >= cross.sum) return left;
    if (right.sum >= left.sum && right.sum >= cross.sum) return right;
    return cross;
}

Result maxSubarray_Onlogn(const vector<int>& A) {
    if (A.empty()) return {0, -1, -1};
    auto r = dcSolve(A, 0, (int)A.size() - 1);
    return {r.sum, r.l, r.r};
}

// ------------------------------------------------------------
// O(n) Kadane (with indices, all-negative safe)
// ------------------------------------------------------------
Result maxSubarray_Kadane(const vector<int>& A) {
    int n = (int)A.size();
    long long best = LLONG_MIN;

    long long cur = 0;
    int curL = 0;
    int bestL = 0, bestR = 0;

    for (int i = 0; i < n; i++) {
        // If starting fresh at i is better than extending
        if (cur <= 0) {
            cur = A[i];
            curL = i;
        } else {
            cur += A[i];
        }

        if (cur > best) {
            best = cur;
            bestL = curL;
            bestR = i;
        }
    }
    return {best, bestL, bestR};
}

// ------------------------------------------------------------
// Timing helper
// ------------------------------------------------------------
template <class F>
pair<Result, long long> timedRun(const vector<int>& A, F func) {
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    Result r = func(A);
    auto t2 = high_resolution_clock::now();
    auto us = duration_cast<microseconds>(t2 - t1).count();
    return {r, (long long)us};
}

static void printResult(const string& name, const Result& r, long long us) {
    cout << setw(22) << left << name
         << " | bestSum=" << setw(12) << r.bestSum
         << " [" << r.left << "," << r.right << "]"
         << " | time=" << us << " us\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------------------
    // INPUT: aynı veriyle tüm yöntemler
    // ---------------------------
    // 1) İstersen elle gir:
    // N ve dizi elemanları
    // 2) İstersen random üret (aşağıda açık)
    //
    // Burada: random üretelim (proje karşılaştırması için pratik).
    int N = 2000;              // O(n^3) için çok büyük seçme (ör: 2000 -> O3 patlar)
    int lo = -100, hi = 100;   // değer aralığı

    // İstersen komut satırından N al:
    // if (cin >> N) { ... }  // veya argv ile
    // Bu örnekte sabit + seed.

    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(lo, hi);

    vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = dist(rng);

    cout << "N=" << N << " (values in [" << lo << "," << hi << "])\n\n";

    // ---------------------------
    // RUN + TIME
    // ---------------------------
    // Dikkat: O(n^3) çok yavaş olabilir. Büyük N için kapat.
    // Projede genelde N'leri kademeli büyütüp ölçersin.
    auto [r3, t3]  = timedRun(A, maxSubarray_O3);
    auto [r2, t2]  = timedRun(A, maxSubarray_O2);
    auto [rnl, tnl]= timedRun(A, maxSubarray_Onlogn);
    auto [rk, tk]  = timedRun(A, maxSubarray_Kadane);

    // ---------------------------
    // VALIDATION (aynı sonucu buluyorlar mı?)
    // ---------------------------
    auto sameSum = (r3.bestSum == r2.bestSum) && (r2.bestSum == rnl.bestSum) && (rnl.bestSum == rk.bestSum);
    cout << "All sums equal? " << (sameSum ? "YES" : "NO") << "\n\n";

    printResult("O(n^3) Brute Force", r3, t3);
    printResult("O(n^2) Improved",    r2, t2);
    printResult("O(n log n) D&C",     rnl, tnl);
    printResult("O(n) Kadane",        rk, tk);

    return 0;
}
