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

// ------------------------------------------------------------
// Dizi toplamı
// ------------------------------------------------------------
int sumArr(int A[], int N) {
    // Base case
    if (N == 1) return A[0];

    // Recursive step
    int partialSum = sumArr(A, N - 1);

    // Merge
    return partialSum + A[N - 1];
}

// ------------------------------------------------------------
// a^n
// ------------------------------------------------------------
int power(int a, int n) {
    // Base case
    if (n == 0) return 1;

    // Recursive step
    int partialPower = power(a, n - 1);

    // Merge
    return partialPower * a;
}

// ------------------------------------------------------------
// Fibonacci
// ------------------------------------------------------------
int fibonacci(int n) {
    // Base case
    if (n == 0 || n == 1) return n;

    // Recursive step
    int partialFib = fibonacci(n - 1);

    // Merge
    return partialFib + fibonacci(n - 2);
}   

// ------------------------------------------------------------
// Tower of Hanoi
// ------------------------------------------------------------
void towerOfHanoi(int n, int src, int dest, int aux) {
    // Base case
    if (n <= 0) return ;

    // Recursive step
    towerOfHanoi(n - 1, src, aux, dest);

    printf("Move disk %d from %d to %d\n", n, src, dest);
    // Merge
    towerOfHanoi(n - 1, aux, dest, src);
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