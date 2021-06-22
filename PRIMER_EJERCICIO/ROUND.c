#include<stdio.h>

int main(int n, char **args) {
	printf("\t-----ROUND ROBIN-----");
	int num_pro=11, procesos[10], quantum = 0, num_q = 0;
	double tiempo_promedio = 0;// tiempo promedio.
	int finalizado = 0;
	printf("\n NUMERO DE PROCESOS (%d)",num_pro);
	while (num_pro > 10 || num_pro <= 0) {
		printf("\n Ingrese el Numero de procesos menor al tamaño asignado = ", num_pro);
		scanf("%d", &num_pro);
		if(num_pro>10){
			printf(" \n ERROR NUMERO DE PROCESOS MAYOR AL INDICADO");
		}else{
			printf("\n TAMAÑO DE PROCESOS CORRECTO");
		}
	}
	// Se pide el tamaño de cada proceso
	for(int i=0; i<num_pro; i++) {
		printf("\n Ingresa el tiempo de rafaga del proceso %d = ", i+1);
		scanf("%d", &procesos[i]);
	}
	while (quantum <= 0) {
		printf("\n Tamaño de quantum:");
		scanf("%d", &quantum);
	}
	// Algoritmo
	while(finalizado == 0) {
		finalizado = 1;// Sí finalizado
		printf("\nORDEN DE ATENCION \tPROCESOS ATENDIDOS Y/O TERMINADOS \t");
		for(int i=0; i<num_pro; i++) {
			if(procesos[i] > 0) {
				procesos[i] -= quantum;
				num_q++;
				printf("\n Quantum = [%d]\t\t\tProceso %d",num_q, i+1);
				if (procesos[i]>0) {
					finalizado = 0; //No finalizado
				} else {
					tiempo_promedio += num_q*quantum;
				}
			}
		}
	}
	tiempo_promedio = tiempo_promedio / num_pro;
	printf("\n\n Tiempo promedio de los procesos %f ", tiempo_promedio);
	return 0;
}
