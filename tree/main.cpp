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

Node* cariMin(Node* akar) {
    while (akar->left != NULL) {
        akar = akar->left;
    }
    return akar;
}

Node* hapus(Node* akar, int angka) {
    if (akar == NULL) {
        return akar;
    }

    if (angka < akar->data) {
        akar->left = hapus(akar->left, angka);
    } else if (angka > akar->data) {
        akar->right = hapus(akar->right, angka);
    } else {
        // Node ketemu
        if (akar->left == NULL && akar->right == NULL) {
            delete akar;
            return NULL;
        } else if (akar->left == NULL) {
            Node* tmp = akar->right;
            delete akar;
            return tmp;
        } else if (akar->right == NULL) {
            Node* tmp = akar->left;
            delete akar;
            return tmp;
        } else {
            Node* pengganti = cariMin(akar->right);
            akar->data = pengganti->data;
            akar->right = hapus(akar->right, pengganti->data);
        }
    }

    return akar;
}

void cetakInorder(Node* akar) {
    if (akar != NULL) {
        cetakInorder(akar->left);
        cout << akar->data << " ";
        cetakInorder(akar->right);
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

    cout << "\nData awal (inorder): ";
    cetakInorder(akar);
    cout << endl;

    int hapusAngka;
    cout << "Masukkan angka yang ingin dihapus: ";
    cin >> hapusAngka;

    akar = hapus(akar, hapusAngka);

    cout << "Setelah dihapus: ";
    cetakInorder(akar);
    cout << endl << endl;
}
