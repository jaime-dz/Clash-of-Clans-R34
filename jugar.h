#ifndef JUGAR_H_
#define JUGAR_H_
#include "Estructuras.h"

//Cabecera: void colocacion_barcos(Jugador* jugadores, registro_configuracion* config, Barcos* barcos)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion:
void colocacion_barcos(Jugador* , registro_configuracion* , Barcos* );

//Cabecera: void Jugar(Jugador* jugadores, registro_configuracion* config);
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: menu previo al comienzo de la partida
void Jugar(Jugador* , registro_configuracion* , Barcos* );

//Cabecera: void jugar_partida(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: menu para jugar la partida
void jugar_partida(Jugador* jugadores, registro_configuracion* config);

//Cabecera:void Libera_Memoria(char ***m,int dim);
//Precondicion: inicializar una matriz dinamica
//Postcondicion: libera su memoria asignada
void Liberar_Memoria(char ***, int );

//Cabecera:void imprimir_matriz(char **m,int dim);
//Precondicion: recibe una matriz de caracteres inicializada y su dimensión
//Postcondicion: la imprime por pantalla
void imprimir_matriz(char **,int );

//Cabecera: void reiniciar_partida(Jugador *jugadores,registro_configuracion *config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: inicializa los valores de todas las variables incluidos los tableros
void reiniciar_partida(Jugador *,registro_configuracion *);

//Cabecera: void Resumen(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: muestra por pantalla el resumen de la partida
void Resumen(Jugador* , registro_configuracion* );

//Cabecera: void Contadores_Resumen(Jugador* jugadores,registro_configuracion* config);
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: devuelve el numero de casillas de cada tipo
void Contadores_Resumen(Jugador* ,registro_configuracion* );

//Cabecera:void elimina(char *c1);
//Precondicion: recibe una cadena de caracteres inicializada
//Postcondicion: elimina el salto de línea de la cadena introducido por fgets
void elimina(char *c1);

//Cabecera: void inicializar_tablero(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: inicializa los tableros de juego de ambos jugadores
void inicializar_tablero(Jugador* , registro_configuracion* );

//Cabecera: void generar_matriz_dinamica(char*** matriz, int longitud)
//Precondicion: inicializar la longitud del tablero
//Postcondicion: genera una matriz dinamica sin inicializar
void generar_matriz_dinamica(char*** , int );

//Cabecera: void mostrar_tablero(char **tablero, int t_tablero);
//Precondicion: recibe una matriz de caracteres inicializada y su dimensión
//Postcondicion: muestra el tablero por pantalla
void mostrar_tablero(char **, int );

#endif