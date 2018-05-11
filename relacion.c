#include "relacion.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int nextId();

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Inicializa un id negativo y el campo isEmpty en true de la Relacion parametrizada.
 *
 * \param relacion Relacion*
 * \return void
 *
 */
void relacion_init(Relacion * relacion){
    Relacion relacionAux;
    relacionAux.id = -1;
    relacionAux.isEmpty = TRUE;
    relacionAux.idCliente = -1;
    relacionAux.idPublicacion = -1;
    *relacion = relacionAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa con datos aleatorios a la Relacion paramerizada.
 *
 * \param relacion Relacion*
 * \return void
 *
 */
void relacion_randomInit(Relacion * relacion){
    Relacion relacionAux;
    relacionAux.id = nextId();
    relacionAux.isEmpty = FALSE;
    relacionAux.idCliente = 3;
    relacionAux.idPublicacion = 0;
    *relacion = relacionAux;
}
/* ------------------------------------------------------------------ */
/** \brief Pide al usuario los campos de una Relacion.
 *
 * \param relacion Relacion*
 * \param addMode int
 * \return int
 *
 */
int relacion_constructor(Relacion * relacion, int addMode, ArrayCliente clientes, ArrayPublicacion * publicaciones){
    Relacion relacionAux = *relacion;
    ArrayPublicacion publicacionesAux = *publicaciones;
    arrayCliente_showList(clientes);

    showSeparator(6);
    showSeparator(4);
    if(util_getInt(&relacionAux.idCliente, "Ingrese ID de cliente: ", "Ingrese un ID correcto. \n", 0, arrayCliente_getLastID(clientes), 3) == FAIL_1)
        return FAIL_1;
    int index = arrayCliente_getIndexOfID(clientes, relacionAux.idCliente);
    if(index < 0 || clientes.listClientes[index].isEmpty)
        return FAIL_1;
    if(arrayPublicacion_add(&publicacionesAux) == FAIL_1)
        return FAIL_1;
    showSeparator(4);
    showSeparator(6);

    relacionAux.idPublicacion = arrayPublicacion_getLastID(publicacionesAux);
    relacionAux.isEmpty = FALSE;
    if(addMode)
        relacionAux.id = nextId();
    *relacion = relacionAux;
    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los campos de una relacion parametrizada.
 *
 * \param relacion Relacion
 * \return void
 *
 */
void relacion_showData(Relacion relacion, Cliente cliente, Publicacion publicacion){
    showHeader(4);
    printf("ID #%d \n", relacion.id);
    cliente_showData(cliente);
    publicacion_showData(publicacion);
}
/* ------------------------------------------------------------------ */
/** \brief Swapea el valor de dos Relacion.
 *
 * \param stP Relacion*
 * \param ndP Relacion*
 * \return int
 *
 */
int relacion_swap(Relacion * stP, Relacion * ndP){
    Relacion auxiliar;
    auxiliar = *stP;
    *stP = *ndP;
    *ndP = auxiliar;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
static int nextId(){
    static int id = -1;
    id++;
    return id;
}
/* ------------------------------------------------------------------ */
