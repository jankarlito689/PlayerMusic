#include <iostream>
#include <limits>
#include "File/File.hpp"
#include "List/circularList.hpp"
#include "Player/player.hpp"
#include "UI/menu.hpp"
#include "Utils/utils.hpp"
using namespace std;

int main() {
    File file;
    CircularList playlist;
    Player player;

    limpiar();
    string path;
    cout << "Ingrese la ruta del archivo de playlist (.txt): ";
    getline(cin, path);

    auto songs = file.readPlaylist(path);
    if (songs.empty()) {
        cerr << "No se encontraron canciones.\n";
        pausar();
        return 1;
    }

    for (auto &song : songs)
        playlist.insert_Last(song);
    
    Node *current = playlist.getHead();
    if (!current) return 0;

    player.play(current->song);

    int opc = -1; 

    while (opc != 0) {
        limpiar();    
        cout << "\n";
        playlist.print();             
        cout << "\n";
        Ui::drawMenu();
        cout << "\n";
        Ui::showPlayingInfo(current->song.name, current->song.artist, current->song.duration);
        cout << "\n-------------------------------------\n";
        cout << "Seleccione una opción: ";
        cin >> opc;

        cout << "\n-------------------------------------\n";
        switch (opc) {
            case 1:
                player.pause();
                break;
            case 2:
                player.resume();
                break;
            case 3:
                current = playlist.nextSong(current);
                player.play(current->song);
                break;
            case 4:
                current = playlist.prevSong(current);
                player.play(current->song);
                break;
            case 0:
                player.stop();
                cout << "👋  Gracias por usar el reproductor.\n";
                break;
            default:
                cout << "⚠️  Opción no válida.\n";
        }

        if (opc != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // espera Enter
        }
    }

    return 0;
}
