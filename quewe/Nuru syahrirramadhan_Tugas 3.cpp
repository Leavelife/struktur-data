#include <iostream>
#include <queue>
#include <limits>
using namespace std;

// Fungsi untuk mencari elemen dalam queue
bool searchQueue(queue<int> q, int value) {
    while (!q.empty()) {
        if (q.front() == value)
            return true;
        q.pop();
    }
    return false;
}

// Fungsi untuk mengedit elemen dalam queue
void editQueue(queue<int> &q, int oldValue, int newValue) {
    queue<int> temp;
    bool found = false;
    while (!q.empty()) {
        if (q.front() == oldValue && !found) {
            temp.push(newValue);
            found = true;
        } else {
            temp.push(q.front());
        }
        q.pop();
    }
    q = temp;
}

// Fungsi untuk menghitung total, rata-rata, nilai terbesar, dan nilai terkecil
void queueStatistics(queue<int> q) {
    if (q.empty()) {
        cout << "Queue kosong!" << endl;
        return;
    }
    int total = 0, count = 0, maxVal = numeric_limits<int>::min(), minVal = numeric_limits<int>::max();
    while (!q.empty()) {
        int val = q.front();
        total += val;
        maxVal = max(maxVal, val);
        minVal = min(minVal, val);
        count++;
        q.pop();
    }
    cout << "Total: " << total << endl;
    cout << "Rata-rata: " << (double)total / count << endl;
    cout << "Nilai terbesar: " << maxVal << endl;
    cout << "Nilai terkecil: " << minVal << endl;
}

int main() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    cout << "Mencari elemen 20 dalam queue: " << (searchQueue(q, 20) ? "Ditemukan" : "Tidak ditemukan") << endl;
    editQueue(q, 20, 25);
    cout << "Queue setelah mengedit 20 menjadi 25: " << endl;
    queue<int> temp = q;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;

    queueStatistics(q);
    return 0;
}