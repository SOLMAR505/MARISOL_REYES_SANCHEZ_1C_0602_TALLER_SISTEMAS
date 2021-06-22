/*
* Includes del sistema
*/
#include <stdio.h>
//#include <Socket_Cliente.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8087
#define MAX 1024 
#define ip "127.0.0.1"


int Socket_Cliente;
struct sockaddr_in serverAddr;
char buffer[MAX ];
void Cliente();

void main(int argc, char *argv[]){
	Cliente();
    
}
/*
	* Descriptor del socket y buffer para datos
	*/	
	void Cliente(){

	/*
	* Se abre el socket servidor
	*/
	Socket_Cliente=socket(PF_INET, SOCK_STREAM, 0);
	if(Socket_Cliente<0){
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}else{
	
		printf("\t---CONEXION EXITOSA---\n");
		memset(&serverAddr,'\0',sizeof(serverAddr));	

		//Datos del servidor
		serverAddr.sin_family=AF_INET;
		serverAddr.sin_port=htons(PORT);
		serverAddr.sin_addr.s_addr=inet_addr(ip);

		/*
		* Se espera un cliente que quiera conectarse
		*/
	
		if(connect(Socket_Cliente, (struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
			printf ("No se puede abrir socket de cliente\n");
			exit (-1);
		}
		else{
			printf("\t\t--CLIENTE--\n");
			//Datos del servidor
			printf("La direccion ip del servidor es--->[%s]\n",ip);
			printf("El puerto es--->[%d]",PORT);
			memset(&buffer,'\0',sizeof(buffer));
			
			/*
			* Se lee la informacion enviada por el servidor
			*/
			recv(Socket_Cliente,buffer,MAX ,0);
            //SE SOLICITA EL PRIMER NUMERO
			char num1[MAX ];
			printf("\nIngrese el primer numero: \n");
			scanf("%s",num1);
            //Enviamos el numero 1 al servidor
			send(Socket_Cliente,num1,strlen(num1),0);
			memset(&buffer,'\0',sizeof(buffer));

			//Pedimos el segundo numero 
			recv(Socket_Cliente,buffer,MAX ,0);
			char num2[MAX ];	
			printf("\nIngrese el segundo numero: \n");
			scanf("%s",num2);
            //Enviamos el numero 2 al servidor
			send(Socket_Cliente,num2,strlen(num2),0);
			memset(&buffer,'\0',sizeof(buffer));
			
			//SE REALIZA LA SUMA EN EL SERVIDOR Y ENVIA EL RESULTADO AL CLIENTE
			recv(Socket_Cliente,buffer,MAX,0);
			printf("\n\nEl resultado de la suma es-->[%s ] \n",buffer);

			printf("\nCONEXION FINALIZADA\n");
		
		}
	
	}
	}