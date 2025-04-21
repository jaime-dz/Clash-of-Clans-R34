#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "Estructuras.h"
#include "CargaDatos.h"
#include "Jugar.h"

int main(){

    int c, i;
    Jugador jugadores[2];
    registro_configuracion config;
    Barcos* barcos;
    cargaBarcos(&barcos);
    borrar_configuracion(jugadores,&config);

    do{
        printf("---------- Hundir la flota ----------\n\n");
        printf("    1. Configuracion.\n");
        printf("    2. Jugar.\n");
        printf("    3. Salir.\n\n");
        printf("    -> ");
        scanf("%i",&c);
        fflush(stdin);
        system("cls");
        switch(c){
            case 1:
                configuracion(jugadores,&config,barcos);
                break;
            case 2:
                Jugar(jugadores,&config,barcos);
                break;
            case 3:
                break;
            default:
                system("cls");
                printf("Opcion no valida...\n");
                printf("Por favor introduzca una opcion valida...\n\n");
                break;
        }
    }while(c!=3);

    for(i=0;i<2;i++){
        Liberar_Memoria(&jugadores[i].Flota,config.t_tablero);
        Liberar_Memoria(&jugadores[i].Oponente,config.t_tablero);
    }

    return 0;
}
