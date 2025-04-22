#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jugar.h"
#include "Estructuras.h"
#include "configuracion.h"
void Jugar(Jugador* , registro_configuracion* , Barcos* );
void Liberar_Memoria(char ***, int );
void Reserva_Memoria(char ***,int );
void imprimir_matriz(char **,int );
void elimina(char *);
void inicializar_tablero(Jugador* , registro_configuracion* );
void generar_matriz_dinamica(char*** , int );
void Resumen(Jugador* , registro_configuracion* );
void jugar_partida(Jugador* , registro_configuracion* );
void reiniciar_partida(Jugador *,registro_configuracion *);
void Contadores_Resumen(Jugador* ,registro_configuracion* );
void mostrar_tablero(char **, int );
void colocacion_barcos(Jugador* , registro_configuracion* , Barcos* );
void colocar_barcos(Jugador *, registro_configuracion *, Barcos *);
int posicion_valida(char **, int , int , int , int , int );

//Cabecera: void Jugar(Jugador* jugadores, registro_configuracion* config);
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: menu previo al comienzo de la partida
void Jugar(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){
    int c;
    do{
        printf("---------- Jugar Partida ----------\n\n");
        printf("    1. Colocar Barcos\n");
        printf("    2. Jugar Partida\n");
        printf("    3. Reiniciar partida\n");
        printf("    4. Resumen\n");
        printf("    5. Volver\n\n");
        printf("    -> ");
        scanf("%i",&c);
        fflush(stdin);
        system("cls");
        switch(c){
            case 1:
                colocacion_barcos(jugadores,config,barcos);
                break;
            case 2:
                jugar_partida(jugadores,config);
                break;
            case 3:
                reiniciar_partida(jugadores,config);
                break;
            case 4:
                Resumen(jugadores, config);
                break;
            case 5:
                break;
            default:
                system("cls");
                printf("Opcion no valida...\n");
                printf("Por favor introduzca una opcion valida...\n\n");
                break;
        }
    }while(c!=4);
}
//Cabecera: void colocacion_barcos(Jugador* jugadores, registro_configuracion* config, Barcos* barcos)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion:
void colocacion_barcos(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){
    char c;
    do{
        printf("Desea generar los tableros de forma manual o de forma aleatoria:\n");
        printf("    - Pulse 'm' si desea construirlos de forma manual.\n");
        printf("    - Pulse 'a' si desea construirlos de forma aleatoria.\n\n");
        printf("    -> ");
        scanf(" %c",&c);
        if(c!='a' && c!='m'){
            system("cls");
            printf("Opcion no valida...\n");
            printf("Por favor introduzca una opcion valida...\n\n");
        }
    }while(c!='a' && c!='m');
    system("cls");
    switch(c){
        case 'm':
            system("cls");
            printf("Ha seleccionado generar los tableros de forma manual.\n\n");
            colocar_barcos(jugadores,config,barcos);
            system("cls");
            break;
        case 'a':
            system("cls");
            printf("Esta opcion no esta disponible temporalmente.\n\n");
            break;
    }
}
//Cabecera: void jugar_partida(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: menu para jugar la partida
void jugar_partida(Jugador* jugadores, registro_configuracion* config){

    int turno;
    system("cls");
    if(config->comienzo==1){
        printf("El primer turno es para %s.\n\n", jugadores[0].Nomb_jugador);
        turno=config->comienzo;
    }else{
        printf("El primer turno es para %s.\n", jugadores[1].Nomb_jugador);
        turno=config->comienzo;
    }
    while(jugadores[0].Ganador!=1 && jugadores[1].Ganador!=1){
        if(turno==1){
            mostrar_tablero(jugadores[0].Flota, config->t_tablero);
            if(jugadores[0].Tipo_disparo=='a') disparo_automatico(jugadores,*config,config->t_tablero);
            if(jugadores[0].Tipo_disparo=='m') disparo_manual(jugadores,*config,config->t_tablero);
            turno=2;
            if(jugadores[0].barcos_hundidos==config->n_barcos_flota) jugadores[0].Ganador=1;
        }
        if(turno==2){
            mostrar_tablero(jugadores[0].Flota, config->t_tablero);
            if(jugadores[1].Tipo_disparo=='a') disparo_automatico(jugadores,*config,config->t_tablero);
            if(jugadores[1].Tipo_disparo=='m') disparo_manual(jugadores,*config,config->t_tablero);
            turno=1;
            if(jugadores[1].barcos_hundidos==config->n_barcos_flota) jugadores[0].Ganador=1;
        }
    }
}
//Cabecera: void colocar_barcos(Jugador *jugadores, registro_configuracion *config, Barcos *barcos);
//Precondicion: recibe el numero de barcos de cada tipo y el tablero de cada jugador
//Postcondicion: coloca los barcos en el tablero de cada jugador
void colocar_barcos(Jugador *jugadores, registro_configuracion *config, Barcos *barcos){
    int jugador_actual, tipo, cantidad, orientacion, fila, col;
    int i, f, c, colocado;
    int df[] = {1, 0, 1, 1};     // desplazamientos fila: vertical, horizontal, diagonal izq, diagonal der
    int dc[] = {0, 1, -1, 1};    // desplazamientos columna

    for(jugador_actual = 0; jugador_actual < 2; jugador_actual++) {
        printf("\nTurno del jugador %s\n", jugadores[jugador_actual].Nomb_jugador);
        for (tipo = 0; tipo < config->n_tipos_barco; tipo++) {
            for (cantidad = 0; cantidad < config->c_barco[tipo]; cantidad++) {
                colocado = 0;
                while (!colocado) {
                    printf("\nColocando barco '%s' de tamanyo %d (Barco %d de %d)\n", 
                        barcos[tipo].Nomb_barco, barcos[tipo].Tam_barco, 
                        cantidad + 1, config->c_barco[tipo]);

                    mostrar_tablero(jugadores[jugador_actual].Flota, config->t_tablero);
                    // Pedir orientación
                    do {
                        printf("Elige orientacion:\n");
                        printf("  1. Vertical\n");
                        printf("  2. Horizontal\n");
                        printf("  3. Diagonal izquierda (↙)\n");
                        printf("  4. Diagonal derecha (↘)\n");
                        printf("-> ");
                        scanf("%d", &orientacion);
                        orientacion--;
                    } while (orientacion < 0 || orientacion > 3);
                    // Pedir coordenadas
                    printf("Fila inicial: ");
                    scanf("%d", &fila);
                    printf("Columna inicial: ");
                    scanf("%d", &col);
                    if (posicion_valida(jugadores[jugador_actual].Flota, fila, col, barcos[tipo].Tam_barco, orientacion, config->t_tablero)) {
                        // Colocar barco
                        for (i = 0; i < barcos[tipo].Tam_barco; i++) {
                            f = fila + i * df[orientacion];
                            c = col + i * dc[orientacion];
                            jugadores[jugador_actual].Flota[f][c] = '*';
                        }
                        printf("Barco colocado correctamente.\n");
                        colocado = 1;
                    } else {
                        printf("No se puede colocar el barco ahi. Intenta otra posicion.\n");
                    }
                }
            }
        }
        printf("\nTablero final del jugador %s:\n", jugadores[jugador_actual].Nomb_jugador);
        mostrar_tablero(jugadores[jugador_actual].Flota, config->t_tablero);
        system("cls");
    }
}
//Cabecera: void mostrar_tablero(char **tablero, int t_tablero);
//Precondicion: recibe una matriz de caracteres inicializada y su dimensión
//Postcondicion: muestra el tablero por pantalla
void mostrar_tablero(char **tablero, int t_tablero) {
    int i,l;
    printf("    ");
    for (i = 0; i < t_tablero; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (i = 0; i < t_tablero; i++) {
        printf("%2d |", i);
        for (l = 0; l < t_tablero; l++) {
            printf(" %c ", tablero[i][l]);
        }
        printf("\n");
    }
}
//Cabecera: int posicion_valida(char **matriz, int fila, int col, int tam, int orientacion, int dim);
//Precondicion: recibe el tablero, las coordenadas, el tamañom del barco, la orientacion y la dimension del tablero
//Postcondicion: Comprueba si se puede colocar el barco en la posición introducida por el usuario
int posicion_valida(char **matriz, int fila, int col, int tam, int orientacion, int dim){
    int df[] = {1, 0, 1, 1};  // vertical, horizontal, diag izq, diag der
    int dc[] = {0, 1, -1, 1};
    int i,f,c,x,y,nf,nc;

    for (i = 0; i < tam; i++) {
        f = fila + i * df[orientacion];
        c = col + i * dc[orientacion];

        if (f < 0 || f >= dim || c < 0 || c >= dim)
            return 0;

        // Verifica la celda y alrededores
        for (x = -1; x <= 1; x++) {
            for (y = -1; y <= 1; y++) {
                nf = f + x;
                nc = c + y;
                if (nf >= 0 && nf < dim && nc >= 0 && nc < dim) {
                    if (matriz[nf][nc] == 'x')
                        return 0;
                }
            }
        }
    }

    return 1;
}
//Cabecera: void Contadores_Resumen(Jugador* jugadores,registro_configuracion* config);
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: devuelve el numero de casillas de cada tipo
void Contadores_Resumen(Jugador* jugadores,registro_configuracion* config){
    int i,l,m;
    for(m=0;m<2;m++){
        for(i=0;i<config->t_tablero;i++){
            for(l=0;l<config->t_tablero;l++){
                switch(jugadores[m].Oponente[i][l]){
                    case '*':
                        jugadores[m].aguas++;
                        break;
                    case '-':
                        jugadores[m].vacias++;
                        break;
                    case 't':
                        jugadores[m].tocadas++;
                        break;
                    case 'h':
                        jugadores[m].hundidas++;
                        break;
                }
            }
        }
    }
    for(i=0;i<2;i++){
        jugadores[i].restan=config->n_barcos_flota-jugadores[i].barcos_hundidos;
    }
}
//Cabecera: void Resumen(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: muestra por pantalla el resumen de la partida
void Resumen(Jugador* jugadores, registro_configuracion* config){
    int i, j, salir;
    //inicializar_tablero(jugadores,config);
    Contadores_Resumen(jugadores,config);
    printf("Resumen de la partida:\n\n");
    printf("    - Jugador 1: %s\n", jugadores[0].Nomb_jugador);
    printf("        - Valor de las casillas:\n");
    printf("            - Disparos -> %i\n", jugadores[0].Num_disp);
    printf("            - Vacias -> %i\n", jugadores[0].vacias);
    printf("            - Aguas -> %i\n", jugadores[0].aguas);
    printf("            - Tocadas -> %i\n", jugadores[0].tocadas);
    printf("            - Hundidas -> %i\n", jugadores[0].hundidas);
    printf("        - Barcos:\n");
    printf("            - Hundidos -> %i\n", jugadores[0].barcos_hundidos);
    printf("            - Restan -> %i\n", jugadores[0].restan);
    printf("            - Ganador -> %i\n", jugadores[0].Ganador);
    printf("\n");
    printf("        - FLOTA:\n");
    for(i=0;i<config->t_tablero;i++){
        printf("\n");
        for(j=0;j<config->t_tablero;j++){
            printf("[%c]", jugadores[0].Flota[i][j]);
        }
    }
    printf("\n\n");
    printf("        - OPONENTE:\n");
    for(i=0;i<config->t_tablero;i++){
        printf("\n");
        for(j=0;j<config->t_tablero;j++){
            printf("[%c]", jugadores[0].Oponente[i][j]);
        }
    }
    printf("\n\n");
    printf("    - Jugador 2: %s\n", jugadores[1].Nomb_jugador);
    printf("        - Valor de las casillas:\n");
    printf("            - Disparos -> %i\n", jugadores[1].Num_disp);
    printf("            - Vacias -> %i\n", jugadores[1].vacias);
    printf("            - Aguas -> %i\n", jugadores[1].aguas);
    printf("            - Tocadas -> %i\n", jugadores[1].tocadas);
    printf("            - Hundidas -> %i\n", jugadores[1].hundidas);
    printf("        - Barcos:\n");
    printf("            - Hundidos -> %i\n", jugadores[1].barcos_hundidos);
    printf("            - Restan -> %i\n", jugadores[1].restan);
    printf("            - Ganador -> %i\n", jugadores[1].Ganador);
    printf("\n");
    printf("        - FLOTA:\n");
    for(i=0;i<config->t_tablero;i++){
        printf("\n");
        for(j=0;j<config->t_tablero;j++){
            printf("[%c]", jugadores[1].Flota[i][j]);
        }
    }
    printf("\n\n");
    printf("        - OPONENTE:\n");
    for(i=0;i<config->t_tablero;i++){
        printf("\n");
        for(j=0;j<config->t_tablero;j++){
            printf("[%c]", jugadores[1].Oponente[i][j]);
        }
    }
    printf("\n\n");
    printf("Pulse cualquier tecla para continuar:\n");
    printf("    -> ");
    scanf("%i", &salir);
    fflush(stdin);
    system("cls");
}
//Cabecera: void reiniciar_partida(Jugador *jugadores,registro_configuracion *config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: inicializa los valores de todas las variables incluidos los tableros
void reiniciar_partida(Jugador *jugadores,registro_configuracion *config){
    int i, j, k, aux;
    aux=config->t_tablero;
    borrar_configuracion(jugadores,config);
    config->t_tablero=aux;
    for(i=0;i<2;i++){
        for(j=0;j<config->t_tablero;j++){
            for(k=0;k<config->t_tablero;k++){
                jugadores[i].Flota[j][k]='-';
                jugadores[i].Oponente[j][k]='-';
            }

        }
    }
}
//Cabecera:void imprimir_matriz(char **m,int dim);
//Precondicion: recibe una matriz de caracteres inicializada y su dimensión
//Postcondicion: la imprime por pantalla
void imprimir_matriz(char **m,int dim){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            printf("%c",m[i][j]);
        }
        printf("\n");
    }
}
//Cabecera:void Libera_Memoria(char ***m,int dim);
//Precondicion: inicializar una matriz dinamica
//Postcondicion: libera su memoria asignada
void Liberar_Memoria(char ***matriz, int longitud){
    int i;
    for(i=0;i<longitud;i++){
        free((*matriz)[i]);
    }
    free(*matriz);
    *matriz=NULL;
}
//Cabecera:void Reserva_Memoria(char ***m,int dim);
//Precondicion:recibe una matriz dinamica sin reservar y su dimension
//Postcondicion:reserva memoria para la matriz
void Reserva_Memoria(char ***m,int dim){
    int i;
    *m=(char**)malloc(dim*sizeof(char*));
    if(*m==NULL){
        printf("Error, no se pudo asignar memoria para las filas\n");
        exit(1);
    }
    for(i=0;i<dim;i++){
        (*m)[i]=(char*)malloc(dim*sizeof(char));
        if((*m)[i]==NULL){
            printf("Error, no se ha podido asignar memoria\n");
            exit(1);
        }
    }
}
//Cabecera: void generar_matriz_dinamica(char*** matriz, int longitud)
//Precondicion: inicializar la longitud del tablero
//Postcondicion: genera una matriz dinamica sin inicializar
void generar_matriz_dinamica(char*** matriz, int longitud){
    int i;
    *matriz=(char**)malloc(longitud*sizeof(char*));
    if(*matriz==NULL){
        printf("Se ha producido un error...\n");
        exit(1);
    }
    for(i=0;i<longitud;i++){
        (*matriz)[i]=(char*)malloc(longitud*sizeof(char));
        if((*matriz)[i]==NULL){
            printf("Se ha producido un error...\n");
            exit(1);
        }
    }
}
//Cabecera: void inicializar_tablero(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: inicializa los tableros de juego de ambos jugadores
void inicializar_tablero(Jugador* jugadores, registro_configuracion* config){
    int i, j, k;
    for(i=0;i<2;i++){
        generar_matriz_dinamica(&jugadores[i].Flota,config->t_tablero);
        generar_matriz_dinamica(&jugadores[i].Oponente,config->t_tablero);
    }
    for(i=0;i<2;i++){
        for(j=0;j<config->t_tablero;j++){
            for(k=0;k<config->t_tablero;k++){
                jugadores[i].Flota[j][k]='-';
                jugadores[i].Oponente[j][k]='-';
            }
        }
    }
}
//Cabecera:void elimina(char *c1);
//Precondicion: recibe una cadena de caracteres inicializada
//Postcondicion: elimina el salto de línea de la cadena introducido por fgets
void elimina(char *c1){
    int i=0;
    while(c1[i]!='\0'){
        if(c1[i]=='\n'){
            c1[i]='\0';
        }
        i++;
    }
}