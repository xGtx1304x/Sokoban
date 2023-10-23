#include <iostream>
#include "Juego.h"
#include <Windows.h>
#include <Wincon.h>

using namespace std;

/*string** getNiveles() {
    string** niveles = new string*[3];
    niveles[0] = new string[10]{
        "#####",
        "#@  #",
        "# $ #",
        "### #",
        "#.$ #",
        "#  .#",
        "#####"
    };
    niveles[1] = new string[10]{
        "  ##### ",
        "###   # ",
        "#.@$  # ",
        "### $.# ",
        "#.# $ # ",
        "# # . ##",
        "#$  $ .#",
        "#  !   #",
        "########"
    };
    niveles[2] = new string[10]{
        "  ####   ",
        "###  ####",
        "#     $ #",
        "#    #$ #",
        "#.  .#@ #",
        "#########"
    };
    return niveles;
}*/

int main() {
    Juego juego;
    bool ganador = false;
    bool salir = false;
    int op = 0;
    
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
        return 1;
    }
    DWORD numRead;
    INPUT_RECORD irInBuf[128];
    
    while (!juego.final() && !salir) {
        ReadConsoleInput(hStdin, irInBuf, 128, &numRead);
        ganador = false;
        op = 0;
        system("cls");
        cout << "- Presiona la tecla 'R' para reiniciar el nivel -" << endl;
        cout << "- Presiona la tecla 'ESC' para salir -" << endl << endl;
        cout << juego.mostrarNivel() << endl;
        
        for (DWORD i = 0; i < numRead; i++) {
            if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                // Se ha presionado una tecla
                WORD keyCode = irInBuf[i].Event.KeyEvent.wVirtualKeyCode;

                if (keyCode == VK_LEFT) {
                    // Flecha izquierda
                    if (juego.mover(Left)) {
                        ganador = true;
                    }
                }
                else if (keyCode == VK_RIGHT) {
                    // Flecha derecha
                    if (juego.mover(Right)) {
                        ganador = true;
                    }
                }
                else if (keyCode == VK_UP) {
                    // Flecha arriba
                    if (juego.mover(Up)) {
                        ganador = true;
                    }
                }
                else if (keyCode == VK_DOWN) {
                    // Flecha abajo
                    if (juego.mover(Down)) {
                        ganador = true;
                    }
                }
                else if (keyCode == 82) {
                    // Tecla "R" presionada
                    juego.reset();
                }
                else if (keyCode == VK_ESCAPE) {
                    // Tecla "ESC" presionada
                    salir = true;
                }
            }
        }
        if (ganador) {
            vector<Direccion> gameplay = juego.gameplay();
            while (op != 2) {
                system("cls");
                cout << juego.mostrarNivel() << endl;
                cout << "Felicidades!" << endl;
                cout << "1. Repeticion" << endl;
                cout << "2. Siguiente" << endl;
                cin >> op;
                switch (op) {
                case 1:
                    juego.reset();
                    for (auto i : gameplay) {
                        juego.mover(i);
                        system("cls");
                        cout << juego.mostrarNivel() << endl;
                        Sleep(500);
                    }
                    break;
                case 2:
                    juego.avanzar();
                    break;
                default:
                    cout << "- Opcion incorrecta, por favor intente de nuevo -" << endl;
                    Sleep(1000);
                    break;
                }
            }
        }
    }
    system("cls");
    if (juego.final()) cout << "Felicidades! Ganaste!" << endl;
    cout << "Gracias por jugar!" << endl;
    
    return 0;
}
