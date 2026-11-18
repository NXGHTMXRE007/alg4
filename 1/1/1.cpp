#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {

public:
    struct Node {
        T data;      
        Node* prev;   
        Node* next;

        Node(const T& value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };

private:
    Node* head;
    Node* tail;
    int count;

public:

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    DoublyLinkedList(const DoublyLinkedList& other) {
        head = nullptr;
        tail = nullptr;
        count = 0;

        Node* current = other.head;

        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        count = 0;
    }


    void push_front(const T& value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        count++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        count++;
    }

    Node* find(const T& value) const {
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value)
                return current;

            current = current->next;
        }

        return nullptr;
    }

    void insert_after(Node* node, const T& value) {
        if (node == nullptr) {
            push_front(value);
            return;
        }

        Node* newNode = new Node(value);

        newNode->next = node->next;
        newNode->prev = node;

        if (node->next != nullptr)
            node->next->prev = newNode;
        else
            tail = newNode;

        node->next = newNode;

        count++;
    }

    void print() const {
        Node* current = head;

        cout << "[";

        while (current != nullptr) {
            cout << current->data;

            if (current->next != nullptr)
                cout << ", ";

            current = current->next;
        }

        cout << "]" << endl;
    }

    DoublyLinkedList intersection(DoublyLinkedList& other) const {

        DoublyLinkedList result;

        Node* current = head;

        while (current != nullptr) {

            if (other.find(current->data) != nullptr) {

                if (result.find(current->data) == nullptr) {

                    result.push_back(current->data);
                }
            }

            current = current->next;
        }

        return result;
    }
};


int main() {

    setlocale(LC_ALL, "Russian");

    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(4);
    list1.push_back(5);

    list2.push_back(2);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(6);

    cout << "Первый список: ";
    list1.print();

    cout << "Второй список: ";
    list2.print();

    cout << endl;

    DoublyLinkedList<int> result = list1.intersection(list2);


    cout << "Результат: ";
    result.print();

    return 0;
}
