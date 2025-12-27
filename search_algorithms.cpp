#include <bits/stdc++.h>
using namespace std;
/* 
3. ARAMA ALGORİTMALARI
- İleri Yönlü Lineer Arama
- Geri Yönlü Lineer Arama
- İkili Arama
*/

// ---------------------------------------------------------
// İleri Yönlü Lineer Arama
// ---------------------------------------------------------
int linearSearchForward(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // Bulduysa indeksi dondurur
        }
    }
    return -1; // Bulamadıysa -1 dondurur
}

// ---------------------------------------------------------
// Geri Yönlü Lineer Arama
// ---------------------------------------------------------
int linearSearchBackward(int arr[], int n, int target) {
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == target) {
            return i; // Bulduysa indeksi dondurur
        }
    }
    return -1; // Bulamadıysa -1 dondurur
}

// ---------------------------------------------------------
// İkili Arama
// ---------------------------------------------------------
int binarySearch(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // Orta nokta hesaplama
        
        if (arr[mid] == target) {
            return mid; // Bulduysa indeksi dondurur
        } else if (arr[mid] < target) {
            left = mid + 1; // Arama aralığını sağa kaydır
        } else {
            right = mid - 1; // Arama aralığını sola kaydır
        }
    }
    
    return -1; // Bulamadıysa -1 dondurur
}

// Yardımcı fonksiyon: Zaman ölçümü ve çalıştırma
void measureTime(string algName, int(*func)(int[], int, int), int arr[], int n, int target) {
    auto start = chrono::high_resolution_clock::now();
    int result = func(arr, n, target);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> duration = end - start;
    
    cout << algName << " -> Sonuc: " << result 
         << " | Sure: " << fixed << setprecision(5) << duration.count() << " ms" << endl;
}

int main() {
    // Türkçe karakterler için 
    setlocale(LC_ALL, "Turkish");
    
    // Hızlandırma
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 1. Veri Hazırlığı
    // Binary Search için dizinin sıralı olması gerekir.
    const int N = 10000000; // 10 Milyon eleman
    int* arr = new int[N];  // Heap üzerinde yer ayıralım (Stack taşabilir)
    
    // Diziyi sıralı bir şekilde dolduralım
    for (int i = 0; i < N; i++) {
        arr[i] = i; 
    }
    
    // Test Senaryosu: Dizinin sonlarına yakın bir elemanı aramak
    // Bu senaryo, ileri yönlü arama için kötü, geri yönlü için iyi, binary search için logaritmik performansı gösterir.
    int target = N - 1000; 
    
    cout << "Veri Seti Boyutu: " << N << endl;
    cout << "Aranan Eleman: " << target << endl;
    cout << "---------------------------------------------------------" << endl;
    
    // 2. Algoritmaların Çalıştırılması ve Kıyaslanması
    
    // İleri Yönlü Lineer Arama
    measureTime("Ileri Yonlu Lineer Arama", linearSearchForward, arr, N, target);
    
    // Geri Yönlü Lineer Arama
    measureTime("Geri Yonlu Lineer Arama", linearSearchBackward, arr, N, target);
    
    // İkili Arama (Binary Search)
    measureTime("Ikili Arama (Binary Search)", binarySearch, arr, N, target);
    
    // Bellek temizliği
    delete[] arr;
    
    return 0;
}