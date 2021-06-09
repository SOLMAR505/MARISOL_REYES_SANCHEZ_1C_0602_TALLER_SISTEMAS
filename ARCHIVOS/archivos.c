#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Las palabras que contiene el archivo
#define TAM_NOMBRE 100
// Debe ser de la máxima + 1. Por ejemplo, si la máxima es 4, defínela como 5
#define MAXIMA_LONGITUD_CADENA 10000

FILE *inputFile = NULL;
FILE *outputFile = NULL;
int existe_archivo(char *nombre_arch);
int crear_archivo(char *nombre_arch);
void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch);
FILE *abrir_Archivo_lectura_escritura(char *nombre_arch);
int tiene_datos_arch(char *nombre_arch);
FILE *abrir_Archivo_solo_Lectura(char *nombre_arch);
void burbuja(char arreglo[][TAM_NOMBRE], int longitud);
int total_numeros_Arch(char *nombre_arch);

// Implementación del método de la burbuja en C, para arreglos de cadenas
void burbuja(char arreglo[][TAM_NOMBRE], int longitud){
    // Arreglo temporal para el intercamio de las cadenas
    char temporal[TAM_NOMBRE];

    int i, iActual;
    for (i = 0; i < longitud; i++){
        for (iActual = 0; iActual < longitud - 1; iActual++){
            int iSig = iActual + 1;

            // Si la cadena es menor que la siguiente (alfabeticamente) entonces intercambiamos
            if (strcmp(arreglo[iActual], arreglo[iSig]) > 0){
                // Movemos la cadena actual a la temporal
                memcpy(temporal, arreglo[iActual], TAM_NOMBRE);
                // Movemos al actual el siguiente elemento
                memcpy(arreglo[iActual], arreglo[iSig], TAM_NOMBRE);
               // Y en el siguiente elemento, lo que había antes en el actual pero ahora está en temporal
                memcpy(arreglo[iSig], temporal, TAM_NOMBRE);
            }
        }
    }
    // No hay necesidad de devolver nada, pues modificamos al arreglo de manera interna
}


