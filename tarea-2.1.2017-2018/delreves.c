#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"

//Usamos el preporcesador #define para definir la constante TAM_CAD con un tamaño máximo de 2048 caracteres por línea
#define TAM_CAD 2048

/**
 * Recibe dos parametros de entrada argc y argv.
 * Estos argumentos son usado como una forma de enviar argumentos al programa.
 * El programa recibe el número de argumentos en args y el array de argumentos en argv.
*/

int main(int argc, char **argv)
{
	//Definimos un array que pueda guardar como máximo 2048 caracteres por línea
	char cadena[TAM_CAD];
	int i = 0;
	FILE *AEntrada = NULL; //Inicializamos un fichero AEntrada
	if (argc == 1)
	{
		while (fgets(cadena, TAM_CAD, stdin) != NULL)
		{ //En caso de que el número de argumentos que recibe el programa sea 1 voy leyendo el fichero línea por línea
			int j;
			int length = strlen(cadena); //Obtengo la longitud del char cadena
			for (j = length - 2; j >= 0; j--)
			{
				printf("%c", cadena[j]); //Imprime el anterior caracter del char
			}
			printf("\n");
		}
		return 0;
	}
	if (strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "--help") == 0)) //strcmp (s1, s2) nos devolverá 0 si s1 y s2 son iguales; menos de 0 si s1 <s2; mayor que 0 si s1> s2.
	{
		printf("delreves: .*Uso: .*delreves.c...El programa recibe un fichero o cadena de texto,\n");
		printf("delreves: El programa devuelve cada  linea del fichero leida  de derecha a izquierda(al reves).\n");
		return EX_OK;
	}

	if (argc < 2)
	{
		argv0 = "delreves";
		Error(EX_NOINPUT, "%s", "El numero de argumentos incorrectos.");
	}
	for (i = 1; i < argc; i++)
	{
		AEntrada = NULL;
		AEntrada = fopen(argv[i], "r"); // leer el array en la posición i
		if (AEntrada == NULL)
		{
			argv0 = "delreves";
			Error(EX_NOINPUT, ".*El fichero \"%s\" no puede ser  leido.", argv[i]);//seguiremos leyendo caracteres aunque el archivo no sea válido

		} 
		else
		{	
			while (fgets(cadena, TAM_CAD, AEntrada) != NULL)//En caso de que el número de argumentos que recibe el programa sea mayor que 1 voy leyendo el fichero línea por línea
			{ 
				int j = 0;
				int length = strlen(cadena);//Obtengo la longitud del char cadena
				for (j = length - 2; j >= 0; j--) 
				{
					printf("%c", cadena[j]); //Imprime el anterior caracter del char 
				}
				printf("\n");
			}
		}
		fclose(AEntrada);
	}
	return 0;
}
