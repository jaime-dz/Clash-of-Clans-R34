#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugar.h"
#include "Estructuras.h"
/*#include "cargar.h"
#include "configuracion.h"
#include "guardar.h"*/
void Menu_Jugar(Jugador *);
void inicializar_matriz(char **,int );
void Libera_Memoria(char ***,int );
void Reserva_Memoria(char ***,int );
void imprimir_matriz(char **,int );
void Resumen(Jugador *,int);
void Jugar_Partida(Jugador *,int );
void Reiniciar_Partida(Jugador *,int );
void Contadores_Resumen(Jugador *,int ,int *,int *,int *, int *,int *, int *);
int main(){
    int i;
    Jugador j[N_JUG];
    for(i=0;i<N_JUG;i++){
        Reserva_Memoria(&(j[i].Flota),10);
        Reserva_Memoria(&(j[i].Oponente),10);
    }
    for(i=0;i<N_JUG;i++){
        inicializar_matriz(j[i].Flota,10);
        inicializar_matriz(j[i].Oponente,10);
    }
    Menu_Jugar(j);

    for(i=0;i<N_JUG;i++){
        Libera_Memoria(&(j[i].Flota),10);
        Libera_Memoria(&(j[i].Oponente),10);
    }
    
    system("cls");
    return 0;
}
//Cabecera: void Menu_Jugar(Jugador *j);
//Precondicion: recibe el vector de estructura con los datos de los jugadores
//Postcondicion: imprime el menu de Jugar y realiza la acción necesaria segun la opcion del usuario
void Menu_Jugar(Jugador *j){
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
        switch(opc_menu){
            case 1:
                Jugar_Partida(j,10);
                break;
            case 2:
                Reiniciar_Partida(j,10);
                break;
            case 3:
                Resumen(j,10);
                break;
            case 4:
                break;
            default:
                system("cls");
                printf("Opcion no valida\n\n");
                break;
        }
    }while(opc_menu!=4);
}
//Cabecera: void Contadores_Resumen(Jugador *j,int dim,int *nvac,int *nag,int *ntoc, int *nhuna,int *nhuno, int *nrest);
//Precondicion: Recibe el vector de estructuras, la dimensión de las matrices y vectores por referencia para los contadores del nº de aguas, casillas tocadas, hundidas, vacías y el nº de barcos hundidos y restantes
//Postcondicion: Devuelve por referencia el nº de casillas vacías, tocadas, hundidas, aguas, barcos hundidos y no hundidos
void Contadores_Resumen(Jugador *j,int dim,int *nvac,int *nag,int *ntoc, int *nhuna,int *nhuno, int *nrest){
    int i,l,m;
    for(m=0;m<N_JUG;m++){
        for(i=0;i<dim;i++){
            for(l=0;l<dim;l++){
                switch(j[m].Oponente[i][l]){
                    case '*':
                        nag[m]++;
                        break;
                    case '-':
                        nvac[m]++;
                        break;
                    case 't':
                        ntoc[m]++;
                        break;
                    case 'h':
                        nhuna[m]++;
                        break;
                }
                switch(j[m].Flota[i][l]){
                    case 'x':
                        nrest[m]++;
                }
                
            }
        }
    }
    
    
}
//Cabecera: void Resumen(Jugador *j,int dim);
//Precondicion: recibe el vector de estructuras con los datos de cada jugador y sus tableros
//Postcondicion: muestra por pantalla el resumen de la partida al acabar esta
void Resumen(Jugador *j,int dim){
    int i,m,n,cont=1;
    int nvac[2]={0,0},nag[2]={0,0},ntoc[2]={0,0},nhuna[2]={0,0},nhuno[2]={0,0},nrest[2]={0,0};
    Contadores_Resumen(j,10,nvac,nag,ntoc,nhuno,nhuna,nrest);
    printf("           |          Valor de las casillas      |         Barcos        |\n");
    printf("Jugador    |Disparos|Vacias|Agua|Tocadas|Hundidas|Hundidos|Restan|Ganador|\n");
    printf("-----------|--------|------|----|-------|--------|--------|------|-------|\n");
    printf("%s   |      %d|    %d|  %d|     %d|      %d|      %d|    %d|     %d|\n",j[0].Nomb_jugador,j[0].Num_disp,nvac[0],nag[0],ntoc[0],nhuna[0],nhuno,j[0].Ganador);
    printf("%s   |      %d|    %d|  %d|     %d|      %d|      %d|    %d|     %d|\n",j[1].Nomb_jugador,j[1].Num_disp,nvac[1],nag[1],ntoc[1],nhuna[1],nhuno[1],j[1].Ganador);
    printf("\n\n");
    for(i=0;i<N_JUG;i++){
        printf("Jugador %d:     FLOTA                               OPONENTE\n",i+1);
        printf("   |");
        for (n = 0; n < dim; n++) printf("%2d|", n);
        printf("     |");
        for (n = 0; n < dim; n++) printf("%2d|", n);
        printf("\n");

        // Línea divisoria
        printf("---+");
        for (n = 0; n < dim; n++) printf("--+");
        printf("     +");
        for (n = 0; n < dim; n++) printf("--+");
        printf("\n");
        for(m=0;m<dim;m++){
            printf("%2d|", m);
            for(n=0;n<dim;n++){
                printf(" %c|",j[i].Flota[m][n]);
            }
            printf("   |");
            printf("%2d|", m);
            for(n=0;n<dim;n++){
                printf(" %c|",j[i].Oponente[m][n]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
    system("pause");
    system("cls");
}
//Cabecera: void Reiniciar_Partida(Jugador *j,int dim);
//Precondicion: recibe el vector de estructuras con los datos de ambos jugadores y la dimension de los tableros
//Postcondicion: elimina el nº de disparos, si es ganador o no y resetea los tableros de cada jugador
void Reiniciar_Partida(Jugador *j,int dim){
    int i,p,u;
    for(i=0;i<N_JUG;i++){
        j[i].Num_disp=0;
        j[i].Ganador=0;
        for(p=0;p<dim;p++){
            for(u=0;u<dim;u++){
                j[i].Flota[p][u]='-';
                j[i].Oponente[p][u]='-';
            }
        }
    }
}
//Cabecera:
//Precondicion:
//Postcondicion:
void Jugar_Partida(Jugador *j,int dim){
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
            break;
        case 'a':
        case 'A':
            break;
        default:
            printf("No es una opcion valida\n\n");
            break;
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
//Precondicion: recibe una matriz dinamica reservada y su dimension
//Postcondicion: libera su memoria asignada
void Libera_Memoria(char ***m,int dim){
    int i;
    for(i=0;i<dim;i++){
        free((*m)[i]);
    }
    free(*m);
    *m=NULL;
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
//Cabecera:void inicializar_matriz(char **,int );
//Precondicion: recibe una matriz cuadrada dinamica sin inicializar y su dimensión
//Postcondicion:inicializa las matrices a sus valores nulos antes de colocar los barcos
void inicializar_matriz(char **m,int dim){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            m[i][j]='-';
        }
    }
}