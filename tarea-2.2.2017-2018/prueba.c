#include <stdio.h>
#include <string.h>

/**
 * Recibe dos parametros de entrada argc y argv.
 * Estos argumentos son usado como una forma de enviar argumentos al programa.
 * El programa recibe el número de argumentos en args y el array de argumentos en argv.
*/
int main(int argc, char **argv)
{
    int i = 0;
    FILE *AEntrada = NULL;

    if (argc < 2)
    {
        printf("Numero de argumentos incorrectos \n");
        return -1;
    }

    for (i = 1; i < argc; i++)
    {
        AEntrada = NULL;
        fpos_t posicion; //Posicion para situarnos en el fichero
        AEntrada = fopen(argv[i], "r");
        if (AEntrada == NULL)
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

            while (posicion.__pos >= 0)
            {
                fsetpos(AEntrada, &posicion);
                printf("%c", fgetc(AEntrada));
                posicion.__pos--;
            }
        }
        fclose(AEntrada);
        printf("\n");
    }
    return 0;
}
