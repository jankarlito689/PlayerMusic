#include "utils.hpp"
#include <iostream>
#include <limits>
#include <cctype>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
using namespace std;

void pausar() {
    cin.clear();
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void limpiar() {
    cout << "\033[2J\033[H";
}
char getch_noblock(){
    // Guardamos flags y termios originales
    int fd = STDIN_FILENO;
    termios oldt{};
    if (tcgetattr(fd, &oldt) == -1) return 0;

    termios newt = oldt;
    // Modo no canónico (ICANON off) y sin eco (ECHO off)
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;  // lectura inmediata
    newt.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &newt) == -1) return 0;

    // Poner descriptor en non-blocking
    int oldf = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, oldf | O_NONBLOCK);

    char c = 0;
    ssize_t r = read(fd, &c, 1);
    if (r <= 0) {
        c = 0; // no input
    }

    // Restaurar flags y termios
    fcntl(fd, F_SETFL, oldf);
    tcsetattr(fd, TCSANOW, &oldt);

    return c;
}
// Lectura segura de enteros
int leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia cualquier resto de la línea
            return valor;
        }

        cout << "Entrada no válida. Intente nuevamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
//Mover la ui en la pantalla
void gotoxy(int x, int y){
    cout << "\033[" << y << ";" << x << "H";
}
void restoreCursor(){
    printf("\033[u");
}
void saveCursor(){
    printf("\033[s");
}