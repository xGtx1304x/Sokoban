#include "Juego.h"

Juego::Juego() {
	for (int i = 0; i < 3; i++) {
		this->mapa[i] = new string[20];
	}
	this->cargarMapas();
	for (int i = 0; i < 3; i++) {
		this->mapas[i] = new ListaGrid(this->mapa[i]);
	}
	this->nivel = 0;
}

bool Juego::ganador() {
	return mapas[nivel]->ganador();
}

ListaGrid** Juego::getMapas() {
	return this->mapas;
}

void Juego::cargarMapas() {
    ifstream archivo("Niveles.txt");

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo para lectura." << std::endl;
        return;
    }

    string linea;
    int numeroNivel = 0;
	int n = 0;
    bool enNivel = false;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            // Cambio de nivel
            enNivel = false;
            numeroNivel++;
			n = 0;
			continue;
        }

        // Imprimir la línea de la representación del nivel
        cout << linea << "\n";
		this->mapa[numeroNivel][n++] = linea;
    }

    archivo.close();
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