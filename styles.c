#include "styles.h"

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
void tab(int size){
     int i;
     for(i = 0; i < size; i++)
        printf("\t");
}
/* ------------------------------------------------------------------ */
void showHeader(int size){
     int i;
     printf("\n");
     for(i = 0; i < size; i++)
        printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\");
     printf("\n");
}
/* ------------------------------------------------------------------ */
void showSeparator(int size){
     int i;
     for(i = 0; i < size; i++)
        printf("||||");
     printf("\n");
}
/* ------------------------------------------------------------------ */
void showGraph(int * columns, int size){
    int i;
    int j;
    int maximo = util_getMax(columns, size);

    for(i = maximo; i > 0; i--){
        tab(TABSIZE);
        for(j = 0; j < size; j++)
            printf("|%c\t", util_getChar(i, columns[j]));
        printf("| #%d\n", i);
    }
    tab(TABSIZE);
    showSeparator(6);
}
/* ------------------------------------------------------------------ */
