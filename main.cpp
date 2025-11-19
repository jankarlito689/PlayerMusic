#include <iostream>
#include <limits>
#include <filesystem>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include "File/File.hpp"
#include "List/circularList.hpp"
#include "Player/player.hpp"
#include "UI/menu.hpp"
#include "Utils/utils.hpp"

using namespace std;
namespace fs = std::filesystem;

// Esperar Enter sin borrar nada
void waitEnter() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    File file;
    CircularList playlist;
    Player player;

    limpiar();
    string path;
    
    while (true) {
        cout << "Ingrese la ruta del archivo de playlist (.txt): ";
        getline(cin, path);

        if (fs::exists(path)) break;

        cerr << "⚠️  Error: el archivo no existe.\n";
        pausar();
    }

    auto songs = file.readPlaylist(path);
    if (songs.empty()) {
        cerr << "No se encontraron canciones.\n";
        pausar();
        return 1;
    }

    for (auto &song : songs) playlist.insert_Last(song);
    
    Node *current = playlist.getHead();
    if (!current) return 0;

    player.play(current->song);

    int opc = -1;

    bool freezeUI = false;   // Bloquea el refresco cuando hay input
    bool inSubMenu = false;  // Bloquea refresco dentro de menú 6

    // ----------------------------------
    // Loop principal reactivo
    // ----------------------------------
    while (opc != 0) {

        // SI la UI NO está congelada y no estamos en submenú -> refrescamos
        if (!freezeUI && !inSubMenu) {
            this_thread::sleep_for(chrono::milliseconds(50));
            limpiar();

            playlist.print();
            cout << "\n";

            float currentTime = player.getPlayingOffset();
            float totalTime = player.getDuration();

            Ui::drawMenu();
            Ui::showPlayingInfo(current->song.name, current->song.artist, current->song.duration);
            Ui::drawProgressBar(currentTime, totalTime);

            cout << "\n-------------------------------------\n";
            cout << "(Ingrese opción 0-6) → ";
            cout.flush();
        }
        // ----------------------------------
        // Entrada NO bloqueante (solo en menú principal)
        // ----------------------------------
        if (!inSubMenu) {
            char key = getch_noblock();
            if (key >= '0' && key <= '9') {
                opc = key - '0';
                freezeUI = true;  // congelamos repaint mientras procesamos
                //cout << "\n-------------------------------------\n";
                //cout << "(Ingrese opción 0-6) → " << opc << "\n\n";
                cout.flush();
                // pequeño margen para que el usuario vea la tecla (ajusta si quieres)
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }
        // Si no hay opción pendiente, continuamos
        if (opc == -1) continue;
        // ----------------------------------
        // PROCESAR OPCIONES
        // ----------------------------------
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
            case 5: {
                // Detener repaints y usar entrada bloqueante para la ruta
                freezeUI = true;
                player.stop();
                playlist.clear();

                limpiar();
                //cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Ingrese nueva ruta de playlist: ";
                getline(cin, path);

                auto newSongs = file.readPlaylist(path);
                if (newSongs.empty()) {
                    cerr << "No se encontraron canciones.\n";
                    waitEnter();
                    break;
                }
                for (auto &s : newSongs) playlist.insert_Last(s);
                current = playlist.getHead();
                player.play(current->song);
                break;
            }
            case 6: {
                // Entrar al submenú: detenemos completamente el loop reactivo
                inSubMenu = true;
                freezeUI = true;

                // Limpieza segura del buffer antes de usar cin
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int subopc = -1;
                while (subopc != 0) {
                    limpiar();
                    playlist.print();
                    cout << "\n";
                    Ui::drawPlayListMenu();
                    cout << "Seleccione: ";
                    cout.flush();

                    // lectura bloqueante aquí (dentro del submenú)
                    if (!(cin >> subopc)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Entrada inválida.\n";
                        waitEnter();
                        continue;
                    }
                    // limpiar newline pendiente antes de usar getline luego
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (subopc) {
                        case 1: {
                            Song newSong;
                            cout << "Nombre: "; getline(cin, newSong.name);
                            cout << "Artista: "; getline(cin, newSong.artist);
                            cout << "Ruta: "; getline(cin, newSong.path);
                            playlist.newSong(newSong);
                            break;
                        }
                        case 2: {
                            string q;
                            cout << "Buscar: ";
                            getline(cin, q);
                            Node *found = playlist.FindSong(q);
                            if (found) {
                                current = found;
                                player.play(current->song);
                            } else {
                                cout << "No encontrado.\n";
                            }
                            break;
                        }
                        case 3: {
                            int tipo;
                            cout << "Ordenar por (1-ID,2-Nombre,3-Artista): ";
                            if (!(cin >> tipo)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (tipo == 1) playlist.sortbyid();
                            if (tipo == 2) playlist.sortbyName();
                            if (tipo == 3) playlist.sortbyArtist();

                            int asc;
                            cout << "Ascendente(1) / Descendente(2): ";
                            if (!(cin >> asc)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (asc == 2) playlist.invertList();
                            break;
                        }
                        case 4:
                            playlist.invertList();
                            break;
                        case 5: {
                            int id;
                            cout << "ID: ";
                            if (!(cin >> id)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            Song newData;
                            cout << "Nuevo nombre: "; getline(cin, newData.name);
                            cout << "Nuevo artista: "; getline(cin, newData.artist);
                            cout << "Nueva duración: "; getline(cin, newData.duration);
                            cout << "Nueva ruta: "; getline(cin, newData.path);
                            newData.id = id;

                            Node *edited = playlist.editSong(id, "", newData);
                            if (edited) {
                                current = edited;
                                player.play(current->song);
                            }
                            break;
                        }
                        case 6: {
                            int id;
                            cout << "ID: ";
                            if (!(cin >> id)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); break; }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            playlist.deleteSong(id, "");
                            break;
                        }
                        case 7:
                            playlist.clear();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opción inválida.\n";
                            break;
                    } // switch subopc
                    waitEnter();
                } // while subopc
                // restablecer flags
                inSubMenu = false;
                freezeUI = false;
                opc = -1;
                break;
            } // case 6
            case 0:
                player.stop();
                cout << "👋 Gracias por usar el reproductor.\n";
                return 0;
            default:
                cout << "Opción inválida.\n";
                break;
        }
        // reactivar repaint y resetear opcion
        freezeUI = false;
        opc = -1;
    }
    return 0;
}
