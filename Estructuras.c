#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estructuras.h"

//Cabecera: void escribir_barco (Barcos *bar)
//Precondicion: Recibe la estructura barcos ya inicializada
//Postcondicion: Escribe en el fichero barcos.txt

void escribir_barco (Barcos *bar){  // Quiero reciclar esta funcion
    FILE *fichero2;
    if((fichero2=fopen("Barcos.txt","w"))==NULL){
        printf("Error al abrir el fichero barcos.txt");
    }

    // Necesito el mismo bucle que en la funcion de abajo y que la estructura Barcos este inicializada
    fprintf(fichero2, "%s-%c\n",bar->Nomb_barco,bar->Id_barco);
    fclose(fichero2);
}

//Cabecera: void escribir_jugador (Jugador *jug, int n, int tam)
//Precondicion: inicializar la estructura jugador
//Postcondicion: escribe en un fichero los datos de configuracion del jugador

void escribir_jugador (Jugador *jug, int n, int tam, registro_configuracion* config){
    int i = 0;
    FILE *fichero1;
    fichero1 = fopen("Juego.txt","w+");
    if (fichero1 == NULL) {
        printf ("Error al abrir el fichero");
        exit (1);
    }
    fprintf(fichero1, "%i-%i-%i\n", config->t_tablero, config->n_barcos_flota, config->n_tipos_barco);
    for (i = 0; i < n; i++) {
        fprintf(fichero1, "%d-%s-%i-%c-%i\n", jug[i].Id_jugador,jug[i].Nomb_jugador,jug[i].Num_disp,jug[i].Tipo_disparo,jug[i].Ganador);
    }
    fclose(fichero1);
    // Aqui faltan las matrices, Luis ya lo tiene programado
}
