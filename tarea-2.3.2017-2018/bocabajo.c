#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"

//Usamos el prefijo const para declarar la constante LENGTH con un tamaño máximo de 2048
const int LENGTH = 2048;

/**
 * El programa recibe dos parámetros de entrada: argc y argv[]
 * Estos dos son conocidos como argumentos de la línea de comandos
 * argc hace referencia al número de parámetros que se le pasan al programa
 * argv[] es un array de punteros en el que cada elemento es un puntero a uno de los argumentos introducidos
*/

int main(int argc, char *argv[]) {
 char **pprimer;
 char *psegun;
 int i = 0, j = 0, contador = 0, aux = 0;
 char cadena[LENGTH]; //El array cadena va a poder almacenar como máximo 2048 carácteres por línea
 FILE *AEntrada = NULL;
 
 if(argc == 1) {
  //malloc(size_t size) asigna la memória solicitada y le devuelve un puntero. Con ello creamos el puntero pprimer del array comprobamos que no sea nulo
  if((pprimer = (char **)malloc(sizeof(char *))) == NULL) {
   argv0 = "bocabajo";
   Error(EX_OSERR, "%s", "No se pudo ubicar la memória dinámica necesaria");
  }
  /**
   * fgets lee el contenido del fichero stdin (estandard input), es decir el nombre que le hemos introducido como argumento
   * Luego lo copia en cadena
   * Esta función solo lee LENGTH - 1 carácteres
   * Minetras sean distintos de NULL la función sigue leyendo
   */
  while(fgets(cadena, LENGTH, stdin) != NULL) {
   //Con la función realloc() se puede incrementar el tamaño donde esta asignado el bloque de memoria permitiendo que el puntero de la línea siguiente entre en nuestro array
   pprimer = (char **)realloc(pprimer, ((contador + 1) * sizeof(char *)));

   /**
    * Devuelve un puntero a una cadena de bytes terminados en nulo, que es un duplicado de la cadena apuntada por strdup(cadena).
    * Se comprueba que no es nulo.
    * El puntero devuelto se debe liberar para evitar una pérdida de memoria.
    * Si se produce un error, se devuelve un puntero nulo y se puede establecer un errno.
    */
   if((psegun = (char *)strdup(cadena)) == NULL) {
    argv0 = "bocabajo";
    Error(EX_OSERR, "%s", "No se pudo ubicar la memória dinámica necesaria.");
   }
   else {
    //En este caso guardaremos el puntero, psegun, en la posición siguiente del array
    *(pprimer + contador) = psegun;
   }
   contador++;
  }
  /**
   * Mediante el uso de la función free(void *adress) liberamos un bloque de memoria especificado por la dirección que es el puntero de la ultima línea leida
   * al ser un salto de línea no deseado.
  */
  free(pprimer[contador]);
  //Recorremos el array de punteros
  for(j = contador - 1; j >= 0; j--) {
   //Imprimimos cada carácter contenido en el array pprimer desde el final al principio de éste
   printf("%s", pprimer[j]);
   //Una vez impresa esa posición la liberamos
   free(pprimer[j]);
  }
  //Liberamos el array completo
  free(pprimer);
  return (EX_OK);
 }

 /**
  * La función strcmp(s1, s2) devuelve los siguientes valores dependiendo de los argumentos que se le pasen:
  * 0 si s1 y s2 son iguales
  * menor que 0 si s1 < s2
  * mayor que 0 si s1 > s2
 */
 if(strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "--help") == 0)) {
  printf("bocabajo: Uso: bocabajo [fichero...]\n");
  printf("bocabajo: Invierte el orden de las líneas de los ficheros (o de la entrada).\n");
  return (EX_OK);
 }
 if(argc < 2) {
  argv0 = "bocabajo";
  Error(EX_NOINPUT, "%s", "El número de argumentos introducido es incorrecto.");
 }
 if(argc >= 2) {
  for(i = 1; i <= argc - 1; i++) {
   AEntrada = NULL;
   //Leemos el archivo y si no existe lanzamos un error
   AEntrada = fopen(argv[i], "r");
   if(AEntrada = NULL) {
    argv0 = "bocabajo";
    Error(EX_NOINPUT, "%s", argv[i], "No es legible.");
    //Aunque el fichero no sea válido continuamos en el for
   }
   else {
    //Leemos las líneas
    while(fgets(cadena, LENGTH, AEntrada) != NULL) {
     aux = 1;
     //Prier caso
     if(contador == 0) {
      //Creamos el puntero pprimer del array y comprobamos que no sea nulo
      if((pprimer = (char **)malloc(sizeof(char *))) == NULL) {
       argv0 = "bocabajo";
       Error(EX_OSERR, "%s", "No se pudo ubicar la memória dinámica necesaria.");
      }
      //Duplicamos la línea leída en memoria dinámica y comprobamos que el puntero a dicha línea no sea nulo
      if((psegun = (char **)malloc(sizeof(char *))) == NULL) {
       argv0 = "bocabajo";
       Error(EX_OSERR, "%s", "No se pudo ubicar la memória dinámica necesaria.");
      }
      //Guardamos el puntero en la primera posición del array de punteros
      else {
       *pprimer = psegun;
      }
     }
     else {
      //Aumentamos el tamaño del array de punteros para que entre el puntero de la línea siguiente
      pprimer = (char **)realloc(pprimer, ((contador + 1) * sizeof(char *)));
      if((psegun = (char *)strdup(cadena)) == NULL) {
       argv0 = "bocabajo";
       Error(EX_OSERR, "%s", "No se pudo ubicar la memória dinámica necesaria.");
      }
      else {
       *(pprimer + contador) = psegun;
      }
     }
     contador++;
    }
   }
   fclose(AEntrada);
  }
  if(aux != 0) {
   for(j = contador -1; j >= 0; j--) {
    printf("%s", pprimer[j]);
    free(pprimer[j]);
   }
   free(pprimer);
  }
 }
 return (EX_OK)
}