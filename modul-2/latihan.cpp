#include <iostream>
#include <iomanip>
using namespace std;

void selectionSort(int array[], const int size) {
    int i, j, small,temp;
    for (i = 0; i < size; i++) {
        cout << "tahap ke " << i + 1<< endl;
        small = i;
        for (j = 0; j < size; j++) {
            if (array[j] > array[small]) {
                cout << "angka " << array[small] << " ditukar " << array[j] << endl;
                small = j;
                temp = array[i];
                array[i] = array[small];
                array[small] = temp;
            } else {
                cout << "angka " << array[small] << " tidak ditukar " << array[j] << endl;
            }
            for (int i = 0; i < size; i++) {
                cout << array[i] << setw(3);
            }
            cout << endl;
        }
        for (int i = 0; i < size; i++) {
            cout << array[i] << setw(3);
        }
        cout << endl;
    }
}

int main() {
    int data[10] = {6, 1, 8, 2, 3, 9, 0, 7, 5, 4};

    cout << "data sebelum diurutkan: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << data[i] << setw(3);
    }
    cout << endl << endl;
    selectionSort(data, 10);

    cout << "data setelah diurutkan: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << data[i] << setw(3);
    }
    cout << endl;
}