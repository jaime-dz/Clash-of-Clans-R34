#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Estructuras.h"
#include "disparar.h"

//Para este algoritmo de busqueda organizare el recorrido de ida y vuelta de la matriz mediante parejas
//(Arriba y abajo) (izquierda y derecha) (Dos diagonales cruzadas)

int disparo_manual (Jugador *jug, registro_configuracion confi, int n) {
    int filas, columnas, turno = 0, valido;
    do { // 1
        do { // 2
        printf ("Introduce un entero para apuntar a una fila: "); // 3
        scanf (" %d",&filas); // 4
        printf ("\nIntroduce un entero para apuntar a una columna: "); // 5
        scanf (" %d",&columnas); // 6 
        }while (filas<0 || columnas<0 ||filas>=confi.t_tablero || columnas >=confi.t_tablero); // 7
        valido = comprobar_disparo(jug, &confi, filas, columnas, n); // 8
        if (valido == 0) { // 9 
            printf("\nLugar ya disparado"); // 10 
        } else { // 11
            if (jug[n].Oponente[filas][columnas] == 't') { // 12
                printf ("\n¡Has tocado un barco!"); // 13 
                turno = 1; // 14 
            } else if (jug[n].Oponente[filas][columnas] == 'h') { // 15
                printf ("\n¡Has hundido un barco!"); // 16 
                jug[n].barcos_hundidos++; // 17 
                turno = 1; // 18 
            } else if (jug[n].Oponente[filas][columnas] == '*') { // 19 
                printf ("\nHas fallado tu disparo, ¡Mejor suerte para el siguiente!"); // 20 
            }
        }
     jug[n].Num_disp = jug[n].Num_disp + 1; // 21
    } while (turno == 1); // 22 
    return turno; // 23
}

