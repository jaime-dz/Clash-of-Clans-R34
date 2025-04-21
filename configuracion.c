#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "configuracion.h"
#include "Estructuras.h"
#include "CargaDatos.h"
#include "Jugar.h"

//cabecera: configuracion()
//precondicion:
//postcondicion: devuelve la configuracion general del juego

void configuracion(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){

    int c;
    srand(time(NULL));
    do{
        printf("---------- Configuracion ----------\n\n");
        printf("    1. Introducir Datos\n");
        printf("    2. Mostrar\n");
        printf("    3. Borrar\n");
        printf("    4. Guardar\n");
        printf("    5. Cargar\n");
        printf("    6. Volver\n\n");
        printf("    -> ");
        scanf("%i",&c);
        fflush(stdin);
        system("cls");
        switch(c){
            case 1:
                introducir_datos(jugadores, config, barcos);
                break;
            case 2:
                mostrar(jugadores, config, barcos);
                break;
            case 3:
                borrar_configuracion(jugadores, config);
                break;
            case 4:
                guardar(jugadores,2,config,barcos);
                break;
            case 5:
                cargaJuego(jugadores,config);
                break;
            case 6:
                break;
            default:
                system("cls");
                printf("Opcion no valida...\n");
                printf("Por favor introduzca una opcion valida...\n\n");
                break;
        }
    }while(c!=6);
}

//cabecera: void introducir_datos(Jugador* jugadores)
//precondicion:
//postcondicion: devuelve todos los elementos configurables del juego previos a comenzar la partida

void introducir_datos(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){

    int j;
    printf("Introduce el nombre del jugador_1: ");
    fgets(jugadores[0].Nomb_jugador,20,stdin);
    quitar_salto_linea(jugadores[0].Nomb_jugador);
    fflush(stdin);
    system("cls");
    do{
        printf("Elija el tipo de disparo:\n");
        printf("    1. Pulsa 'a' para hacer un disparo automatico\n");
        printf("    2. Pulsa 'm' para hacer un disparo manual\n\n");
        printf("    -> ");
        scanf("%c", &jugadores[0].Tipo_disparo);
        fflush(stdin);
        system("cls");
        if(jugadores[0].Tipo_disparo!='a' && jugadores[0].Tipo_disparo!='m'){
            printf("Opcion no valida...\n");
            printf("Por favor introduzca una opcion valida...\n\n");
        }
    }while(jugadores[0].Tipo_disparo!='a' && jugadores[0].Tipo_disparo!='m');
    jugadores[0].Id_jugador=1;
    system("cls");
    printf("Introduce el nombre del jugador_2: ");
    fgets(jugadores[1].Nomb_jugador,20,stdin);
    quitar_salto_linea(jugadores[1].Nomb_jugador);
    fflush(stdin);
    system("cls");
    do{
        printf("Elija el tipo de disparo:\n");
        printf("    1. Pulsa 'a' para hacer un disparo automatico\n");
        printf("    2. Pulsa 'm' para hacer un disparo manual\n\n");
        printf("    -> ");
        scanf("%c", &jugadores[1].Tipo_disparo);
        fflush(stdin);
        system("cls");
        if(jugadores[1].Tipo_disparo!='a' && jugadores[1].Tipo_disparo!='m'){
            printf("Opcion no valida...\n");
            printf("Por favor introduzca una opcion valida...\n\n");
        }
    }while(jugadores[1].Tipo_disparo!='a' && jugadores[1].Tipo_disparo!='m');
    jugadores[1].Id_jugador=2;
    system("cls");

    tipo_barcos_a_utilizar(jugadores,config,barcos);

    system("cls");
    do{
        printf("Que jugador comenzara la partida:\n");
        printf("    1. Pulsa '1' para que comience el jugador 1.\n");
        printf("    2. Pulsa '2' para que comience el jugador 2.\n");
        printf("    3. Pulsa '3' para que decida el sistema.\n\n");
        printf("    -> ");
        scanf("%i", &j);
        fflush(stdin);
        if(j==3){
            while(j==3 || j==0){
                j=generar_n_aleatorio()%3;
            }
        }
        system("cls");
        if(j!=1 && j!=2 && j!=3){
            printf("Opcion no valida...\n");
            printf("Por favor introduzca una opcion valida...\n\n");
        }
    }while(j!=1 && j!=2 && j!=3);
    config->comienzo=j;
    system("cls");
    do{
        printf("Cual sera la longitud del tablero:\n");
        printf("    -> ");
        scanf("%i", &config->t_tablero);
        fflush(stdin);
        system("cls");
        if(config->t_tablero<10){
            printf("Opcion no valida...\n");
            printf("El tablero debe tener una longitud de al menos 10x10 casillas.\n");
            printf("Por favor introduzca una opcion valida...\n\n");
        }
        if(config->t_tablero>20){
            printf("Opcion no valida...\n");
            printf("La longitud maxima de tablero es 20x20 casillas.\n");
            printf("Por favor introduzca una opcion valida...\n\n");
        }
    }while(config->t_tablero<10 || config->t_tablero>20);
    inicializar_tablero(jugadores,config);
}

