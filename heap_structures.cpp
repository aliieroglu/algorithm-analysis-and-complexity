/* 
5. HEAP YAPILARI 
- Binary Heap 
- findmin, deletemin(Heapify), insertHeap 
- Buildheap (maxHeap ve minHeap) 
- decreaseKey, increaseKey, deleteKey 
- Merge(H1, H2)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class MinHeap {
public:
    MinHeap() {
        // 1-indexed yapi: 0. indis bos birakilir.
        heap_.push_back(0);
    }

    int size() const {
        return static_cast<int>(heap_.size()) - 1;
    }

    bool empty() const {
        return size() == 0;
    }

    vector<int> elements() const {
        return vector<int>(heap_.begin() + 1, heap_.end());
    }

    bool findMin(int& out) const {
        if (empty()) {
            return false;
        }
        out = heap_[1];
        return true;
    }

    bool deleteMin(int& out) {
        if (empty()) {
            return false;
        }
        out = heap_[1];
        heap_[1] = heap_.back();
        heap_.pop_back();
        if (!empty()) {
            percolateDown(1);
        }
        return true;
    }

    void insertKey(int key) {
        heap_.push_back(key);
        percolateUp(size());
    }

    void buildHeap(const vector<int>& data) {
        // Bottom-up heap insasi.
        heap_.assign(1, 0);
        heap_.insert(heap_.end(), data.begin(), data.end());
        for (int i = size() / 2; i >= 1; i--) {
            percolateDown(i);
        }
    }

    bool decreaseKey(int index, int newValue) {
        if (index < 1 || index > size()) {
            return false;
        }
        if (newValue > heap_[index]) {
            return false;
        }
        heap_[index] = newValue;
        percolateUp(index);
        return true;
    }

    bool increaseKey(int index, int newValue) {
        if (index < 1 || index > size()) {
            return false;
        }
        if (newValue < heap_[index]) {
            return false;
        }
        heap_[index] = newValue;
        percolateDown(index);
        return true;
    }

    bool deleteKey(int index, int& removed) {
        if (index < 1 || index > size()) {
            return false;
        }
        removed = heap_[index];
        if (index == size()) {
            heap_.pop_back();
            return true;
        }
        heap_[index] = heap_.back();
        heap_.pop_back();
        if (index > 1 && heap_[index] < heap_[index / 2]) {
            percolateUp(index);
        } else {
            percolateDown(index);
        }
        return true;
    }

    MinHeap mergeByInsert(const MinHeap& other) const {
        MinHeap result = *this;
        vector<int> otherData = other.elements();
        for (int value : otherData) {
            result.insertKey(value);
        }
        return result;
    }

    MinHeap mergeByBuild(const MinHeap& other) const {
        vector<int> combined = elements();
        vector<int> otherData = other.elements();
        combined.insert(combined.end(), otherData.begin(), otherData.end());
        MinHeap result;
        result.buildHeap(combined);
        return result;
    }

    void print(const string& label) const {
        cout << label << " (size=" << size() << "): ";
        for (int i = 1; i <= size(); i++) {
            cout << heap_[i] << (i == size() ? "" : " ");
        }
        cout << endl;
    }

private:
    void percolateUp(int index) {
        // Ebeveyn daha buyukse yukari tasima.
        while (index > 1) {
            int parent = index / 2;
            if (heap_[parent] <= heap_[index]) {
                break;
            }
            swap(heap_[parent], heap_[index]);
            index = parent;
        }
    }

    void percolateDown(int index) {
        // En kucuk cocugu bularak asagi tasima.
        int n = size();
        while (true) {
            int left = index * 2;
            int right = left + 1;
            int smallest = index;
            if (left <= n && heap_[left] < heap_[smallest]) {
                smallest = left;
            }
            if (right <= n && heap_[right] < heap_[smallest]) {
                smallest = right;
            }
            if (smallest == index) {
                break;
            }
            swap(heap_[index], heap_[smallest]);
            index = smallest;
        }
    }

    vector<int> heap_;
};

int main() {
    vector<int> data = {10, 4, 7, 1, 3, 9, 2, 8, 6, 5};

    MinHeap heap;
    heap.buildHeap(data);
    heap.print("Ilk heap");

    int minValue = 0;
    if (heap.findMin(minValue)) {
        cout << "findMin sonucu: " << minValue << endl;
    }

    heap.insertKey(0);
    heap.print("insertKey(0) sonrasi");
    if (heap.findMin(minValue)) {
        cout << "findMin sonucu: " << minValue << endl;
    }

    if (heap.deleteMin(minValue)) {
        cout << "deleteMin sonucu: " << minValue << endl;
    }
    heap.print("deleteMin sonrasi");

    if (heap.decreaseKey(5, 1)) {
        cout << "decreaseKey indeks 5 -> 1" << endl;
    }
    heap.print("decreaseKey sonrasi");

    if (heap.increaseKey(3, 20)) {
        cout << "increaseKey indeks 3 -> 20" << endl;
    }
    heap.print("increaseKey sonrasi");

    int removed = 0;
    if (heap.deleteKey(4, removed)) {
        cout << "deleteKey indeks 4 silinen: " << removed << endl;
    }
    heap.print("deleteKey sonrasi");

    MinHeap heapA;
    heapA.buildHeap({12, 3, 14, 6});
    MinHeap heapB;
    heapB.buildHeap({9, 2, 11, 1});

    heapA.print("Heap A");
    heapB.print("Heap B");

    MinHeap mergedInsert = heapA.mergeByInsert(heapB);
    mergedInsert.print("Insert ile birlesim (O(N log N))");

    MinHeap mergedBuild = heapA.mergeByBuild(heapB);
    mergedBuild.print("Build ile birlesim (O(N))");

    return 0;
}
