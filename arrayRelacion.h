#include "relacion.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define ARRAYRELACION_LENGTH 7
/** OPTIONS */
#define RELACION_RAND 0
#define RELACION_ADD 1
#define RELACION_DEL 2
#define RELACION_EDIT 3
#define RELACION_STOP 4
#define RELACION_REINIT 5
#define RELACION_SHOWL 6
#define RELACION_RETURN 7
/** MESSAGE */
#define RELACION_ASKID "Ingrese el ID de relacion: "
#define RELACION_ASKIDFAIL "Ingrese un ID de relacion valido."
#define RELACION_GENERICMSGFAIL "Agoto el limite de reintentos. Vuelva a intentar."
#define RELACION_ENTITY "PUBLICACION"
#define RELACION_SHWLMSGOK "¡Aqui esta la lista!"
#define RELACION_ADDMSGOK "¡Relacion agregada correctamente!"
#define RELACION_DELMSGOK "¡Relacion borrada correctamente!"
#define RELACION_EDITMSGOK "¡Relacion editada correctamente!"
#define RELACION_SHWLMSGF1 "¡Aun no hay relaciones en la lista!"
#define RELACION_ADDMSGF1 "¡Ya esta el cupo de relaciones! Escriba opcion %d para borrar relaciones."
#define RELACION_EDITDELMSGF1 "¡Aun no ingreso a esta relacion! Escriba opcion %d para agregar relaciones."

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct ArrayRelacion {
   Relacion listRelaciones[ARRAYRELACION_LENGTH];
   int length;
} ArrayRelacion;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void arrayRelacion_init(ArrayRelacion * relaciones);
void arrayRelacion_showOptions(void);
int arrayRelacion_add(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion * publicaciones);
int arrayRelacion_del(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones);
int arrayRelacion_edit(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion * publicaciones);
int arrayRelacion_showList(ArrayRelacion relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones);
int arrayRelacion_showResp(ArrayRelacion * relaciones, int option, ArrayCliente clientes, ArrayPublicacion  * publicaciones);
int arrayRelacion_getIndexOfID(ArrayRelacion relaciones, int id);
