#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "auxiliar.h"


const int LENGTH = 3000;


int main(int argc, char **argv) {
 char cadena[LENGTH];
 int i = 0;
 FILE *AEntrada = NULL;
 if(argc == 1) {
  while (fgets(cadena,LENGTH,stdin) != NULL) {
   int j;
   for(j = LENGTH - 2; j >= 0; j--) {
    printf("%c", cadena[j]);
   }
   printf("\n");
  }
  return 0;
 }
 if(strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "--help") == 0)) {
  printf("delreves: Uso:")
 }
}