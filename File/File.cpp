#include "File.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// Lee una lista de reproducción desde un archivo y devuelve un vector de canciones
vector<Song> File::readPlaylist(const string &path){
    ifstream file(path);
    vector<Song> songs;
    string line;
    int IdCounter = 1;

    if (!file.is_open()) {
        cerr << "⚠️  Error: no se pudo abrir el archivo " << path << endl;
        return songs;
    }
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, artist, album, songPath;

        // Divide la línea por ';'
        getline(ss, name, ';');
        getline(ss, artist, ';');
        getline(ss, album, ';');
        getline(ss, songPath, ';');

        // asigna campos (maneja si faltan)
        Song song;
        song.id = IdCounter++;
        song.name     = name.size() > 0 ? name : "Desconocido";
        song.artist   = artist.size() > 0 ? artist : "Desconocido";
        song.album    = album.size() > 0 ? album : "N/A";
        song.duration = songPath.size() > 0 ? songPath : "00:00";
        song.path     = songPath.size() > 0 ? songPath : "";

        // Duración opcional: calculamos con SFML si el archivo existe
        songs.push_back(song);
    }
    file.close();
    return songs;
}
