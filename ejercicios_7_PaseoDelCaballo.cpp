#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

/* Movimientos posibles:

horizontal[ 0 ] = 2 vertical[ 0 ] = -1
horizontal[ 1 ] = 1 vertical[ 1 ] = -2
horizontal[ 2 ] = -1 vertical[ 2 ] = -2
horizontal[ 3 ] = -2 vertical[ 3 ] = -1
horizontal[ 4 ] = -2 vertical[ 4 ] = 1
horizontal[ 5 ] = -1 vertical[ 5 ] = 2
horizontal[ 6 ] = 1 vertical[ 6 ] = 2
horizontal[ 7 ] = 2 vertical[ 7 ] = 1

*/

int intentarResolver();

int main(){
    int counter = 1;
    int flag = 1;
    while(flag == 1 && counter != 65){
        flag = 7;
        flag = intentarResolver();
        counter++;
        cout<<"=================================================================== INTENTO: "<<counter<<" ==================================================================="<<endl;
    }
    cout<<"Intentos: "<<counter<<endl;
    return 0;
}

int intentarResolver(){
    const int size_fila = 8;
    const int size_columna = 8;
    array<array<int, size_fila>, size_columna> tablero = {0};                                                    // Defino el array bidimensional que representa el tablero.
    array<array<int, size_fila>, size_columna> accesibilidad =
    {2, 3, 4, 4, 4, 4, 3, 2,
     3, 4, 6, 6, 6, 6, 4, 3,
     4, 6, 8, 8, 8, 8, 6, 4,
     4, 6, 8, 8, 8, 8, 6, 4,
     4, 6, 8, 8, 8, 8, 6, 4,
     4, 6, 8, 8, 8, 8, 6, 4,
     3, 4, 6, 6, 6, 6, 4, 3,
     2, 3, 4, 4, 4, 4, 3, 2,};                                                                                   // Heurística (o estrategia) para mover el caballo.

    array<int, size_fila> vertical = {-1,-2,-2,-1,1,2,2,1};
    array<int, size_columna> horizontal = {2,1,-1,-2,-2,-1,1,2};                                                 // Se definen mediante 2 arrays unidimensionales los 8 movimientos que realiza el caballo.

    static int iterador_vertical = 0;
    static int iterador_horizontal = 0;
    int fila_actual = iterador_vertical;                                                                         // Posicion inicial del caballo en sentido vertical.
    int columna_actual = iterador_horizontal;                                                                    // Posicion inicial del caballo en sentido horizontal.
    iterador_horizontal++;
    if(iterador_horizontal >= 8){
        iterador_vertical++;
        iterador_horizontal = 0;
    }
    if(iterador_vertical >= 8){
        iterador_vertical = 0;
    }

    int counter = 1;                                                                                             // Cuenta la cantidad de movimientos realizados.
    int numeroMovimiento = 0;                                                                                    // Variable usada para almacenar el movimiento elegido por el jugador.
    tablero[fila_actual][columna_actual] = counter;                                                              // Marca las casillas ya visitadas.
    accesibilidad[fila_actual][columna_actual] = 0;                                                              // Elimina la importancia simbolica de la heuristica.
    vector<int>invalidos(0,99);                                                                                  // Maneja los movimientos invalidos, negandolos, evita que se repita el mismo movimiento invalido.
    while (counter <= 64){
        cout<<"Posiciones validas: "<<endl<<endl;

        for (unsigned int x = 0 ; x < 8 ; x++){                                                                  // Comprobacion de posiciones disponibles mediante bucle.
            for (unsigned int y = 0 ; y < 8 ; y++){
                cout<<setw(3)<<tablero[x][y];
            }
            cout<<"                                  ";
            for (unsigned int z = 0 ; z < 8 ; z++){                                                              // Bucle para imprimir la heuristica (estrategia que sigue el caballo).
                cout<<setw(3)<<accesibilidad[x][z];
            }
            cout<<endl;
        }
        cout<<endl;

        cout<<"Posicion actual: "<<"["<<fila_actual<<"]"<<"["<<columna_actual<<"]"<<endl<<endl;                  // Muestra la posicion actual.
        int invalidacion = 0;
        int valor_heuristica = 9;
        numeroMovimiento = 0;                                                                                    // Es necesario reinicia numeroMovimiento, para que no guarde valores anteriores.
        for (unsigned int i = 0; i < 8; i++){                                                                    // Loop para elegir el mejor movimiento.
            invalidacion = 0;
            if (accesibilidad[fila_actual + (vertical[i])][columna_actual + (horizontal[i])] < valor_heuristica
                && (accesibilidad[fila_actual + (vertical[i])][columna_actual + (horizontal[i])]) >= 2){         // Toma el dato de la heuristica de los diferentes movimientos.
                cout<<"heuristica: "<<accesibilidad[fila_actual + (vertical[i])][columna_actual + (horizontal[i])]<<endl;
                for (auto &elemento : invalidos){
                    if (i == elemento){
                        cout<<"invalidacion: "<<i<<endl;
                        invalidacion = 77;
                    }
                }
                if (invalidacion != 77){
                    numeroMovimiento = i;                                                                         // Si la nueva posicion tiene mas valor que la anterior, se toma.
                    valor_heuristica = accesibilidad[fila_actual + (vertical[i])][columna_actual + (horizontal[i])];
                }
            }else if (accesibilidad[fila_actual + (vertical[i])][columna_actual + (horizontal[i])] == valor_heuristica){
                for (unsigned int j = 0; j < 8; j++){
                    invalidacion = 0;
                    if ((fila_actual + (vertical[i])) >= 0 && (columna_actual + (horizontal[i])) >= 0 &&
                        (fila_actual + (vertical[i])) < 8 && (columna_actual + (horizontal[i])) < 8 ){
                        if (accesibilidad[(fila_actual + vertical[i]) + vertical[j]][(columna_actual + horizontal[i]) + horizontal[j]] < valor_heuristica
                            && (accesibilidad[(fila_actual + vertical[i]) + vertical[j]][(columna_actual + horizontal[i]) + horizontal[j]]) >= 2){
                            cout<<"heuristica =: "<<accesibilidad[(fila_actual + vertical[i]) + vertical[j]][(columna_actual + horizontal[i]) + horizontal[j]]<<endl;
                            for (auto &elemento : invalidos){
                                if (i == elemento){
                                    cout<<"invalidacion: "<<i<<endl;
                                    invalidacion = 77;
                                }
                            }
                            if (invalidacion != 77){
                                numeroMovimiento = i;                                                                        // Si la nueva posicion tiene mas valor que la anterior, se toma.
                                valor_heuristica = accesibilidad[fila_actual + (vertical[i])][columna_actual + (horizontal[i])];
                            }
                        }
                    }
                }
            }
        }
        cout<<"Movimiento elegido: "<<numeroMovimiento<<endl;
        //cout<<"Haz tu movimiento: ";cin>>numeroMovimiento;                                                     // Pide al jugador elegir el siguiente movimiento.

        if ((fila_actual + (vertical[numeroMovimiento])) >= 0 && (columna_actual + (horizontal[numeroMovimiento])) >= 0 &&
            (fila_actual + (vertical[numeroMovimiento])) < 8 && (columna_actual + (horizontal[numeroMovimiento])) < 8 ){ // Condicion para que el jugador no se salga de los limites del tablero.

            if (tablero[fila_actual + vertical[numeroMovimiento]][columna_actual + horizontal[numeroMovimiento]] == 0){

                fila_actual += vertical[numeroMovimiento];                                                       // Establece la nueva posicion en sentido vertical.
                columna_actual += horizontal[numeroMovimiento];                                                  // Establece la nueva posicion en sentido horizontal.
                counter++;                                                                                       // Suma +1 al contador de movimientos.
                accesibilidad[fila_actual][columna_actual] = 0;                                                  // Elimina la importancia simbolica de la heuristica.
                invalidos.clear();
                tablero[fila_actual][columna_actual] = counter;                                                  // Marca las casillas ya visitadas.
                cout<<"Movimiento: "<<counter<<endl;                                                             // Muestra la cantidad de movimientos actuales.
                if(counter == 64){
                    tablero[fila_actual][columna_actual] = counter;
                    for (unsigned int x = 0 ; x < 8 ; x++){                                                                  // Comprobacion de posiciones disponibles mediante bucle.
                        for (unsigned int y = 0 ; y < 8 ; y++){
                            cout<<setw(3)<<tablero[x][y];
                        }
                        cout<<"                                  ";
                        for (unsigned int z = 0 ; z < 8 ; z++){                                                              // Bucle para imprimir la heuristica (estrategia que sigue el caballo).
                            cout<<setw(3)<<accesibilidad[x][z];
                        }
                        cout<<endl;
                    }
                    exit(0);
                    return 7;
                }
            }else{
                if (invalidos.size() == 8){
                    invalidos.clear();
                    return 1;
                }
                invalidos.push_back(numeroMovimiento);                                                               // Hacer que el siguiente movimiento sea diferente.
                continue;                                                                                        // La posicion ya fue utilizada, se omite este paso (no cuenta el contador) y se elige uno valido.
            }
        }else{                                                                                                   // En caso de que el movimiento nos saque del tablero, simplemente se intenta denuevo (el contador de movimientos no suma, simplemente el paso se omite).
            cout<<"Movimiento invalido !"<<endl<<endl;
            cout<<"Movimiento: "<<counter<<endl;
            if (invalidos.size() == 8){
                invalidos.clear();
                return 1;
            }
            invalidos.push_back(numeroMovimiento);                                                               // Hacer que el siguiente movimiento sea diferente.
            continue;                                                                                            // Omitimos este paso invalido.
        }

    }
}
