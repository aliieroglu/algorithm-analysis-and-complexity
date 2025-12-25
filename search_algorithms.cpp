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
