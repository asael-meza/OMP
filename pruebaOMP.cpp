#include <iostream>
#include <omp.h> // Uso de OpenMP

// Constantes 
#define N 1000      // Elementos en los arreglos
#define chunk 100   // Tamaño de los chunks asignados a cada hilo
#define mostrar 100  // Elementos a mostrar en consola

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Arreglos y variable de control para el ciclo
    float a[N], b[N], c[N];
    int i;

    //// Arreglos de forma secuencial
    for (i = 0; i < N; i++)
    {
        a[i] = i * 1.5f; // Rellenamos 'a' con flotantes
        b[i] = (i + 2) * 2.0f; // Rellenamos 'b'
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

    // Impresión de resultados
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c (resultado): " << std::endl;
    imprimeArreglo(c);

    return 0;
}

// Imprime una cantidad limitada de elementos de un arreglo
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}