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
int sumArr(int A[], int N, long long& callCount) {
    ++callCount;
    // Base case
    if (N == 1) return A[0];

    // Recursive step
    int partialSum = sumArr(A, N - 1, callCount);

    // Merge
    return partialSum + A[N - 1];
}

// ------------------------------------------------------------
// a^n
// ------------------------------------------------------------
int power(int a, int n, long long& callCount) {
    ++callCount;
    // Base case
    if (n == 0) return 1;

    // Recursive step
    int partialPower = power(a, n - 1, callCount);

    // Merge
    return partialPower * a;
}

// ------------------------------------------------------------
// Fibonacci
// ------------------------------------------------------------
int fibonacci(int n, long long& callCount) {
    ++callCount;
    // Base case
    if (n == 0 || n == 1) return n;

    // Recursive step
    int partialFib = fibonacci(n - 1, callCount);

    // Merge
    return partialFib + fibonacci(n - 2, callCount);
}   

// ------------------------------------------------------------
// Tower of Hanoi
// ------------------------------------------------------------
void towerOfHanoi(int n, int src, int dest, int aux, long long& callCount) {
    ++callCount;
    // Base case
    if (n <= 0) return ;

    // Recursive step
    towerOfHanoi(n - 1, src, aux, dest, callCount);

    // printf("Move disk %d from %d to %d\n", n, src, dest); // Cikti karmasikligini azaltmak icin commentledim
    // Merge
    towerOfHanoi(n - 1, aux, dest, src, callCount);
}   

// ------------------------------------------------------------
// Recursive Digit Sum
// ------------------------------------------------------------
int recursiveDigitSum(int n, long long& callCount) {
    ++callCount;
    // Base case
    if (n < 10) {
        return n;
    }
    
    int toplam = 0;
    // Sayının rakamlarını topla
    while (n > 0) {
        toplam += n % 10;
        n /= 10;
    }
    
    // Elde edilen toplam ile fonksiyonu tekrar çağır
    return recursiveDigitSum(toplam, callCount);
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

    // ---------------------------------------------------------
    // Cikti formati
    // ---------------------------------------------------------
    cout << left << setw(25) << "Problem" 
         << setw(20) << "Girdi" 
         << setw(15) << "Sonuc" 
         << setw(15) << "Cagri Sayisi" << "\n";
    cout << string(75, '-') << "\n";

    // 1+2+...+N
    long long calls = 0;
    int res1 = sumOnetoN(N, calls);
    cout << left << setw(25) << "1+2+...+N" 
         << setw(20) << ("N=" + to_string(N)) 
         << setw(15) << res1 
         << setw(15) << calls << "\n";

    // Dizi Toplami
    calls = 0;
    int Arr[] = {1, 2, 3, 4, 5}; // Ornek dizi
    int arrSize = sizeof(Arr)/sizeof(Arr[0]);
    int res2 = sumArr(Arr, arrSize, calls);
    cout << left << setw(25) << "Dizi Toplami" 
         << setw(20) << "Arr size=5" 
         << setw(15) << res2 
         << setw(15) << calls << "\n";

    // a^n
    calls = 0;
    int base = 2;
    int res3 = power(base, N, calls);
    cout << left << setw(25) << "a^N" 
         << setw(20) << ("a=2, N=" + to_string(N)) 
         << setw(15) << res3 
         << setw(15) << calls << "\n";

    // Fibonacci
    calls = 0;
    // Fibonacci degeri hizli buyudugu icin kucuk bir N kullanalim veya N'i direkt kullanalim
    // Warning: N cok buyukse bu cok yavas calisir (exponential)
    int effN = (N > 15) ? 15 : N; // Hizli sonuc gormek icin limit
    int res4 = fibonacci(effN, calls);
    cout << left << setw(25) << "Fibonacci" 
         << setw(20) << ("N=" + to_string(effN)) 
         << setw(15) << res4 
         << setw(15) << calls << "\n";
    
    // Tower of Hanoi
    calls = 0;
    int hanoiN = (N > 10) ? 4 : N; // Cok buyuk N icin kisitlama
    towerOfHanoi(hanoiN, 1, 3, 2, calls); // return void
    cout << left << setw(25) << "Tower of Hanoi" 
         << setw(20) << ("N=" + to_string(hanoiN)) 
         << setw(15) << "-" 
         << setw(15) << calls << "\n";

    // Recursive Digit Sum
    calls = 0;
    int digitNum = 9875;
    int res5 = recursiveDigitSum(digitNum, calls);
    cout << left << setw(25) << "Recursive Digit Sum" 
         << setw(20) << ("Num=" + to_string(digitNum)) 
         << setw(15) << res5 
         << setw(15) << calls << "\n";

    return 0;
}