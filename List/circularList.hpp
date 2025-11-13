#pragma once
#include <string>
#include "../Models/song.hpp"
using namespace std;

class Node {
public:
    Song song;
    Node *next;
    Node *back;

    Node(const Song &s);
};

class CircularList {
private:
    Node *ptrHead;

public:
    CircularList();
    ~CircularList();
    bool empty();
    void insert_Last(const Song &song);
    void print();
    void clear();
    Node* nextSong(Node* current);
    Node* prevSong(Node* current);
    Node* getHead();
};
