#include "cliente.h"
/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define ARRAYCLIENTE_LENGTH 7
/** OPTIONS */
#define CLIENTE_RAND 0
#define CLIENTE_ADD 1
#define CLIENTE_DEL 2
#define CLIENTE_EDIT 3
#define CLIENTE_SHOWL 4
#define CLIENTE_SHOWGR 5
#define CLIENTE_RETURN 6
/** MESSAGE */
#define CLIENTE_ASKID "Ingrese el ID de cliente: "
#define CLIENTE_ASKIDFAIL "Ingrese un ID de cliente valido."
#define CLIENTE_GENERICMSGFAIL "Agoto el limite de reintentos. Vuelva a intentar."
#define CLIENTE_ENTITY "CLIENTE"
#define CLIENTE_SHWLMSGOK "¡Aqui esta la lista!"
#define CLIENTE_ADDMSGOK "¡Cliente agregada correctamente!"
#define CLIENTE_DELMSGOK "¡Cliente borrada correctamente!"
#define CLIENTE_EDITMSGOK "¡Cliente editada correctamente!"
#define CLIENTE_SHWLMSGF1 "¡Aun no hay clientes en la lista!"
#define CLIENTE_ADDMSGF1 "¡Ya esta el cupo de clientes! Escriba opcion %d para borrar clientes."
#define CLIENTE_EDITDELMSGF1 "¡Aun no ingreso a esta cliente! Escriba opcion %d para agregar clientes."

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct ArrayCliente {
   Cliente listClientes[ARRAYCLIENTE_LENGTH];
   int length;
} ArrayCliente;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void arrayCliente_init(ArrayCliente * clientes);
void arrayCliente_showOptions(void);
int arrayCliente_add(ArrayCliente * clientes);
int arrayCliente_del(ArrayCliente * clientes);
int arrayCliente_edit(ArrayCliente * clientes);
int arrayCliente_showList(ArrayCliente clientes);
int arrayCliente_showResp(ArrayCliente * clientes, int option);
int arrayCliente_getIndexOfID(ArrayCliente clientes, int id);
