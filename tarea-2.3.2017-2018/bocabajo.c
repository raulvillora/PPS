#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"

#define TAM_CAD 2048

int main(int argc, char **argv)
{
	char **pprimer;
	char *psegun;
	int j = 0;
	int contador = 0;
	int i = 0;
	int aux = 0;
	char cadena[TAM_CAD];
	FILE *AEntrada = NULL;
	if (argc == 1)
	{
		if ((pprimer = (char **)malloc(sizeof(char *))) == NULL)
		{
			argv0 = "bocabajo";
			Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
		}
		while (fgets(cadena, TAM_CAD, stdin) != NULL)
		{
			pprimer = (char **)realloc(pprimer, ((contador + 1) * sizeof(char *)));
			if ((psegun = (char *)strdup(cadena)) == NULL)
			{
				argv0 = "bocabajo";
				Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
			}
			else
			{
				*(pprimer + contador) = psegun;
			}
			contador++;
		}
		free(pprimer[contador]);
		for (j = contador - 1; j >= 0; j--)
		{
			printf("%s", pprimer[j]);
			free(pprimer[j]);
		}
		free(pprimer);
		return 0;
	}
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
			AEntrada = fopen(argv[i], "r");
			if (AEntrada == NULL)
			{
				argv0 = "bocabajo";
				Error(EX_NOINPUT, ".*\"%s\"", argv[i], "no legible");
				/*continue; Aunque el fichero no sea valido continuamos en el for*/
			}
			else
			{
				while (fgets(cadena, TAM_CAD, AEntrada) != NULL) /*Leemos las lines*/
				{
					aux = 1;
					if (contador == 0) /*primer caso*/
					{

						if ((pprimer = (char **)malloc(sizeof(char *))) == NULL) /*Creamos puntero del array de punteros,y comprobamos que no sea nulo*/
						{
							argv0 = "bocabajo";
							Error(EX_OSERR, "%s", "No se  pudo ubicar la memoria dinamica necesaria.");
						}
						if ((psegun = (char *)strdup(cadena)) == NULL) /*Duplicamos la linea leida en memoria dinamica y comprobamos que el puntero a dicha linea no sea nulo*/
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
					{
						pprimer = (char **)realloc(pprimer, ((contador + 1) * sizeof(char *))); /*Aumentamos el tamaño del array de punteros para que entre el puntero de la linea siguiente*/
						if ((psegun = (char *)strdup(cadena)) == NULL)				/*/*Duplicamos la linea leida en memoria dinamica y comprobamos que el puntero a dicha linea no sea nulo*/
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
					free(pprimer);
				}
			}
			/*free(pprimer[contador]);Liberamos el puntero de la ultima linea leida al ser un salto de linea no deseado*/
			fclose(AEntrada);
		}
		if (aux != 0)
		{
			for (j = contador - 1; j >= 0; j--) /*Bucle para recorrer el array de  punteros*/
			{
				printf("%s", pprimer[j]); /*Impresion lineas caracter a caracter*/
				free(pprimer[j]);	 /*Liberar array de  punteros*/
			}
			free(pprimer); /*Liberar array de  punteros*/
		}
	}
	return 0;
}
