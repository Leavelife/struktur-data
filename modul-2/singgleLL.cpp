#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList();
    void append(int data);
    void prepend(int data);
    void print() const;
    void deleteNode(int data);
    bool search(int data) const;
    bool searchWithTail(int data) const;
    void insertAfter(int data, int newData);
    void insertBefore(int data, int newData);
};

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::append(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::prepend(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

void LinkedList::print() const {
    Node* current = head;
    if (current == nullptr) {
        cout << "Linked list kosong.\n";
        return;
    }
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::deleteNode(int data) {
    if (head == nullptr) return;

    // Hapus head
    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        if (tail == temp) tail = nullptr;
        delete temp;
        return;
    }

    // Cari node yang akan dihapus
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return;

    // Update tail jika perlu
    if (current == tail) tail = prev;
    
    prev->next = current->next;
    delete current;
}

bool LinkedList::search(int data) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

bool LinkedList::searchWithTail(int data) const {
    if (head == nullptr) return false;
    if (tail->data == data) return true;
    
    Node* current = head;
    while (current != tail) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

void LinkedList::insertAfter(int data, int newData) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            Node* newNode = new Node(newData);
            newNode->next = current->next;
            current->next = newNode;
            if (current == tail) tail = newNode;
            return;
        }
        current = current->next;
    }
    cout << "Data tidak ditemukan!\n";
}

void LinkedList::insertBefore(int data, int newData) {
    if (head == nullptr) {
        cout << "List kosong!\n";
        return;
    }

    if (head->data == data) {
        prepend(newData);
        return;
    }

    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    Node* newNode = new Node(newData);
    prev->next = newNode;
    newNode->next = current;
}

int main() {
    LinkedList list;
    int choice, data, posData;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Data di Akhir\n";
        cout << "2. Tambah Data di Depan\n";
        cout << "3. Tampilkan Data\n";
        cout << "4. Hapus Data\n";
        cout << "5. Cari Data (Head saja)\n";
        cout << "6. Cari Data (Head & Tail)\n";
        cout << "7. Sisipkan Setelah Data\n";
        cout << "8. Sisipkan Sebelum Data\n";
        cout << "9. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Masukkan data: ";
                cin >> data;
                list.append(data);
                break;
            case 2:
                cout << "Masukkan data: ";
                cin >> data;
                list.prepend(data);
                break;
            case 3:
                list.print();
                break;
            case 4:
                cout << "Masukkan data yang dihapus: ";
                cin >> data;
                list.deleteNode(data);
                break;
            case 5:
                cout << "Masukkan data yang dicari: ";
                cin >> data;
                cout << (list.search(data) ? "Ditemukan" : "Tidak ditemukan") << endl;
                break;
            case 6:
                cout << "Masukkan data yang dicari: ";
                cin >> data;
                cout << (list.searchWithTail(data) ? "Ditemukan" : "Tidak ditemukan") << endl;
                break;
            case 7:
                cout << "Masukkan data posisi: ";
                cin >> posData;
                cout << "Masukkan data baru: ";
                cin >> data;
                list.insertAfter(posData, data);
                break;
            case 8:
                cout << "Masukkan data posisi: ";
                cin >> posData;
                cout << "Masukkan data baru: ";
                cin >> data;
                list.insertBefore(posData, data);
                break;
            case 9:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while(choice != 9);
}