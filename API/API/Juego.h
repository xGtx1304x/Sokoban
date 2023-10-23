#ifndef JUEGO_H
#define JUEGO_H

#include "ListaGrid.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Juego {
private:
	ListaGrid* mapas[3];
	vector<Direccion> repeticion[3];
	int nivel;
	string* mapa[3];
public:
	Juego();
	virtual ~Juego() = default;
	ListaGrid** getMapas();
	bool ganador();
	void cargarMapas();
	void reset();
	bool mover(Direccion dir);
	string mostrarNivel();
	vector<Direccion> gameplay();
	bool final();
	void avanzar();
};

#endif
