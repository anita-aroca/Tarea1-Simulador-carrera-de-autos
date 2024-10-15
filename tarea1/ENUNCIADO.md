# DEPARTAMENTO DE SISTEMAS DE INFORMACIÓN

## Sistemas Operativos

### Tarea 1: Simulador carrera de autos.

#### Objetivos

- Reforzar conceptos básicos de procesos/hebras, comunicación entre procesos y sincronización.
- Implementar un programa que permita aplicar conceptos de concurrencia y paralelismo mediante el uso de hebras.

#### Descripción

Se solicita simular una carrera de autos utilizando programación multihebras. Cada automóvil competidor correrá en una hebra distinta. La carrera consiste en que cada auto recorrerá una distancia de **M** metros en intervalos de tiempo aleatorios.

Cada automóvil:

- Tendrá un identificador único (ej: Auto1, Auto2, etc.).
- Avanzará una cantidad aleatoria de metros en cada iteración.
- Se detendrá por un tiempo aleatorio (representando la velocidad aleatoria del auto) en cada iteración.

La carrera finalizará cuando todos los autos hayan terminado el recorrido.

Deberá implementar la simulación en **C++** (compilador GNU g++ std=c++11 o superior) utilizando la biblioteca estándar de hebras (`thread`). El programa deberá mostrar el progreso de cada auto en la terminal y los resultados finales.

#### Requisitos:

- Utilizar la biblioteca `thread` de **C++** para manejar las hebras (cada auto en una hebra separada).
- Por cada auto y en cada iteración, calcular un valor aleatorio para la distancia que avanza (máximo de 10 metros) y cambia la velocidad (entre 100-500 ms).
- Mostrar el avance de cada auto en tiempo real en la terminal.
- La carrera debe tener un ganador y mostrar el orden de llegada.
- La distancia total en metros (**M**) de la carrera y el número de autos (**N**) se deben indicar como parámetros al iniciar la carrera.

#### Ejemplo de salida por la terminal (carrera de M=100 metros con N=3 autos):

\`\`\` bash
$ ./carrera 100 3

Distancia total carrera: 100 metros
------------------------------
Auto2 avanza 7 metros (total: 7 metros)
Auto1 avanza 10 metros (total: 10 metros)
Auto0 avanza 10 metros (total: 10 metros)
Auto1 avanza 2 metros (total: 12 metros)
Auto2 avanza 3 metros (total: 10 metros)
Auto0 avanza 1 metros (total: 11 metros)
...
Auto0 avanza 7 metros y termina la carrera en el lugar 1!
Auto1 avanza 10 metros (total: 87 metros)
Auto2 avanza 4 metros (total: 93 metros)
Auto1 avanza 10 metros (total: 97 metros)
Auto1 avanza 7 metros y termina la carrera en el lugar 2!
Auto2 avanza 5 metros (total: 98 metros)
Auto2 avanza 6 metros y termina la carrera en el lugar 3!

Lugar Auto
------------
1 Auto0
2 Auto1
3 Auto2
\`\`\`

Al revisar los procesos en el sistema mientras la carrera está en curso se debería poder ver el proceso con sus 3 hebras (vista utilizando `htop`)

#### Consideraciones

- El programa debe correr en equipos con sistema operativo Linux.
- Debe utilizar el lenguaje de programación **C++** y el compilador **GNU g++**.
- Debe utilizar un archivo **Makefile** para la compilación mediante el comando `make`.
- No olvidar un archivo **README** con las instrucciones para compilar y ejecutar el programa.
- El programa debe estar bien documentado y utilizar nombres descriptivos de variables, funciones, métodos, etc.
- La tarea es en parejas.
- El programa debe compilar para ser revisado, de lo contrario será considerado como **NCR**. Realice pruebas del programa en distintos equipos.

#### Entrega

- Debe subir a la plataforma moodle un enlace al proyecto/repositorio alojado en alguna plataforma de gestión de proyectos informáticos como **Gitlab**, **Github**, **Bitbucket**, etc.
- Para la revisión de la tarea se considerará la fecha/hora del último commit realizado.
