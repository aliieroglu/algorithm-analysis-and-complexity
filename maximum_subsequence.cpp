#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------

/* 1. MAXIMUM SUBSEQUENCE PROBLEMİ 
    A[0..N-1] dizisi için problem aşağıdaki 4 yaklaşımla 
    çözülecektir: 
    - O(n^3) Brute Force 
    - O(n^2) İyileştirilmiş Brute Force 
    - O(n log n) Divide and Conquer 
    - O(n) Kadane Algoritması

    Her  yaklaşım  için  aynı  giriş  verisi  kullanılarak 
    performans karşılaştırması yapılmalıdır.
    */
// ------------------------------------------------------------


// Maksimum alt dizi sonucunu tek yerde toplamak icin kullanilir:
// bestSum: en iyi toplam, left/right: alt dizinin sinirlari (dahil).
struct Result {
    long long bestSum;
    int left, right; // dahil
};

// ------------------------------------------------------------
// O(n^3) Brute Force
// Tum alt dizileri tek tek deneyip en buyuk toplami bulur.
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
// Her baslangic icin artan toplami biriktirir, ic dongu azalir.
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
// Diziyi ikiye bolup sol, sag ve ortayi kesen en iyi sonucu karsilastirir.
// ------------------------------------------------------------
// D&C adiminda ara sonuclari tek degiskenle tasimak icin.
struct DCResult {
    long long sum;
    int l, r;
};

DCResult maxCrossing(const vector<int>& A, int lo, int mid, int hi) {
    // solda en iyi suffix
    long long leftBest = LLONG_MIN, s = 0;
    int bestL = mid;
    for (int i = mid; i >= lo; --i) {
        s += A[i];
        if (s > leftBest) {
            leftBest = s; bestL = i;
        }
    }

    // sagda en iyi prefix
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
// Tek geciste en iyi alt dizi; negatiflerde yeniden baslatma mantigi.
// ------------------------------------------------------------
Result maxSubarray_Kadane(const vector<int>& A) {
    int n = (int)A.size();
    long long best = LLONG_MIN;

    long long cur = 0;
    int curL = 0;
    int bestL = 0, bestR = 0;

    for (int i = 0; i < n; i++) {
        // i'den yeni baslamak uzatmaya gore daha iyiyse
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
// Bir fonksiyonun calisma suresini mikro-saniye cinsinden olcer.
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

// Sonucu tutarli formatta yazdirma.
static void printResult(const string& name, const Result& r, long long us) {
    cout << setw(22) << left << name
         << " | bestSum=" << setw(12) << r.bestSum
         << " [" << r.left << "," << r.right << "]"
         << " | time=" << us << " us\n";
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------------------
    // INPUT: ayni veriyle tum yontemler
    // ---------------------------
    // Varsayilan: rastgele uret ve karsilastir.
    int N = 2000;              // varsayilan N (buyukse O(n^3) yavas olabilir)
    int lo = -100, hi = 100;   // deger araligi
    int seed = 12345;

    // Basit komut satiri: maximum_subsequence.exe [N] [seed]
    if (argc > 1) {
        try { N = stoi(argv[1]); } catch (...) { cerr << "Gecersiz N, bir tamsayi olmali\n"; return 1; }
    }
    if (argc > 2) {
        try { seed = stoi(argv[2]); } catch (...) { cerr << "Gecersiz seed, bir tamsayi olmali\n"; return 1; }
    }
    if (N <= 0) { cerr << "N > 0 olmali\n"; return 1; }

    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(lo, hi);

    vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = dist(rng);

    cout << "N=" << N << " (degerler [" << lo << "," << hi << "]) seed=" << seed << "\n\n";

    // ---------------------------
    // RUN + TIME
    // ---------------------------
    // O(n^3) cok yavas; buyuk N icin atla (ornegin: N>600)
    bool ranO3 = false;
    Result r3{0, -1, -1}; long long t3 = 0;
    if (N <= 600) {
        ranO3 = true;
        auto p = timedRun(A, maxSubarray_O3);
        r3 = p.first; t3 = p.second;
    } else {
        cout << "O(n^3) Brute Force atlandi (N cok buyuk). Calistirmak icin daha kucuk N kullanin.\n\n";
    }

    auto [r2, t2]  = timedRun(A, maxSubarray_O2);
    auto [rnl, tnl]= timedRun(A, maxSubarray_Onlogn);
    auto [rk, tk]  = timedRun(A, maxSubarray_Kadane);

    // ---------------------------
    // VALIDATION (ayni sonucu buluyorlar mi?)
    // ---------------------------
    bool sameSum = true;
    long long expected = r2.bestSum;
    if (ranO3 && r3.bestSum != expected) sameSum = false;
    if (rnl.bestSum != expected) sameSum = false;
    if (rk.bestSum != expected) sameSum = false;

    cout << "Tum toplamlar esit mi? " << (sameSum ? "EVET" : "HAYIR") << "\n\n";

    if (ranO3) printResult("O(n^3) Brute Force", r3, t3);
    else cout << setw(22) << left << string("O(n^3) Brute Force") << " | atlandi\n";
    printResult("O(n^2) Improved",    r2, t2);
    printResult("O(n log n) D&C",     rnl, tnl);
    printResult("O(n) Kadane",        rk, tk);

    return 0;
}
