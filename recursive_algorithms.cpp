#include <bits/stdc++.h>
using namespace std;

/* 
2. REKÜRSİF ALGORİTMALAR 
- 1+2+...+N 
- Dizi toplamı 
- a^n   
- Fibonacci 
- Tower of Hanoi 
- Recursive Digit Sum 
Her problem için rekürsif çağrı sayısı hesaplanmalıdır.

*/

// ------------------------------------------------------------
// 1_+2+...+N
// ------------------------------------------------------------
int sumOnetoN(int n, long long& callCount) {
    // sayac
    ++callCount;

    // Base case
    if (n == 1) return 1;

    // Recursive step
    int partialSum = sumOnetoN(n - 1, callCount);

    // Merge
    return partialSum + n;
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 10; // varsayilan N

    // Komut satiri: recursive_algorithms.exe [N]
    if (argc > 1) {
        try { N = stoi(argv[1]); } catch (...) { cerr << "Gecersiz N, bir tamsayi olmali\n"; return 1; }
    }
    if (N <= 0) { cerr << "N > 0 olmali\n"; return 1; }

    // 1+2+...+N
    long long callCount1 = 0;
    int sum = sumOnetoN(N, callCount1);
    cout << "1 + 2 + ... + " << N << " = " << sum << "\n";
    cout << "sumOnetoN cagrilma sayisi: " << callCount1 << "\n";

    return 0;
}