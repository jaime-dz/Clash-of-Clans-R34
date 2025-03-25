#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "Estructuras.h"
 
void introducir_barco (Barcos *bar) {
    char nombre [20]; 
    do {
    printf("Introduce un nombre para el barco: "); 
    fgets (nombre, 20, stdin); } while(strlen(nombre)>20);
    nombre[strcspn(nombre, "\n")] = 0;
    nombre[strcspn(nombre, " ")] = 0;
    strcpy(bar->Nomb_barco, nombre); 
    bar->Id_barco = nombre[0]; 
    printf ("\nIntroduce el size del barco: "); 
    scanf("%d",&bar->Tam_barco);  
    getchar(); 
}

void escribir_barco (Barcos *bar) {
    FILE *fichero2;
    if ((fichero2=fopen("Barcos.txt","w"))==NULL) {
        printf("Error al abrir el fichero barcos.txt"); 
    }
    fseek(fichero2, 0, SEEK_END); 
    fprintf(fichero2, "%s-%c-%d\n",bar->Nomb_barco,bar->Id_barco,bar->Tam_barco);
    fclose(fichero2); 
}

int main () {
    Barcos barcos; 
    introducir_barco (&barcos); 
    escribir_barco (&barcos); 
    return 0; 
}

void escribir_jugador (Jugador *jug, int n, int tam) { //La funcion escribir jugador en fichero recibe la estructura jugador y un entero, correspondiente al numero de jugadores que hay en la estructura y otro que represente el tamaño del tablero.  
    int i = 0, j = 0, k = 0; 
    FILE *fichero1; 
    fichero1 = fopen("jugador.txt","w+"); 
    if (fichero1 == NULL) {
        printf ("Error al abrir el fichero"); 
        exit (1); 
    }
    for (i = 0; i < n; i++) {
        fprintf(fichero1, "%d-%s-%i-%c-%i\n", jug[i].Id_jugador,jug[i].Nomb_jugador,jug[i].Num_disp,jug[i].Tipo_disparo,jug[i].Ganador);
        for(j = 0; j < tam; j++) {
            for(k = 0; k < tam; k++) {
                if (k == 0) {
                    fprintf(fichero1, " ( ");
                }
                fprintf(fichero1, " %c ",jug[i].Flota[j][k]);
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
                fprintf(fichero1, " %c ",jug[i].Oponente[j][k]);
                if (k == tam - 1) {
                    fprintf(fichero1, " ) \n");
                }
            }
        }
    }
    fclose(fichero1);
}

/*
void escribir_flota (Jugador **jug, int n, char* fichero1, int tam) { //Recibe la estructura y el elemento en concreto del que hay que escribirlo   
    int j = 0, k = 0;
    for(j = 0; j<tam; j++) {
        for(k = 0; k<tam; k++) {
            if (k == 0) {
                fprintf(fichero1, " ( ");
            }
            fprintf(fichero1, " %c ",jug[n].Flota[j][k]);
            if (k == tam - 1) {
                fprintf(fichero1, " ) \n");
            }
        }
    }

}
*/