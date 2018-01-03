#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"

//Usamos el prefijo const para declarar la constante LENGTH con un tamaño máximo de 2048
const int LENGTH = 2048;

/**
 * Recibe dos parámetros de entrada: argc y argv.
 * Estos dos son conocidos como argumentos para la línea de comandos.
 * argc hace referencia al número de argumentos que le estamos pasando al programa.
 * argv es un array de punteros, en el que cada elemento que tiene dentro apunta a uno de los argumentos que le hemos pasado.
*/

int main(int argc, char *argv[]) {
 //El array cadena va a poder almacenar como máximo 2048 carácteres por línea
 char cadena[LENGTH];

 //Inicializamos el fichero AEntrada de salida estándar
 FILE *AEntrada;

 /*
  * La función strcmp(s1, s2) devuelve los siguientes valores dependiendo de los argumentos que se le pasen:
  * 0 si s1 y s2 son iguales
  * menor que 0 si s1 < s2
  * mayor que 0 si s1 > s2
 */
 if (strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "--help") == 0))
 {
  printf("delreves: .*Uso: .*delreves.c...El programa recibe un fichero o cadena de texto,\n");
  printf("delreves: El programa devuelve cada línea del fichero leida de derecha a izquierda (al reves).\n");
  return (EX_OK);
 }

 /**
  * Contemplamos el caso de que solo se le pase un argumento al programa.
  * Lo primero que haremos en este caso es leer el fichero línea por línea.
  * Una vez hallada la longitud del char cadena procedemos a invertir el texto.
 */
 if(argc == 1) {
  //fgets lee el contenido del fichero stdin (nombre introducido como argumento) y lo copia en cadena
  //Esta función sólo lee LENGTH-1 caracteres
  while (fgets(cadena,LENGTH,stdin) != NULL) {
   int i;
   //Con este for sacamos por pantalla los caracteres de cada línea, empezando por el final de cada una de estas
   for(i = LENGTH - 2; i >= 0; i--) {
    printf("%c", cadena[i]);
   }
   printf("\n");
  }
  return (EX_OK);
 }

 int i;
 for(i = 1; i < argc; i++) {
  //Leemos el archivo
  AEntrada = fopen(argv[i], "r");
  //Si no existe lanzamos un error
  if(AEntrada == NULL) {
   fprintf(stderr, "delreves: Error(EX_NOINPUT), no se puede abrir el archivo de entrada.\n");
   fprintf(stderr, "delreves+ El fichero \"%s\"no existe o no puede ser leído.\n", argv[i]);
   return (EX_NOINPUT);
  } else {
   while(fgets(cadena, LENGTH, AEntrada) != NULL) {
    int j = 0;
    int length = strlen(cadena);
    for(j = length - 2; j >= 0; j--) {
     printf("%c", cadena[j]);
    }
    printf("\n");
   }
  }
  fclose(AEntrada);
 }
 return (EX_OK);
}