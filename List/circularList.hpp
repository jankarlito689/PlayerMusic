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
    void newSong(const Song &song);//se encarga de agregar una cancion nueva a la lista(playList)
    void FindSong(const string &name, const string &artis, const int &id);//busca una cancion en la lista(playList) por nombre, artista o id
    void sortbyName();
    void sortbyArtist();
    int sortbyid();
    void sortAsc();
    void sortDesc();
    void invertList();
    void editSong(const int &id, const string &name, const Song &newSongData);//edita los datos de una cancion en la lista(playList) por id o name
    void deleteSong(const int &id, const string &name);//elimina una cancion de la lista(playList) por id o name
    Node* nextSong(Node* current);
    Node* prevSong(Node* current);
    Node* getHead();
};
