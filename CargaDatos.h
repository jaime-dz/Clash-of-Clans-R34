#ifndef CARGADATOS_H
#define CARGADATOS_H
#include "Estructuras.h"

//Cabecera: int cargaBarcos(Barcos **barcos)
//Preconcidion:
//Postcondicion: carga en la estructura barcos los tipos de barcos y devuelve la cantidad de tipos de barcos
int cargaBarcos(Barcos**);

// Cabecera: void cargaJuego(Jugador *, registro_configuracion *)
// Precondición: Los punteros 'jugador' y 'config' deben apuntar a estructuras válidas. El archivo "juego.txt" debe existir y tener el formato esperado.
// Postcondición: Se cargan los datos de configuración, los barcos disponibles, los datos de ambos jugadores y las matrices de flotas y
// oponentes en memoria dinámica asociada a los jugadores. Las matrices quedan listas para el uso en el juego.
void cargaJuego(Jugador *jugador,registro_configuracion *config);

#endif