//cabecera: int generar_n_aleatorio();
//precondicion:
//postcondicion: devuelve un numero aleatorio entre 0 y 9

int generar_n_aleatorio(){

    int n_aleatorio;
    n_aleatorio=rand()%10;

    return n_aleatorio;
}

//cabecera: void mostrar()
//precondicion:
//postcondicion: devuelve un resumen de la configuracion actual

void mostrar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){

    int salir;
    int primero;
    int i;
    system("cls");
    printf("Resumen de la configuracion:\n\n");
    printf("    - Jugador 1: ");
    printf("%s", jugadores[0].Nomb_jugador);
    if(jugadores[0].Tipo_disparo=='a') printf(" Disparo Automatico");
    if(jugadores[0].Tipo_disparo=='m') printf(" Disparo Manual");
    printf("\n");
    printf("    - Jugador 2: ");
    printf("%s", jugadores[1].Nomb_jugador);
    if(jugadores[1].Tipo_disparo=='a') printf(" Disparo Automatico");
    if(jugadores[1].Tipo_disparo=='m') printf(" Disparo Manual");
    printf("\n");
    printf("    - Se han escogido para la partida los siguientes barcos:\n");
    for(i=0;i<cargaBarcos(&barcos)-2;i++){
        if(config->c_barco[i]!=0) printf("        - %i %s\n", config->c_barco[i], barcos[i].Nomb_barco);
    }
    printf("    - La longitud del tablero es %i x %i.\n", config->t_tablero, config->t_tablero);
    if(config->comienzo==0 || config->comienzo==1){
        primero=0;
    }else primero=1;
    printf("    - El primer turno es para el jugador %s\n", jugadores[primero].Nomb_jugador);
    printf("\n\n");
    printf("Pulse cualquier tecla para continuar:\n");
    printf("    -> ");
    scanf("%i", &salir);
    fflush(stdin);
    system("cls");
}

//cabecera: void quitar_salto_linea(char* cadena)
//precondicion: inicializar con fgets() una cadena de caracteres
//postcondicion: quita el \n del final de la cadena de caracteres

void quitar_salto_linea(char* cadena){

    int longitud;
    longitud=strlen(cadena);
    longitud--;
    cadena[longitud]='\0';
    printf("%s", cadena);
}

//cabecera: void borrar_configuracion(Jugador* jugadores, registro_configuracion* config)
//precondicion: inicializar las estructuras jugadores y config
//postcondicion: borra toda la configuración que hayamos introducido

void borrar_configuracion(Jugador* jugadores, registro_configuracion* config){

    char cadena_borrador[1]="\0";
    char caracter_borrador='\0';
    int entero_borrador=0;
    strcpy(jugadores[0].Nomb_jugador, cadena_borrador);
    strcpy(jugadores[1].Nomb_jugador, cadena_borrador);
    jugadores[0].Tipo_disparo=caracter_borrador;
    jugadores[1].Tipo_disparo=caracter_borrador;
    config->t_tablero=entero_borrador;
    jugadores[0].Id_jugador=entero_borrador;
    jugadores[1].Id_jugador=entero_borrador;
    jugadores[0].Ganador=entero_borrador;
    jugadores[1].Ganador=entero_borrador;
    jugadores[0].Num_disp=entero_borrador;
    jugadores[1].Num_disp=entero_borrador;
    config->n_barcos_flota=0;
    config->n_tipos_barco=0;
    jugadores[0].barcos_hundidos=entero_borrador;
    jugadores[1].barcos_hundidos=entero_borrador;
    jugadores[0].restan=0;
    jugadores[0].vacias=0;
    jugadores[0].aguas=0;
    jugadores[0].tocadas=0;
    jugadores[0].hundidas=0;
    jugadores[1].restan=0;
    jugadores[1].vacias=0;
    jugadores[1].aguas=0;
    jugadores[1].tocadas=0;
    jugadores[1].hundidas=0;

    config->c_barco=(int*)calloc(1,sizeof(int));

}

//cabecera: void tipo_barcos_a_utilizar()
//precondicion: inicializar la estructura barcos
//postcondicion: devuelve los tipos de barcos que utilizaran los jugadores

void tipo_barcos_a_utilizar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){

    int c, salida=0, i, num_barcos=cargaBarcos(&barcos)-2, control=0;
    do{
        for(i=0;i<num_barcos;i++){
            printf("Seleccione la cantidad de barcos que desea utilizar:\n\n");
            printf("    - %s.\n", barcos[i].Nomb_barco);
            printf("    -> ");
            scanf("%i", &c);
            fflush(stdin);
            if(c<0){
                printf("Numero de barcos no valido...\n");
                printf("Por favor introduzca un numero de barcos valido.\n");
            }else{
                if(c!=0){
                    config->n_tipos_barco++;
                    config->n_barcos_flota=config->n_barcos_flota+c;
                    control=1;
                }
                config->c_barco=realloc(config->c_barco, (i+1)*sizeof(int));
                config->c_barco[i]=c;
            }
            system("cls");
        }
        if(control==0){
            printf("Debe escoger al menos un barco antes de comenzar la partida...\n");
        }else salida=1;
    }while(salida!=1);
}
