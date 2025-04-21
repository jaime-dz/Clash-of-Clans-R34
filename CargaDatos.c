#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Estructuras.h"
#define MAX_LINEA 500 //Numero maximo de caracteres de lectura

//Cabecera: int cargaBarcos(Barcos **barcos)
//Preconcidion:
//Postcondicion: carga en la estructura barcos los tipos de barcos y devuelve la cantidad de tipos de barcos
int cargaBarcos(Barcos **barcos) {
    char linea[MAX_LINEA];
    *barcos = NULL;
    int i = 0;
    char *token;
    // int cont = 0;

    FILE *fichero;
    if ((fichero = fopen("Barcos.txt", "r")) == NULL) {
        printf("Error al acceder al fichero.\n");
        exit(1);
    }

    while (fgets(linea, MAX_LINEA, fichero) != NULL) {
        // Reservar memoria de manera segura
        Barcos *temp = (Barcos*)realloc(*barcos, (i + 1) * sizeof(Barcos));
        if (temp == NULL) {
            printf("Error al reservar memoria.\n");
            exit(1);
        }
        *barcos = temp;

        // Procesar línea
        token = strtok(linea, "-");
        if (token) strcpy((*barcos)[i].Nomb_barco, token);

        token = strtok(NULL, "-");
        if (token) strcpy((*barcos)[i].Id_barco, token);

        token = strtok(NULL, "-");
        if (token) (*barcos)[i].Tam_barco = atoi(token);

        i++;
    }

    fclose(fichero);
    return i;  // Devuelve la cantidad de barcos leídos
}

// Cabecera:
// void cargaJuego(Jugador *, registro_configuracion *);

// Precondición:
// Los punteros 'jugador' y 'config' deben apuntar a estructuras válidas.
// El archivo "juego.txt" debe existir y tener el formato esperado:


// Postcondición:
// Se cargan los datos de configuración, los barcos disponibles, los datos de ambos jugadores
// y las matrices de flotas y oponentes en memoria dinámica asociada a los jugadores.
// Las matrices quedan listas para el uso en el juego.

