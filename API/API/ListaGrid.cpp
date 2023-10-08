#include "ListaGrid.h"

ListaGrid::ListaGrid(string* nivel) {
	this->cargarNivel(nivel);
}

ListaGrid::~ListaGrid() {

}

void ListaGrid::cargarNivel(string* nivel) {
	if (nivel) {
		this->inicio = new NodoGrid(nivel[0][0]);
		for (int i = 0; i < nivel[0].length(); i++) {

		}
	}
}