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
    // No bloquear lectura
    int oldf = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    char c = 0;
    if (read(STDIN_FILENO, &c, 1) < 0) {
        return 0;
    }

    // Restaurar flag
    fcntl(STDIN_FILENO, F_SETFL, oldf);
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