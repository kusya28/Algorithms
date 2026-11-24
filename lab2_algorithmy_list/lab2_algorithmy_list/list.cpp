#include <iostream>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Node {
    long long value;
    Node* next;
};

struct CircularList {
    Node* tail = nullptr;
    int size = 0;
};

bool isEmpty(const CircularList& list) {
    return list.tail == nullptr;
}

void insertHead(CircularList& list, long long val) {
    Node* newNode = new Node{ val, nullptr };
    if (isEmpty(list)) {
        newNode->next = newNode;
        list.tail = newNode;
    }
    else {
        newNode->next = list.tail->next;
        list.tail->next = newNode;
    }
    list.size++;
}

void insertTail(CircularList& list, long long val) {
    insertHead(list, val);
    list.tail = list.tail->next;
}

void printList(const CircularList& list) {
    if (isEmpty(list)) {
        cout << "[порожній]";
        return;
    }
    Node* head = list.tail->next;
    Node* curr = head;
    do {
        cout << curr->value;
        curr = curr->next;
        if (curr != head) cout << " -> ";
    } while (curr != head);
}

void clearList(CircularList& list) {
    if (isEmpty(list)) return;
    Node* head = list.tail->next;
    Node* curr = head;
    list.tail->next = nullptr; 
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    list.tail = nullptr;
    list.size = 0;
}

long long taskA(CircularList& L, long long E1, long long E2) {
    if (isEmpty(L)) return 0;
    long long hops = 0;
    Node* head = L.tail->next;
    Node* curr = head;

    do {
        if (curr->value == E1) {
            curr->value = E2;
        }
        curr = curr->next;
        hops++;
    } while (curr != head);

    return hops;
}

long long taskB(CircularList& L, const CircularList& L1, long long E) {
    if (isEmpty(L) || isEmpty(L1)) return 0;

    long long hops = 0;
    Node* head = L.tail->next;
    Node* curr = head;
    Node* target = nullptr;

    do {
        if (curr->value == E) {
            target = curr;
            break;
        }
        curr = curr->next;
        hops++;
    } while (curr != head);

    if (target == nullptr) return hops;

    Node* l1_head = L1.tail->next;
    Node* l1_curr = l1_head;
    Node* insertPos = target;

    do {
        Node* newNode = new Node{ l1_curr->value, insertPos->next };
        insertPos->next = newNode;

        if (insertPos == L.tail) {
            L.tail = newNode;
        }

        insertPos = newNode;
        L.size++;

        l1_curr = l1_curr->next;
        hops++;
    } while (l1_curr != l1_head);

    return hops;
}

long long taskV(const CircularList& L, long long& midValue) {
    if (isEmpty(L)) return 0;

    long long hops = 0;
    Node* head = L.tail->next;
    Node* slow = head;
    Node* fast = head;

    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
        hops += 3; 
    }

    midValue = slow->value;
    return hops;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Ukrainian");

    CircularList L;
    insertTail(L, 10);
    insertTail(L, 20);
    insertTail(L, 30);
    insertTail(L, 20);
    insertTail(L, 50);

    cout << "Початковий список L: ";
    printList(L);
    cout << " (Довжина: " << L.size << ")\n\n";

    long long hopsA = taskA(L, 20, 99);
    cout << "Після Завдання А (заміна 20 на 99): ";
    printList(L);
    cout << " (Довжина: " << L.size << ")\n";

    CircularList L1;
    insertTail(L1, 777);
    insertTail(L1, 888);

    long long hopsB = taskB(L, L1, 99);
    cout << "Після Завдання Б (вставка L1 після першого 99): ";
    printList(L);
    cout << " (Довжина: " << L.size << ")\n";

    long long midVal = 0;
    long long hopsV = taskV(L, midVal);
    cout << "Після Завдання В (знайдено центр: " << midVal << "): ";
    printList(L);
    cout << " (Довжина: " << L.size << ")\n\n";

    cout << "Таблиця переходів за покажчиком:\n";
    cout << "| Завдання    | Кількість переходів |\n";
    cout << "|-------------|---------------------|\n";
    cout << "| Завдання А  | " << hopsA << "                   |\n";
    cout << "| Завдання Б  | " << hopsB << "                   |\n";
    cout << "| Завдання В  | " << hopsV << "                   |\n";

    clearList(L);
    clearList(L1);
    return 0;
}