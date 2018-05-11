#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "styles.h"
/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define PUBLICACION_ID 1
/** MIN AND MAX VALUES */
#define DESC_LENGTH 64
#define PUBLICACION_rubro_MIN 0
#define PUBLICACION_rubro_MAX 5
#define PUBLICACION_ACTIVA 1
#define PUBLICACION_PAUSA 0

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct Publicacion {
    int      isEmpty;
    int      id;
    int      idCliente;
    char     desc[DESC_LENGTH];
    int      rubro;
    int      state;
} Publicacion;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void publicacion_randomInit(Publicacion * publicacion);
void publicacion_init(Publicacion * publicacion);
void publicacion_showData(Publicacion publicacion);
int publicacion_constructor(Publicacion * publicacion, int addMode);
int publicacion_swap(Publicacion * stP, Publicacion * ndP);
