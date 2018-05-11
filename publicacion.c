#include "publicacion.h"
#include "arrayCliente.h"
/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int nextId();

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Inicializa un id negativo y el campo isEmpty en true de la Publicacion parametrizada.
 *
 * \param publicacion Publicacion*
 * \return void
 *
 */
void publicacion_init(Publicacion * publicacion){
    Publicacion publicacionAux;
    publicacionAux.id = -1;
    publicacionAux.isEmpty = TRUE;
    *publicacion = publicacionAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa con datos aleatorios a la Publicacion paramerizada.
 *
 * \param publicacion Publicacion*
 * \return void
 *
 */
void publicacion_randomInit(Publicacion * publicacion){
    Publicacion publicacionAux;
    int i;
    publicacionAux.id = nextId();
    publicacionAux.isEmpty = FALSE;
    publicacionAux.state = PUBLICACION_ACTIVA;
    publicacionAux.rubro = PUBLICACION_rubro_MIN + rand() % (PUBLICACION_rubro_MAX - PUBLICACION_rubro_MIN);
    strcpy(publicacionAux.desc, util_getWord());
    for(i = 0; i < 10; i++)
        strcat(publicacionAux.desc, util_getWord());
    *publicacion = publicacionAux;
}
/* ------------------------------------------------------------------ */
/** \brief Pide al usuario los campos de una Publicacion.
 *
 * \param publicacion Publicacion*
 * \param addMode int
 * \return int
 *
 */
int publicacion_constructor(Publicacion * publicacion, int addMode){
    Publicacion publicacionAux = *publicacion;
    showSeparator(6);
    showSeparator(4);
    if(util_getInt(&publicacionAux.rubro, "Ingrese rubro: ", "Ingrese un rubro correcto. \n", PUBLICACION_rubro_MIN, PUBLICACION_rubro_MAX, 3) == FAIL_1)
        return FAIL_1;
    if(util_getString(&publicacionAux.desc, "Ingrese descripcion: ", DESC_LENGTH) == FAIL_1)
        return FAIL_1;
    showSeparator(4);
    showSeparator(6);

    publicacionAux.state = PUBLICACION_ACTIVA;
    publicacionAux.isEmpty = FALSE;
    if(addMode)
        publicacionAux.id = nextId();
    *publicacion = publicacionAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los campos de una publicacion parametrizada.
 *
 * \param publicacion Publicacion
 * \return void
 *
 */
void publicacion_showData(Publicacion publicacion){
    showSeparator(4);
    printf("ID #%d \t\t", publicacion.id);
    printf("Rubro: %d\t\t", publicacion.rubro);
    printf("Descripcion: %s", publicacion.desc);
}
/* ------------------------------------------------------------------ */
/** \brief Swapea el valor de dos Publicacion.
 *
 * \param stP Publicacion*
 * \param ndP Publicacion*
 * \return int
 *
 */
int publicacion_swap(Publicacion * stP, Publicacion * ndP){
    Publicacion auxiliar;
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
