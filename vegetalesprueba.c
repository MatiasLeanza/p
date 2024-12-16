#include <stdio.h>

#include <stdlib.h>

#define GREEN   "\x1b[32m"

#define YELLOW  "\x1b[33m"

#define BLUE    "\x1b[34m"

#define MAGENTA "\x1b[35m"

#define CYAN    "\x1b[36m"

#define BLACK   "\x1B[30m"

#define RED     "\x1b[31m"

#define WHITE   "\x1B[37m"



#define OPERADORES 7

#define TIPOS_VIANDA 4

   
    //Precio de las viandas, Vegetales, Carne, Pescado, Frutas

    float precios_viandas[TIPOS_VIANDA] = {100.0, 150.0, 200.0, 50.0};

   

    // Variables globales

    // Ganancia total por cada tipo de vianda

    float ganancia_vianda[TIPOS_VIANDA] = {0};                

    // Contador de ventas que superan las 4 unidades

    int ventas_mayores_a_4 = 0;                              

    // Matriz para contar ventas por operador y tipo de vianda

    int ventas[OPERADORES][TIPOS_VIANDA] = {{0}};            

    // Matriz para comisiones por operador y tipo de vianda

    float comisiones[OPERADORES][TIPOS_VIANDA] = {{0}};      


    // Funcion para ingresar datos de una venta

    int ingresar_datos(int *operador, int *tipo_vianda, int *cantidad) {

        printf(RED"Operador (1-7, o 0 para terminar): ");

        scanf("%d", operador);

       

        // Terminar ingreso de datos

        if (*operador == 0) return 0;

       

        if (*operador < 1 || *operador > OPERADORES) {

            printf(WHITE"Operador invalido. Ingrese un nmero entre 1 y 7.\n");

            return -1;

        }

   

        printf(BLUE"Tipo de vianda (0=Vegetales, 1=Carne, 2=Pescado, 3=Frutas): ");

        scanf("%d", tipo_vianda);

        if (*tipo_vianda < 0 || *tipo_vianda >= TIPOS_VIANDA) {

            printf(WHITE"Tipo de vianda invalido. Ingrese un nmero entre 0 y 3.\n");

            return -1;

        }

   

        printf(BLUE"Cantidad de viandas: ");

        scanf("%d", cantidad);

   

        return 1;

    }


    // Funcion para actualizar los datos de las ventas

    void actualizar_datos(int operador, int tipo_vianda, int cantidad) {

        // Ajustar dice (para operador 1 -> dice 0)

        operador--;

   

        // Actualizar matriz de ventas

        ventas[operador][tipo_vianda] += cantidad;

        ganancia_vianda[tipo_vianda] += cantidad * precios_viandas[tipo_vianda];

   

        // Calcular y actualizar comisiones

        float venta_total = cantidad * precios_viandas[tipo_vianda];

        // 10% comisin base

        comisiones[operador][tipo_vianda] += venta_total * 0.10;

   

        // Comprobar si la venta supera las 4 unidades

        if (cantidad > 4) {

            ventas_mayores_a_4++;

            // 3% comisin adicional

            comisiones[operador][tipo_vianda] += venta_total * 0.03;

        }

    }

   

    // Funcin para calcular la comisin total de cada operador

    float calcular_comision_total(int operador) {

        float comision_total = 0;

        for (int i = 0; i < TIPOS_VIANDA; i++) {

            comision_total += comisiones[operador][i];

        }

        return comision_total;

    }


    // Funcin para imprimir los resultados

    void imprimir_resultados() {

        printf(CYAN"\n<<<< Resultados de ventas >>>>\n");

        printf(RED"Cantidad total de ventas que superan las 4 unidades: %d\n", ventas_mayores_a_4);

   

        printf(BLUE"\nGanancia por tipo de vianda:\n");

        printf(YELLOW"Vegetales: $%.2f\n", ganancia_vianda[0]);

        printf(MAGENTA"Carne: $%.2f\n", ganancia_vianda[1]);

        printf(GREEN"Pescado: $%.2f\n", ganancia_vianda[2]);

        printf(BLUE"Frutas: $%.2f\n", ganancia_vianda[3]);

   

        printf(MAGENTA"\nCantidad de viandas vendidas y comisin por operador:\n");

        for (int i = 0; i < OPERADORES; i++) {

            int total_ventas_operador = 0;

            for (int j = 0; j < TIPOS_VIANDA; j++) {

                total_ventas_operador += ventas[i][j];

            }

            printf(WHITE"Operador %d - Viandas vendidas: %d, Comisin total: $%.2f\n",

                   i + 1, total_ventas_operador, calcular_comision_total(i));

        }

    }


int main() {

    int operador, tipo_vianda, cantidad;

    int resultado;


    printf("Ingrese los datos de las ventas (operador 0 para terminar):\n");


    while (1) {

        resultado = ingresar_datos(&operador, &tipo_vianda, &cantidad);

        // Finalizar ingreso de datos

        if (resultado == 0) break;    

        // Reintentar ingreso en caso de error

        if (resultado == -1) continue;


        // Actualizar datos de ventas

        actualizar_datos(operador, tipo_vianda, cantidad);

    }


    // Imprimir resultados finales

    imprimir_resultados();


    return 0;

}
