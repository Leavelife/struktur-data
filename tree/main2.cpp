#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* buatNode(int angka) {
    Node* baru = new Node();
    baru->data = angka;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

Node* tambah(Node* akar, int angka) {
    if (akar == NULL) {
        return buatNode(angka);
    }

    if (angka < akar->data) {
        akar->left = tambah(akar->left, angka);
    } else {
        akar->right = tambah(akar->right, angka);
    }

    return akar;
}

void cetakInorder(Node* akar) {
    if (akar != NULL) {
        cetakInorder(akar->left);
        cout << akar->data << " | ";
        cetakInorder(akar->right);
    }
}

void cariAnak(Node* akar, int angka) {
    if (akar == NULL) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }

    if (akar->data == angka) {
        cout << "Node: " << akar->data << endl;
        if (akar->left != NULL)
            cout << "Anak kiri: " << akar->left->data << endl;
        else
            cout << "Tidak ada anak kiri." << endl;

        if (akar->right != NULL)
            cout << "Anak kanan: " << akar->right->data << endl << endl;
        else
            cout << "Tidak ada anak kanan.\n" << endl;
    } else if (angka < akar->data) {
        cariAnak(akar->left, angka);
    } else {
        cariAnak(akar->right, angka);
    }
}

int main() {
    Node* akar = NULL;
    akar = tambah(akar, 40);
    akar = tambah(akar, 20);
    akar = tambah(akar, 60);
    akar = tambah(akar, 10);
    akar = tambah(akar, 30);
    akar = tambah(akar, 50);
    akar = tambah(akar, 70);

    cout << "\nData tree (inorder): ";
    cetakInorder(akar);
    cout << endl;

    int cari;
    cout << "Masukkan angka node yang ingin dilihat anaknya: ";
    cin >> cari;

    cariAnak(akar, cari);

    return 0;
}
