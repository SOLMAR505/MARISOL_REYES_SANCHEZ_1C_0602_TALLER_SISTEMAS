#!/bin/bash
ROOT_UID=0
SUCCESS=0
#VALIDACIÒN DE USUARIO ROOT.
if [ "$UID" -ne "$ROOT_UID" ]
then
  echo "Se debe estar como root para ejecutar este script"
  exit $E_NOTROOT
fi  
#VALIDACIÒN DE CARGAR LA LISTA.
file=$1
if [ "${file}X" = "X" ];
then
   echo "Debe indicar el archivo del listado con Nombres de grupo a ingresar..."
   exit 1
fi

# Del archivo con el listado de grupos a ingresar:
# Este es el formato:
# ejemplo
#    |   
#    f1  
#$f1 = nombreGrupo
#Ejemplo1:sol:5004:1010:user1:/home/:/bin/bash:

crearUsuario(){
    #echo "----> Crear usuarios <----"
    eval username="$1"
    eval password="$2"
    eval userid="$3"
    eval grupoid="$4"
    eval infouser="$5"
    eval home="$6"
    eval comandoshell="$7"
    
    if grep -q ${grupoid} /etc/group  
    	then  
    	echo "El ID del grupo-->${grupoid}-->YA EXISTE"
    if grep -q ${username} /etc/passwd  #Si el usuario existe MENSAJE DE EXISTENCIA
    	then 
    	echo "El Usuario-->${username} -->YA EXISTE"
    else  #Si no exixte se crea un nuevo usuario
    	echo "El Usuario-->${username} --> NO EXISTE"
    	useradd -c "${userid} ${infouser}"  -p "${password}" -d "${home}""${username}" -s "${comandoshell}" "${username}"   -u  "${grupoid}"       
    	echo "--Usuario creado--"
    fi
    else  #Si No existe se crea un nuevo grupo
    	echo "Se creara un nuevo grupo con ID = ${grupoid}"
    	echo "El shell es--> ${comandoshell}"
    	echo "El ID del grupo es-->${grupoid}-->NO EXISTE"
    	groupadd "${grupoid}" 
    
    if grep -q ${username} /etc/passwd  
    	then 
    	echo "------------------------"
    	echo "El Usuario-->${username} -->YA EXISTE"
    	echo "------------------------"
    else  
    	echo "El Usuario-->${username} --> NO EXISTE"
    fi
    	useradd  -c "${userid} ${infouser}" -p "${password}" -d "${home}""${username}" -s "${comandoshell}" "${username}"  -u "${grupoid}"  
   	 	echo "---Usuario creado--"
 
    fi
}

while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do
 
    crearUsuario "\${f1}" "\${f2}" "\${f3}" "\${f4}" "\${f5}" "\${f6}" "\${f7}"
done < ${file}

exit 0
