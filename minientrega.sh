#!/bin/bash
#minientrega.sh

#VARI=$1
#$1 hace referencia al primer argumento que se le pasa al script
#$# nos dice el número de argumentos que se le pueden pasar al script

if [$# -ne 1]
 then 
  echo minientrega.sh: Error\(EX_USAGE\), uso incorrecto del mandato. \"Success\"
  echo minientrega.sh+ debe ser invocado con un argumento que identifique la práctica.
 exit 64
fi
#Si el numero de argumentos que le pasamos al script no es uno nos salta un error

if [$1 = "-h"]
 then
  echo minientrega.sh: Uso: minientrega.sh \[-h \| --help \| ID_PRACTICA\]
  echo minientrega.sh: realiza la entrega de la practica ID_PRACTICA 
 exit 0
fi
if [$1 = "--help"]
 then
  echo minientrega.sh: Uso: minientrega.sh \[-h\| --help \| ID_PRACTICA\]
  echo minientrega.sh: realiza la entrega de la practica ID_PRACTICA
 exit 0;
fi
#Si se quiere acceder a la ayuda del script se puede utilizar tanto -h como --help

if ![-d $MINIENTREGA_CONF]
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no es accesible el directorio ""$MINIENTREGA_CONF"" 
 exit 64
fi
#-d devuelve true si la variable existe y es realmente un directorio
#Con este if estamos comprobando si no es un directorio, en cuyo caso salta error

if ![-s $MINIENTREGA_CONF]
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no es accesible el directorio ""$MINIENTREGA_CONF"" 
 exit 64
fi
#-s devuelve true si el directorio existe y no esta vacio
#Con este if estamos comprobando si el fichero esta vacio, en cuyo caso salta error

if ![-r $MINIENTREGA_CONF] #Preguntar al profesor: en help test solo true si se puede leer, en man test true si existe Y se puede leer (-e redundante?)
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no es accesible el directorio ""$MINIENTREGA_CONF"" 
 exit 64
fi
#-r devuelve true si el directorio existe y se tienen permisos de lectura 
#Con este if estamos comprobando si no se puede leer el directorio, en cuyo caso salta error

if ![-r "$MINIENTREGA_CONF/$1"]
 then
  echo minientreg.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no es accesible el fichero "$1"
 exit 66
fi
#-r sirve el mismo proposito que en la condicion anterior, pero en este caso comprueba que el fichero de practica especificado es el que no se puede leer, en cuyo caso salta error 

source $MINIENTREGA_CONF/$1
declare -a ficheros=($MINIENTREGA_FICHEROS)
#Mediante el source podemos acceder al archivo especificado en el argumento $1 y crear un array con los nombres de los ficheros del directorio donde se encuetra
 
fechaActual=`date +%F`
#date +FORMATO, en este caso el formato es el de full date, lo saca como %Y-%m-%d

if [-z "$MINIENTREGA_FECHALIMITE"]
 then
  echo minentrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ campo de fecha vacio
 exit 65
fi
#Comprobamos que la cadena en la que esta contenida la fecha no es nula

validar_fecha=`echo "$MINIENTREGA_FECHALIMITE" | grep [0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}`
if ["$validar_fecha" == '']
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ fecha incorrecta "$MINIENTREGA_FECHALIMITE"
 exit 65
 else 
  >/dev/null
fi
#Con este proceso estamos comprobando si la cadena que contiene a la fecha esta en el formato de fecha valido

separadores=$IFS
IFS="-"
#IFS viene de Internal File Separator, variable de entorno
#Primero declaramos la variable de entorno de separadores de campo y le asignamos el valor de '-'

set -- "$MINIENTEGA_FECHALIMITE" 
#set separa la fecha que le hemos pasado en tres argumentos separados por los ifs, y el -- les asigna valores de parametros posicionales $1, $2 y $3

declare -a array_fecha_lim=($*)
#Metemos los parametros de la fecha en un array para poder hacer comprobaciones de año, mes y dia por separado

if ["${array_fecha_lim[0]}" -gt 2100] || ["${array_fecha_lim[0]}" -lt 2017] 
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ fecha incorrecta "$MINIENTREGA_FECHALIMITE"
 exit 65
fi

if ["${array_fecha_lim[1]}" -gt 12] || ["${array_fecha_lim[1]}" -lt 1]
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ fecha incorrecta "$MINIENTREGA_FECHALIMITE"
 exit 65
fi

if ["${array_fecha_lim[2]}" -gt 31] || ["${array_fecha_lim[2]}" -lt 1] #Realizar comprobacion de dias dependiendo del mes?
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ fecha incorrecta "$MINIENTREGA_FECHALIMITE"
 exit 65
fi
#Con esto comprobamos, independientemente, que el año, el mes y el dia que nos pasa la fecha sean correctos

#if [${array_fecha_act[0]} -gt ${array_fecha_lim[0]}]
# then 
#  echo minientrega.sh: Error, no se pudo realizar la entrega
#  echo minientrega.sh+ el plazo acababa el "$MINIENTREGA_FECHALIMITE"
# exit 65
#fi

#if [${array_fecha_act[1]} -gt ${array_fecha_lim[1]}] #Suponiendo que se entrega el mismo año que el dicho en la fecha limite (?)
# then 
#  echo minientrega.sh: Error, no se pudo realizar la entrega
#  echo minientrega.sh+ el plazo acababa el "$MINIENTREGA_FECHALIMITE"
# exit 65
#fi
#Metodo poco eficiente para ver si la practica esta siendo entregada dentro de plazo, muchas cosas a tener en cuenta a la hora de comprobar el dia

fecha_act=`echo ${fechaActual//-/}`
fecha_lim=`echo ${MINIENTREGA_FECHALIMITE//-/}`
#Eliminamos los guiones de ambas fechas para convertirlas en enteros y poder operar con ellas

let resul=$fecha_lim-$fecha_act
#Realizamos la resta de ambos numeros

if ["$resul" -lt 0]
 then 
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ el plazo acababa el "$MINIENTREGA_FECHALIMITE"
 exit 65
fi
#Si el resultado de la resta de ambos numeros es menor que 0, entonces la fecha limite es menor que la fecha actual, luego la fecha actual es superior a la limite

source "$MINIENTREGA_CONF/$VARI"
#VARI tiene guardado el nombre del archivo que le hemos pasado al script, lo hemos almacenado al principio del programa

if ![-d "$MINIENTREGA_DESTINO"]
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no se pudo crear el subdirectorio de entrega "$MINIENTREGA_DESTINO"
 exit 73
fi
#Comprobamos que exista y se trate realmente de un directorio, y no de un archivo

if ![-w "$MINIENTREGA_DESTINO"]
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no se pudo crear el subdirectorio de entrega "$MINIENTREGA_DESTINO"
 exit 73
fi
#Finalmente comprobamos que se pueda escribir en dicho directorio

if ![-d "$MINIENTREGA_DESTINO/$USER"]
 then
  mkdir -p "$MINIENTREGA_DESTINO/$USER"
fi
#Estamos comprobando si existe o no el directorio de entrega, si no existe lo creamos

if ![-d "$MINIENTREGA_DESTINO/$USER"]
 then
  echo minientrega.sh: Error, no se pudo realizar la entrega
  echo minientrega.sh+ no se pudo crear el subdirectorio de entrega "$MINIENTREGA_DESTINO/$USER"
 exit 73
fi

IFS=$separadores
#Restauramos los IFS

for destino in ${ficheros[*]}
do
 cp -a "${destino[*]}" "$MINIENTREGA_DESTINO/$USER"
done
#Copiamos todos los archivos al directorio de entrega

exit 0
