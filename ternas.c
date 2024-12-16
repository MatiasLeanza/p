#include <stdio.h>
#include <stdbool.h>

#define MAX_JUGADORES 30
#define MAX_JUEGOS 7

void colorear(const char *texto, const char *color) {
    printf("%s%s\033[0m", color, texto);
}

int main() {
    float premios[MAX_JUEGOS];
    float calificaciones[MAX_JUGADORES][MAX_JUEGOS] = {0}; // Almacena el promedio de las calificaciones
    bool calificado[MAX_JUGADORES] = {false};              // Marca si el jugador fue calificado
    int contador_calificaciones[MAX_JUGADORES][MAX_JUEGOS] = {0};

    // Colores para la terminal
    const char *VERDE = "\033[0;32m";
    const char *ROJO = "\033[0;31m";
    const char *AZUL = "\033[0;34m";

    colorear("\nIngrese los premios por cada juego:\n", VERDE);
    for (int i = 0; i < MAX_JUEGOS; i++) {
        printf("Premio para el juego %d: ", i + 1);
        scanf("%f", &premios[i]);
    }

    colorear("\nIngrese las ternas de datos (jugador, juego, calificación). Introduzca 0 para terminar:\n", AZUL);
    while (1) {
        int jugador, juego, calificacion;
        printf("Jugador (1-30): ");
        scanf("%d", &jugador);
        if (jugador == 0) break;

        printf("Juego (1-7): ");
        scanf("%d", &juego);

        printf("Calificación (1-10): ");
        scanf("%d", &calificacion);

        if (jugador < 1 || jugador > 30 || juego < 1 || juego > 7 || calificacion < 1 || calificacion > 10) {
            colorear("\nEntrada inválida. Por favor ingrese valores dentro del rango permitido.\n", ROJO);
            continue;
        }

        // Ajustamos índices a base 0
        jugador--;
        juego--;

        // Actualizamos la matriz y el contador
        calificaciones[jugador][juego] += calificacion;
        contador_calificaciones[jugador][juego]++;
        calificado[jugador] = true;
    }

    colorear("\nResultados:\n", VERDE);

    // Calculamos los promedios y mostramos resultados
    int jugadores_no_calificados = 0;
    float monto_jugador[MAX_JUGADORES] = {0};

    for (int i = 0; i < MAX_JUGADORES; i++) {
        bool jugador_sin_calificacion = true;
        for (int j = 0; j < MAX_JUEGOS; j++) {
            if (contador_calificaciones[i][j] > 0) {
                jugador_sin_calificacion = false;
                calificaciones[i][j] /= contador_calificaciones[i][j];
                printf("Jugador %d - Juego %d: Promedio %.2f\n", i + 1, j + 1, calificaciones[i][j]);
                if (calificaciones[i][j] > 8) {
                    monto_jugador[i] += premios[j];
                }
            }
        }
        if (jugador_sin_calificacion) {
            jugadores_no_calificados++;
        }
    }

    // Informar el porcentaje de jugadores no calificados
    printf("\nPorcentaje de jugadores no calificados: %.2f%%\n", (jugadores_no_calificados / (float)MAX_JUGADORES) * 100);

    // Informar el monto total que cobrará cada jugador
    colorear("\nMonto que cobrará cada jugador:\n", AZUL);
    for (int i = 0; i < MAX_JUGADORES; i++) {
        if (monto_jugador[i] > 0) {
            printf("Jugador %d: $%.2f\n", i + 1, monto_jugador[i]);
        }
    }

    return 0;
}
