#include<stdio.h>
#include<string.h>

int main(int argc, char **argv)
{
        int i=0;   
        FILE *AEntrada=NULL;

        //Para evaluar los argumentos de entrada usamos argc y argv
        //argc es un contador con el numero de argumentos pasado y argv
        //es un array de cadenas con los argumentos propiamente
        //El primer argumento es el nombre del programa
        if(argc < 2) 
        {
            printf("Numero de argumentos incorrectos \n");
            return -1;
        }
        

        for(i = 1; i < argc; i++)
        {
            AEntrada = NULL; 
            fpos_t posicion;   //Posicion para situarnos en el fichero
            AEntrada=fopen(argv[i],"r");
            if(AEntrada==NULL)
            {
                printf("Error al acceder o al crear los archivos");
                continue; //Aunque el fichero no sea valido continuamos en el for
            }
            else
	    {
	       printf("\n");
	       fseek(AEntrada, 0L, SEEK_END);
  	       fgetpos(AEntrada, &posicion);
	       posicion.__pos--; //Para no apuntar al EOF

		while(posicion.__pos >=0)
		{
  	          fsetpos(AEntrada,&posicion);
                  printf("%c", fgetc(AEntrada));
		  posicion.__pos--;
                }
            }
            fclose(AEntrada);
	    printf("\n");
        }
        return 0;
}
