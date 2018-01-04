#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"

int main(int argc, char *argv[]) {
 double hasta = 10, desde = 1, paso = 1;
 int max = 100;
 int contador = 0;
 char *final, *limite = getenv("MAX_OUTPUT");
 switch(argc) {
  case 1:
  break;

  case 2:
  //Ayuda
  if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
   printf("secuencia: Uso: secuencia[ hasta [ desde [ paso ]]]\n");
   printf("secuencia: Genera la secuencia de números en el intervalo y paso indicados.\n");
   return (EX_OK);
  }

  hasta = strtod(argv[1], &final);
  if(argv[1] == final || *final != '\0') {
   fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
   fprintf(stderr, "secuencia+ El parametro \"hasta\! no es un número real válido.\n");
   return (EX_USAGE);
  }
  break;

  case 3: 
  hasta = strtod(argv[1], &final);
  if(argv[1] == final || *final = '\0') {
   fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
   fprintf(stderr, "secuencia+ El parametro \"hasta\" no es un número real valido.\n");
   return (EX_USAGE);
  }
  desde = strtod(argv[2], &final);
  if(argv[2] == final || *final != '\0') {
   fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
   fprintf(stderr, "secuencia+ El parametro \"desde\" no es un número real valido.\n");
   return (EX_USAGE);
  }
  break;

  case 4:
  hasta = strtod(argv[1], &final);
  if(argv[1] == final || *final != '\0') {
   fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
   fprintf(stderr, "secuencia+ El parametro \"hasta\" no es un número real valido.\n");
   return (EX_USAGE);
  }
  desde = strtod(argv[2], &final);
  if (argv[2] == final || *final != '\0')
  {
   fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
   fprintf(stderr, "secuencia+ El parametro \"desde\" no es un número real valido.\n");
   return (EX_USAGE);
  }
  paso = strtod(argv[3], &final);
  if (argv[3] == final || *final != '\0')
  {
   fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
   fprintf(stderr, "secuencia+ El parametro \"paso\" no es un número real valido.\n");
   return (EX_USAGE);
  }
  break;
 }

 if((hasta < desde && paso >= 0) || (hasta > desde && paso <= 0)) {
  fprintf(stderr, "secuencia: Error(EX_USAGE), uso incorrecto del mandato. \"Success\"\n");
  fprintf(stderr, "secuencia+ El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".\n");
  return (EX_USAGE);
 }
 if(limite != NULL && strlen(limite) != 0 && atoi(getenv("MAX_OUTPUT")) >= 0 && strtod(getenv("MAX_OUTPUT"), &final) - atoi(getenv("MAX_OUTPUT")) == 0) {
  max = atoi(getenv("MAX_OUTPUT"));
 }
 double i;
 for(i = desde; (paso > 0 && i < hasta) || (paso < 0 && i >=hasta); i = i + paso) {
  if(contador >= max)  {
   fprintf(stderr, "secuencia: Error(EX_NOPERM), permiso denegado. \"Success\"\n");
   fprintf(stderr, "secuencia+ Se intento superar el límite de salida establecido por MAX_OUTPUT.\n");
   return (EX_NOPERM);
  }
  printf("\t%g\n", i);
  contador++;
 }
 return (EX_OK);
}