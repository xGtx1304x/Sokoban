#include "Juego.h"

Juego::Juego(string** mapas) {
	for (int i = 0; i < 3; i++) {
		this->mapas[i] = new ListaGrid(mapas[i]);
		this->mapa[i] = mapas[i];
	}
	this->nivel = 0;
}

bool Juego::ganador() {
	return mapas[nivel]->ganador();
}

void Juego::reset() {
	this->mapas[nivel] = new ListaGrid(this->mapa[nivel]);
	this->repeticion[nivel].clear();
}

void Juego::avanzar() {
	this->nivel++;
}

bool Juego::mover(Direccion dir) {
	this->mapas[nivel]->mover(dir);
	this->repeticion[nivel].push_back(dir);
	if (this->ganador()) {
		return true;
	}
	return false;
}

string Juego::mostrarNivel() {
	stringstream s;
	s << "Nivel: " << nivel + 1 << endl << endl;
	s << this->mapas[this->nivel]->toString();
	return s.str();
}

vector<Direccion> Juego::gameplay() {
	return this->repeticion[nivel];
}

bool Juego::final() {
	return this->nivel == 3;
}