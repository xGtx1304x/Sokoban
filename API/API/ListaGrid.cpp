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

ListaGrid::NodoGrid* ListaGrid::obtenerPosicion(int x, int y) {
    // Verificar que x y y estén dentro de los límites de la matriz
    if (x < 0 || y < 0) {
        cerr << "Coordenadas inválidas." << endl;
        return nullptr; // Devolver un valor predeterminado en caso de coordenadas inválidas
    }

    NodoGrid* current = inicio;
    int row = 0;
    int col = 0;

    // Moverse hacia abajo hasta la fila deseada (coordenada y)
    while (row < y && current != nullptr) {
        current = current->down;
        row++;
    }

    // Moverse hacia la derecha hasta la columna deseada (coordenada x)
    while (col < x && current != nullptr) {
        current = current->right;
        col++;
    }

    // Verificar si se llegó al nodo deseado
    if (row == y && col == x && current != nullptr) {
        return current;
    }
    else {
        cerr << "Coordenadas fuera de los límites de la matriz." << endl;
        return nullptr; // Devolver un valor predeterminado en caso de coordenadas fuera de los límites
    }
}

ListaGrid::NodoGrid* ListaGrid::buscarObjeto(char o) {
    // Iniciar desde el primer nodo de la primera fila
    NodoGrid* current = inicio;

    int x = 0;
    int y = 0;

    while (current != nullptr) {
        NodoGrid* rowStart = current; // Marcar el inicio de la fila actual
        y = 0;
        // Recorrer la fila actual y concatenar los valores
        while (current != nullptr) {
            if (current->val == o) {
                return current;
            }
            y++;
            current = current->right;
        }

        x++;
        current = rowStart->down; // Moverse a la siguiente fila
    }

    return nullptr;
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

int* ListaGrid::posicionJugador() {
    // Iniciar desde el primer nodo de la primera fila
    NodoGrid* current = inicio;

    int x = 0;
    int y = 0;

    while (current != nullptr) {
        NodoGrid* rowStart = current; // Marcar el inicio de la fila actual
        y = 0;
        // Recorrer la fila actual y concatenar los valores
        while (current != nullptr) {
            if (current->val == '@') {
                return new int[2] {x, y};
            }
            y++;
            current = current->right;
        }

        x++;
        current = rowStart->down; // Moverse a la siguiente fila
    }

    return nullptr;
}

bool ListaGrid::mover(Direccion dir) {
    // Buscar la posición actual del jugador '@'
    NodoGrid* jugador = buscarObjeto('@');

    if (jugador == nullptr) {
        cerr << "El jugador no se encuentra en la matriz." << endl;
        return false; // No se puede mover si no se encuentra el jugador
    }

    int* posJugador = this->posicionJugador();

    int x = posJugador[0];
    int y = posJugador[1];

    // Calcular las coordenadas de destino según la dirección
    int destX = y;
    int destY = x;

    switch (dir) {
    case Up:
        destY--;
        break;
    case Down:
        destY++;
        break;
    case Left:
        destX--;
        break;
    case Right:
        destX++;
        break;
    default:
        cerr << "Dirección no válida." << endl;
        return false; // Dirección no válida
    }

    // Obtener el nodo en la dirección de destino
    NodoGrid* destino = obtenerPosicion(destX, destY);

    if (destino == nullptr) {
        cerr << "Coordenadas fuera de los límites de la matriz." << endl;
        return false; // Coordenadas fuera de los límites de la matriz
    }

    // Realizar el movimiento según las reglas
    if (destino->val == ' ') {
        // Intercambiar los valores de jugador y destino
        jugador->val = ' ';
        destino->val = '@';
        return true; // Movimiento válido
    }
    else if (destino->val == '#') {
        return false; // No se puede mover a una pared '#'
    }
    else if (destino->val == '.') {
        return false; // No se puede mover a un objetivo '.'
    }
    else if (destino->val == '!') {
        return false; // No se puede mover a un objetivo con caja '!'
    }
    else if (destino->val == '$') {
        // Calcular las coordenadas del nodo siguiente
        int nextX = destX;
        int nextY = destY;

        switch (dir) {
        case Up:
            nextY--;
            break;
        case Down:
            nextY++;
            break;
        case Left:
            nextX--;
            break;
        case Right:
            nextX++;
            break;
        }

        // Obtener el nodo siguiente
        NodoGrid* siguiente = obtenerPosicion(nextX, nextY);

        if (siguiente == nullptr) {
            cerr << "Coordenadas fuera de los límites de la matriz." << endl;
            return false; // Coordenadas fuera de los límites de la matriz
        }

        // Realizar el movimiento según las reglas adicionales para '$'
        if (siguiente->val == ' ') {
            // Intercambiar los valores de destino, jugador y siguiente
            destino->val = '@';
            jugador->val = ' ';
            siguiente->val = '$';
            return true; // Movimiento válido
        }
        else if (siguiente->val == '#') {
            return false; // No se puede mover una caja '$' hacia una pared '#'
        }
        else if (siguiente->val == '!') {
            return false; // No se puede mover una caja '$' hacia un objetivo con caja '!'
        }
        else if (siguiente->val == '$') {
            return false; // No se puede mover una caja '$' hacia otra caja '$'
        }
        else if (siguiente->val == '.') {
            // Intercambiar los valores de destino, jugador y siguiente,
            // y cambiar el objetivo '.' a objetivo con caja '!'
            destino->val = '@';
            jugador->val = ' ';
            siguiente->val = '!';
            //siguiente->right->val = '!';
            return true; // Movimiento válido
        }
    }

    return false; // Movimiento no válido por defecto
}