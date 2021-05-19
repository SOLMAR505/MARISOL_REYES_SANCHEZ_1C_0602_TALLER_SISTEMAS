#include<stdlib.h>
#include<stdio.h>

int main(){

char x;
char y;
char *p;
char *puntero;

p=&x;
puntero=&y;

x='x';

printf("la direccion de memoria de 'x' es: %p",&x);
printf("el contenido es: %c",*p);


*p=(*p) + 1;
printf("el contenido es: %c",*p);

*p=(*p) + 2;
printf("el contenido es: %c",*p);


y='y';
printf("la direccion de memoria de 'y' es: %p ",&y);
printf("el contenido es: %c \n",*puntero);

}