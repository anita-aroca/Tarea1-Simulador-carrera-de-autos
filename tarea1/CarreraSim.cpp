/** Autores:
 * Ana Aroca Sanhueza
 * Javier González Catalán
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <random>

using namespace std; // cout, endl
using namespace chrono; // tiempo, unidades de medida
using namespace this_thread;
using namespace std::chrono;

mutex mtx;
vector<int> posiciones; // Vector para almacenar las posiciones de llegada de los autos

const string morao = "\033[35m";
const string reset = "\033[0m";
const string rojo = "\033[31m";

// Definir un auto:
struct Auto{
    int id = 0;
    int distRec = 0;
};

// Función para randomizar valores
int funcRandom(int a, int b){
    random_device rd;
    uniform_int_distribution<int> range(a, b);
    return range(rd);
}

// Función para avanzar un auto
void funcAutoAvanza(Auto& corredor, int M){
    while(corredor.distRec < M){
        // Generar avance aleatorio entre 1 y 10 metros
        int avanza = funcRandom(1, 10);

        // Calcular cuántos metros faltan para llegar a la meta
        int distanciaRestante = M - corredor.distRec;

        // Si el avance es mayor que la distancia restante, ajusta el avance
        if(avanza > distanciaRestante){
            avanza = distanciaRestante;
        }

        // Generar tiempo aleatorio entre 100 y 500 milisegundos
        int tiempo = funcRandom(100, 500);

        // Bloquear el mutex para modificar la distancia recorrida y mostrar información
        mtx.lock();
        corredor.distRec += avanza;
        cout << "Auto " << corredor.id << " avanza " << avanza << " metros (total: " << corredor.distRec << " metros)" << endl;
        mtx.unlock();
        // Si alcanza o supera la meta, termina la carrera
        // Si alcanza o supera la meta, termina la carrera
        if(corredor.distRec >= M){
            // Bloquear el mutex para modificar el vector de posiciones y mostrar el mensaje
            mtx.lock();
            posiciones.push_back(corredor.id); // Almacenar el ID del auto en el vector de posiciones
            size_t posicion = posiciones.size(); // La posición es el tamaño actual del vector
            cout << morao << "¡Auto " << corredor.id << " ha terminado la carrera y en el lugar " << posicion << "!" << reset << endl;
            mtx.unlock();
        }

        // Dormir el tiempo aleatorio generado
        sleep_for(milliseconds(tiempo));
    }
}


// Función principal
int main(int argc, char* argv[]){
    if (argc != 3){
        cerr << rojo << "Uso: " << argv[0] << " <distancia_total> <numero_autos>" << reset <<endl;
        return 1;
    }

    int M = stoi(argv[1]); // Distancia total de la carrera
    int N = stoi(argv[2]); // Número de autos

    // Verificaciones de entrada
    if(N < 2){
        cerr << rojo << "Se necesita al menos 2 autos para realizar una carrera." << reset <<endl;
        return 1;
    }
    if(M < 30){
        cerr << rojo <<"La distancia de la carrera debe ser de al menos 30 metros." << reset <<endl;
        return 1;
    }

    // Mostrar información de la carrera
    cout << "Distancia total de la carrera: " << M << " metros" << endl;
    cout << "---------------------------------------------------" << endl;

    // Crear autos y hilos
    Auto autos[N];
    vector<thread> hilos;

    for(int i = 0; i < N; ++i){
        autos[i].id = i + 1;
        hilos.emplace_back(funcAutoAvanza, ref(autos[i]), M);
    }

    // Esperar a que todos los hilos terminen
    for(auto& hebra: hilos){
        hebra.join();
    }

    // Mostrar tabla de posiciones
    cout << "===========================================" << endl;
    cout << "\tLugar\tAuto" << endl;
    cout << "-------------------------------------------" << endl;
    for(size_t i = 0; i < posiciones.size(); ++i){
        cout << "\t" << i + 1 << "\tAuto " << posiciones[i] << endl;
    }
    return 0;
}
