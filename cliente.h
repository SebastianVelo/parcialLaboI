#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "styles.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define CLIENTE_ID 0
/** MIN AND MAX VALUES */
#define NAME_LENGTH 30
#define CLIENTE_DNI_MIN 5000000
#define CLIENTE_DNI_MAX 99999999
#define CLIENTE_edad_MIN 0
#define CLIENTE_edad_MAX 100

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct Cliente {
   int      isEmpty;
   int      id;
   char     name[NAME_LENGTH];
   char     surname[NAME_LENGTH];
   int      DNI;
   int      publicaciones;
} Cliente;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void cliente_randomInit(Cliente * cliente);
void cliente_init(Cliente * cliente);
void cliente_showData(Cliente cliente);
int cliente_constructor(Cliente * cliente, int addMode);
int cliente_swap(Cliente * stP, Cliente * ndP);
