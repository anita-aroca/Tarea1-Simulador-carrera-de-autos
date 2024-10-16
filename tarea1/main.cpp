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
vector<int> posiciones;
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
void funcAutoAvanza(Auto& corredor, int M) {
    // Mientras el auto no haya alcanzado la meta (M metros)
    int posicionI = 1;
    while (corredor.distRec < M) {
        // Generar avance aleatorio entre 1 y 10 metros
        int avanza = funcRandom(1,  10);
        // Generar tiempo aleatorio entre 100 y 500 milisegundos
        int tiempo = funcRandom(100, 500);
        // Protege/Bloquea la variable a la que se accede.
        mtx.lock();
        corredor.distRec += avanza;
        cout << "Auto" << corredor.id << " avanza " << avanza << " metros (total: " << corredor.distRec << " metros)" << reset << endl;
        //Libera mutex después de imprimir
        mtx.unlock();

        // Si alcanza o supera la meta, termina la carrera.
        if(corredor.distRec >= M){
            cout << morao <<"¡Auto" << corredor.id << " ha terminado la carrera y en el lugar " << endl;
            posiciones.push_back(corredor.id); // Almacenar el ID del auto en el vector de posiciones
            break;
        }

        // Dormir el tiempo aleatorio generado
        sleep_for(milliseconds(tiempo));
    }
}

// Función principal
int main(int argc, char* argv[]) {
    // Si no se ingresan los argumentos necesarios, se muestra un mensaje de error.
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <distancia_total> <numero_autos>" << endl;
        return 1;
    }
    // Verificar que al menos se hayan ingresado 2 autos en la carrera:
    if (stoi(argv[2]) < 2) {
        cerr << "Se necesita al menos 2 autos para realizar una carrera." << endl;
        return 1;
    }
    // Verificar que la carrera tenga una distancia mayor a al menos 30 metros:
    if (stoi(argv[1]) < 30) {
        cerr << "La distancia de la carrera debe ser de al menos 30 metros." << endl;
        return 1;
    }

    // Se obtienen los argumentos ingresados por el usuario.
    int M = stoi(argv[1]); // Distancia total de la carrera
    int N = stoi(argv[2]); // Número de autos

    // Mostrar datos de cada auto a medida de que avanza
    cout << "Distancia total de la carrera: " << M << " metros" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Se crea un vector de autos
    Auto autos[N];

    // Se crean los hilos para cada auto
    thread hilo[N]; //-> Vector de N hilos
    vector<thread> hilos;
    for (int i = 0; i < N; ++i) {
        // Los identificadores de los autos se le sumarán 1 para que no comiencen en 0.
        autos[i].id = i + 1;
        // Invocar la función de los hilos para inicializarlos.
        hilos[i] = thread(funcAutoAvanza, ref(autos[i]), M);
    }

    // Se espera a que todos los hilos terminen
    for (auto& hebra : hilos) {
        hebra.join();
    }

    // Mostrar tabla de posiciones.
    cout << "\t=================================================================" << endl;
    cout << "\tLugar\tAuto" << endl;
    cout << "\t------------------------" << endl;
    for(int i = 0; i < N; i++) {
        cout << i + 1 << "\tAuto" << posiciones[i] << endl;
    }


    return 0;
}



