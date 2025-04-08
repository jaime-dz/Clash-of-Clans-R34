#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <stdlib.h>
#include <stdio.h>

// Este codigo es de Luis

typedef struct{
    char Nomb_barco [20];
    char Id_barco;
    int Tam_barco;
}Barcos;

typedef struct{
    int Id_jugador;
    char Nomb_jugador [20];
    char Tipo_disparo;
    int Num_disp;
    int Ganador;
    char **Flota;
    char **Oponente;  //oponente [][]
    Barcos *barco;
}Jugador;

// Este codigo es mio

typedef struct{

    int t_tablero; // longitud_tablero
    int comienzo;  // jugador que comienza la partida
    int n_barcos_flota;
    int n_tipos_barco;
    // Cambios a la hora de contar barcos
    int P; // cantidad de portaaviones
    int A; // cantidad de acorazados
    int C; // cantidad de cruceros
    int D; // cantidad de destructores
    int F; // cantidad de fragatas
    int S; // cantidad de submarinos

    char* id_barco;
    int* c_barco;

}registro_configuracion;



//Cabecera: void escribir_barco (Barcos *bar)
//Precondicion: Recibe la estructura barcos ya inicializada
//Postcondicion: Escribe en el fichero barcos.txt
void escribir_barco (Barcos *bar);

//Cabecera: void escribir_jugador (Jugador *jug, int n, int tam)
//Precondicion: inicializar la estructura jugador
//Postcondicion: escribe en un fichero los datos de configuracion de los jugadores
void escribir_jugador (Jugador *jug, int n, int tam, registro_configuracion*);

#endif
