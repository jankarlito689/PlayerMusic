#include <iostream>
#include "File/File.hpp"
#include "List/circularList.hpp"
#include "Player/player.hpp"

using namespace std;

int main() {
    File file;
    CircularList playlist;
    Player player;

    string path;
    cout << "Ingrese la ruta del archivo de playlist (.txt): ";
    getline(cin, path);

    auto songs = file.readPlaylist(path);
    if (songs.empty()) {
        cerr << "No se encontraron canciones.\n";
        return 1;
    }

    for (auto &song : songs)
        playlist.insert_Last(song);

    playlist.print();

    Node *current = playlist.getHead();
    if (!current) return 0;

    player.play(current->song);

    int opc;
    do {
        cout << "\n╔═══════════════════════════════╗\n";
        cout << "║     🎵 MENÚ DEL REPRODUCTOR    ║\n";
        cout << "╠═══════════════════════════════╣\n";
        cout << "║ 1) Pausar                     ║\n";
        cout << "║ 2) Reanudar                   ║\n";
        cout << "║ 3) Siguiente canción          ║\n";
        cout << "║ 4) Canción anterior           ║\n";
        cout << "║ 0) Salir                      ║\n";
        cout << "╚═══════════════════════════════╝\n";
        cout << "Opción: ";
        cin >> opc;

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
                break;
            default:
                cout << "Opción no válida.\n";
        }

    } while (opc != 0);

    return 0;
}