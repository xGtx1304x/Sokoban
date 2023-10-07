#ifndef LISTAGRID_H
#define LISTAGRID_H

#include<iostream>

using namespace std;

class ListaGrid {
private:

	struct NodoGrid {
		NodoGrid* up;
		NodoGrid* down;
		NodoGrid* left;
		NodoGrid* right;
		string val;

		NodoGrid(string val) : 
			val(val), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
	};

	NodoGrid* inicio;
public:
	ListaGrid(string* nivel);
	virtual ~ListaGrid();
	void cargarNivel(string* nivel);
	bool mover(int dir);
	bool ganador();
	string toString();
};

#endif
