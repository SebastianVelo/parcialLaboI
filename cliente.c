#include "cliente.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int nextId();

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Inicializa un id negativo y el campo isEmpty en true de la Cliente parametrizada.
 *
 * \param cliente Cliente*
 * \return void
 *
 */
void cliente_init(Cliente * cliente){
    Cliente clienteAux;
    clienteAux.id = -1;
    clienteAux.isEmpty = TRUE;
    clienteAux.publicaciones = 0;
    *cliente = clienteAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa con datos aleatorios a la Cliente paramerizada.
 *
 * \param cliente Cliente*
 * \return void
 *
 */
void cliente_randomInit(Cliente * cliente){
    Cliente clienteAux;
    clienteAux.id = nextId();
    clienteAux.isEmpty = FALSE;
    clienteAux.DNI = CLIENTE_DNI_MIN + rand() % (CLIENTE_DNI_MAX - CLIENTE_DNI_MIN);
    strcpy(clienteAux.name, util_getWord());
    strcpy(clienteAux.surname, util_getWord());
    clienteAux.publicaciones = 0;
    *cliente = clienteAux;
}
/* ------------------------------------------------------------------ */
/** \brief Pide al usuario los campos de una Cliente.
 *
 * \param cliente Cliente*
 * \param addMode int
 * \return int
 *
 */
int cliente_constructor(Cliente * cliente, int addMode){
    Cliente clienteAux = *cliente;

    showSeparator(6);
    showSeparator(4);
    if(util_getString(&clienteAux.name, "Ingrese nombre: ", NAME_LENGTH) == FAIL_1)
        return FAIL_1;
    if(util_getString(&clienteAux.surname, "Ingrese apellido: ", NAME_LENGTH) == FAIL_1)
        return FAIL_1;
    if(util_getInt(&clienteAux.DNI, "Ingrese DNI: ", "Ingrese un DNI correcto. \n", CLIENTE_DNI_MIN, CLIENTE_DNI_MAX, 3) == FAIL_1)
        return FAIL_1;
    showSeparator(4);
    showSeparator(6);

    clienteAux.isEmpty = FALSE;
    if(addMode)
        clienteAux.id = nextId();
    *cliente = clienteAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los campos de una cliente parametrizada.
 *
 * \param cliente Cliente
 * \return void
 *
 */
void cliente_showData(Cliente cliente){
    showSeparator(4);
    printf("ID #%d \t\t", cliente.id);
    printf("Nombre completo: %s %s\t\t", cliente.name, cliente.surname);
    printf("DNI: %d \t", cliente.DNI);
    printf("Publicaciones: %d \n", cliente.publicaciones);
}
/* ------------------------------------------------------------------ */
/** \brief Swapea el valor de dos Cliente.
 *
 * \param stP Cliente*
 * \param ndP Cliente*
 * \return int
 *
 */
int cliente_swap(Cliente * stP, Cliente * ndP){
    Cliente auxiliar;
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
