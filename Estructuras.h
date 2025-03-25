#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H 
#define N_JUG 2

typedef struct {
    int Id_jugador;
    char Nomb_jugador [20]; 
    char Tipo_disparo;
    int Num_disp;
    int Ganador; 
    char **Flota; 
    char **Oponente;  //oponente [][]
} Jugador;

typedef struct  
{
    char Nomb_barco [20];
    char Id_barco[5]; 
    int Tam_barco; 
} Barcos;

//Cabecera: void introducir_barco (Barcos *bar)
//Preconcidion: Recibe la estructura Barcos
//Postcondicion: Introduce a la estructura Barcos un nuevo tipo de barco 
void introducir_barco (Barcos *bar);

//Cabecera: void escribir_barco (Barcos *bar)
//Precondicion: Recibe la estructura barcos ya inicializada
//Postcondicion: Escribe en el fichero barcos.txt
void escribir_barco (Barcos *bar); 


#endif