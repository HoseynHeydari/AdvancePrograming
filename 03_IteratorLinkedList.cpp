#include <iostream>
using namespace std;

class List {
private:
    class Node {
    public:
        Node(int d, Node *n = NULL, Node *p = NULL) 
            : data(d), next(n), prev(p) {}

        int data;
        Node *next;
        Node *prev;
    };

public:
    class Iterator {
    public:
        int value() { return current->data; }
        void move() { current = current->next; }
        bool has_more_elements() {
            return current != NULL;
        }
    private:
        Node *current;
        Iterator(Node* n) { current = n; }
        friend class List;
    };

public:
    List();
    ~List();
    void print();
    void push_front(int x);
    void push_back(int x);
    void clear();
    bool has(int x);
    bool hasr(int x);
    void append(const List &l);
    Iterator get_iterator() {
        return Iterator(_head);
    }
private:
    bool hasr(int x, Iterator it);
    Node* _head;
    Node* _last;
};

List::List() {
    _head = NULL;
    _last = NULL;
}

void List::print() {
    for (Node* p = _head; p != NULL; p = p->next)
        cout << p->data << ' ';
}

void List::push_front(int x) {
    Node *new_node = new Node(x);
    new_node->next = _head;
    if (_head != NULL)
        _head->prev = new_node;
    _head = new_node;
    if (_last == NULL)
        _last = new_node;
}

void List::push_back(int x) {
    if (_head == NULL)
        push_front(x);
    else {
        Node *new_node = new Node(x);
        new_node->prev = _last;
        _last->next = new_node;
        _last = new_node;
    }
}

bool List::has(int x) {
    List::Iterator it = this->get_iterator();
    while (it.has_more_elements()){
        if (it.value() == x)
            return true;
        it.move();
    }
    return false;
}

bool List::hasr(int x, Iterator it) {
    if (!it.has_more_elements())
        return false;
    if (it.value() == x)
        return true;
    else {
        it.move();
        return hasr(x, it);
    }
}

bool List::hasr(int x) {
    return List::hasr(x, _head);
}

void List::append(const List &l) {
    Node *p = l._head;
    while (p != NULL) {
        this->push_back(p->data);
        p = p->next;
    }
}

List::~List() {
    clear();
}

void List::clear() {
    Node *p = _head;
    while (p != NULL) {
        Node *q = p;
        p = p->next;
        delete q;
    }
    _head = NULL;
    _last = NULL;
}

int main() {
    List l;
    
    l.push_back(86);
    l.push_front(43);
    l.push_front(12);
    
    l.print();
    cout << endl;

    List l1;
    
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    
    l1.print();
    cout << endl;

    l.append(l1);

    l.print();
    cout << endl;
}