/*
* Includes del sistema
*/
//#include <socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8087 
#define MAX 1024 
#define ip "127.0.0.1"
    int Socket_Servidor; 			/* descriptor para el socket */
	int NuevoSocket;
	struct sockaddr_in newAddr; 	/* direccion IP y numero de puerto del cliente */
    struct sockaddr_in serverAddr; 	/* direccion IP y numero de puerto local */
	socklen_t addr_size;
	char Paquete[MAX];
	char *p;
	void Servidor();

/*
*	Abre socket servidor UNIX. Se le pasa el servicio que se desea atender 
* Devuelve el descritor del socket servidor
*/
int main(int argc, char *argv[]){	
	Servidor();
}
void Servidor(){
	/* se crea el socket */
 	Socket_Servidor=socket(PF_INET,SOCK_STREAM,0);
	if(Socket_Servidor<0){
		printf("El servidor no fue creado\n");
		exit (-1);
	}else{
		printf("\t\tEL SERVIOR SE HA CREADO\n");

		memset(&serverAddr,'\0',sizeof(serverAddr));//COPIAR 

		
		serverAddr.sin_family=AF_INET;
		serverAddr.sin_port=htons(PORT);
		serverAddr.sin_addr.s_addr=inet_addr(ip);

		//Avisar al sistema que se creo un socket
		if(bind(Socket_Servidor,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
			printf ("No se puede abrir socket de cliente\n");
			exit (-1);
		}else{
            printf("\t---SERVIDOR---\n");
			printf("La direccion ip del servidor es--->[%s]\n",ip);
			printf("El puerto es--->[%d]",PORT);

			 //Establecer el socket en modo escucha
			if(listen(Socket_Servidor,5)<0){
				 printf("error en listen()\n");
				exit (-1);
			}else{
				//Enviamos un mensaje al CLiente cuando este se conecte al Servidor
				addr_size=sizeof(newAddr);
				NuevoSocket=accept(Socket_Servidor,(struct sockaddr*)&newAddr,&addr_size);
				strcpy(Paquete,"Te has conectado a los servicios del servidor\n");
				send(NuevoSocket,Paquete,strlen(Paquete),0);
				 printf("\n---SERVIDOR EN ESPERA...\n");
 				printf("\n----CLIENTE CONECTADO---\n");
				printf("\tREALIZAR SUMA\n");

                //Pedimos al cliente que nos mande el primer  valor
				memset(&Paquete,'\0',sizeof(Paquete));
				strcpy(Paquete,"Envia el primer valor: \n");
				send(NuevoSocket,Paquete,strlen(Paquete),0);
				//Se resive el paquete de datos que ha sido enviado por el cliente
				memset(&Paquete,'\0',sizeof(Paquete));
				recv(NuevoSocket,Paquete,MAX,0);
				printf("VALOR_1= --->[%s] \n",Paquete);

				//Declaramos las longitudes de los valores emplepleados numero 1 numero 2 
				unsigned long long int numb=strlen(Paquete);
                unsigned long long int num1=strtoul(Paquete, &p, 0);

				//Validacion de valores erroneos ingresador por buffer del teclado
				if(strlen(p)>=1){
					printf("\n--VALORES INCORRECTOS--\n");
				}

	            //SE SOLICITA AL CLIENTE EL SEGUNDO VALOR Y SE RECIBE
				memset(&Paquete,'\0',sizeof(Paquete));
				strcpy(Paquete,"Envia el Segundo valor\n");
				send(NuevoSocket,Paquete,strlen(Paquete),0);	

				memset(&Paquete,'\0',sizeof(Paquete));
				recv(NuevoSocket,Paquete,MAX,0);
				printf("VALOR_2--->[%s] \n",Paquete);
				numb=strlen(Paquete);
				printf ("Numero de Bytes resibidos---->[%llu]\n",numb);
				//Declaramos la variable para resivir al valor 2
				unsigned long int num2=strtoul(Paquete, &p, 0);
	
                //SE REALIZA LA SUMA CON LAS DATOS ENVIADOS DESDE EL CLIENTE
				memset(&Paquete,'\0',sizeof(Paquete));
				unsigned long long int suma=num1+num2;
				sprintf(Paquete, "%llu",suma);
				send(NuevoSocket,Paquete,strlen(Paquete),0);	
		
				}
	
			}
	
		}
	
	}