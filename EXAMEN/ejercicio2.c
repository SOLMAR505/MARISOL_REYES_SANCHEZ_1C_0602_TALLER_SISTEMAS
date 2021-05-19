#include<stdlib.h>
#include<stdio.h>

int main(){
char arrayChar [5];
int i = 0;

for (int caracter = 97; caracter < 102; caracter++){
	arrayChar[i] = caracter;
	i++;
}

char *punteroChar;
punteroChar = &arrayChar[1];

char *punteroCharDos;
punteroCharDos = $arrayChar[0];

printf("contenido [%c] arrayChar : %c ", arrayChar[0]);
printf("el contenido es: %c \n",*punteroChar);
printf("el contenido es: %c \n",*punteroCharDos);
printf("arrayChar[%c] : %c ", arrayChar[4]);
}