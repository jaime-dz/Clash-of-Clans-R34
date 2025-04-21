#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jugar.h"
#include "Estructuras.h"
#include "configuracion.h"
void Jugar(Jugador *,registro_configuracion *);
void Liberar_Memoria(char ***, int );
void Reserva_Memoria(char ***,int );
void imprimir_matriz(char **,int );
void elimina(char *);
void inicializar_tablero(Jugador* , registro_configuracion* );
void generar_matriz_dinamica(char*** , int );
void Resumen(Jugador* , registro_configuracion* );
void Jugar_Partida(Jugador* , registro_configuracion* , Barcos* );
void reiniciar_partida(Jugador *,registro_configuracion *);
void Contadores_Resumen(Jugador* ,registro_configuracion* );
void mostrar_tablero(char **tablero, int t_tablero);
void colocar_barcos(Jugador *, registro_configuracion *, Barcos *);
int posicion_valida(char **matriz, int fila, int col, int tam, int orientacion, int dim);

//Cabecera: void Jugar(Jugador* jugadores, registro_configuracion* config);
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: menu previo al comienzo de la partida
void Jugar(Jugador *j,registro_configuracion *reg){
    int opc_menu;
    do{
        printf("-----Jugar partida-----\n\n");
        printf("1.Jugar partida\n");
        printf("2.Reiniciar partida\n");
        printf("3.Resumen\n");
        printf("4.Volver\n");
        printf("->");
        scanf("%d",&opc_menu);
        fflush(stdin);
        system("cls");
        switch(opc_menu){
            case 1:
                Jugar_Partida(jugadores,config,barcos);
                break;
            case 2:
                Reiniciar_Partida(jugadores,config);
                break;
            case 3:
                Resumen(jugadores,config);
                break;
            case 4:
                break;
            default:
                system("cls");
                printf("Opcion no valida...\n\n");
                printf("Por favor introduzca una opcion valida...\n\n");
                break;
        }
    }while(opc_menu!=4);
}
//Cabecera: void Jugar_Partida(Jugador* jugadores, registro_configuracion* config)
//Precondicion: inicializar los valores de las estructuras jugadores y config
//Postcondicion: menu para jugar la partida
void Jugar_Partida(Jugador* jugadores, registro_configuracion* config, Barcos* barcos){//dim para probar
    int i,k,cont_p=1;
    char op_partida;
    printf("Desea generar los tableros manualmente o de forma aleatoria? (m/a)\n");
    printf("->");
    scanf(" %c",&op_partida);
    switch(op_partida){
        case 'm':
        case 'M':
            printf("Ha seleccionado generar los tableros manualmente\n\n");
            for(i=0;i<N_JUG;i++){
                inicializar_matriz(j[i].Flota,dim);
                inicializar_matriz(j[i].Oponente,dim);
            }
            for(i=0;i<N_JUG; i++){
                printf("Jugador %d - Tablero de Flota\n", i+1);
                imprimir_matriz(j[i].Flota, dim);
                printf("\n");
            
                printf("Jugador %d - Tablero de Oponente\n", i+1);
                imprimir_matriz(j[i].Oponente, dim);
                printf("\n\n");
            }
            printf("Pulse cualquier tecla para continuar:\n");
            printf("->\n\n");
            colocar_barcos(j,reg,b);
            break;
        case 'a':
        case 'A':
            printf("No implementado\n");
            break;
        default:
            printf("No es una opcion valida\n\n");
            break;
    }
   
}
//Cabecera:
//Precondicion: 
//Postcondicion: coloca los barcos en el tablero de cada jugador
void colocar_barcos(Jugador *j, registro_configuracion *r, Barcos *b){
    /*int i,l,orientacion,f,c;
    printf("Empieza el jugador %s\n",j[r->comienzo].Nomb_jugador);
    for(i=0;i<r->n_barcos_flota;i++){
        do{
            printf("Desea colocarlo de manera vertical, horizontal, diagonal izquierda o diagonal derecha?\n");
            printf("1. Vertical\n");
            printf("2. Horizontal\n");
            printf("3. Diagonal izquierda\n");
            printf("4. Diagonal derecha\n");
            printf("->");
            scanf("%d",&orientacion);
            fflush(stdin);
        }while(orientacion<1 || orientacion>4);

        printf("Introduzca la fila y la columna donde desea colocar el barco\n");
        printf("Fila: ");
        scanf("%d",&f);
        fflush(stdin);
        printf("Columna: ");
        scanf("%d",&c);
        fflush(stdin);
        switch(orientacion){
            case 1:
                if(f+r->c_barco[i]<r->t_tablero){
                    for(l=0;l<r->c_barco[i];l++){
                        if(j[r->comienzo].Flota[f+l][c]=='-'){
                            j[r->comienzo].Flota[f+l][c]='*';
                        }else{
                            printf("No se puede colocar el barco en esa posicion\n");
                            break;
                        }
                    }
                }else{
                    printf("No se puede colocar el barco en esa posicion\n");
                }
                break;
            case 2:
                if(c+r->c_barco[i]<r->t_tablero){
                    for(l=0;l<r->c_barco[i];l++){
                        if(j[r->comienzo].Flota[f][c+l]=='-'){
                            j[r->comienzo].Flota[f][c+l]='*';
                        }else{
                            printf("No se puede colocar el barco en esa posicion\n");
                            break;
                        }
                    }
                }else{
                    printf("No se puede colocar el barco en esa posicion\n");
                }
                break;
            case 3:
                if(f+r->c_barco[i]<r->t_tablero && c-r->c_barco[i]>0){
                    for(l=0;l<r->c_barco[i];l++){
                        if(j[r->comienzo].Flota[f+l][c-l]=='-'){
                            j[r->comienzo].Flota[f+l][c-l]='*';
                        }else{
                            printf("No se puede colocar el barco en esa posicion\n");
                            break;
                        }
                    }
                }else{
                    printf("No se puede colocar el barco en esa posicion\n");
                }
                break;
            case 4:
                if(f+r->c_barco[i]<r->t_tablero && c+r->c_barco[i]<r->t_tablero){
                    for(l=0;l<r->c_barco[i];l++){
                        if(j[r->comienzo].Flota[f+l][c+l]=='-'){
                            j[r->comienzo].Flota[f+l][c+l]='*';
                        }else{
                            printf("No se puede colocar el barco en esa posicion\n");
                            break;
                        }
                    }
                }else{
                    printf("No se puede colocar el barco en esa posicion\n");
                }
                break;
        }
        r->c_barco[i]--;
    }*/

    
    
    
    int jugador_actual = r->comienzo;
    int tipo,cantidad,orientacion,fila,col,i,f,c,colocado;
    for(jugador_actual=0;jugador_actual<N_JUG;jugador_actual++){
        printf("Comienza el jugador %s\n", j[jugador_actual].Nomb_jugador);
    
        for (tipo = 0; tipo < r->n_barcos_flota; tipo++) {
            for (cantidad = 0; cantidad < b[i].Tam_barco; cantidad++) {
                colocado = 0;
                while (!colocado) {
                    printf("\nColocando barco tipo %s (tamanyo: %d)\n", b[tipo].Nomb_barco, b[tipo].Tam_barco);
        
                    mostrar_tablero(j[jugador_actual].Flota, r->t_tablero);
        
                    do {
                        printf("Orientacion:\n");
                        printf("1. Vertical\n2. Horizontal\n3. Diagonal Izquierda\n4. Diagonal Derecha\n-> ");
                        scanf("%d", &orientacion);
                        orientacion--;  // de 0 a 3
                    } while (orientacion < 0 || orientacion > 3);
        
                    printf("Fila inicial: ");
                    scanf("%d", &fila);
                    printf("Columna inicial: ");
                    scanf("%d", &col);
        
                    if (posicion_valida(j[jugador_actual].Flota, fila, col, b[tipo].Tam_barco, orientacion, r->t_tablero)) {
                        for (i = 0; i < b[tipo].Tam_barco; i++) {
                            f = fila + i * (orientacion == 0 || orientacion == 2 || orientacion == 3);
                            c = col + i * (orientacion == 1 || orientacion == 3) - i * (orientacion == 2);
                            j[jugador_actual].Flota[f][c] = '*';
                        }
                        printf("Barco colocado correctamente.\n");
                        colocado = 1;
                    } else {
                        printf("No se puede colocar el barco ahí. Inténtalo de nuevo.\n");
                    }
                }
            }
        }
        
            // Mostramos tablero final
            printf("\nTablero final del jugador %s:\n", j[jugador_actual].Nomb_jugador);
            mostrar_tablero(j[jugador_actual].Flota, r->t_tablero);
    }
}
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
// Verifica si se puede colocar el barco en la posición deseada con separación
int posicion_valida(char **matriz, int fila, int col, int tam, int orientacion, int dim) {
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
                    if (matriz[nf][nc] == '*')
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
    inicializar_tablero(jugadores,config);
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