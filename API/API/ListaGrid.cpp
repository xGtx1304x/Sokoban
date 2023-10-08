#include "ListaGrid.h"

ListaGrid::ListaGrid(string* nivel) {
	this->cargarNivel(nivel);
}

ListaGrid::~ListaGrid() {

}

void ListaGrid::generarMatriz(int n, int m) {
    if (n <= 0 || m <= 0) {
        cerr << "Tamaño de matriz no válido." << endl;
        return;
    }

    inicio = new NodoGrid('a');
    NodoGrid* current = inicio;

    for (int i = 1; i < m; i++) {
        current->right = new NodoGrid('a');
        current->right->left = current;
        current = current->right;
    }

    NodoGrid* prevRow = inicio;

    for (int j = 1; j < n; j++) {
        current = new NodoGrid('a');
        prevRow->down = current;
        current->up = prevRow;

        NodoGrid* firstInRow = current; // Mantén una referencia al primer nodo de la fila

        for (int i = 1; i < m; i++) {
            current->right = new NodoGrid('a');
            current->right->left = current;
            current->right->up = prevRow->right;
            prevRow->right->down = current->right;
            current = current->right;
            prevRow = prevRow->right;
        }

        prevRow = firstInRow; // Ahora puedes usar la referencia al primer nodo de la fila
    }
}

string ListaGrid::toString() {
    string result = "";

    // Iniciar desde el primer nodo de la primera fila
    NodoGrid* current = inicio;

    while (current != nullptr) {
        NodoGrid* rowStart = current; // Marcar el inicio de la fila actual

        // Recorrer la fila actual y concatenar los valores
        while (current != nullptr) {
            result += current->val;
            current = current->right;
        }

        result += '\n'; // Agregar una nueva línea al final de cada fila
        current = rowStart->down; // Moverse a la siguiente fila
    }

    return result;
}

void ListaGrid::cargarNivel(string* nivel) {
    int n = Utiles::size(nivel);
    int m = nivel[0].length();
    if (n <= 0 || m <= 0) {
        cerr << "Tamaño de matriz no válido." << endl;
        return;
    }

    inicio = new NodoGrid(nivel[0][0]);
    NodoGrid* current = inicio;

    for (int i = 1; i < m; i++) {
        current->right = new NodoGrid(nivel[0][i]);
        current->right->left = current;
        current = current->right;
    }

    NodoGrid* prevRow = inicio;

    for (int j = 1; j < n; j++) {
        current = new NodoGrid(nivel[j][0]);
        prevRow->down = current;
        current->up = prevRow;

        NodoGrid* firstInRow = current; // Mantén una referencia al primer nodo de la fila

        for (int i = 1; i < m; i++) {
            current->right = new NodoGrid(nivel[j][i]);
            current->right->left = current;
            current->right->up = prevRow->right;
            prevRow->right->down = current->right;
            current = current->right;
            prevRow = prevRow->right;
        }

        prevRow = firstInRow; // Ahora puedes usar la referencia al primer nodo de la fila
    }
}