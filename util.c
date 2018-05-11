#include "util.h"

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
int util_getInt(int *resultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
    long resultadoAux = 0;
    int ret = FAIL_1;
    do{
        fflush(stdin);

		printf("%s", mensaje);
        scanf("%ld", &resultadoAux);
        if((resultadoAux >= minimo && resultadoAux <= maximo)){
            *resultado = (int) resultadoAux;
            ret = SUCCESS;
            break;
        }
        printf("%s", mensajeError);
        reintentos--;
    }while(reintentos > 0);

    return ret;
}
/* ------------------------------------------------------------------ */
int util_getFloat(float *resultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
    float resultadoAux = 0;
    int ret = FAIL_1;
    do{
        fflush(stdin);

		printf("%s", mensaje);
        scanf("%f", &resultadoAux);
        int isValid = (resultadoAux > minimo && resultadoAux < maximo);
        if(isValid) {
            *resultado = resultadoAux;
            ret = SUCCESS;
            break;
        }
        printf("%s", mensajeError);
        reintentos--;
    }while(reintentos > 0);

    return ret;
}
/* ------------------------------------------------------------------ */
int util_getString(char *resultado, char* mensaje, int length){
    int ret = SUCCESS;
    fflush(stdin);
    printf("%s", mensaje);
    fgets(resultado, length, stdin);
    return ret;
}
/* ------------------------------------------------------------------ */
int util_getMax(int * arrayInt, int size){
    int max = arrayInt[0];
    int i;
    for(i = 0; i < size; i++){
        if(arrayInt[i] > max)
            max = arrayInt[i];
    }
    return max;
}
/* ------------------------------------------------------------------ */
int util_getMin(int * arrayInt, int size){
    int min = arrayInt[0];
    int i;
    for(i = 0; i < size; i++){
        if(arrayInt[i] < min)
            min = arrayInt[i];
    }
    return min;
}
/* ------------------------------------------------------------------ */
char util_getChar(int i, int n){
    return (i > n) ? ' ' : '*';
}
/* ------------------------------------------------------------------ */
char * util_getWord(){
    char consonante[] = "BCDFGHJKLMNPQRSTVWXYZ";
    char vocal[]      = "AEIOU";
    char ret[7];
    int i;
    for(i = 0; i < 6; i++){
        if(i % 2 == 0)
            ret[i] = consonante[rand() % 20];
        else
            ret[i] = vocal[rand() % 4];
    }
    return ret;
}