int main(int argc, char const *argv[]){     
    char ingresar[TAM_NOMBRE];
    char salida[TAM_NOMBRE];
    int contador = 0;
    char buferarchivo[30];
    int existe_arch = 0;    


    if (argc > 2 && argc <= 3){
        strcpy(ingresar, argv[1]);
        strcpy(salida, argv[2]);
        printf("Cantidad de argumentos: %i\n", argc);
        printf("programa = %s\n", argv[0]);
        printf("Argumento 1: %s\n", ingresar);
        printf("Argumento 2: %s\n", salida);
    } else{
        printf("Agrega dos argumentos antes de la ejecución del programa!\n");
    }
//verificar si existe el archivo o no
    existe_arch = existe_archivo(ingresar);
        if(existe_arch){
            printf("--------------------------------------------------\n");
            printf("\tEl archivo -> %s <- YA EXISTE.\n", ingresar);
            printf("--------------------------------------------------\n");
            }
        else{
            printf("---------------------------------------------------------------\n");
            printf("\tEl archivo -> %s <- NO EXISTE.\n", ingresar);
            printf("---------------------------------------------------------------\n");            
            if(crear_archivo(ingresar)){
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("\tEl archivo -> %s <- Fue creado EXITOSAMENTE.\n", ingresar);    
            }
            else{
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("\tEl archivo -> %s <- NO pudo crearse.\n", ingresar);            
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
        }
//se verifica si tiene DATOS y PERMITE ABRIR EL ARCHIVO
    if(tiene_datos_arch(ingresar)){
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("\tEL ARCHIVO -> %s <-TIENE DATOS.\n", ingresar);     
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("\n------------------------------> LECTURA <----------------------------------\n");                
        inputFile = abrir_Archivo_solo_Lectura(ingresar);
        if(inputFile == NULL){
            printf("****************************************************************\n");
            printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", ingresar);            
            printf("****************************************************************\n");
        }
        else{
            printf("****************************************************************\n");
            printf("\tArchivo -> %s <- Abierto Correctamente.\n", ingresar);         
            printf("****************************************************************\n");
            // equivalente a la función scanf()
            fscanf(inputFile, "%s", buferarchivo);
            while(!feof(inputFile)){
                printf("%s\n", buferarchivo);
                fscanf(inputFile, "%s",buferarchivo);
                contador++;
            } 
            char palabras[contador+1][TAM_NOMBRE];
            cerrar_archivo(inputFile, ingresar);
   
            inputFile = abrir_Archivo_solo_Lectura(ingresar);
            contador = 0;
            fscanf(inputFile, "%s", buferarchivo);
            memcpy(palabras[contador], buferarchivo, TAM_NOMBRE);
            while(!feof(inputFile)){
                contador++;
                fscanf(inputFile, "%s", buferarchivo);
                memcpy(palabras[contador], buferarchivo, TAM_NOMBRE);
            }
            cerrar_archivo(inputFile, ingresar);

        
            printf("\n----ARREGLO SIN ORDENAR----\n");
            int i;
            for (i = 0; i < contador; i++){
                printf("%d.  %s\n", i, palabras[i]);
            }
            burbuja(palabras, contador);

            printf("\n-----LISTA ORDENADA ALFABETICAMENTE----\n");
            for (i = 0; i < contador; i++){
                printf("%d. %s\n", i, palabras[i]);
            }
        }                                  
            printf("---------------------------------------------------------------------------\n");
            printf("\t---> LECTURA TERMINADA <---\n");                  
    }else{
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("\tEL ARCHIVO -> %s <- NO TIENE DATOS.\n", ingresar);
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    }           
    printf("\n");       
    return 0;

}
//METODOS PARA ABRIR ARCHIVO TXT
int total_numeros_Arch(char *nombre_arch){
    int lee_linea = 0, contador = 0;
    FILE *ptrArchivo;
    ptrArchivo = abrir_Archivo_solo_Lectura(nombre_arch);
    if(ptrArchivo == NULL){
        printf("El archivo -> %s <- NO se pudo abrir desde total_numeros().\n", nombre_arch);                   
    }
    else{
        printf("Archivo -> %s <- abierto desde total_numeros().\n", nombre_arch);
        // leo si hay datos
        fscanf(ptrArchivo, "%d", &lee_linea);
        // mientras no sea fin de archivo.
        while(!feof(ptrArchivo)){
            contador++;
            // leo si hay datos
            fscanf(ptrArchivo, "%d", &lee_linea);           
        }
        cerrar_archivo(ptrArchivo, nombre_arch);
    }
    return contador;
}

int tiene_datos_arch(char *nombre_arch){
    int hay_Datos = 0;
    FILE *ptrArchivo;
    int lee_linea = 0, contador = 0;
    ptrArchivo = abrir_Archivo_solo_Lectura(nombre_arch);
    if(ptrArchivo == NULL){
        printf("El archivo -> %s <- NO se pudo abrir desde tiene_datos_arch().\n", nombre_arch);            
        hay_Datos = 0;
    }
    else{
        printf("Archivo -> %s <- abierto desde tiene_datos_arch().\n", nombre_arch);
        // leo si hay datos
        fscanf(ptrArchivo, "%d", &lee_linea);
        // mientras no sea fin de archivo.
        while(!feof(ptrArchivo)){
            contador++;
            // leo si hay datos
            fscanf(ptrArchivo, "%d", &lee_linea);
            if(contador > 0){
                hay_Datos = 1;
                break;
            }
        }
        cerrar_archivo(ptrArchivo, nombre_arch);
    }   
    return hay_Datos;
}

FILE *abrir_Archivo_solo_Lectura(char *nombre_arch){
    FILE *ptrArchivo;
    ptrArchivo = fopen(nombre_arch, "r");
    if( ptrArchivo == NULL ){
        // con r Abre un archivo para lectura.
        printf("---> El archivo -> %s <- NO pudo abrirse (uso de r).\n", nombre_arch);
    }   
    else{
        printf("---> Archivo -> %s <- Abierto (uso de r).\n", nombre_arch);
    }
    return ptrArchivo;
}

FILE *abrir_Archivo_lectura_escritura(char *nombre_arch){
    FILE *ptrArchivo;
    ptrArchivo = fopen(nombre_arch, "r+");
    if( ptrArchivo == NULL ){
        // con r+ Abre un archivo para actualización (lectura y escritura).
        printf("---> El archivo -> %s <- NO pudo abrirse (uso de r+).\n", nombre_arch);
    }   
    else{
        printf("---> Archivo -> %s <- Abierto (uso de r+).\n", nombre_arch);
    }
    return ptrArchivo;
}

int existe_archivo(char *nombre_arch){
    FILE *ptrArchivo;
    int existe = 0;
    // Con r abre un archivo para lectura.
    ptrArchivo = fopen(nombre_arch, "r");
    if( ptrArchivo != NULL ){
        existe = 1;
        cerrar_archivo(ptrArchivo, nombre_arch);
    }   
    return existe;
}

int crear_archivo(char *nombre_arch){
    int creado = 0;
    FILE *ptrArchivo;
    ptrArchivo = fopen(nombre_arch, "w");
    if( ptrArchivo == NULL ){
        // con w crea un archivo para escritura. Si el archivo ya existe, descarta el contenido actual.
        printf("----> El archivo -> %s <- no pudo crearse (abrir; uso de w).\n", nombre_arch);
    }   
    else{
        creado = 1;
        printf("----> Archivo -> %s <- Creado (abierto; uso de w).\n", nombre_arch);
        cerrar_archivo(ptrArchivo, nombre_arch);
    }
    return creado;
}

void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch){
    fclose(ptrArchivo);
    printf("----> Archivo -> %s <- Cerrado Correctamente.\n", nombre_arch);
}

