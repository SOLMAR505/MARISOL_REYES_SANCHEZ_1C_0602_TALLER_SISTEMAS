#include <stdio.h>
#include <string.h>
// Las palabras que contiene el archivo
#define TAM_NOMBRE 100
// Debe ser de la máxima + 1. Por ejemplo, si la máxima es 4, defínela como 5
#define MAXIMA_LONGITUD_CADENA 10000

int existe_archivo(char *nombre_arch);
int crear_archivo(char *nombre_arch);
void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch);
FILE *abrir_Archivo_lectura_escritura(char *nombre_arch);
int tiene_datos_arch(char *nombre_arch);
FILE *abrir_Archivo_solo_Lectura(char *nombre_arch);
void imprimir_vector(int vector[], int tam);
void burbuja(char arreglo[][TAM_NOMBRE], int longitud);
int total_numeros_Arch(char *nombre_arch);

int main(int argc, char const *argv[]){     
    char inputNombre[TAM_NOMBRE];
    char outputNombre[TAM_NOMBRE];
    int contador = 0;
    char buferarchivo[30];
    int existe_arch = 0;    
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    if (argc > 2 && argc <= 3){
        strcpy(inputNombre, argv[1]);
        strcpy(outputNombre, argv[2]);
        printf("Cantidad de argumentos: %i\n", argc);
        printf("bin = %s\n", argv[0]);
        printf("Argumento 1: %s\n", inputNombre);
        printf("Argumento 2: %s\n", outputNombre);
    } else{
        printf("Agrega dos argumentos antes de la ejecución del programa!\n");
        printf("\t-> Primer argumento - Archivo a Leer\n");
        printf("\t\t-> Segundo argumento - Archivo a Escribir!\n");
    }
//verificar si existe el archivo o no
    existe_arch = existe_archivo(inputNombre);
        if(existe_arch){
            printf("--------------------------------------------------\n");
            printf("\tEl archivo -> %s <- YA EXISTE.\n", inputNombre);
            }
        else{
            printf("---------------------------------------------------------------\n");
            printf("\tEl archivo -> %s <- NO EXISTE.\n", inputNombre);
            printf("---------------------------------------------------------------\n");            
            if(crear_archivo(inputNombre)){
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("\tEl archivo -> %s <- Fue creado EXITOSAMENTE.\n", inputNombre);    
            return -1;
            }
            else{
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("\tEl archivo -> %s <- NO pudo crearse.\n", inputNombre);            
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
            return -1;
        }

    if(tiene_datos_arch(inputNombre)){
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("\tEL ARCHIVO -> %s <-TIENE DATOS.\n", inputNombre);     
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("\n------------------------------> LECTURA <----------------------------------\n");                
        inputFile = abrir_Archivo_solo_Lectura(inputNombre);
        if(inputFile == NULL){
            printf("****************************************************************\n");
            printf("\tEl archivo -> %s <- NO pudo Abrirse.\n", inputNombre);            
            printf("****************************************************************\n");
        }
        else{
            printf("****************************************************************\n");
            printf("\tArchivo -> %s <- Abierto Correctamente.\n", inputNombre);         
            printf("****************************************************************\n");
            // equivalente a la función scanf()
            fscanf(inputFile, "%s", buferarchivo);
            while(!feof(inputFile)){
                printf("%s\n", buferarchivo);
                fscanf(inputFile, "%s",buferarchivo);
                contador++;
            } 
            printf("\nTotal de palabras leídas: %d\n", contador);
            char palabras[contador+1][TAM_NOMBRE];
            cerrar_archivo(inputFile, inputNombre);
   
            inputFile = abrir_Archivo_solo_Lectura(inputNombre);
            contador = 0;
            fscanf(inputFile, "%s", buferarchivo);
            memcpy(palabras[contador], buferarchivo, TAM_NOMBRE);
            while(!feof(inputFile)){
                contador++;
                fscanf(inputFile, "%s", buferarchivo);
                memcpy(palabras[contador], buferarchivo, TAM_NOMBRE);
            }
            cerrar_archivo(inputFile, inputNombre);

        
            printf("\nImprimiendo arreglo sin ordenar\n");
            int i;
            for (i = 0; i < contador; i++){
                printf("%d.  %s\n", i, palabras[i]);
            }
            burbuja(palabras, contador);

            printf("\nImprimirendo arreglo ordenado\n");
            for (i = 0; i < contador; i++){
                printf("%d. %s\n", i, palabras[i]);
            }
        }              
            printf("\t Total de palabras leidas = %d\n\n", contador);                    
            printf("---------------------------------------------------------------------------\n");
            printf("\t---> LECTURA TERMINADA <---\n");                  
    }else{
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("\tEL ARCHIVO -> %s <- NO TIENE DATOS.\n", inputNombre);
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        return -1;
    }           
    printf("\n");       
    return 0;

}

void burbuja(char arreglo[][TAM_NOMBRE], int longitud){
    // Arreglo temporal para el intercamio de las cadenas
    char temporal[TAM_NOMBRE];

    int i, iActual;
    for (i = 0; i < longitud; i++){
        for (iActual = 0; iActual < longitud - 1; iActual++){
            int iSig = iActual + 1;

            // Si la cadena es mayor que la siguiente (alfabeticamente) entonces intercambian
            if (strcmp(arreglo[iActual], arreglo[iSig]) > 0){
                // Mueve la cadena actual a a temporal
                memcpy(temporal, arreglo[iActual], TAM_NOMBRE);
                // Mueve al actual el siguiente elemento
                memcpy(arreglo[iActual], arreglo[iSig], TAM_NOMBRE);
                // El siguiente elemento, lo que había antes en el actual ahora está en el temporal
                memcpy(arreglo[iSig], temporal, TAM_NOMBRE);
            }
        }
    }
    // No se devuelve anda
}

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

