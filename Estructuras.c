#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estructuras.h"
#include "CargaDatos.h"

//Cabecera: void guardar (Jugador *jugadores, int n, registro_configuracion* config, Barcos* barcos)
//Precondicion: inicializar la estructura jugador
//Postcondicion: escribe en un fichero los datos de configuracion del jugador

void guardar (Jugador *jugadores, int n, registro_configuracion* config, Barcos* barcos){
    int i = 0, j = 0, k = 0, tam=config->t_tablero;
    FILE *fichero1;
    fichero1 = fopen("Juego.txt","w+");
    if (fichero1 == NULL) {
        printf ("Error al abrir el fichero");
        exit (1);
    }
    fprintf(fichero1, "%i-%i-%i\n", config->t_tablero, config->n_barcos_flota, config->n_tipos_barco);
    for(i=0;i<cargaBarcos(&barcos)-2;i++){
        if(config->c_barco[i]!=0) fprintf(fichero1, "%c-%i\n", barcos[i].Id_barco[0], config->c_barco[i]);
    }
    for (i = 0; i < n; i++) {
        fprintf(fichero1, "%d-%s-%i-%c-%i\n", jugadores[i].Id_jugador,jugadores[i].Nomb_jugador,jugadores[i].Num_disp,jugadores[i].Tipo_disparo,jugadores[i].Ganador);
        for(j = 0; j < tam; j++) {
            for(k = 0; k < tam; k++) {
                if (k == 0) {
                    fprintf(fichero1, " ( ");
                }
                fprintf(fichero1, " %c ",jugadores[i].Flota[j][k]);
                if (k == tam - 1) {
                    fprintf(fichero1, " ) \n");
                }
            }
        }
        for(j = 0; j < tam; j++) {
            for(k = 0; k < tam; k++) {
                if (k == 0) {
                    fprintf(fichero1, " ( ");
                }
                fprintf(fichero1, " %c ",jugadores[i].Oponente[j][k]);
                if (k == tam - 1) {
                    fprintf(fichero1, " ) \n");
                }
            }
        }
    }
    fclose(fichero1);
}
