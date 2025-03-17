#include <iostream>
#include <conio.h>
#include <limits>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    // Konstruktor Node
    Node(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;  // Pointer ke node terdepan
    Node* tail;  // Pointer ke node terbelakang

public:
    // Konstruktor: inisialisasi head & tail = nullptr
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Mengecek apakah list kosong
    bool isEmpty() const {
        return (head == nullptr);
    }

    // Membuat node baru dan menambahkannya di akhir list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (!newNode) {
            cout << "Gagal mengalokasikan memori.\n";
            return;
        }

        // Jika list masih kosong
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Data " << value << " berhasil ditambahkan di akhir.\n";
    }

    // Menampilkan isi list (dari head ke tail)
    void displayList() {
        if (isEmpty()) {
            cout << "List kosong.\n";
            return;
        }
        cout << "Isi list (head -> tail): ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Menghapus node yang memiliki nilai data tertentu
    void removeByValue(int value) {
        if (isEmpty()) {
            cout << "List kosong, tidak ada yang dihapus.\n";
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                // Jika node yang dihapus adalah head
                if (current == head) {
                    head = current->next;
                    if (head) {
                        head->prev = nullptr;
                    } else {
                        // Jika setelah dihapus, list jadi kosong
                        tail = nullptr;
                    }
                }
                // Jika node yang dihapus adalah tail
                else if (current == tail) {
                    tail = current->prev;
                    if (tail) {
                        tail->next = nullptr;
                    } else {
                        // Jika setelah dihapus, list jadi kosong
                        head = nullptr;
                    }
                }
                // Node di tengah
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                cout << "Data " << value << " berhasil dihapus.\n";
                return;
            }
            current = current->next;
        }
        cout << "Data " << value << " tidak ditemukan di dalam list.\n";
    }

    // Mencari data dari arah head
    Node* searchFromHead(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current; // mengembalikan pointer node jika ketemu
            }
            current = current->next;
        }
        return nullptr; // tidak ketemu
    }

    // Mencari data dari arah tail
    Node* searchFromTail(int value) {
        Node* current = tail;
        while (current != nullptr) {
            if (current->data == value) {
                return current; // mengembalikan pointer node jika ketemu
            }
            current = current->prev;
        }
        return nullptr; // tidak ketemu
    }

    // Menyisipkan node baru setelah data 'key'
    void insertAfter(int key, int newValue) {
        // Jika list kosong, langsung jadikan node baru sebagai node pertama
        if (isEmpty()) {
            cout << "List masih kosong. Node baru akan menjadi head.\n";
            insertAtEnd(newValue);
            return;
        }

        // Cari node dengan data == key
        Node* current = searchFromHead(key);
        if (!current) {
            cout << "Data " << key << " tidak ditemukan. Penyisipan dibatalkan.\n";
            return;
        }

        // Jika key ada di tail, langsung insert di akhir
        if (current == tail) {
            insertAtEnd(newValue);
            return;
        }

        Node* newNode = new Node(newValue);
        if (!newNode) {
            cout << "Gagal mengalokasikan memori.\n";
            return;
        }

        // Sisipkan newNode di antara current dan current->next
        Node* nextNode = current->next;
        newNode->next = nextNode;
        newNode->prev = current;
        current->next = newNode;
        if (nextNode) {
            nextNode->prev = newNode;
        }

        // Jika kebetulan current adalah tail, perbarui tail
        if (current == tail) {
            tail = newNode;
        }
        cout << "Data " << newValue << " berhasil disisipkan setelah " << key << ".\n";
    }

    // Menyisipkan node baru sebelum data 'key'
    void insertBefore(int key, int newValue) {
        // Jika list kosong, langsung jadikan node baru sebagai node pertama
        if (isEmpty()) {
            cout << "List masih kosong. Node baru akan menjadi head.\n";
            insertAtEnd(newValue);
            return;
        }

        // Cari node dengan data == key
        Node* current = searchFromHead(key);
        if (!current) {
            cout << "Data " << key << " tidak ditemukan. Penyisipan dibatalkan.\n";
            return;
        }

        // Jika key ada di head, sisipkan di depan head
        if (current == head) {
            Node* newNode = new Node(newValue);
            if (!newNode) {
                cout << "Gagal mengalokasikan memori.\n";
                return;
            }
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << "Data " << newValue << " berhasil disisipkan sebelum " << key << " (menjadi head).\n";
            return;
        }

        Node* newNode = new Node(newValue);
        if (!newNode) {
            cout << "Gagal mengalokasikan memori.\n";
            return;
        }

        // Sisipkan newNode di antara current->prev dan current
        Node* prevNode = current->prev;
        newNode->next = current;
        newNode->prev = prevNode;
        current->prev = newNode;
        prevNode->next = newNode;
        cout << "Data " << newValue << " berhasil disisipkan sebelum " << key << ".\n";
    }
};

// Fungsi utama dengan menu
int main() {
    LinkedList list;
    int pilihan;
    int value, key;
    Node* foundNode;

    do {
        cout << "\n===== MENU LINKED LIST =====\n"
             << "1. Tambah data (di akhir)\n"
             << "2. Lihat data\n"
             << "3. Cari data (dari head)\n"
             << "4. Cari data (dari tail)\n"
             << "5. Hapus data tertentu\n"
             << "6. Sisipkan setelah data tertentu\n"
             << "7. Sisipkan sebelum data tertentu\n"
             << "0. Keluar\n"
             << "Pilihan Anda: ";

        if (!(cin >> pilihan)) {
            cout << "\nError: Input harus berupa angka!\n";
            cin.clear(); // Menghapus error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
            getch();
            continue; // Ulangi iterasi loop
        }

        switch (pilihan) {
            case 1:
                cout << "Masukkan sebuah data (angka): ";
                cin >> value;
                list.insertAtEnd(value);
                getch();
                system("cls");
                break;
            case 2:
                list.displayList();
                getch();
                system("cls");
                break;
            case 3:
                cout << "Masukkan data yang ingin dicari (dari head): ";
                cin >> value;
                foundNode = list.searchFromHead(value);
                if (foundNode) {
                    cout << "Data " << value << " ditemukan.\n";
                } else {
                    cout << "Data " << value << " tidak ditemukan.\n";
                }
                getch();
                system("cls");
                break;
            case 4:
                cout << "Masukkan data yang ingin dicari (dari tail): ";
                cin >> value;
                foundNode = list.searchFromTail(value);
                if (foundNode) {
                    cout << "Data " << value << " ditemukan.\n";
                } else {
                    cout << "Data " << value << " tidak ditemukan.\n";
                }
                getch();
                system("cls");
                break;
            case 5:
                cout << "Masukkan data yang ingin dihapus: ";
                cin >> value;
                list.removeByValue(value);
                getch();
                system("cls");
                break;
            case 6:
                cout << "Masukkan data 'key' (setelah data ini akan disisipkan): ";
                cin >> key;
                cout << "Masukkan data baru yang akan disisipkan: ";
                cin >> value;
                list.insertAfter(key, value);
                getch();
                system("cls");
                break;
            case 7:
                cout << "Masukkan data 'key' (sebelum data ini akan disisipkan): ";
                cin >> key;
                cout << "Masukkan data baru yang akan disisipkan: ";
                cin >> value;
                list.insertBefore(key, value);
                getch();
                system("cls");
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                getch();
                system("cls");
                break;
        }
    } while (pilihan != 0);

    return 0;
}
