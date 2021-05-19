#!/bin/bash
ROOT_UID=0
SUCCESS=0

#Validaciòn de acceso root
if [ "$UID" -ne "$ROOT_UID" ]
then
  echo "Se debe estar como root para ejecutar este script"
  exit $E_NOTROOT
fi  

file=$1


if [ "${file}X" = "X" ];
then
   echo "Debe indicar el archivo con el listado de usuarios a eliminar..."
   exit 1
fi


eliminarGrupo(){
	eval nombreGrupo="$1"
	if grep -q ${nombreGrupo} /etc/group  
    then  
        groupdel "${nombreGrupo}"
		echo "Grupo[${nombreGrupo}] eliminado correctamente..."
	else 
		echo "Grupo [${nombreGrupo}] No se pudo eliminar..."
	fi
}

while IFS=: read -r f1
do
	eliminarGrupo "\${f1}"	
done < ${file}

exit 0