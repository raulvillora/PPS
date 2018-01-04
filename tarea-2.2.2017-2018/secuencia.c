#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sysexits.h>
#include	"auxiliar.h"

int	main(int	argc,	char	*argv[])
{
	double	hasta	=	10,	desde	=	1,	paso	=	1;
	int	max	=	100;
	int	contador	=	0;
	char	*final,	*limite	=	getenv("MAX_OUTPUT");

	/**
		* Si el número de argumentos que se le pasan al programa es 2:
		*	Primero comprobamos si ha sido el comando de ayuda, en cuyo caso sacamos mensaje de ayuda
		*	Si no se trata de ayuda entonces el argumento debe de ser un número que representa el valor hasta
		* Convertimos el valor que se nos ha pasado a un double y lo metemos en final
		*	Si no es un número válido sale error
	*/
	if	(argc	==	2)
	{
		if	(strcmp(argv[1],	"-h")	==	0	||	strcmp(argv[1],	"--help")	==	0)
		{
			printf("secuencia: Uso: secuencia[ hasta [ desde [ paso ]]]\n");
			printf("secuencia: Genera la secuencia de números en el intervalo y paso indicados.\n");
			return	(EX_OK);
		}
		hasta	=	strtod(argv[1],	&final);
		if	(argv[1]	==	final	||	*final	!=	'\0')
		{
			//fprintf saca el mensaje escrito por la salida que se le indique, en este caso la salida de errores estandar
			fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
			fprintf(stderr,	"secuencia+ El parametro \"hasta\" no es un número real válido.\n");
			return	(EX_USAGE);
		}
	}

	/** 
		* Realizamos la misma comprobación que en el paso anterior, pero esta vez para los parametros hasta y desde
		* Y en el siguiente if, si argc == 4 igual pero añadiendo además paso
	*/
	if	(argc	==	3)
	{
		hasta	=	strtod(argv[1],	&final);
		if	(argv[1]	==	final	||	*final	!=	'\0')
		{
			fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
			fprintf(stderr,	"secuencia+ El parametro \"hasta\" no es un número real valido.\n");
			return	(EX_USAGE);
		}
		desde	=	strtod(argv[2],	&final);
		if	(argv[2]	==	final	||	*final	!=	'\0')
		{
			fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
			fprintf(stderr,	"secuencia+ El parametro \"desde\" no es un número real valido.\n");
			return	(EX_USAGE);
		}
	}

	if	(argc	==	4)
	{
		hasta	=	strtod(argv[1],	&final);
		if	(argv[1]	==	final	||	*final	!=	'\0')
		{
			fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
			fprintf(stderr,	"secuencia+ El parametro \"hasta\" no es un número real valido.\n");
			return	(EX_USAGE);
		}
		desde	=	strtod(argv[2],	&final);
		if	(argv[2]	==	final	||	*final	!=	'\0')
		{
			fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
			fprintf(stderr,	"secuencia+ El parametro \"desde\" no es un número real valido.\n");
			return	(EX_USAGE);
		}
		paso	=	strtod(argv[3],	&final);
		if	(argv[3]	==	final	||	*final	!=	'\0')
		{
			fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
			fprintf(stderr,	"secuencia+ El parametro \"paso\" no es un número real valido.\n");
			return	(EX_USAGE);
		}
	}

	/**
		*	Si el número de argumentos es mayor que cuatro
		* El número de parametros que se le ha pasado el programa es incorrecto
		* Sale un mensaje de error EX_USAGE
		*/
	if	(argc	>	4)
	{
		fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
		fprintf(stderr,	"secuencia+ El número de argumentos no es correcto.\n");
		return	(EX_USAGE);
	}

	/**
		* Si hasta es menor que desde los pasos a dar seran negativos y viceversa
		* Si el parametro paso no permite ir desde el valor desde hasta el valor de hasta sale un error EX_USAGE
	*/
	if	((hasta	<	desde	&&	paso	>=	0)	||	(hasta	>	desde	&&	paso	<=	0))
	{
		fprintf(stderr,	"secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
		fprintf(stderr,	"secuencia+ El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".\n");
		return	(EX_USAGE);
	}
	if	(limite	!=	NULL	&&	strlen(limite)	!=	0	&&	atoi(getenv("MAX_OUTPUT"))	>=	0	&&	strtod(getenv("MAX_OUTPUT"),	&final)	-	atoi(getenv("MAX_OUTPUT"))	==	0)
	{
		max	=	atoi(getenv("MAX_OUTPUT"));
	}

	double	i;
	for	(i	=	desde;	(paso	>	0	&&	i	<=	hasta)	||	(paso	<	0	&&	i	>	hasta);	i	=	i	+	paso)
	{
		if	(contador	>=	max)
		{
			fprintf(stderr,	"secuencia: Error(EX_NOPERM), permiso denegado. \"Success\"\n");
			fprintf(stderr,	"secuencia+ Se intentó superar el límite de salida.\n");
			return	(EX_NOPERM);
		}
		printf("\t%g\n",	i);
		contador++;
	}
	return	(EX_OK);
}