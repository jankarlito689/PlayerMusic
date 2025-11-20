#include "circularList.hpp"
#include <iostream>

using namespace std;

Node::Node(const Song &s) : song(s), next(nullptr), back(nullptr) {}

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

void CircularList::insert_Last(const Song &song) {
    Node *new_node = new Node(song);
    new_node ->song.id = getNextId();
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
    cout << "Índice | Nombre - Artista - Duración\n";
    do {
        cout << temp->song.id << " | " << temp->song.name << " - "
                    << temp->song.artist << " - " << temp->song.duration << "\n";
        temp = temp->next;
    } while (temp != ptrHead);
}

void CircularList::clear(){
    if (!ptrHead) return;
    Node* temp = ptrHead;
    do {
        Node* next = temp->next;
        delete temp;
        temp = next;
    } while (temp != ptrHead);
    ptrHead = nullptr;
}

void CircularList::newSong(const Song &song){
    insert_Last(song);
    cout << "✅ Canción agregada: " << song.name << " - " << song.artist << "\n";
}

Node* CircularList::FindSong(const string &query){
    if (empty()) {
        cout << "Lista vacía.\n";
        return nullptr;
    }

    bool found = false;
    Node* firstMatch = nullptr;

    // Intentar convertir a número para buscar por ID
    int idSearch = -1;
    try {
        idSearch = stoi(query);
    } catch (...) {
        idSearch = -1;
    }

    Node *temp = ptrHead;

    cout << "🎵 Resultados de búsqueda:\n";

    do {
        bool match = false;

        // Si es ID
        if (idSearch != -1 && temp->song.id == idSearch)
            match = true;

        // Si coincide nombre
        else if (temp->song.name == query)
            match = true;

        // Si coincide artista
        else if (temp->song.artist == query)
            match = true;

        if (match) {
            cout << "➡️  " << temp->song.id << " | "
                << temp->song.name << " - "
                << temp->song.artist << " - "
                << temp->song.duration << "\n";

            if(!firstMatch)
                firstMatch = temp;
            found = true;
        }

        temp = temp->next;
    } while (temp != ptrHead);

    if (!found)
        cout << "⚠️ No se encontró ninguna coincidencia.\n";

    return firstMatch;
}

int CircularList::sortbyid(){
    if (empty()) return 0;
    bool swapped;
    do {
        swapped = false;
        Node *temp = ptrHead;
        do {
            Node *next = temp->next;
            if (temp->song.id > next->song.id) {
                swap(temp->song, next->song);
                swapped = true;
            }
            temp = temp->next;
        } while (temp->next != ptrHead);
    } while (swapped);
    return 1;
}

void CircularList::sortbyName(){
    if (empty()) return;
    bool swapped;
    do {
        swapped = false;
        Node *temp = ptrHead;
        do {
            Node *next = temp->next;
            if (temp->song.name > next->song.name) {
                swap(temp->song, next->song);
                swapped = true;
            }
            temp = temp->next;
        } while (temp->next != ptrHead);
    } while (swapped);
}

void CircularList::sortbyArtist(){
    if (empty()) return;
    bool swapped;
    do {
        swapped = false;
        Node *temp = ptrHead;
        do {
            Node *next = temp->next;
            if (temp->song.artist > next->song.artist) {
                swap(temp->song, next->song);
                swapped = true;
            }
            temp = temp->next;
        } while (temp->next != ptrHead);
    } while (swapped);
}

void CircularList::sortAsc(){
    sortbyid();
}

void CircularList::sortDesc(){
    if(empty()) return;
    sortbyid();
    invertList();
}

void CircularList::invertList(){
    if(empty() || ptrHead ->next == ptrHead) return;

    Node *current = ptrHead;
    Node *prev = nullptr;
    Node *next = nullptr;
    do {
        next = current->next;
        current->next = current->back;
        current->back = next;
        prev = current;
        current = next;
    } while (current != ptrHead);
    ptrHead = prev;
}

Node* CircularList::editSong(const int &id, const string &name, const Song &newSongData){
    if (empty()) return nullptr;

    Node *temp = ptrHead;
    do {
        if ((id != -1 && temp->song.id == id) || (!name.empty() && temp->song.name == name)) {
            if (!newSongData.name.empty())
                temp->song.name = newSongData.name;

            if (!newSongData.artist.empty())
                temp->song.artist = newSongData.artist;

            if (!newSongData.duration.empty())
                temp->song.duration = newSongData.duration;

            if (!newSongData.path.empty())
                temp->song.path = newSongData.path;

            cout << "✏️ Canción actualizada: " << temp->song.name << "\n";

            return temp;
        }
        temp = temp->next;
    } while (temp != ptrHead);
    cout << "⚠️ No se encontró la canción a editar.\n";
    return nullptr;
}
void CircularList::deleteSong(const int &id, const string &name){
    if (empty()) return;

    Node *temp = ptrHead;
    Node *prev = nullptr;

    do {
        if ((id != -1 && temp->song.id == id) || (!name.empty() && temp->song.name == name)) {
            if (temp == ptrHead && temp->next == ptrHead) {
                delete temp;
                ptrHead = nullptr;
                cout << "🗑️ Lista vacía tras eliminar última canción.\n";
                return;
            }
            if (temp == ptrHead)
                ptrHead = ptrHead->next;

            temp->back->next = temp->next;
            temp->next->back = temp->back;
            delete temp;
            cout << "🗑️ Canción eliminada.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    } while (temp != ptrHead);

    cout << "⚠️ No se encontró la canción a eliminar.\n";
}
Node* CircularList::getHead() const { return ptrHead; }

Node* CircularList::nextSong(Node* current) {
    return current ? current->next : nullptr;
}

Node* CircularList::prevSong(Node* current) {
    return current ? current->back : nullptr;
}
