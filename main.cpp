#include <iostream>
#include <limits>
#include <filesystem>
#include "File/File.hpp"
#include "List/circularList.hpp"
#include "Player/player.hpp"
#include "UI/menu.hpp"
#include "Utils/utils.hpp"

using namespace std;
namespace fs = std::filesystem;



int main() {
    File file;
    CircularList playlist;
    Player player;

    limpiar();
    string path;
    
    while (true) {
        cout << "Ingrese la ruta del archivo de playlist (.txt): ";
        getline(cin, path);

        if (fs::exists(path)) {
            break;
        } else {
            cerr << "⚠️  Error: el archivo " << path << " no existe.\n";
            pausar();
        }
    }

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
        
        playlist.print();             
        cout << "\n";

        //Obtenemos tiempo y duracion para la barra de progreso
        float currentTime = player.getPlayingOffset();
        float totalTime = player.getDuration();

        Ui::drawMenu();
        Ui::showPlayingInfo(current->song.name, current->song.artist, current->song.duration);
        Ui::drawProgressBar(currentTime, totalTime);
        cout << "\n-------------------------------------\n";
        cout << "Presione una opción (0-6): ";
        cin >> opc;
        cout << "\n-------------------------------------\n";
        switch (opc) {
            case 1: player.pause(); break;
            case 2: player.resume();break;
            case 3:
                current = playlist.nextSong(current);
                player.play(current->song);
                break;
            case 4:
                current = playlist.prevSong(current);
                player.play(current->song);
                break;
            case 5: {
                player.stop();
                playlist.clear(); // 🧹 Limpia la lista actual (asegúrate de tener este método)
                limpiar();

                cout << "Ingrese la nueva ruta del archivo de playlist (.txt): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, path);

                auto newSongs = file.readPlaylist(path);

                if (newSongs.empty()) {
                    cerr << "No se encontraron canciones en la nueva playlist.\n";
                    pausar();
                    break;
                }

                for (auto &song : newSongs)
                    playlist.insert_Last(song);

                current = playlist.getHead();
                if (!current) {
                    cerr << "Error: playlist vacía.\n";
                    break;
                }
                player.play(current->song);
                cout << "✅ Playlist cambiada correctamente.\n";
                break;
            }
            case 6:{
                int subopc = -1;
                while (subopc != 0) {
                    limpiar();
                    playlist.print();
                    cout << "\n";
                    Ui::drawPlayListMenu();
                    cout << "Seleccione una opción: ";
                    cin >> subopc;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (subopc){
                        case 1: { // Registrar
                            Song newSong;
                            cout << "Nombre: "; getline(cin, newSong.name);
                            cout << "Artista: "; getline(cin, newSong.artist);
                            cout << "Ruta del archivo (.ogg/.wav): "; getline(cin, newSong.path);
                            playlist.newSong(newSong);
                            break;
                        }
                        case 2: { // Buscar
                            string q;
                            cout << "Buscar canción (ID / Nombre / Artista): ";
                            getline(cin, q);
                            
                            Node *found = playlist.FindSong(q); // asegúrate que FindSong devuelva Node*

                            if (found) {
                                current = found;
                                player.play(current->song);
                            } else {
                                cout << "No se encontró la canción.\n";
                            }
                            break;
                        }
                        case 3: {
                            int tipo;
                            cout << "Ordenar por: 1) ID  2) Nombre  3) Artista: ";
                            cin >> tipo;
                            if (tipo == 1) playlist.sortbyid();
                            else if (tipo == 2) playlist.sortbyName();
                            else if (tipo == 3) playlist.sortbyArtist();
                            int asc;
                            cout << "1) Ascendente  2) Descendente: ";
                            cin >> asc;
                            if (asc == 2) playlist.invertList();
                            cout << "✅ Lista ordenada.\n";
                            break;
                        }
                        case 4:{
                            playlist.invertList();
                            cout << "🔁 Lista invertida.\n";
                            break;
                        }
                        case 5: {
                            int id;
                            cout << "ID de la canción a editar: ";
                            cin >> id;
                            cin.ignore();

                            Song newData;

                            cout << "Nuevo nombre (enter para dejar igual): ";
                            getline(cin, newData.name);
                            cout << "Nuevo artista (enter para dejar igual): ";
                            getline(cin, newData.artist);
                            cout << "Nueva duración (enter para dejar igual): ";
                            getline(cin, newData.duration);
                            cout << "Nueva ruta (enter para dejar igual): ";
                            getline(cin, newData.path);

                            newData.id = id;

                            Node* edited = playlist.editSong(id, "", newData);

                            if (edited) {
                                current = edited;
                                player.play(current->song);
                                cout << "🎧 Reproduciendo canción editada...\n";
                            }
                            break;
                        }
                        case 6: {
                            int id;
                            cout << "ID de la canción a eliminar: ";
                            cin >> id;
                            playlist.deleteSong(id, "");
                            break;
                        }
                        case 7:{
                            playlist.clear();
                            cout << "🧹 Lista vaciada.\n";
                            break;
                        }
                        case 0:
                            cout << "Volviendo al menú principal...\n";
                            break;
                        default:
                            cout << "⚠️ Opción no válida.\n";
                    }
                    cout << "\nPresione Enter para continuar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 0:
                player.stop();
                cout << "👋  Gracias por usar el reproductor.\n";
                break;
            default:
            cout << "  Opción no válida.\n";
        }
    }

    return 0;
}
