#include <iostream>
#include <string>
using namespace std;

class Data {
    private:
        string nama;
        int nim;
    public:
        Data(const string &nama, const int &nim) {
            this->nama = nama;
            this->nim = nim;
        }
        void read() {
            cout << "nama: " << Data::nama << "\nnim: " << this->nim << endl << endl;
        }
};

int main() {
    string inputNama;
    int inputnim;
    cout << "Masukkan data" << endl;
    cout << "nama: "; cin >> inputNama;
    cout << "nim: "; cin >> inputnim; cout << endl;

    Data saya = Data(inputNama, inputnim);
    saya.read();
}