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
using namespace chrono;
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




int main(int argc, char argv)
{
    cout << "Hello, World!" << endl;
    return 0;
}


/*TODO: En cada iteración, cada distancia avanzada por un auto es un número aleatorio entre 1 y 10 (metros), igual que la velocidad
 * que cambia entre 100-500 ms. Se debe ir guardando la velocidad que avanza cada auto para luego mostrar un total de
 * metros avanzados cada vez que un auto determinado avance.
*/



