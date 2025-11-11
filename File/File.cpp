#include "File.hpp"
#include <fstream>
#include <iostream>

using namespace std;

// Lee una lista de reproducción desde un archivo y devuelve un vector de cadenas con las canciones
vector<string> File::readPlaylist(const string &path){
    ifstream file(path);
    vector<string> songs;
    string line;

    if (!file.is_open()) {
        cerr << "⚠️  Error: no se pudo abrir el archivo " << path << std::endl;
        return songs;
    }

    while (getline(file, line)) {
        if (!line.empty()) songs.push_back(line);
    }

    file.close();
    return songs;
}
