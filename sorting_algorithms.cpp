#include <bits/stdc++.h>
using namespace std;
/* 
4. SIRALAMA ALGORİTMALARI 
- Selection, Bubble, Insertion 
- Merge, Quick, Heap 
- Counting Sort (Satellite Data) 
- Radix Sort 
- External Sorting 
Tüm sıralama algoritmaları için çalışma süresi ölçümü 
zorunludur (chrono).
 */

// ------------------------------------------------------------




// Selection Sort
// ------------------------------------------------------------
void selectionSort(int A[], int N) {
    for (int i = 0; i < N - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < N; j++) {
            if (A[j] < A[minIdx]) {
                minIdx = j;
            }
        }
        swap(A[i], A[minIdx]);
    }
}

// Bubble Sort
// ------------------------------------------------------------
void bubbleSort(int A[], int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
            }
        }
    }
}

// Insertion Sort
// ------------------------------------------------------------
void insertionSort(int A[], int N) {
    for (int i = 1; i < N; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}


// Merge Sort
// ------------------------------------------------------------
void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }

    while (i < n1) {
        A[k++] = L[i++];
    }
    while (j < n2) {
        A[k++] = R[j++];
    }
}

void mergeSort(int A[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}   

// Quick Sort
// ------------------------------------------------------------
int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (A[j] < pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return i + 1;
}

void quickSort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}

// Heap Sort
// ------------------------------------------------------------
void heapify(int A[], int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && A[left] > A[largest])
        largest = left;
    if (right < N && A[right] > A[largest])
        largest = right;
    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, N, largest);
    }
}

void heapSort(int A[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(A, N, i);
    for (int i = N - 1; i > 0; i--) {
        swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}


// Counting Sort (Satellite Data)
// ------------------------------------------------------------
void countingSort(int A[], int N, int maxVal) {
    vector<int> count(maxVal + 1, 0);
    for (int i = 0; i < N; i++) {
        count[A[i]]++;
    }
    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i]-- > 0) {
            A[index++] = i;
        }
    }
}

// Radix Sort
// ------------------------------------------------------------
int getMax(int A[], int N) {
    int maxVal = A[0];
    for (int i = 1; i < N; i++) {
        if (A[i] > maxVal)
            maxVal = A[i];
    }
    return maxVal;
}

