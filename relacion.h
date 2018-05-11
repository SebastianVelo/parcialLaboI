#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "styles.h"
#include "arrayCliente.h"
#include "arrayPublicacion.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define RELACION_ID 1

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct Relacion {
   int      isEmpty;
   int      id;
   int      idCliente;
   int      idPublicacion;
} Relacion;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void relacion_randomInit(Relacion * relacion);
void relacion_init(Relacion * relacion);
void relacion_showData(Relacion relacion, Cliente cliente, Publicacion publicacion);
int relacion_constructor(Relacion * relacion, int addMode, ArrayCliente clientes, ArrayPublicacion * publicaciones);
int relacion_swap(Relacion * stP, Relacion * ndP);
