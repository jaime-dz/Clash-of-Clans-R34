#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "configuracion.h"
#include "Estructuras.h"

//cabecera: configuracion()
//precondicion:
//postcondicion: devuelve la configuracion general del juego

void configuracion(Jugador* jugadores, registro_configuracion* config){

    int c;
    srand(time(NULL));
    do{
        printf("---------- Configuracion ----------\n\n");
        printf("1. Introducir Datos\n");
        printf("2. Mostrar\n");
        printf("3. Borrar\n");
        printf("4. Guardar\n");
        printf("5. Cargar\n");
        printf("6. Volver\n\n");
        printf("    -> ");
        scanf("%i",&c);
        fflush(stdin);
        system("cls");
        switch(c){
            case 1:
                introducir_datos(jugadores, config);
                break;
            case 2:
                mostrar(jugadores, config);
                break;
            case 3:
                borrar_configuracion(jugadores, config);
                break;
            case 4:
                escribir_jugador(jugadores,2,10,config); // Falta la funcion de guardar las matrices y los barcos de los jugadores
                break;
            case 5:
                // Falta la funcion de cargar partida;
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

void introducir_datos(Jugador* jugadores, registro_configuracion* config){

    int j;
    printf("Introduce el nombre del jugador_1: ");
    fgets(jugadores[0].Nomb_jugador,20,stdin);
    quitar_salto_linea(jugadores[0].Nomb_jugador);
    jugadores[0].Ganador=0;
    jugadores[1].Ganador=0;
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
    tipo_barcos_a_utilizar(jugadores,config);
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

void mostrar(Jugador* jugadores, registro_configuracion* config){

    int salir;
    int primero;
    system("cls");
    printf("Resumen de la configuarion:\n\n");
    printf("    - Jugador 1: ");
    printf("%i", jugadores[0].Id_jugador);
    printf(" ");
    printf("%s", jugadores[0].Nomb_jugador);
    if(jugadores[0].Tipo_disparo=='a') printf(" Disparo Automatico");
    if(jugadores[0].Tipo_disparo=='m') printf(" Disparo Manual");
    printf("\n");
    printf("    - Jugador 2: ");
    printf("%i", jugadores[1].Id_jugador);
    printf(" ");
    printf("%s", jugadores[1].Nomb_jugador);
    if(jugadores[1].Tipo_disparo=='a') printf(" Disparo Automatico");
    if(jugadores[1].Tipo_disparo=='m') printf(" Disparo Manual");
    printf("\n");
    // Cambios a la hora de contar barcos
    printf("    - Se han escogido para la partida:\n");
    printf("        - %i Portaaviones.\n", config->P);
    printf("        - %i Acorazados.\n", config->A);
    printf("        - %i Cruceros.\n", config->C);
    printf("        - %i Destructores.\n", config->D);
    printf("        - %i Fragatas.\n", config->F);
    printf("        - %i Submarinos.\n", config[0].S);
    printf("    - El tamaño del tablero es %i x %i\n", config->t_tablero, config->t_tablero);
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
    // Cambios a la hora de contar barcos
    config->P=0;
    config->A=0;
    config->C=0;
    config->D=0;
    config->F=0;
    config->S=0;

}

//cabecera: void guardar(Jugador* jugadores, registro_configuracion* config)
//precondicion: inicializar las estructuras jugadores y config
//postcondicion: escribe en un fichero los datos de configuracion de los jugadores

void guardar(Jugador* jugadores, registro_configuracion* config){

    escribir_jugador(jugadores, 2, 10, config);

}

//cabecera: void tipo_barcos_a_utilizar()
//precondicion: inicializar la estructura barcos
//postcondicion: devuelve los tipos de barcos que utilizaran los jugadores

void tipo_barcos_a_utilizar(Jugador* jugadores, registro_configuracion* config){

    int c, salida=0;

    config->id_barco=(char*)malloc(1*sizeof(char));
    if(config->id_barco==NULL){
        printf("No se ha podido reservar memoria...\n");
    }
    do{
    printf("Que tipo de barcos se van a utilizar en la partida.\n");
    printf("Pulse el numero asociado al barco:\n");
    printf("    1. Portaaviones (6 casillas).\n");
    printf("    2. Acorazado (5 casillas).\n");
    printf("    3. Crucero (4 casillas).\n");
    printf("    4. Destructor (3 casillas).\n");
    printf("    5. Fragata (2 casillas).\n");
    printf("    6. Submarino (1 casilla).\n\n");
    printf("    Pulsa 7 para continuar si ya ha elegido sus barcos.\n");
    printf("    -> ");
    scanf("%i", &c);
    fflush(stdin);

    // Cambios a la hora de contar barcos
        switch(c){
            case 1:
                system("cls");

                config->c_barco=realloc(config->c_barco,1*sizeof(int));
                if(config->c_barco==NULL){
                    printf("No se ha podido reservar memoria...\n");
                }

                config->P++;
                if(config->P>=1) config->n_barcos_flota++;
                if(config->P==1) config->n_tipos_barco++;
                break;
            case 2:
                system("cls");
                config->A++;
                if(config->A>=1) config->n_barcos_flota++;
                if(config->A==1) config->n_tipos_barco++;
                break;
            case 3:
                system("cls");
                config->C++;
                if(config->C>=1) config->n_barcos_flota++;
                if(config->C==1) config->n_tipos_barco++;
                break;
            case 4:
                system("cls");
                config->D++;
                if(config->D>=1) config->n_barcos_flota++;
                if(config->D==1) config->n_tipos_barco++;
                break;
            case 5:
                system("cls");
                config->F++;
                if(config->F>=1) config->n_barcos_flota++;
                if(config->F==1) config->n_tipos_barco++;
                break;
            case 6:
                system("cls");
                config->S++;
                if(config->S>=1) config->n_barcos_flota++;
                if(config->S==1) config->n_tipos_barco++;
                break;
            case 7:
                if(config->P<1 || config->A<1 || config->C<1 || config->D<1 || config->F<1 || config->S<1){
                    system("cls");
                    printf("Debe introducir al menos un barco para comenzar la partida...\n");
                }
                if(config->P>=1 || config->A>=1 || config->C>=1 || config->D>=1 || config->F>=1 || config->S>=1) salida=1;
                break;
            default:
                system("cls");
                printf("Opcion no valida...\n");
                printf("Por favor introduzca una opcion valida...\n\n");
                break;
        }
    }while(salida!=1);
}
