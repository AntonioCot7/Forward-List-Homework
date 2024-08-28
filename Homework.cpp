#include <iostream>
#include <cmath>
#include <cstdio>
using std::cout, std::endl;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& val): data(val), next(nullptr) {};
};

template <typename T>
class List {
    Node<T>* head;
public:
    T front() {
        if(head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back() {
        if(head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        auto current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data;
    }

    void push_front(const T& e) {
        auto new_node = new Node<T>(e);
        new_node->next = head;
        head = new_node;
    }

    void push_back(const T& e) {
        if(head == nullptr) {
            head = new Node<T>(e);
            return;
        }
        auto current = head;
        while(current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node<T>(e);
    }

    void pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        auto temp  = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if(head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        if(head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        auto temp = head;
        while(temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    T& operator[](const int& i) {
        if (i < 0 or i >= size()) {
            throw std::out_of_range("Index out of bounds");
        }
        auto current = head;
        for(int k = 0; k < i; k++) {
            current = current->next;
        }
        return current->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        int s = 0;
        auto current = head;
        while(current != nullptr) {
            s++;
            current = current->next;
        }
        return s;
    }

    void clear() {
        while(head != nullptr) {
            pop_front();
        }
    }

    void print() {
        auto current = head;
        while(current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void insert(const T& val, const int pos) {
        if(pos == 0) {
            push_front(val);
            return;
        }
        auto current = head;
        int i = 0;
        while(current != nullptr and i < pos - 1) {
            current = current->next;
            i++;
        }
        if(current == nullptr) {
            throw std::out_of_range("Position out of bounds");
        }
        auto new_node = new Node<T>(val);
        new_node->next = current->next;
        current->next = new_node;
    }

    void sort() {
        if (head == nullptr or head->next == nullptr) return;  // Lista vacía o con un solo elemento
        for (auto i = head; i->next != nullptr; i = i->next) {
            for (auto j = i->next; j != nullptr; j = j->next) {
                if (i->data > j->data) {
                    std::swap(i->data, j->data);
                }
            }
        }
    }

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    List(Node<T>* head): head(head) {}

    List(): head(nullptr) {}

    ~List() {
        clear();
    }
};

int main() {
    List<int> myList;

    myList.push_back(3);
    myList.push_back(1);
    myList.push_back(4);
    myList.push_back(1);
    myList.push_back(5);

    cout << "Original list: ";
    myList.print();

    cout << "Reversed list: ";
    myList.reverse();
    myList.print();

    cout << "Sorted list: ";
    myList.sort();
    myList.print();

    return 0;
}
