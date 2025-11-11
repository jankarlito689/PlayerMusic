#include "circularList.hpp"
#include <iostream>

using namespace std;

Node::Node(const string &s) : song(s), next(nullptr), back(nullptr) {}

CircularList::CircularList() : ptrHead(nullptr) {}

CircularList::~CircularList() {
    if (!ptrHead) return;
    Node *temp = ptrHead->next;
    while (temp != ptrHead) {
        Node *aux = temp;
        temp = temp->next;
        delete aux;
    }
    delete ptrHead;
}

bool CircularList::empty() { return ptrHead == nullptr; }

void CircularList::insert_Last(const string &song) {
    Node *new_node = new Node(song);
    if (ptrHead == nullptr) {
        new_node->next = new_node;
        new_node->back = new_node;
        ptrHead = new_node;
    } else {
        Node *last = ptrHead->back;
        new_node->next = ptrHead;
        new_node->back = last;
        last->next = new_node;
        ptrHead->back = new_node;
    }
}

void CircularList::print() {
    if (empty()) {
        cout << "(Lista vacía)\n";
        return;
    }

    Node *temp = ptrHead;
    cout << "\n🎵 Playlist cargada:\n";
    do {
        cout << "→ " << temp->song << endl;
        temp = temp->next;
    } while (temp != ptrHead);
}

Node* CircularList::getHead() { return ptrHead; }

Node* CircularList::nextSong(Node* current) {
    return current ? current->next : nullptr;
}

Node* CircularList::prevSong(Node* current) {
    return current ? current->back : nullptr;
}
