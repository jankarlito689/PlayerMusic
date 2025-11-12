#include "utils.hpp"
#include <iostream>
#include <limits>
#include <cctype>

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