void cargaJuego(Jugador *jugador,registro_configuracion *config) {  //cantidad barcos es temporal


    FILE *archivo = fopen("juego.txt", "r");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return;
    }

    char c;
    int dimension = 0,CantidadBarcos;
    char linea[128];

    // --------------------------------
    // LEER DATOS GENERALES
    // --------------------------------

    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        fprintf(stderr, "Error al leer datos del jugador\n");
        fclose(archivo);
        return;
    }

    // Quitar salto de línea
    linea[strcspn(linea, "\r\n")] = '\0';

    //Parsear campos
    char *token = strtok(linea, "-");
    if (token) config->t_tablero = atoi(token);

    token = strtok(NULL, "-");
    if (token) config->n_barcos_flota = atoi(token);

    token = strtok(NULL, "-");
    if (token) config->n_tipos_barco = atoi(token);





    // --------------------------------
    // LEER DATOS DE BARCOS
    // --------------------------------


    CantidadBarcos=config->n_tipos_barco;
    // config->id_barco = malloc(CantidadBarcos * sizeof(char));
    config->c_barco = malloc(CantidadBarcos * sizeof(int));


    for (int i = 0; i < CantidadBarcos; i++) {
        if (fgets(linea, sizeof(linea), archivo) == NULL) {
            fprintf(stderr, "Error al leer línea de barco %d\n", i);
            fclose(archivo);
            return;
        }

        // Quitar salto de línea
        linea[strcspn(linea, "\r\n")] = '\0';

        // Separar por '-'
        char *token = strtok(linea, "-");
        // if (token) config->id_barco[i] = token[0];

        token = strtok(NULL, "-");
        if (token) config->c_barco[i] = atoi(token);
    }


    // -----------------------
    // LEER LÍNEA DEL JUGADOR 1
    // -----------------------
    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        fprintf(stderr, "Error al leer datos del jugador\n");
        fclose(archivo);
        return;
    }

    // Quitar salto de línea
    linea[strcspn(linea, "\r\n")] = '\0';

    // Parsear campos separados por guiones
    token = strtok(linea, "-");
    if (token) jugador[0].Id_jugador = atoi(token);

    token = strtok(NULL, "-");
    if (token) strncpy(jugador[0].Nomb_jugador, token, sizeof(jugador[1].Nomb_jugador));

    token = strtok(NULL, "-");
    if (token) jugador[0].Num_disp = atoi(token);

    token = strtok(NULL, "-");
    if (token) jugador[0].Tipo_disparo = token[0];

    token = strtok(NULL, "-");
    if (token) jugador[0].Ganador = atoi(token);






    // --------------------
    // LEER PRIMERA MATRIZ
    // --------------------


    long pos = ftell(archivo);

    // Contar caracteres válidos en la primera línea
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') break;
        if (c != ' ' && c != '\r') {
            dimension++;
        }
    }

    // Configurar y reservar primera matriz
    jugador[0].Flota = malloc(dimension * sizeof(char *));
    for (int i = 0; i < dimension; i++)
        jugador[0].Flota[i] = malloc(dimension * sizeof(char));

    jugador[1].Oponente = malloc(dimension * sizeof(char *));
    for (int i = 0; i < dimension; i++)
        jugador[1].Oponente[i] = malloc(dimension * sizeof(char));


    // Retroceder para re-leer la matriz completa
    fseek(archivo, pos, SEEK_SET);
    int fila = 0, columna = 0;

    while ((c = fgetc(archivo)) != EOF && fila < dimension) {
        if (c == ' ' || c == '\n' || c == '\r') continue;

        jugador[0].Flota[fila][columna] = c;
        jugador[1].Oponente[fila][columna++] = c;
        if (columna == dimension) {
            columna = 0;
            fila++;
        }
    }



    // -----------------------
    // LEER LÍNEA DEL JUGADOR 2
    // -----------------------
    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        fprintf(stderr, "Error al leer datos del jugador\n");
        fclose(archivo);
        return;
    }

    // Quitar salto de línea
    linea[strcspn(linea, "\r\n")] = '\0';
    // Parsear campos separados por guiones
    token = strtok(linea, "-");                                            //*******************************************************************

    if (token) jugador[1].Id_jugador = atoi(token);

    token = strtok(NULL, "-");
    if (token) strncpy(jugador[1].Nomb_jugador, token, sizeof(jugador[1].Nomb_jugador));

    token = strtok(NULL, "-");
    if (token) jugador[1].Num_disp = atoi(token);

    token = strtok(NULL, "-");
    if (token) jugador[1].Tipo_disparo = token[0];

    token = strtok(NULL, "-");
    if (token) jugador[1].Ganador = atoi(token);





    // ---------------------
    // LEER SEGUNDA MATRIZ
    // ---------------------
    // Volver a contar dimensión (segunda matriz)
    dimension = 0;
    pos = ftell(archivo); // guardar posición actual
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') break;
        if (c != ' ' && c != '\r') {
            dimension++;
        }
    }

    // Configurar y reservar segunda matriz
    jugador[0].Oponente = malloc(dimension * sizeof(char *));
    for (int i = 0; i < dimension; i++)
        jugador[0].Oponente[i] = malloc(dimension * sizeof(char));

    jugador[1].Flota = malloc(dimension * sizeof(char *));
    for (int i = 0; i < dimension; i++)
        jugador[1].Flota[i] = malloc(dimension * sizeof(char));


    fseek(archivo, pos, SEEK_SET); // volver al inicio de la segunda matriz

    fila = 0; columna = 0;
    while ((c = fgetc(archivo)) != EOF && fila < dimension) {
        if (c == ' ' || c == '\n' || c == '\r') continue;

        jugador[0].Oponente[fila][columna] = c;
        jugador[1].Flota[fila][columna++] = c;
        if (columna == dimension) {
            columna = 0;
            fila++;
        }
    }




    fclose(archivo);
}