void countingSortByDigit(int A[], int N, int exp) {
    vector<int> output(N);
    int count[10] = {0};

    for (int i = 0; i < N; i++) {
        int digit = (A[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = N - 1; i >= 0; i--) {
        int digit = (A[i] / exp) % 10;
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }
    for (int i = 0; i < N; i++) {
        A[i] = output[i];
    }
}

void radixSort(int A[], int N) {
    int maxVal = getMax(A, N);
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(A, N, exp);
    }
}

// External Sorting
// ------------------------------------------------------------
// External Merge Sort aciklama (adim adim):
// 1) Girdi dosyasini parcalara (chunk) boleriz, her parcayi RAM'e aliriz.
// 2) Her parcayi kendi icinde siralar ve gecici bir "run" dosyasina yazariz.
// 3) Tum run dosyalarini ayni anda acip kucukten buyuge k-way merge yapariz.
// 4) En kucuk elemani ciktiya yazar, o run dosyasindan siradaki sayiyi heap'e ekleriz.
// 5) Tum run dosyalari bitince cikti dosyasi sirali olur ve temp dosyalar silinir.
string makeTempFileName(size_t index) {
    return "external_run_" + to_string(index) + ".txt";
}

void writeRunToFile(const vector<int>& run, const string& filename) {
    ofstream out(filename);
    for (int value : run) {
        out << value << '\n';
    }
}

vector<string> createRuns(const string& inputFile, size_t chunkSize) {
    ifstream in(inputFile);
    if (!in) {
        return {};
    }

    // 1) Parcalama: dosyadan chunkSize kadar veri al, sirala, run dosyasina yaz.
    vector<string> tempFiles;
    vector<int> chunk;
    chunk.reserve(chunkSize);

    int value = 0;
    size_t runIndex = 0;
    while (in >> value) {
        chunk.push_back(value);
        if (chunk.size() == chunkSize) {
            sort(chunk.begin(), chunk.end());
            string tempName = makeTempFileName(runIndex++);
            writeRunToFile(chunk, tempName);
            tempFiles.push_back(tempName);
            chunk.clear();
        }
    }
    if (!chunk.empty()) {
        sort(chunk.begin(), chunk.end());
        string tempName = makeTempFileName(runIndex++);
        writeRunToFile(chunk, tempName);
        tempFiles.push_back(tempName);
        chunk.clear();
    }

    return tempFiles;
}

void mergeRuns(const vector<string>& tempFiles, const string& outputFile) {
    ofstream out(outputFile);
    if (tempFiles.empty()) {
        return;
    }

    // 2) K-way merge icin her run dosyasindan ilk elemani oku.
    vector<ifstream> runStreams;
    runStreams.reserve(tempFiles.size());
    vector<int> currentValues(tempFiles.size(), 0);
    vector<bool> hasValue(tempFiles.size(), false);

    for (size_t i = 0; i < tempFiles.size(); i++) {
        runStreams.emplace_back(tempFiles[i]);
        if (runStreams.back() >> currentValues[i]) {
            hasValue[i] = true;
        }
    }

    using Node = pair<int, size_t>;
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;

    // 3) Heap'e (min) her run'in mevcut elemanini ekle.
    for (size_t i = 0; i < hasValue.size(); i++) {
        if (hasValue[i]) {
            minHeap.push({currentValues[i], i});
        }
    }

    // 4) En kucuk elemani ciktiya yaz, ayni run'dan yeni eleman oku.
    while (!minHeap.empty()) {
        Node node = minHeap.top();
        minHeap.pop();
        int val = node.first;
        size_t idx = node.second;
        out << val << '\n';

        if (runStreams[idx] >> currentValues[idx]) {
            minHeap.push({currentValues[idx], idx});
        }
    }

    // 5) Temp dosyalari temizle.
    for (const string& tempFile : tempFiles) {
        remove(tempFile.c_str());
    }
}

void externalMergeSort(const string& inputFile, const string& outputFile, size_t chunkSize) {
    vector<string> tempFiles = createRuns(inputFile, chunkSize);
    mergeRuns(tempFiles, outputFile);
}

// ---------------------------------------------------------------------------
// Main function to demonstrate sorting algorithms with timing.
int main() {
    const int N = 3000;
    const int maxValue = 10000;
    const size_t externalChunkSize = 500;
    const string externalInput = "external_input.txt";
    const string externalOutput = "external_output.txt";

    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, maxValue);

    vector<int> data;
    data.reserve(N);
    for (int i = 0; i < N; i++) {
        data.push_back(dist(rng));
    }

    auto timeSort = [&](const string& name, const function<void(vector<int>&)>& sorter) {
        vector<int> arr = data;
        auto start = chrono::high_resolution_clock::now();
        sorter(arr);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << name << " time: " << duration << " us" << endl;
    };

    timeSort("Selection Sort", [&](vector<int>& arr) {
        selectionSort(arr.data(), static_cast<int>(arr.size()));
    });

    timeSort("Bubble Sort", [&](vector<int>& arr) {
        bubbleSort(arr.data(), static_cast<int>(arr.size()));
    });

    timeSort("Insertion Sort", [&](vector<int>& arr) {
        insertionSort(arr.data(), static_cast<int>(arr.size()));
    });

    timeSort("Merge Sort", [&](vector<int>& arr) {
        mergeSort(arr.data(), 0, static_cast<int>(arr.size()) - 1);
    });

    timeSort("Quick Sort", [&](vector<int>& arr) {
        quickSort(arr.data(), 0, static_cast<int>(arr.size()) - 1);
    });

    timeSort("Heap Sort", [&](vector<int>& arr) {
        heapSort(arr.data(), static_cast<int>(arr.size()));
    });

    timeSort("Counting Sort", [&](vector<int>& arr) {
        int maxVal = *max_element(arr.begin(), arr.end());
        countingSort(arr.data(), static_cast<int>(arr.size()), maxVal);
    });

    timeSort("Radix Sort", [&](vector<int>& arr) {
        radixSort(arr.data(), static_cast<int>(arr.size()));
    });

    ofstream externalIn(externalInput);
    for (int value : data) {
        externalIn << value << '\n';
    }
    externalIn.close();

    auto runStart = chrono::high_resolution_clock::now();
    vector<string> tempFiles = createRuns(externalInput, externalChunkSize);
    auto runEnd = chrono::high_resolution_clock::now();
    auto runDuration = chrono::duration_cast<chrono::microseconds>(runEnd - runStart).count();
    cout << "External Run Creation time: " << runDuration << " us" << endl;

    auto mergeStart = chrono::high_resolution_clock::now();
    mergeRuns(tempFiles, externalOutput);
    auto mergeEnd = chrono::high_resolution_clock::now();
    auto mergeDuration = chrono::duration_cast<chrono::microseconds>(mergeEnd - mergeStart).count();
    cout << "External Merge time: " << mergeDuration << " us" << endl;

    return 0;
}
