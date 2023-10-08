#include "utiles.h"

int Utiles::size(string* coleccion) {
    int res = 0;
    while (coleccion[res] != "") {
        res++;
    }
    return res;
}