#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sysexits.h>
#include "auxiliar.h"

#define TAM_CAD   2048

int main(int argc, char **argv)
{
	char cadena[TAM_CAD]; /* Un array lo suficientemente grande como para guardar la línea más larga del fichero */
    	int i=0;
   	FILE *AEntrada=NULL;
	if(argc == 1)
    	{
   		while(fgets(cadena,TAM_CAD,stdin)!= NULL){
 			int j;
       			int length = strlen(cadena);    
       			for(j = length-2 ; j >= 0;j--){   
                   		printf("%c", cadena[j]);
			}	
		printf("\n");
		}
	return 0;
    	}
    	if(strcmp(argv[1], "-h") == 0 || (strcmp(argv[1] , "--help") ==0 ))
    	{
     		printf("delreves: .*Uso: .*delreves.c...El programa recibe un fichero o cadena de texto,\n");
        	printf("delreves: El programa devuelve cada  linea del fichero leida  de derecha a izquierda(al reves).\n");
        	return EX_OK;
    	}
/*
	Para evaluar los argumentos de entrada usamos argc y argv
        argc es un contador con el numero de argumentos pasado y argv
        es un array de cadenas con los argumentos propiamente
        El primer argumento es el nombre del programa
*/
        if(argc < 2)
        {
		argv0="delreves";
            	Error (EX_NOINPUT, "%s", "El numero de argumentos incorrectos.");
        }
	for(i = 1; i < argc; i++)
        {
            	AEntrada = NULL;
            	AEntrada=fopen(argv[i],"r");
       	    	if(AEntrada==NULL)
            	{
             		/*Aqui en realidad no se sale, lo que se hace es seguir comprobando y si hay otro argumento con otro fichero, ir a evaluarlo*/
			argv0="delreves";                	
			Error (EX_NOINPUT,".*El fichero \"%s\" no puede ser  leido.", argv[i] );
                	/*continue; Aunque el fichero no sea valido continuamos en el for*/
            	}
            	else
            	{
             		while (fgets(cadena, TAM_CAD, AEntrada) != NULL)    /*Voy leyendo el fichero linea a linea*/
                	{
                    		int j=0;
                    		int length = strlen(cadena);                    /*Obtengo el tamaño real de la nueva linea*/
                    		for(j = length-2 ; j >= 0;j--)                 /*Empiezo a imprimir desde el final hasta el principio*/
				{                        	
					printf("%c", cadena[j]);
                		}
				printf("\n");
			}
           	}
            	fclose(AEntrada);
        }
	return 0;
}
