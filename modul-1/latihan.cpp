#include <iostream>
using namespace std;

struct Mahasiswa {
    string NIM;
    string NamaMhs;
    int Nilai;
};

// Fungsi untuk melakukan Shell Sort
void shellSort(Mahasiswa arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Mahasiswa temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].NamaMhs > temp.NamaMhs; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    int n = 5;
    Mahasiswa mhs[n] = {
        {"2201", "Budi", 85},
        {"2204", "Ani", 90},
        {"2202", "Doni", 75},
        {"2208", "Citra", 95},
        {"2206", "Eka", 80}
    };

    // Mengurutkan mahasiswa berdasarkan NamaMhs
    shellSort(mhs, n);

    // Menampilkan hasil
    cout << "\nData mahasiswa setelah diurutkan berdasarkan NamaMhs:\n";
    for (int i = 0; i < n; i++) {
        cout << mhs[i].NIM << " - " << mhs[i].NamaMhs << " - " << mhs[i].Nilai << endl;
    }
    return 0;
}