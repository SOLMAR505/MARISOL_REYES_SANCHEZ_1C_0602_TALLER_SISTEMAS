#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Debe ser de la máxima + 1. Por ejemplo, si la máxima es 4, defínela como 5
#define MAXIMA_LONGITUD_CADENA 1000
// Las palabras que contiene el archivo
#define CANTIDAD_PALABRAS 500
#define TAM 25
#define NOMBRE_ARCHIVO "aux.txt"
typedef struct nodo{
char valor[TAM];
struct nodo *siguiente;
}tiponodo;
typedef tiponodo *pnodo;
typedef tiponodo *lista;
void insertar(lista *l,char p[TAM]);
void borrar(lista *l,int v);
int listavacia(lista l);
void borrarlista(lista *);
void mostrarlista(lista l);
void burbuja(char arreglo[][MAXIMA_LONGITUD_CADENA],int longitud);

// Implementación del método de la burbuja en C, para arreglos de cadenas
void burbuja(char arreglo[][MAXIMA_LONGITUD_CADENA],int longitud)
{
    // Útil para hacer intercambio de cadenas
    char temporal[MAXIMA_LONGITUD_CADENA];
    int x, indiceActual;
    for (x = 0; x < longitud; x++)
    {
        for (indiceActual = 0; indiceActual < longitud - 1;
             indiceActual++)
        {
            int indiceSiguienteElemento = indiceActual + 1;
            // Si la cadena es mayor que la siguiente (alfabeticamente) entonces intercambiamos
           if (strcmp(arreglo[indiceActual], arreglo[indiceSiguienteElemento]) > 0)
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
void main(int argc,char *argv[])
{
    lista lista=NULL;
    FILE *archi;
    FILE *aux;
    char linea[TAM];
     archi=fopen("lista.txt","r+");
    aux=fopen("aux.txt","w+");
    printf("\n ----------Cadenas a insertar --------\n ") ;
    int v=0;
  
    while(!feof(archi)&&!ferror(archi))
    {
     
        fscanf(archi,"%s",linea);
        fputs(linea,aux);
        fputs("\n",aux);
         puts(linea);
        insertar(&lista,linea);
    }
     fclose(archi);
     fclose(aux);
     mostrarlista(lista);
     borrarlista(&lista);

    printf("\n\t--------- LISTA ORDENADA------------\n\n");
    // Arreglo de cadenas: aquí almacenamos todas las palabras
    char palabras[CANTIDAD_PALABRAS][MAXIMA_LONGITUD_CADENA];
    // Útil para leer el archivo
    char buferArchivo[MAXIMA_LONGITUD_CADENA];
    // Abrir el archivo...
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r+");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo");
        
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
    int longitud=sizeof(palabras)/sizeof(palabras[0]);
    burbuja(palabras,longitud);
    int i=0;
    int s=CANTIDAD_PALABRAS-indice;
    for (i =s; i < longitud-1; i++)
    {
        printf("%s\n", palabras[i]);
    }
}

//metodos
void insertar(lista *lista,char p[TAM])
{
 pnodo nuevo,anterior;

 nuevo=(pnodo)malloc(sizeof(tiponodo));
 strcpy(nuevo->valor,p);

 if(listavacia(*lista))
 {
 nuevo->siguiente=*lista;
 *lista=nuevo;
 }
 else
 {
  anterior=*lista;
  while(anterior->siguiente)
      anterior=anterior->siguiente;
 nuevo->siguiente=anterior->siguiente;
  anterior->siguiente=nuevo;
 }
}
void borrarlista(lista *lista)
{
  pnodo nodo;
  while(*lista)
  {
     nodo=*lista;
     *lista=nodo->siguiente;
     free(nodo);
  }
}
int listavacia(lista lista)
{
   return(lista==NULL);
}

void mostrarlista(lista lista)
{
  pnodo nodo=lista;
  if(listavacia(lista))
       printf("lista vacia");
  else
  {
    printf("\n\t--------- LISTA NO ORDENADA------------\n\n");
    while(nodo)
    {
       printf("%s \n",nodo->valor);
       nodo=nodo->siguiente;
       
    int a=0;

    }
  }
}