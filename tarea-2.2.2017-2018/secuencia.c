#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sysexits.h>
#include "auxiliar.h"

int llamada_strtod_hasta(char *s)
{
    	char *endp;
   	 double d;
    	d = strtod(s, &endp);
    	if (s != endp && *endp == '\0')
     		return  0;
    	else
	{
		argv0 = "secuencia"; /* de auxiliar.c */
      		Error(EX_USAGE,"%s","El parametro \"hasta\" no es un real valido");
	}
    	return 0;
}
int llamada_strtod_desde (char *s)
{
    	char *endp;
    	double d;
    	d = strtod(s, &endp);
    	if (s != endp && *endp == '\0')
        	return  0;
    	else
	{
		argv0 = "secuencia"; /* de auxiliar.c */
      	Error(EX_USAGE,"%s","El parametro \"desde\" no es un real valido");
	}
   	 return 0;
}
int llamada_strtod_paso (char *s)
{
    	char *endp;
    	double d;
    	d = strtod(s, &endp);
    	if (s != endp && *endp == '\0')
        	return  0;
    	else
	{
		argv0 = "secuencia"; /* de auxiliar.c */
      		Error (EX_USAGE,"%s","El parametro \"paso\" no es un real valido");
	}    
	return 0;
}
int main(int argc, char **argv)
{
	float i;
	int a=0;
	int limite;
    	char *endp;
	char *lim = getenv("MAX_OUTPUT");

	if((lim == NULL) || (strtod(lim, &endp)<0) || (strtod(lim, &endp) > atoi(lim)) || (strlen(lim)==0))
	{
		limite=100;
	}

	else
	{

		limite=atoi(getenv("MAX_OUTPUT"));
		if (strtod(lim, &endp) ==0 && (strlen(lim)!=0) )
		{
			argv0 = "secuencia"; /* de auxiliar.c */
			Error (EX_NOPERM, "%s", "Se intento superar el limite de salida establecido por MAX_OUTPUT.");
		}

	}

	if(argc==1)
	{
		for(i=1; i<=10; i++)
		{
			printf("\t%g\n", i);
		}
		return  0;
	}
	if(strcmp(argv[1], "-h") == 0 || (strcmp(argv[1] , "--help") ==0 ))
        		{
                		printf("secuencia: Uso: secuencia [ hasta [ desde [ paso ]]]\n");
                		printf("secuencia: Genera la secuencia de numeros en el intervalo y paso indicados.\n");
                		return EX_OK;
        		}
	if(llamada_strtod_hasta(argv[1])==0)
	{
		float hasta=strtod(argv[1], &endp);
        	if(argc==2)
		{
			for(i=1; i<=hasta; i++)
			{
				if(i>limite)
				{
					argv0 = "secuencia"; /* de auxiliar.c */
					Error (EX_NOPERM, "%s", "Se intento superar el limite de salida establecido por MAX_OUTPUT.");
				}
				printf("\t%g\n", i);		
			}
			return 0;	
		}
		if(llamada_strtod_desde(argv[2])==0)
		{
			float desde=strtod(argv[2], &endp);
			if(argc==3)
			{
			
				if(desde>hasta)
				{
					argv0 = "secuencia"; /* de auxiliar.c */
					Error (EX_USAGE, "%s", "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".");
				}
				for(i=desde; i<=hasta; i++)
				{
					printf("\t%g\n", i);
					a++;
					if(a==limite)
					{
						argv0 = "secuencia"; /* de auxiliar.c */
						Error (EX_NOPERM, "%s", "Se intento superar el limite de salida establecido por MAX_OUTPUT.");
					}
				}
				return 0;
			}
			if(llamada_strtod_paso(argv[3])==0)
			{
				float paso=strtod(argv[3], &endp);
				if(argc==4)
				{
					if(paso==0)
					{
						argv0 = "secuencia"; /* de auxiliar.c */
						Error (EX_USAGE, "%s", "El parametro \"paso\" no puede valer 0.");
			
					}
					if((desde>hasta && paso>0) || (desde<hasta && paso<0))
					{
						argv0 = "secuencia"; /* de auxiliar.c */
						Error (EX_USAGE, "%s", "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".");
					}
					if(paso>0)
                			{
						i=desde;
                        			while(i<=hasta)
                        			{
                                			printf("\t%g\n",i);
                                			i=i+paso;
                                			a++;
                                			if(a==limite)
							{
								argv0 = "secuencia"; /* de auxiliar.c */
								Error (EX_NOPERM, "%s", "Se intento superar el limite de salida establecido por MAX_OUTPUT.");
                               				}
                       				}
					return  0;
               	 			}
                			if(paso<0 && desde > hasta)
                			{
						i=desde;
                        			while(i>=hasta)
                       	 			{
                               				printf("\t%g\n",i);
                               				i=i+paso;
                               				a++;
                               				if(a==limite)
                               				{
								argv0 = "secuencia"; /* de auxiliar.c */
								Error (EX_NOPERM, "%s", "Se intento superar el limite de salida establecido por MAX_OUTPUT.");
                                			}
                        			}
                			}
               	 		}
			}
		}
        }
	if(argc>4)
	{
		argv0 = "secuencia"; /* de auxiliar.c */
		Error (EX_USAGE, "%s", "En numero de argumentos no es correcto.");

	}
	return 0;
}
