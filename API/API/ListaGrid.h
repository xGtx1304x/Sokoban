#ifndef LISTAGRID_H
#define LISTAGRID_H

#include<iostream>
#include "utiles.h"

using namespace std;

enum Direccion {
	Up,
	Down,
	Left,
	Right
};

class ListaGrid {
private:

	struct NodoGrid {
		NodoGrid* up;
		NodoGrid* down;
		NodoGrid* left;
		NodoGrid* right;
		char val;

		NodoGrid(char val) : 
			val(val), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
	};

	NodoGrid* inicio;

public:
	ListaGrid(string* nivel);
	virtual ~ListaGrid();
	void cargarNivel(string* nivel);
	NodoGrid* obtenerPosicion(int x, int y);
	int* posicionJugador();
	NodoGrid* buscarObjeto(char o);
	bool mover(Direccion dir);
	bool ganador();
	void generarMatriz(int n, int m);
	string toString();
};

#endif
