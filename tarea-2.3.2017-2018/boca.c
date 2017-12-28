#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sysexits.h>
#include "auxiliar.h"

#define TAM_CAD 2048

int main(int argc, char **argv)
{
	char **pprimer
	char *psegun;
	int j,k;
	int contador = 0;
        int i=0;
	char cadena[TAM_CAD];
        FILE *AEntrada=NULL;
        /*Para evaluar los argumentos de entrada usamos argc y argv
        argc es un contador con el numero de argumentos pasado y argv
        es un array de cadenas con los argumentos propiamente
        El primer argumento es el nombre del programa
        */
    	if(strcmp(argv[1], "-h") == 0 || (strcmp(argv[1] , "--help") ==0 ))
    	{
     		printf("bocabajo: .*Uso: .*bocabajo.c...El programa recibe un fichero o cadena de texto,\n");
        	printf("bocabajo: El programa devuelve cada  linea del fichero leida  de derecha a izquierda(al reves).\n");
        	return EX_OK;
    	}
	
	if(argc < 2)
        {
		argv0="bocabajo";
            	Error (EX_NOINPUT, "%s", "El numero de argumentos incorrectos.");
        }
	for(i = argc-1; i >=1; i--)
        {
            	AEntrada = NULL;
            	AEntrada=fopen(argv[i],"r");
            	if(AEntrada==NULL)
            	{
			argv0="bocabajo";                	
			Error (EX_NOINPUT, ".*\"%s\"", argv[i] ,"no legible");
             		/*continue; Aunque el fichero no sea valido continuamos en el for*/
            	}
           	else
            	{
		    while(fgets(cadena,TAM_CAD,AEntrada)!= NULL)
			{	
				if(contador=0)
				{
					**pprimer = (char **) malloc(sizeof(char*));
					if(pprimer == NULL) 
					{
						argv0 = "bocabajo";
		      				Error(EX_OSERR,"%s","No se  pudo ubicar la memoria dinamica necesaria.");
					}
					if((psegun=strdup(cadena, TAM_CAD))==NULL)
					{
						argv0 = "bocabajo";
		      				Error(EX_OSERR,"%s","No se  pudo ubicar la memoria dinamica necesaria.");
					}
					else
					{
						*pprimer=psegun;
					}
				}
				else
				{
					pprimer=(char*)realloc(pprimer, ((contador+1)*sizeof(char*)));
					if((psegun=strdup(cadena))==NULL)
					{
						argv0 = "bocabajo";
			      			Error(EX_OSERR,"%s","No se  pudo ubicar la memoria dinamica necesaria.");
					}
					else
					{
						*(pprimer+contador)=psegun;
					}

				}
			contador++;
			}
		free(pprimer[contador]);
		for (k=contador-1; k>=0; k--)
		{
			for (j=0; j<=TAM_CAD; j++)
			{
				printf("%s",*((pprimer[k])+j));		
				free(pprimer[k]);		
			}
		}
		free(pprimer);
		}
        	fclose(AEntrada);
        }
        return 0;
}
