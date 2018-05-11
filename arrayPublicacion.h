#include "publicacion.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define ARRAYPUBLICACION_LENGTH 7
/** OPTIONS */
#define PUBLICACION_RAND 0
#define PUBLICACION_ADD 1
#define PUBLICACION_DEL 2
#define PUBLICACION_EDIT 3
#define PUBLICACION_SHOWL 4
#define PUBLICACION_RETURN 5
/** MESSAGE */
#define PUBLICACION_ASKID "Ingrese el ID de publicacion: "
#define PUBLICACION_ASKIDFAIL "Ingrese un ID de publicacion valido."
#define PUBLICACION_GENERICMSGFAIL "Agoto el limite de reintentos. Vuelva a intentar."
#define PUBLICACION_ENTITY "PUBLICACION"
#define PUBLICACION_SHWLMSGOK "¡Aqui esta la lista!"
#define PUBLICACION_ADDMSGOK "¡Publicacion agregada correctamente!"
#define PUBLICACION_DELMSGOK "¡Publicacion borrada correctamente!"
#define PUBLICACION_EDITMSGOK "¡Publicacion editada correctamente!"
#define PUBLICACION_SHWLMSGF1 "¡Aun no hay publicaciones en la lista!"
#define PUBLICACION_ADDMSGF1 "¡Ya esta el cupo de publicaciones! Escriba opcion %d para borrar publicaciones."
#define PUBLICACION_EDITDELMSGF1 "¡Aun no ingreso a esta publicacion! Escriba opcion %d para agregar publicaciones."

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct ArrayPublicacion {
   Publicacion listPublicaciones[ARRAYPUBLICACION_LENGTH];
   int length;
} ArrayPublicacion;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void arrayPublicacion_init(ArrayPublicacion * publicaciones);
void arrayPublicacion_showOptions(void);
//int arrayPublicacion_add(ArrayPublicacion * publicaciones, ArrayCliente clientes);
int arrayPublicacion_del(ArrayPublicacion * publicaciones);
//int arrayPublicacion_edit(ArrayPublicacion * publicaciones, ArrayCliente clientes);
int arrayPublicacion_showList(ArrayPublicacion publicaciones);
//int arrayPublicacion_showResp(ArrayPublicacion * publicaciones, int option,  ArrayCliente clientes);
int arrayPublicacion_getIndexOfID(ArrayPublicacion publicaciones, int id);
