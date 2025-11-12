#include "menu.hpp"

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
    cout << "║" << WHITE << "                🎧  REPRODUCTOR MUSICAL C++                " << CYAN << "║\n";
    cout << "╠════════════════════════════════════════════════════════════╣\n";
    cout << RESET;
}

void drawFooter() {
    cout << CYAN << "╚════════════════════════════════════════════════════════════╝\n" << RESET;
}

void drawMenu() {
    drawHeader();
    cout << WHITE
        << "║ " << YELLOW << "1) " << WHITE << "Pausar canción                              ║\n"
        << "║ " << YELLOW << "2) " << WHITE << "Reanudar canción                            ║\n"
        << "║ " << YELLOW << "3) " << WHITE << "Siguiente canción                           ║\n"
        << "║ " << YELLOW << "4) " << WHITE << "Canción anterior                            ║\n"
        << "║ " << YELLOW << "0) " << WHITE << "Salir del reproductor                       ║\n";
    drawFooter();
}

void showPlayingInfo(const string &name, const string &artist, const string &duration) {
    cout << "\n" << GREEN << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║" << WHITE << " 🎵 Reproduciendo: " << BLUE << name << RESET << endl;
    cout << GREEN << "║" << WHITE << " 👨‍🎤 Artista: " << BLUE << artist << RESET << endl;
    cout << GREEN << "║" << WHITE << " ⏱️  Duración: " << BLUE << duration << RESET << endl;
    cout << GREEN << "╚════════════════════════════════════════════════════════════╝\n" << RESET;
}

} // namespace Ui
