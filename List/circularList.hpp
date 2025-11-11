#pragma once
#include <string>

using namespace std;

class Node {
public:
    string song;
    Node *next;
    Node *back;

    Node(const string &s);
};

class CircularList {
private:
    Node *ptrHead;

public:
    CircularList();
    ~CircularList();
    bool empty();
    void insert_Last(const string &song);
    void print();
    Node* nextSong(Node* current);
    Node* prevSong(Node* current);
    Node* getHead();
};
