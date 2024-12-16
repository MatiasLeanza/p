#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_TABLERO 15
#define MAX_POZOS 2
#define MAX_COMODINES 2
#define MAX_CAIDAS 3

// Colores para la terminal
const char *VERDE = "\033[0;32m";
const char *ROJO = "\033[0;31m";
const char *AZUL = "\033[0;34m";
const char *AMARILLO = "\033[0;33m";
const char *RESET = "\033[0m";

void colorear(const char *texto, const char *color) {
    printf("%s%s%s", color, texto, RESET);
}

void inicializarTablero(char tablero[TAM_TABLERO][TAM_TABLERO]) {
    for (int i = 0; i < TAM_TABLERO; i++) {
        for (int j = 0; j < TAM_TABLERO; j++) {
            tablero[i][j] = 'x';
        }
    }
}

void colocarElementos(char tablero[TAM_TABLERO][TAM_TABLERO], char elemento, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        int fila, columna;
        do {
            fila = rand() % TAM_TABLERO;
            columna = rand() % TAM_TABLERO;
        } while (tablero[fila][columna] != 'x');
        tablero[fila][columna] = elemento;
    }
}

void mostrarTablero(char tablero[TAM_TABLERO][TAM_TABLERO], int filaT, int columnaT, int filaL, int columnaL) {
    for (int i = 0; i < TAM_TABLERO; i++) {
        for (int j = 0; j < TAM_TABLERO; j++) {
            if (i == filaT && j == columnaT)
                printf("%sT%s ", VERDE, RESET);
            else if (i == filaL && j == columnaL)
                printf("%sL%s ", VERDE, RESET);
            else if (tablero[i][j] == 'x')
                printf("%s%c%s ", AZUL, tablero[i][j], RESET);
            else if (tablero[i][j] == 'O')
                printf("%s%c%s ", ROJO, tablero[i][j], RESET);
            else if (tablero[i][j] == 'C')
                printf("%s%c%s ", AMARILLO, tablero[i][j], RESET);
            else if (tablero[i][j] == 'M')
                printf("%s%c%s ", VERDE, tablero[i][j], RESET);
        }
        printf("\n");
    }
}

int moverJugador(char tablero[TAM_TABLERO][TAM_TABLERO], int *fila, int *columna, int pasos, char jugador, int *caidasPozos, int *comodinesUsados, int *modoComodin) {
    for (int i = 0; i < pasos; i++) {
        if (*columna + 1 < TAM_TABLERO) {
            (*columna)++;
        } else if (*fila + 1 < TAM_TABLERO) {
            *columna = 0;
            (*fila)++;
        } else {
            return 1; // El jugador alcanzó la meta
        }

        if (tablero[*fila][*columna] == 'O') {
            (*caidasPozos)++;
            if (*caidasPozos >= MAX_CAIDAS) {
                return -1; // Perdió el juego
            }
        } else if (tablero[*fila][*columna] == 'C') {
            (*comodinesUsados)++;
            *modoComodin = !(*modoComodin); // Cambia el modo de avance
            printf("%sEl jugador %c agarró un comodín. Ahora avanza %s.%s\n", AMARILLO, jugador, *modoComodin ? "el doble del dado" : "según el dado", RESET);
            tablero[*fila][*columna] = 'x'; // Elimina el comodín del tablero
        }
    }
    return 0; // Continúa el juego
}

int main() {
    char tablero[TAM_TABLERO][TAM_TABLERO];
    int filaT = 0, columnaT = 0, filaL = 0, columnaL = 0;
    int caidasPozosT = 0, caidasPozosL = 0;
    int comodinesT = 0, comodinesL = 0;
    int resultado;
    int modoComodinT = 0, modoComodinL = 0; // Modos para controlar avance por comodines
    int dadoT, pasosT, dadoL, pasosL;

    srand(time(NULL));

    // Inicializar tablero y colocar elementos
    inicializarTablero(tablero);
    colocarElementos(tablero, 'O', MAX_POZOS);
    colocarElementos(tablero, 'C', MAX_COMODINES);
    tablero[TAM_TABLERO - 1][TAM_TABLERO - 1] = 'M'; // Coloca la meta

    colorear("\nTablero inicial:\n", VERDE);
    mostrarTablero(tablero, filaT, columnaT, filaL, columnaL);

    while (1) {
        // Turno de la tortuga
        printf("\nTurno de la tortuga (T): Presiona ENTER para lanzar el dado...\n");
        getchar();
        dadoT = rand() % 6 + 1;
        pasosT = modoComodinT ? dadoT * 2 : dadoT;
        printf("Modo comodín: %s\n", modoComodinT ? "ACTIVO" : "INACTIVO");
        printf("Dado: %d, Pasos calculados: %d\n", dadoT, pasosT);
        resultado = moverJugador(tablero, &filaT, &columnaT, pasosT, 'T', &caidasPozosT, &comodinesT, &modoComodinT);
        mostrarTablero(tablero, filaT, columnaT, filaL, columnaL);
        if (resultado == 1) {
            colorear("\nLa tortuga gana!\n", VERDE);
            break;
        } else if (resultado == -1) {
            colorear("\nLa tortuga perdió por caer en pozos.\n", ROJO);
            break;
        }

        // Turno de la liebre
        printf("\nTurno de la liebre (L): Presiona ENTER para lanzar el dado...\n");
        getchar();
        dadoL = rand() % 6 + 1;
        pasosL = modoComodinL ? dadoL : dadoL * 2;
        printf("Modo comodín: %s\n", modoComodinL ? "ACTIVO" : "INACTIVO");
        printf("Dado: %d, Pasos calculados: %d\n", dadoL, pasosL);
        resultado = moverJugador(tablero, &filaL, &columnaL, pasosL, 'L', &caidasPozosL, &comodinesL, &modoComodinL);
        mostrarTablero(tablero, filaT, columnaT, filaL, columnaL);
        if (resultado == 1) {
            colorear("\nLa liebre gana!\n", VERDE);
            break;
        } else if (resultado == -1) {
            colorear("\nLa liebre perdió por caer en pozos.\n", ROJO);
            break;
        }
    }

    printf("\nResumen:\n");
    printf("Tortuga - Pozos: %d, Comodines: %d\n", caidasPozosT, comodinesT);
    printf("Liebre - Pozos: %d, Comodines: %d\n", caidasPozosL, comodinesL);

    return 0;
}
