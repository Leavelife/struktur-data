#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

int data1[10], data2[10]; 
int n;

void inputData() {
    cout << endl << "Masukkan jumlah data: "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Masukkan data ke " << (i + 1) << " : ";
        cin >> data1[i];
        data2[i] = data1[i];
    }
}
void bubbleSort() {
    clock_t start, end;
    start = clock();

    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            if (data1[j] < data1[j - 1]) {
                int t; 
                t = data1[j - 1];
                data1[j - 1] = data1[j];
                data1[j] = t;
            }
            for (int a = 0; a < n; a++) {
                cout << data1[a] << ", ";
            } 
            cout << endl;
        }
    }
    end = clock();
    double waktu = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Waktu eksekusi: " << waktu << " detik" << std::endl;
}
void selectionSort() {
    clock_t start, end;
    start = clock();
    int pos;
    for (int i = 0; i < n - 1; i++) {
        cout << endl << "Tahap " << i + 1 << endl;
        pos = i;
        for(int j = i + 1; j < n; j++) {
            if(data1[j] < data1[pos]) {
                cout << "pos: " << data1[pos] << " dengan " << data1[j] << endl;
                pos = j;
                cout << "menjadi pos: " << data1[pos] << " dengan " << data1[j] << endl;
            } else {
                cout << "pos: " << data1[pos] << " dengan " << data1[j] << endl;
            }
            for (int a = 0; a < n; a++) {
                cout << data1[a] << ", ";
            } 
            cout << endl;
        }
        if(pos != i) {
            int t; 
            t = data1[i];
            data1[i] = data1[pos];
            data1[pos] = t;
            cout << "Tukar angka " << data1[pos] << " dan " << data1[i]<< endl;
        } else {
            cout << data1[i] << " tidak ditukar " << data1[pos]<< endl;
        }
        for (int a = 0; a < n; a++) {
            cout << data1[a] << ", ";
        } 
        cout << endl;
    }
    end = clock();
    double waktu = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Waktu eksekusi: " << waktu << " detik" << std::endl;
}
void insertionSort() {
    clock_t start, end;
    start = clock();
    int temp;
    for (int i = 1; i < n; i++) {
        cout << endl << "Tahap " << i << endl;
        temp = data1[i];
        int j = i - 1;
        while (data1[j] < temp && j >= 0) {
            data1[j + 1] = data1[j];
            j--;
        }
        data1[j + 1] = temp;
        for (int a = 0; a < n; a++) {
            cout << data1[a] << ", ";
        } 
        cout << endl;
    }
    end = clock();
    double waktu = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Waktu eksekusi: " << waktu << " detik" << std::endl;
}

int main() {
    int pilihan;
    do {
        cout << endl << "1. Input Data" << endl;
        cout << "2. Bubble Sort" << endl;
        cout << "3. Selection Sort" << endl;
        cout << "4. Insertion Sort" << endl;
        cout << "5. Exit" << endl;
        cout << "Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputData();
                break;
            case 2:
                bubbleSort();
                break;
            case 3:
                selectionSort();
                break;
            case 4:
                insertionSort();
                break;
            default:
                break;
        }
    } while (pilihan != 5);
    cout << "anda keluar program" << endl;
}