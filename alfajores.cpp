// CODIGO COMPILADO EN ONLINEGDB.COM
#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;
// Codigos de colores ANSI
#define Negro "\033[0;30m" 
#define Rojo "\033[0;31m"
#define Verde "\033[0;32m"
#define Amarillo "\033[0;33m"
#define Azul "\033[0;34m"
#define Magenta "\033[0;35m"
#define Cyan "\033[0;36m"
#define RESET_COLOR "\033[0m" // Se usa para dejar de utilizar el color que se venia utilizando

int precios[4] = {100,150,90,200}; // El array precios se inicializa aca para poder usar en el resto de las funciones


void entrada(int entregas[6][4], int errores, int fueraDeProduccion[6]) {
    int operario, tipo, cantidad; // Declaracion de variables utilizadas en la entrada de datos
    cout << "A continuación, ingrese los datos de las ventas: " << endl
         << Rojo "Al ingresar un operario o un tipo de alfajor inválido se terminará la entrada de datos" RESET_COLOR << endl;

    while (1) {
        cout << "Ingrese el tipo de alfajor: " << endl;
        cout << Magenta "1. Chocolate" RESET_COLOR << endl
             << Cyan "2. Dulce de Leche" RESET_COLOR << endl
             << Amarillo "3. Fruta" RESET_COLOR << endl
             << Verde "4. Mixto" RESET_COLOR << endl
             << Rojo "5. Salir" RESET_COLOR << endl;
        cin >> tipo;
        if (tipo > 4 || tipo < 1) { // Lo correcto seria poner un 5 para salir, pero si el usuario ingresa otro numero, tambien se detendra la entrada
            break;
        }
        cout << endl << "Ahora ingrese el operario a cargo de la elaboración de los alfajores (1 a 6): ";
        cin >> operario;
        if (operario > 6 || operario < 1) {
            break;
        }
        cout << "Y por último, ingrese la cantidad de alfajores: ";
        cin >> cantidad;
        if(cantidad < 1) {cantidad = 0;} // Si el usuario ingresa un numero negativo, la cantidad ingresada contara como 0 porque no se pueden entregar -5 alfajores

        entregas[operario - 1][tipo - 1] += cantidad;

        if (cantidad % 6 != 0) {
            errores++;
            fueraDeProduccion[operario - 1] += cantidad % 6;
        }
    }
    cout << endl << "Hay " << errores << " entrega/s con error/es" << endl;
}

void calcularGanancias(int entregas[6][4]) {
    cout << Cyan "Ahora veremos las ganancias de las ventas de alfajores, las ganancias totales y por tipo: " RESET_COLOR<< endl;
    string tipos[4] = {"Chocolate", "Dulce de Leche", "Fruta", "Mixto"};
    float ganancias[4] = {0,0,0,0}; // Array para las ganancias de cada tipo
    float gananciasTotales = 0; // Variable para las ganancias totales, o sea la suma de los 4 elementos del array de ganancias
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            ganancias[j] += (entregas[i][j] / 6) * precios[j]; // Se divide la cantidad de alfajores por 6 para luego multiplicarlo por el precio que le corresponde a ese tipo
        }
    }
    for(int i = 0; i < 4; i++) {
        // Informar la ganancia por tipo de alfajor si se venden todas las entregas de los alfajores elaborados
        cout << "Los alfajores de tipo " << tipos[i] << " consiguieron " << ganancias[i] << " ganancias" << endl;
        gananciasTotales += ganancias[i];
    }
    cout << "Las ganancias totales son " << gananciasTotales << endl; // El ejercicio no pide saber las ganancias totales pero hay una parte donde se mencionan, por lo que me parece un dato importante
}

void produccion(int entregas[6][4], int fueraDeProduccion[6]) {
    cout << Cyan "Ahora veremos la cantidad de alfajores elaborados por tipo de alfajor y la cantidad fuera de produccion:" RESET_COLOR << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Operador " << i + 1 << endl;
        for (int j = 0; j < 4; j++) {
            // Informar la cantidad de alfajores por operario elaborados por tipo de alfajor
            cout << "Tipo " << j + 1 << ": " << entregas[i][j] << " alfajores" << endl;
        }
        if (fueraDeProduccion[i] > 0) {
            // Informar la cantidad fuera de produccion elaborados en cada entrega sin importar el tipo de alfajor
            cout << Rojo "\tFuera de producción: " << fueraDeProduccion[i] << " alfajores" RESET_COLOR <<  endl;
        }
    }

}

int main() {
    cout << Cyan "\t \t PRUEBA DE MATRICES \t \t" RESET_COLOR << endl;
    // Declaracion de variables y matrices
    int entregas[6][4] = {0}; // La matriz entregas representa las entregas de cada operador ([6]) de cada tipo ([4])
    int errores = 0;
    int fueraDeProduccion[6] = {0};
    entrada(entregas, errores, fueraDeProduccion);
    cout << endl;
    calcularGanancias(entregas);
    cout << endl;
    produccion(entregas, fueraDeProduccion);
}
