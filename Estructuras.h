#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <stdlib.h>
#include <stdio.h>
#define N_JUG 2
typedef struct{
    char Nomb_barco [20];
    char Id_barco[1];
    int Tam_barco;
}Barcos;

typedef struct{
    int Id_jugador;
    char Nomb_jugador [20];
    char Tipo_disparo;
    int Num_disp;
    int Ganador;
    int barcos_hundidos;
    char **Flota;
    char **Oponente;
    int vacias;
    int aguas;
    int tocadas;
    int hundidas;
    int restan;
}Jugador;

typedef struct{

    int t_tablero; // longitud_tablero
    int comienzo;  // jugador que comienza la partida
    int n_barcos_flota;
    int n_tipos_barco;
    int* c_barco;

}registro_configuracion;

//Cabecera: void escribir_jugador (Jugador *jug, int n, int tam)
//Precondicion: inicializar la estructura jugador
//Postcondicion: escribe en un fichero los datos de configuracion de los jugadores
void guardar (Jugador *jug, int n, registro_configuracion*, Barcos* barcos);

#endif
