#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"

//Usamos el prefijo const para declarar la constante LENGTH con un tamaño máximo de 2048
#define TAM_CAD 2048

/**
 * Recibe dos parámetros de entrada: argc y argv.
 * Estos dos son conocidos como argumentos para la línea de comandos.
 * argc hace referencia al número de argumentos que le estamos pasando al programa.
 * argv es un array de punteros, en el que cada elemento que tiene dentro apunta a uno de los argumentos que le hemos pasado.
*/

int main(int argc, char **argv)
{
	char **pprimer;
	char *psegun;
	int j = 0;
	int contador = 0;
	int i = 0;
	int aux = 0;
	char cadena[TAM_CAD]; //El array cadena va a poder almacenar como máximo 2048 carácteres por línea
	FILE *AEntrada = NULL;
	if (argc == 1)
	{
		//malloc(size_t size) asgina la memoria solicitada y le devuelve un puntero. Con ello creamos el puntero pprimer del array y comprobamos que no sea nulo
		if ((pprimer = (char **)malloc(sizeof(char *))) == NULL)
		{
			argv0 = "bocabajo";
			Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
		}
		//fgets lee el contenido del fichero stdin (nombre introducido como argumento) y lo copia en cadena
		//Esta función sólo lee 2047 caracteres
		//Mientras sean distintas de NULL se va leyendo
		while (fgets(cadena, TAM_CAD, stdin) != NULL)
		{
			//Mediante la llamada a la función realloc() se puede incrementar el tamaño donde esta asginado el bloque de memoria permitiendo que el puntero de la línea siguiente entre en nuestro array
			pprimer = (char **)realloc(pprimer, ((contador + 1) * sizeof(char *)));
			if ((psegun = (char *)strdup(cadena)) == NULL) // Devuelve un puntero a una cadena de bytes terminados en nulo, que es un duplicado de la cadena apuntada por strdup(cadena). Se comprueba que no es nulo. El puntero devuelto se debe pasar a libre para evitar una pérdida de memoria. Si se produce un error, se devuelve un puntero nulo y se puede establecer un errno.
			{
				argv0 = "bocabajo";
				Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
			}
			else
			{
				*(pprimer + contador) = psegun; //En este caso guardaremos el puntero, psegun, en la posición siguiente del array
			}
			contador++;
		}
		free(pprimer[contador]);			//Mediante el uso de la función free(void *address) liberamos un bloque de memoria especificado por la dirección que es el puntero de la ultima linea leida al ser un salto de linea no deseado
		for (j = contador - 1; j >= 0; j--) //Recorremos el array de punteros
		{
			printf("%s", pprimer[j]); //Imprimimos cada caracter contenido en el array pprimer desde el final al principio de éste
			free(pprimer[j]);		  //Una vez impresa esa posición la liberamos
		}
		free(pprimer); //Se libera el array completo
		return 0;
	}
	/*
	* La función strcmp(s1, s2) devuelve los siguientes valores dependiendo de los argumentos que se le pasen:
	* 0 si s1 y s2 son iguales
	* menor que 0 si s1 < s2
	* mayor que 0 si s1 > s2
	*/
	if (strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "--help") == 0))
	{
		printf("bocabajo: .*Uso: .*bocabajo.c...El programa recibe un fichero o cadena de texto,\n");
		printf("bocabajo: El programa devuelve cada  linea del fichero leida  de derecha a izquierda(al reves).\n");
		return EX_OK;
	}
	if (argc < 2)
	{
		argv0 = "bocabajo";
		Error(EX_NOINPUT, "%s", "El numero de argumentos incorrectos.");
	}
	if (argc >= 2)
	{
		for (i = 1; i <= argc - 1; i++)
		{
			AEntrada = NULL;
			AEntrada = fopen(argv[i], "r"); //Leemos el archivo
			//Si no existe lanzamos un error
			if (AEntrada == NULL)
			{
				argv0 = "bocabajo";
				Error(EX_NOINPUT, ".*\"%s\"", argv[i], "no legible");
			}
			else
			{
				//fgets lee el contenido del fichero stdin (nombre introducido como argumento) y lo copia en cadena
				//Esta función sólo lee 2047 caracteres
				//Mientras sean distintas de NULL se va leyendo
				while (fgets(cadena, TAM_CAD, AEntrada) != NULL)
				{
					aux = 1;
					if (contador == 0) /*primer caso*/
					{
						//malloc(size_t size) asgina la memoria solicitada y le devuelve un puntero. Con ello creamos el puntero pprimer del array y comprobamos que no sea nulo
						if ((pprimer = (char **)malloc(sizeof(char *))) == NULL)
						{
							argv0 = "bocabajo";
							Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
						}
						if ((psegun = (char *)strdup(cadena)) == NULL) // Devuelve un puntero a una cadena de bytes terminados en nulo, que es un duplicado de la cadena apuntada por strdup(cadena). Se comprueba que no es nulo. El puntero devuelto se debe pasar a libre para evitar una pérdida de memoria. Si se produce un error, se devuelve un puntero nulo y se puede establecer un errno.
						{
							argv0 = "bocabajo";
							Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
						}
						else /*Guardamos el puntero en la primera posicion del array de  punteros*/
						{
							*pprimer = psegun;
						}
					}
					else
					{ //Mediante la llamada a la función realloc() se puede incrementar el tamaño donde esta asginado el bloque de memoria permitiendo que el puntero de la línea siguiente entre en nuestro array
						pprimer = (char **)realloc(pprimer, ((contador + 1) * sizeof(char *)));
						if ((psegun = (char *)strdup(cadena)) == NULL) // Devuelve un puntero a una cadena de bytes terminados en nulo, que es un duplicado de la cadena apuntada por strdup(cadena). Se comprueba que no es nulo. El puntero devuelto se debe pasar a libre para evitar una pérdida de memoria. Si se produce un error, se devuelve un puntero nulo y se puede establecer un errno.
						{
							argv0 = "bocabajo";
							Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
						}
						else /*Guardamos el puntero en la posicion siguiente del array*/
						{
							*(pprimer + contador) = psegun;
						}
					}
					contador++;
				}
			}
			fclose(AEntrada);
		}
		if (aux != 0)
		{
			for (j = contador - 1; j >= 0; j--) //Recorremos el array de punteros
			{
				printf("%s", pprimer[j]); //Imprimimos cada caracter contenido en el array pprimer desde el final al principio de éste
				free(pprimer[j]);		  //Una vez impresa esa posición la liberamos
			}
			free(pprimer); //Se libera el array completo
		}
	}
	return 0;
}
