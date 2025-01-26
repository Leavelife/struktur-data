#include <iostream>
#include <string>
using namespace std;

class Mahasiswa {
    private:
        string nama, NIM;
    public:
        Mahasiswa(const string nama, const string NIM) {
            this->nama = nama;
            this->NIM = NIM;
        }
        void read() {
            cout << "Nama Mahasiswa: " << Mahasiswa::nama << "\nNIM: " << this->NIM << endl << endl;
        }
};

int main() {
    string inputNama;
    string inputNIM;
    cout << "Masukkan data mahasiswa" << endl;
    cout << "Nama: "; cin >> inputNama;
    cout << "NIM: "; cin >> inputNIM;

    Mahasiswa mhs1(inputNama, inputNIM);
    mhs1.read();

}