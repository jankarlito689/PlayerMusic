#include "menu.hpp"
#include "../Utils/utils.hpp"
#include <iomanip>

// Colores ANSI
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

namespace Ui {

void drawHeader() {
    cout << CYAN << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║" << WHITE << "                🎧  REPRODUCTOR MUSICAL C+     "       << CYAN <<             "             ║\n";
    cout << "╠════════════════════════════════════════════════════════════╣\n";
    cout << RESET;
}

void drawFooter() {
    cout << CYAN << "╚════════════════════════════════════════════════════════════╝\n" << RESET;
}

void drawProgressBar(float current, float total) {
    int barWidth = 40; // Tamaño de la barra
    float progress = (total > 0 ? current / total : 0);

    int pos = progress * barWidth;

    cout << GREEN << "╔════════════════ PROGRESO ════════════════╗\n";
    cout << "║ ";

    for (int i = 0; i < barWidth; i++) {
        if (i < pos) cout << BLUE << "█";
        else cout << WHITE << "░";
    }

    cout << RESET << " ║\n";

    // Mostrar tiempos
    int currentInt = (int)current;
    int totalInt   = (int)total;

    cout << "║ " << YELLOW 
         << currentInt / 60 << ":" << (currentInt % 60 < 10 ? "0" : "") << currentInt % 60 
         << WHITE << "  /  " << GREEN
         << totalInt / 60 << ":" << (totalInt % 60 < 10 ? "0" : "") << totalInt % 60
         << RESET << "                            ║\n";

    cout << GREEN << "╚══════════════════════════════════════════╝\n" << RESET;
}

void drawMenu() {
    drawHeader();
    cout << WHITE
        << "║ " << YELLOW << "1) " << WHITE << "Pausar canción                                          ║\n"
        << "║ " << YELLOW << "2) " << WHITE << "Reanudar canción                                        ║\n"
        << "║ " << YELLOW << "3) " << WHITE << "Siguiente canción                                       ║\n"
        << "║ " << YELLOW << "4) " << WHITE << "Canción anterior                                        ║\n"
        << "║ " << YELLOW << "5) " << WHITE << "Cambiar de playList                                     ║\n"
        << "║ " << YELLOW << "6) " << WHITE << "Gestión de playList                                     ║\n"
        << "║ " << YELLOW << "0) " << WHITE << "Salir del reproductor                                   ║\n";
    drawFooter();
}

void drawPlayListMenu() {
    drawHeader();
    cout << WHITE
        << "║ " << YELLOW << "1) " << WHITE << "Registrar nueva canción                                 ║\n"
        << "║ " << YELLOW << "2) " << WHITE << "Buscar canción                                          ║\n"
        << "║ " << YELLOW << "3) " << WHITE << "Ordenar canciones                                       ║\n"
        << "║ " << YELLOW << "4) " << WHITE << "Invertir lista                                          ║\n"
        << "║ " << YELLOW << "5) " << WHITE << "Editar canción                                          ║\n"
        << "║ " << YELLOW << "6) " << WHITE << "Eliminar canción                                        ║\n"
        << "║ " << YELLOW << "7) " << WHITE << "Vaciar lista                                            ║\n"
        << "║ " << YELLOW << "0) " << WHITE << "Volver al menú principal                                ║\n";
    drawFooter();
}

void showPlayingInfo(const string &name, const string &artist, const string &duration) {
    cout << "\n" << GREEN << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║" << WHITE << " 🎵 Reproduciendo: " << BLUE << name << RESET << endl;
    cout << GREEN << "║" << WHITE << " 👨‍🎤 Artista: " << BLUE << artist << RESET << endl;
    cout << GREEN << "║" << WHITE << " ⏱️  Duración: " << BLUE << duration << RESET << endl;
    cout << GREEN << "╚════════════════════════════════════════════════════════════╝\n" << RESET;
}

void drawPlaylist(const CircularList &playlist, Node *currentPlaying) {
    saveCursor();   // Guardar posición original

    int X = 75;  
    int Y = 2;

    gotoxy(X, Y);
    cout << CYAN << "╔══════════════════════════════════════════════════════════════════════════╗";

    gotoxy(X, Y + 1);
    cout << "║ " << WHITE << "PLAYLIST ACTUAL" << CYAN
         << "                                                          ║";

    gotoxy(X, Y + 2);
    cout << "╠══════════════════════════════════════════════════════════════════════════╣";

    // Encabezados
    gotoxy(X, Y + 3);
    cout << WHITE 
         << "║ " << CYAN << setw(6) << left << "Índice"
         << WHITE << "│ " << CYAN << setw(25) << left << "Nombre Canción"
         << WHITE << "│ " << CYAN << setw(20) << left << "Artista"
         << WHITE << "│ " << CYAN << setw(8)  << left << "Duración" << WHITE
         << " ║";

    gotoxy(X, Y + 4);
    cout << CYAN << "╠══════════════════════════════════════════════════════════════════════════╣" 
         << RESET;

    Node* temp = playlist.getHead();

    int row = 5;

    if (!temp) {
        gotoxy(X, Y + row);
        cout << "║ (Lista vacía)                                                             ║";

        gotoxy(X, Y + row + 1);
        cout << CYAN << "╚══════════════════════════════════════════════════════════════════════════╝" 
             << RESET;

        restoreCursor();
        return;
    }
    do {
        gotoxy(X, Y + row);

        bool isPlaying = (temp == currentPlaying);

        if (isPlaying) {
            cout << BLUE << "║ "
                 << WHITE << setw(6) << left << temp->song.id
                 << BLUE << "│ " << WHITE << setw(25) << left << temp->song.name
                 << BLUE << "│ " << WHITE << setw(20) << left << temp->song.artist
                 << BLUE << "│ " << WHITE << setw(8)  << left << temp->song.duration
                 << BLUE << " ║" << RESET;
        } else {
            cout << "║ "
                 << WHITE << setw(6) << left << temp->song.id
                 << WHITE << "│ " << setw(25) << left << temp->song.name
                 << "│ " << setw(20) << left << temp->song.artist
                 << "│ " << setw(8)  << left << temp->song.duration
                 << " ║";
        }

        temp = temp->next;
        row++;

    } while (temp != playlist.getHead());

    gotoxy(X, Y + row);
    cout << CYAN << "╚══════════════════════════════════════════════════════════════════════════╝"
        << RESET;
    restoreCursor();  // ← ESTE SÍ VA AQUÍ (solo una vez)
}
} // namespace Ui
