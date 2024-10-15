/* Autores:
 * Ana Aroca Sanhueza
 * Javier González Catalán
*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <random>

using namespace std; // cout endl
using namespace chrono; //tiempo, unidades de medida
using namespace this_thread;
std::mutex mtx;
//#define verde "\033[32m" :v
#define morao "\033[35m"
#define reset "\033[0m"


// Definir un auto:
struct Auto{
    int id = 0;
    int distRec = 0;

};

// Función para randomizar valores
int funcRandom(int a, int b) {
    random_device rd;
    uniform_int_distribution range(a, b);
    return range(rd);
}

// Función para avanzar un auto
void avanzarAuto(Auto& corredor, int M) {
    // Mientras el auto no haya alcanzado la meta (M metros)
    while (corredor.distRec < M) {
        // Generar avance aleatorio entre 1 y 10 metros
        int avanza = funcRandom(1,  10);
        // Generar tiempo aleatorio entre 100 y 500 milisegundos
        int tiempo = funcRandom(100, 500);
        // Protege/Bloquea la impresión con un mutex para evitar colisiones en la salida
        mtx.lock();
        corredor.distRec += avanza;
        cout << morao << "Auto" << corredor.id << " avanza " << avanza << " metros (total: " << corredor.distRec << " metros)" << reset << endl;
        //Libera mutex después de imprimir
        mtx.unlock();

        // Si alcanza o supera la meta, termina la carrera.
        if (corredor.distRec >= M) {
            cout << morao <<"¡Auto" << corredor.id << " ha terminado la carrera!" << endl;
            break;
        }

        // Dormir el tiempo aleatorio generado
        sleep_for(milliseconds(tiempo));
    }
}

// Función principal
int main(int argc, char* argv[]) {
    cout << morao << "Hello, World!" << reset << endl;
    return 0;
}


/*TODO: En cada iteración, cada distancia avanzada por un auto es un número aleatorio entre 1 y 10 (metros), igual que la velocidad
 * que cambia entre 100-500 ms. Se debe ir guardando la velocidad que avanza cada auto para luego mostrar un total de
 * metros avanzados cada vez que un auto determinado avance.
*/