int disparo_automatico(Jugador *jug, registro_configuracion confi, int n) {
    // srand(time(NULL)); mover al main
    int fila_al, columna_al, direccion, turno = 1, valido; 
    int fila_sig, columna_sig, i, j;
    do {
        do {
            fila_al = rand() % confi.t_tablero;
            columna_al = rand() % confi.t_tablero;
        }while(jug[n].Oponente[fila_al][columna_al] != 'h' && jug[n].Oponente[fila_al][columna_al] != 't' && jug[n].Oponente[fila_al][columna_al] != '*');

        valido = comprobar_disparo (jug, &confi, fila_al, columna_al, n);
        if (valido == 0) {
            printf("\nLugar ya disparado");
        }
        if (jug[n].Oponente[fila_al][columna_al] == '*') {
            printf("\nDisparo fallido.");
            turno = 0;
        } else if (jug[n].Oponente[fila_al][columna_al] == 'h') {
            printf ("\nHas hundido un barco.");
            jug[n].barcos_hundidos++;
        } else if (jug[n].Oponente[fila_al][columna_al] == 't') {
            direccion = rand() % 8;
            switch (direccion)
            {
            case 0:
                fila_sig = fila_al - 1;
                columna_sig = columna_al - 1;
                if (fila_sig < 0 || columna_sig < 0) {
                    printf("\nDireccion no valida.");
                    break;
                }
                comprobar_disparo (jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] ==  't' ) {
                    for (i = fila_sig, j = columna_sig; i>=0 && j>=0; i--, j--) {
                        comprobar_disparo (jug, &confi, i, j, n);
                        if (jug[n].Oponente[i][j] == '*' ) {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            case 1:
                fila_sig = fila_al - 1;
                columna_sig = columna_al;
                if (fila_sig < 0) {
                    printf("\nDireccion no valida.");
                    break;
                }
                comprobar_disparo(jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = fila_sig; i >= 0; i--) {
                        comprobar_disparo (jug, &confi, i, j, n);
                        if (jug[n].Oponente[i][j] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            case 2: 
                fila_sig = fila_al - 1;
                columna_sig = columna_al + 1;
                if (fila_sig < 0 || columna_sig >= confi.t_tablero) {
                    printf ("\nDireccion invalida");
                    break;
                }         
                comprobar_disparo(jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = fila_sig, j = columna_sig; i >= 0 && j <= confi.t_tablero; i--, j++) {
                        comprobar_disparo (jug, &confi, i, j, n);
                        if (jug[n].Oponente[i][j] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            case 3:
                fila_sig = fila_al;
                columna_sig = columna_al + 1;
                if (columna_sig >= confi.t_tablero) {
                    printf ("\nDireccion invalida.");
                    break;
                } 
                comprobar_disparo (jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = columna_sig; i < confi.t_tablero; i++) {
                        comprobar_disparo (jug, &confi, fila_sig, i, n);
                        if (jug[n].Oponente[fila_sig][n] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            case 4: 
                fila_sig = fila_al + 1;
                columna_sig = columna_al + 1;
                if (fila_sig > confi.t_tablero || columna_sig >= confi.t_tablero) {
                    printf("\nDireccion no valida");
                    break;
                }
                comprobar_disparo(jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = fila_sig, j = columna_sig; i < confi.t_tablero && j < confi.t_tablero; i++, j++) {
                        comprobar_disparo (jug, &confi, i, j, n);
                        if (jug[n].Oponente[i][j] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0; 
                    break;
                }
                break;
            case 5:
                fila_sig = fila_al + 1;
                columna_sig = columna_al;
                if (fila_sig >= confi.t_tablero) {
                    printf("\nDireccion no valida.");
                    break;
                }   
                comprobar_disparo(jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = fila_sig; i < confi.t_tablero; i++) {
                        comprobar_disparo (jug, &confi, i, j, n);
                        if (jug[n].Oponente[i][j] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            case 6: 
                fila_sig = fila_al + 1;
                columna_sig = columna_al - 1;
                if (fila_sig >= confi.t_tablero || columna_sig < 0) {
                    printf ("\nDireccion invalida");
                    break;
                }         
                comprobar_disparo(jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = fila_sig, j = columna_sig; i < confi.t_tablero && j >= 0; i++, j--) {
                        comprobar_disparo (jug, &confi, i, j, n);
                        if (jug[n].Oponente[i][j] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            case 7: 
                fila_sig = fila_al;
                columna_sig = columna_al - 1;
                if (columna_sig < 0) {
                    printf ("\nDireccion invalida.");
                    break;
                } 
                comprobar_disparo (jug, &confi, fila_sig, columna_sig, n);
                if (jug[n].Oponente[fila_sig][columna_sig] == 't') {
                    for (i = columna_sig; i < confi.t_tablero; i--) {
                        comprobar_disparo (jug, &confi, fila_sig, i, n);
                        if (jug[n].Oponente[fila_sig][i] == '*') {
                            turno = 0;
                            break;
                        }
                    }
                } else {
                    turno = 0;
                    break;
                }
                break;
            default:
                printf("\nDireccion invalida.");
                break;
            }
        }
    } while (turno == 1);
    return turno;
}

int comprobar_disparo (Jugador *jug, registro_configuracion *confi, int fila, int columna, int n) {
    int i, j, fila2 = fila, columna2 = columna, fila_ini, col_ini, fila_fin, col_fin; //fila y columna seran los originales y fila2 y columna2 seran copias modificables, fila_ini y col_ini son las filas y columnas iniciales del barco y fila_fin y col_fin seran las filas y columnas finales
    char letra; //Que hay almacenado en cada posicion del tablero.
    int valido = 1;
    int esta_hundido = 1; //Suponemos que esta hundido.
    int agua1=0, agua2=0, agua3=0, agua4=0, agua5=0, agua6=0, agua7=0, agua8=0; //Suponemos que no hemos inpactado en el agua, es feo, pero asi podemos tener claro que posicion es agua aunque no sea visible apra el jugador
    if (jug[n].Oponente[fila][columna] == 't' || jug[n].Oponente[fila][columna] == 'h' || jug[n].Oponente[fila][columna] == '*') {
        valido = 0;
    }
    if (jug[n].Oponente[fila][columna] == 'x') { //Le dió a algo. 
        if (jug[n].Oponente[fila2-1][columna2-1] == '*') { //Nada en la direccion 1, diagonal izquierda arriba, derecha anajo
            agua1=1; //Impactamos en agua. 
        } else { 
            j = columna2-1;
            for (i = fila2; i>=0 || jug[n].Oponente[i][j] == '*'; i--) {
                j--; 
                fila_ini = i;
                col_ini = j;
            } //Cuando este bucle termina hemos encontrado el principio del barco, luego hacemos una busqueda exacta de las letras almacenadas (T para tocado, X para no tocado pero hay barco)
            //El limite del bucle sera el extremo de su pareja, la direccion 5
            for (i=fila_ini; i<=confi->t_tablero || jug[n].Oponente[i][j] == '*'; i++) {
                j++;
                letra = (jug[n].Oponente[i][j]);
                if (letra == 't') {
                    esta_hundido = 1; 
                }
                if (letra == 'x') {
                    esta_hundido = 0;
                }
                fila_fin = i; 
                col_fin = j; 
            }
            if (esta_hundido == 1) { //El barco, efectivamente esta hundido.
                jug[n].Oponente[fila][columna] = 'h'; //Marcamos como hundido
                j = col_fin;
                for(i = fila_fin; i<=fila_ini; i--) {
                    jug[n].Oponente[i][j] = 'h'; 
                    if (fila_ini > 0 && col_ini > 0) {
                        jug[n].Oponente[fila_ini-1][col_ini-1] = '*';
                    }
                    if (fila_fin < confi->t_tablero && col_fin < confi->t_tablero) {
                        jug[n].Oponente[fila_fin+1][col_fin+1] = '*'; 
                    } 
                    if (i > 0) {
                        jug[n].Oponente[i-1][j] = '*';
                        if (j < confi->t_tablero) {
                            jug[n].Oponente[i-1][j+1] = '*';
                        }
                    }
                    if (i < confi->t_tablero) {
                        jug[n].Oponente[i+1][j] = '*';
                        if (j > 0) {
                            jug[n].Oponente[i+1][j-1] = '*'; 
                        }
                    }
                    if (j < confi->t_tablero) {
                        jug[n].Oponente[i][j+1] = '*';    
                    }
                    j--;
                }
            }
        }
        
        if (jug[n].Oponente[fila2+1][columna2+1] == '*') {
            agua5 = 1; // impacto en agua.
        } //Nada en la direccion 5, como ya hemos visto que hay en su direccion, solo hace falta que comprobemos que si la primera es agua. 


        if (jug[n].Oponente[fila2-1][columna2] == '*') { //Nada en la direccion 2, vertical arriba a abajo 
            agua2 = 1;
        } else {
            j = columna2;
            for (i = fila2; i>=0 || jug[n].Oponente[i][j] == '*'; i--) { 
                fila_ini = i; //Obtenemos la fila inicial
                col_ini = j; //La columna inicial sera la misma que la columna donde se ha recibido el disparo
            }
            for (i=fila_ini; i<=confi->t_tablero || jug[n].Oponente[i][j] == '*'; i++) {
                letra = (jug[n].Oponente[i][j]);
                if (letra == 't') {
                    esta_hundido = 1; 
                }
                if (letra == 'x') {
                    esta_hundido = 0;
                }
                fila_fin = i; 
                col_fin = j; 
            }
            if (esta_hundido == 1) { //El barco, efectivamente esta hundido.
                jug[n].Oponente[fila][columna] = 'h'; //Marcamos como hundido
                j = col_fin;
                for(i = fila_fin; i<=fila_ini; i--) {
                    jug[n].Oponente[i][j] = 'h'; 
                    if (fila_ini > 0) {
                        jug[n].Oponente[fila_ini-1][col_ini] = '*';
                    }
                    if (fila_fin < confi->t_tablero) {
                        jug[n].Oponente[fila_fin+1][col_fin] = '*'; 
                    }
                    if (i < confi->t_tablero) {
                        if (j > 0) {
                            jug->Oponente[i+1][j-1] = '*';
                        } else if (j < confi->t_tablero) {
                            jug[n].Oponente[i+1][j+1] = '*';
                        }
                    }
                    if (i < confi->t_tablero && j > 0) {
                        jug[n].Oponente[i+1][j-1] = '*';
                    }
                }
            }
        } 
        if (jug[n].Oponente[fila2+1][columna2] == '*') { //Nada en la direccion 6, como ya sabemos que hay en su direccion, solo hace falta saber si la primera es agua.
            agua6 = 1;
        }


        if (jug[n].Oponente[fila2-1][columna2+1] == '*') { //Nada en la direccion 3
            agua3 = 1; 
        } else {
            j = columna2+1;
            for (i = fila2; i>=0 || jug[n].Oponente[i][j] == '*'; i++) {
                j--; 
                fila_ini = i;
                col_ini = j;
            }
            for (i=fila_ini; i<=confi->t_tablero || jug[n].Oponente[i][j] == '*'; i--) {
                j--;
                letra = (jug[n].Oponente[i][j]);
                if (letra == 't') {
                    esta_hundido = 1; 
                }
                if (letra == 'x') {
                    esta_hundido = 0;
                }
                fila_fin = i; 
                col_fin = j; 
            }
            if (esta_hundido == 1) { //El barco, efectivamente esta hundido.
                jug[n].Oponente[fila][columna] = 'h'; //Marcamos como hundido
                j = col_fin; 
                for(i = fila_fin; i<=fila_ini; i--) {
                    jug[n].Oponente[i][j] = 'h';
                    if (fila_ini > 0 && col_ini < confi->t_tablero) {
                        jug[n].Oponente[fila_ini-1][col_ini+1] = '*'; 
                    }
                    if (fila_fin > 0 && col_fin < confi->t_tablero) {
                        jug[n].Oponente[fila_fin-1][col_fin+1] = '*';    
                    }
                    if (i > 0) {
                        jug[n].Oponente[i-1][j] = '*';
                        if (j > 0) {
                            jug[n].Oponente[i-1][j-1] = '*';
                    }
                    if (i < confi->t_tablero) {
                        jug[n].Oponente[i+1][j] = '*';
                        if (j < confi->t_tablero) {
                            jug[n].Oponente[i+1][j+1] = '*';
                        }
                    }
                    if (j < confi->t_tablero) {
                        jug[n].Oponente[i][j+1] = '*';
                    } else if (j > 0) {
                        jug[n].Oponente[i][j-1] = '*';
                    }
                    j++;
                }
            }
        }
        if (jug[n].Oponente[fila2+1][columna2-1] == '*') { //Nada en la direccion 7
            agua7=1;    
        }


        if (jug[n].Oponente[fila2][columna2+1] == '*') { //Nada en la direccion 4
            agua4=1;
        } else { 
            i = fila2;
            for (j = columna2; j>=0 || jug[n].Oponente[i][j] == '*'; j++) {
                fila_ini = i;
                col_ini = j;
            }
            for (j=col_ini; i<=confi->t_tablero || jug[n].Oponente[i][j] == '*'; j--) {
                letra = (jug[n].Oponente[i][j]);
                if (letra == 't') {
                    esta_hundido = 1; 
                }
                if (letra == 'x') {
                    esta_hundido = 0;
                }
                fila_fin = i; 
                col_fin = j; 
            }
            if (esta_hundido == 1) { //El barco, efectivamente esta hundido.
                jug[n].Oponente[fila][columna] = 'h'; //Marcamos como hundido
                for(j = col_fin; j<=col_ini; j++) {
                    jug[n].Oponente[i][j] = 'h'; 
                    if (col_ini < confi->t_tablero) {
                        jug[n].Oponente[fila_ini][col_ini+1] = '*';
                    }
                    if (col_fin > 0) {
                        jug[n].Oponente[fila_fin][col_fin-1] = '*'; 
                    }
                    if (i > 0) {
                        jug[n].Oponente[i-1][j] = '*';
                        if (j > 0) {
                            jug[n].Oponente[i-1][j-1] = '*';
                        }
                    }
                    if (i < confi->t_tablero) {
                        jug[n].Oponente[i+1][j] = '*';
                        if (j > 0) {
                            jug[n].Oponente[i+1][j-1] = '*';
                        }
                    }
                }
            }
        } 
        
        if (jug[n].Oponente[fila2][columna2-1] == '*') { //Nada en la direccion 8
            agua8=1; 
        }
        if (agua1 == 1 && agua2 == 1 && agua3 == 1 && agua4 == 1 && agua5 == 1 && agua6 == 1 && agua7 == 1 && agua8 == 1) {
            jug[n].Oponente[fila][columna] = 'h'; //Era un barco de 1
        }
        
    } 
} else { jug[n].Oponente [fila][columna] = '*'; }
return valido;
}