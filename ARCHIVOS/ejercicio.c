#include <stdio.h>
#include <string.h>
// Debe ser de la máxima + 1. Por ejemplo, si la máxima es 4, defínela como 5
#define MAXIMA_LONGITUD_CADENA 1000
// Las palabras que contiene el archivo
#define CANTIDAD_PALABRAS 20
#define NOMBRE_ARCHIVO "lista.txt"

// Implementación del método de la burbuja en C, para arreglos de cadenas
void burbuja(char arreglo[CANTIDAD_PALABRAS][MAXIMA_LONGITUD_CADENA])
{
    int longitud = CANTIDAD_PALABRAS;
    // Útil para hacer intercambio de cadenas
    char temporal[MAXIMA_LONGITUD_CADENA];
    int x, indiceActual;
    for (x = 0; x < longitud; x++)
    {
        for (indiceActual = 0; indiceActual < longitud - 1;
             indiceActual++)
        {
            int indiceSiguienteElemento = indiceActual + 1;
            // Si la cadena es menor que la siguiente (alfabeticamente) entonces intercambiamos
            if (strcmp(arreglo[indiceActual], arreglo[indiceSiguienteElemento]) <= 0)
            {
                // Movemos la cadena actual a la temporal
                memcpy(temporal, arreglo[indiceActual], MAXIMA_LONGITUD_CADENA);
                // Movemos al actual el siguiente elemento
                memcpy(arreglo[indiceActual], arreglo[indiceSiguienteElemento], MAXIMA_LONGITUD_CADENA);
                // Y en el siguiente elemento, lo que había antes en el actual pero ahora está en temporal
                memcpy(arreglo[indiceSiguienteElemento], temporal, MAXIMA_LONGITUD_CADENA);
            }
        }
    }
    // No hay necesidad de devolver nada, pues modificamos al arreglo de manera interna
}

int main()
{
    // Arreglo de cadenas: aquí almacenamos todas las palabras
    char palabras[CANTIDAD_PALABRAS][MAXIMA_LONGITUD_CADENA];
    // Útil para leer el archivo
    char buferArchivo[MAXIMA_LONGITUD_CADENA];
    // Abrir el archivo...
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo");
        return 0;
    }
    // Necesitamos este ayudante para saber en qué línea vamos
    int indice = 0;
    // Mientras podamos leer una línea del archivo
    while (fgets(buferArchivo, MAXIMA_LONGITUD_CADENA, archivo))
    {
        // Remover salto de línea
        strtok(buferArchivo, "\n");
        // Copiar la línea a nuestro arreglo, usando el índice
        memcpy(palabras[indice], buferArchivo, MAXIMA_LONGITUD_CADENA);
        // Aumentarlo en cada iteración
        indice++;
    }

    // Terminamos de leer
    fclose(archivo);
    // Ahora ya tenemos el arreglo. Vamos a ordenarlo.
    // La función no devuelve nada, pues modifica al arreglo de manera interna
    burbuja(palabras);
    // Lo que resta ahora es imprimir, pues ya tenemos el arreglo ordenado
    int i;
    for (i = 0; i < CANTIDAD_PALABRAS; i++)
    {
        printf("%s\n", palabras[i]);
    }
    return 0;
}