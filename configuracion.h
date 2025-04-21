#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_
#include "Estructuras.h"

//cabecera: void configuracion(Jugador* jugadores, registro_configuracion* config, Barcos* barcos)
//precondicion:
//postcondicion: devuelve la configuracion general del juego
void configuracion(Jugador* jugadores, registro_configuracion* config, Barcos* barcos);

//cabecera: void introducir_datos(Jugador*, registro_configuracion*,Barcos* barcos)
//precondicion: pendiente
//postcondicion: devuelve todos los elementos configurables del juego previos a comenzar la partida
void introducir_datos(Jugador*, registro_configuracion*,Barcos* barcos);

//cabecera: int generar_n_aleatorio();
//precondicion:
//postcondicion: devuelve un numero aleatorio entre 0 y 9
int generar_n_aleatorio();

//cabecera: void mostrar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos);
//precondicion:
//postcondicion: devuelve un resumen de la configuracion actual
void mostrar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos);

//cabecera: void quitar_salto_linea(char* cadena)
//precondicion: inicializar con fgets() una cadena de caracteres
//postcondicion: quita el \n del final de la cadena de caracteres
void quitar_salto_linea(char* cadena);

//cabecera: void borrar_configuracion(Jugador* jugadores, registro_configuracion* config)
//precondicion: inicializar las estructuras jugadores y config
//postcondicion: borra toda la configuración que hayamos introducido
void borrar_configuracion(Jugador* jugadores, registro_configuracion* config);

//cabecera: tipo_barcos_a_utilizar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos)
//precondicion: inicializar la estructura barcos
//postcondicion: devuelve los tipos de barcos que utilizaran los jugadores
void tipo_barcos_a_utilizar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos);

#endif
