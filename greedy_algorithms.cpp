#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// ------------------------------------------------------------
// 1) Is Zamanlama (Shortest Processing Time)
// Amac: Ortalama tamamlanma suresini en aza indirmek.
// ------------------------------------------------------------
vector<int> jobScheduling(const vector<int>& times, double& averageCompletion) {
    vector<int> ordered = times;
    sort(ordered.begin(), ordered.end());

    long long totalCompletion = 0;
    long long current = 0;
    for (int t : ordered) {
        current += t;
        totalCompletion += current;
    }

    averageCompletion = ordered.empty() ? 0.0 : static_cast<double>(totalCompletion) / ordered.size();
    return ordered;
}

// ------------------------------------------------------------
// 2) Aktivite Zamanlama (Activity Selection)
// Amac: Cakismayan maksimum sayida aktivite secmek.
// ------------------------------------------------------------
struct Activity {
    int start;
    int finish;
};

vector<Activity> activitySelection(vector<Activity> activities) {
    sort(activities.begin(), activities.end(),
         [](const Activity& a, const Activity& b) { return a.finish < b.finish; });

    vector<Activity> selected;
    int lastFinish = -1;
    for (const auto& act : activities) {
        if (act.start >= lastFinish) {
            selected.push_back(act);
            lastFinish = act.finish;
        }
    }
    return selected;
}

void printJobSchedulingSteps(const vector<int>& times) {
    cout << "Is Zamanlama (Shortest Processing Time)" << endl;
    cout << "Problemli kume (is sureleri): ";
    for (int t : times) {
        cout << t << " ";
    }
    cout << endl;

    double avgCompletion = 0.0;
    vector<int> order = jobScheduling(times, avgCompletion);

    cout << "Siralama (kisa is once): ";
    for (int t : order) {
        cout << t << " ";
    }
    cout << endl;

    cout << "Adim adim cozum:" << endl;
    long long current = 0;
    int step = 1;
    for (int t : order) {
        current += t;
        cout << "Adim " << step++ << ": " << t
             << " secildi, birikimli tamamlanma=" << current << endl;
    }
    cout << "Ortalama tamamlanma suresi: " << avgCompletion << endl;
}

void printActivitySelectionSteps(vector<Activity> activities) {
    cout << "Aktivite Zamanlama (Activity Selection)" << endl;
    cout << "Problemli kume (baslangic,bitis): ";
    for (const auto& act : activities) {
        cout << "[" << act.start << "," << act.finish << "] ";
    }
    cout << endl;

    sort(activities.begin(), activities.end(),
         [](const Activity& a, const Activity& b) { return a.finish < b.finish; });

    cout << "Bitis zamanina gore siralama: ";
    for (const auto& act : activities) {
        cout << "[" << act.start << "," << act.finish << "] ";
    }
    cout << endl;

    cout << "Adim adim cozum:" << endl;
    vector<Activity> selected;
    int lastFinish = -1;
    int step = 1;
    for (const auto& act : activities) {
        if (act.start >= lastFinish) {
            selected.push_back(act);
            lastFinish = act.finish;
            cout << "Adim " << step << ": [" << act.start << "," << act.finish
                 << "] secildi, son bitis=" << lastFinish << endl;
        } else {
            cout << "Adim " << step << ": [" << act.start << "," << act.finish
                 << "] atlandi (cakisma), son bitis=" << lastFinish << endl;
        }
        ++step;
    }

    cout << "Secilen aktiviteler: ";
    for (const auto& act : selected) {
        cout << "[" << act.start << "," << act.finish << "] ";
    }
    cout << endl;
    cout << "Toplam secilen aktivite: " << selected.size() << endl;
}

// ------------------------------------------------------------
// 3) Huffman Kodlama (Encode / Decode)
// Amac: SIk gecen karakterlere kisa, az gecenlere uzun kod vermek.
// ------------------------------------------------------------
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(HuffmanNode* l, HuffmanNode* r)
        : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

struct NodeCompare {
    bool operator()(const HuffmanNode* a, const HuffmanNode* b) const {
        return a->freq > b->freq;
    }
};

HuffmanNode* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, NodeCompare> pq;
    for (const auto& kv : freq) {
        pq.push(new HuffmanNode(kv.first, kv.second));
    }

    if (pq.empty()) {
        return nullptr;
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        pq.push(new HuffmanNode(left, right));
    }

    return pq.top();
}

void buildCodes(HuffmanNode* node, const string& path, unordered_map<char, string>& codes) {
    if (!node) {
        return;
    }
    if (!node->left && !node->right) {
        codes[node->ch] = path.empty() ? "0" : path;
        return;
    }
    buildCodes(node->left, path + "0", codes);
    buildCodes(node->right, path + "1", codes);
}

string huffmanEncode(const string& text, unordered_map<char, string>& codes) {
    HuffmanNode* root = buildHuffmanTree(text);
    buildCodes(root, "", codes);

    string encoded;
    for (char c : text) {
        encoded += codes[c];
    }
    return encoded;
}

string huffmanDecode(HuffmanNode* root, const string& encoded) {
    string decoded;
    if (!root) {
        return decoded;
    }

    HuffmanNode* current = root;
    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;
        if (current && !current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

void freeTree(HuffmanNode* node) {
    if (!node) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main() {
    cout << "Greedy Algoritmalar Ornek Cikti" << endl;
    cout << "--------------------------------" << endl;

    // 1) Is Zamanlama
    vector<int> jobTimes = {3, 8, 10, 15};
    printJobSchedulingSteps(jobTimes);
    cout << endl;

    // 2) Aktivite Zamanlama
    cout << "*****" << endl;
    vector<Activity> acts = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
    };
    printActivitySelectionSteps(acts);
    cout << endl;

    // 3) Huffman Kodlama
    cout << "*****" << endl;
    string text = "huffman ornegi";
    unordered_map<char, string> codes;
    HuffmanNode* root = buildHuffmanTree(text);
    buildCodes(root, "", codes);

    string encoded;
    for (char c : text) {
        encoded += codes[c];
    }

    string decoded = huffmanDecode(root, encoded);

    cout << "Huffman Kodlama" << endl;
    cout << "Metin: " << text << endl;
    cout << "Kodlar: ";
    for (const auto& kv : codes) {
        cout << kv.first << ":" << kv.second << " ";
    }
    cout << endl;
    cout << "Kodlanmis: " << encoded << endl;
    cout << "Cozulmus: " << decoded << endl;

    freeTree(root);

    return 0;
}
