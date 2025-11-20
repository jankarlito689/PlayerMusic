#pragma once
#include <string>


using namespace std;

#include <string>

void pausar();
void limpiar();
int leerEntero(const string& mensaje);
void gotoxy(int x, int y);
void saveCursor();
void restoreCursor();
char getch_noblock();
