#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL_1 SUCCESS-1
#define FAIL_2 FAIL_1-1
#define FAIL_3 FAIL_2-1

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
char util_getChar(int i, int n);
int util_getInt(int *resultado, char* mensaje, char* mensajeError, int maximo, int minimo,  int reintentos);
int util_getFloat(float *resultado, char* mensaje, char* mensajeError, int maximo, int minimo,  int reintentos);
int util_getString(char *resultado, char* mensaje, int length);
int util_getMax(int * arrayInt, int size);
int util_getMin(int * arrayInt, int size);
