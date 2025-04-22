#ifndef DISPARAR_H
#define DISPARAR_H
#include "Estructuras.h"

    //Cabecera: int disparo_manual (Jugador jug, registro_configuracion confi)
    //Precondición: E struct jug, E struct confi, E entero n (numero del jugador)
    //Postcondición: Muestra por pantalla el resultado de un disparo manual realizado por el jugador.
    int disparo_manual (Jugador *jug, registro_configuracion confi, int n);

    //Cabecera: int disparo_automatico(Jugador *jug, registro_configuracion confi, int n)
    //Precondición: E/S struct jug, E struct registro_configuracion, E entero n
    //Postcondición: Muestra por pantalla el resultado del disparo realizado automaticamente por el sistema
    int disparo_automatico(Jugador *jug, registro_configuracion confi, int n); 

    //Cabecera: void comprobar_disparo (Jugador *jug, Configuracion *confi, int fila, int columna)
    //Precondición: E/S struct jug, E/S struct confi, E entero fila, E entero columna, E entero n
    //Postcondición: Comprueba el resultado de un disparo y cambia en el tablero del oponente si el barco esta tocado o hundido.
    int comprobar_disparo (Jugador *jug, registro_configuracion *confi, int fila, int columna, int n);

#endif