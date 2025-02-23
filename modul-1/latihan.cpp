#include <iostream>
#include <string>
#include <conio.h>
#include <typeinfo>
#include <vector>

using namespace std;
#define length 5

struct Mahasiswa {
    int nim[length], nilai[length];
    string namaMhs[length];
};
void showData(Mahasiswa mhs) {
    cout << "Menampilkan data mahasiswa..." << endl;
    for (int i = 0; i < length; i++) {
        cout << "Nim:\t" << mhs.nim[i] << endl;
        cout << "Nama:\t" << mhs.namaMhs[i] << endl;
        cout << "Nil:\t" << mhs.nilai[i] << endl << endl;
    }
}
void sorting(Mahasiswa &mhs, int indexAwal, int indexAkhir) {
    if (indexAwal >= indexAkhir) return;

    string pivot = mhs.namaMhs[indexAkhir];
    int i = indexAwal - 1;

    for (int j = indexAwal; j < indexAkhir; j++) {
        if (mhs.namaMhs[j] < pivot) {
            i++;
            swap(mhs.namaMhs[i], mhs.namaMhs[j]);
            swap(mhs.nim[i], mhs.nim[j]);
            swap(mhs.nilai[i], mhs.nilai[j]);
        }
    }
    swap(mhs.namaMhs[i + 1], mhs.namaMhs[indexAkhir]);
    swap(mhs.nim[i + 1], mhs.nim[indexAkhir]);
    swap(mhs.nilai[i + 1], mhs.nilai[indexAkhir]);

    int pivotIndex = i + 1;

    sorting(mhs, indexAwal, pivotIndex - 1);
    sorting(mhs, pivotIndex + 1, indexAkhir);
}
int main() {
    int pilihan;
    Mahasiswa mhs;

    //data mahasiswa
    mhs.nim[0] = 24001; mhs.namaMhs[0] = "galih"; mhs.nilai[0] = 90;
    mhs.nim[1] = 24002; mhs.namaMhs[1] = "ibnu";mhs.nilai[1] = 89;
    mhs.nim[2] = 24003; mhs.namaMhs[2] = "cantika"; mhs.nilai[2] = 95;
    mhs.nim[3] = 24004; mhs.namaMhs[3] = "agus"; mhs.nilai[3] = 70;
    mhs.nim[4] = 24005; mhs.namaMhs[4] = "tino"; mhs.nilai[4] = 80;

    do {
        system("cls");
        cout << "1. tampilkan data" << endl;
        cout << "2. sort data" << endl;
        cout << "3. keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        if (typeid(pilihan) != typeid(int)) break;
        if (pilihan == 3) break;
        switch (pilihan) {
            case 1:
                showData(mhs);
                getch();
                break;
            case 2:
                cout << endl << "Data di sorting berdasarkan nama!!" << endl;
                sorting(mhs, 0, 4);
                showData(mhs);
                getch();
                break;
            default:
                cout << "pilihan tidak valid" << endl;
            getch();
            break;
        }
    } while (pilihan);
    cout << "keluar dari program" << endl;  
};
