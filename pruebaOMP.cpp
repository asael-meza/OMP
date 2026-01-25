#include <iostream>
#include <omp.h> // Librería necesaria para el uso de funciones y directivas de OpenMP

// Definición de constantes para facilitar el mantenimiento del código
#define N 1000      // Cantidad total de elementos en los arreglos
#define chunk 100   // Tamaño de las porciones (chunks) de trabajo asignadas a cada hilo
#define mostrar 100  // Cantidad de elementos a mostrar en consola

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Declaración de arreglos y variable de control para el ciclo
    float a[N], b[N], c[N];
    int i;

    //// Inicialización de los arreglos de forma secuencial
    for (i = 0; i < N; i++)
    {
        a[i] = i * 1.5f; // Rellenamos 'a' con valores flotantes
        b[i] = (i + 2) * 2.0f; // Rellenamos 'b' con valores diferentes
    }

    int pedazos = chunk;

    /* Directiva de Paralelización:
       - 'parallel for': Indica que el siguiente ciclo 'for' se ejecutará en varios hilos.
       - 'shared': Las variables a, b, c y pedazos son compartidas entre todos los hilos.
       - 'private(i)': Cada hilo tiene su propia copia de la variable 'i' para evitar conflictos.
       - 'schedule(static, pedazos)': Divide el trabajo en bloques fijos del tamaño definido en 'pedazos'.
    */
#pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    // Este ciclo se ejecuta en paralelo según la configuración anterior.
    for (i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }

    // Impresión de resultados usando la función auxiliar
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c (resultado): " << std::endl;
    imprimeArreglo(c);

    return 0;
}

// Función para imprimir una cantidad limitada de elementos de un arreglo
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}