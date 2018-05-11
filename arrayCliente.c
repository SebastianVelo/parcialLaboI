#include "arrayCliente.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int firstIndexAvailable(ArrayCliente clientes);
static int sortArray(ArrayCliente * clientes);
static int showMsg(int option, int resp);

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */

/** \brief Inicializa en vacio el campo listaClientes del ArrayClientes parametrizado.
 *
 * \param clientes ArrayCliente*
 * \return void
 *
 */
void arrayCliente_init(ArrayCliente * clientes){
    ArrayCliente clientesAux;
    clientesAux.length = ARRAYCLIENTE_LENGTH;
    int i;
    for(i = 0; i < clientesAux.length; i++){
        cliente_init(&clientesAux.listClientes[i]);
    }
    *clientes = clientesAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa de manera aleatoria el campo listaClientes del ArrayCliente parametrizado
 *
 * \param clientes ArrayCliente*
 * \return void
 *
 */
void arrayCliente_randomInit(ArrayCliente * clientes){
    ArrayCliente clientesAux;
    clientesAux.length = ARRAYCLIENTE_LENGTH;
    int i;
    for(i = 0; i < clientesAux.length; i++){
        cliente_randomInit(&clientesAux.listClientes[i]);
    }
    *clientes = clientesAux;
}
/* ------------------------------------------------------------------ */
/** \brief Agrega una cliente al campo listaClientes del ArrayCliente parametrizado.
 *
 * \param clientes ArrayCliente*
 * \return int
 *
 */
int arrayCliente_add(ArrayCliente * clientes){
    ArrayCliente clientesAux = *clientes;
    int index = firstIndexAvailable(clientesAux);
    if(index == FAIL_1)
        return FAIL_1;
    if(cliente_constructor(&clientesAux.listClientes[index], TRUE) == FAIL_1)
        return FAIL_3;

    *clientes = clientesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y borra una cliente del campo listaClientes del ArrayCliente parametrizado.
 *
 * \param clientes ArrayCliente*
 * \return int
 *
 */
int arrayCliente_del(ArrayCliente * clientes){
    ArrayCliente clientesAux = *clientes;
    if(arrayCliente_showList(clientesAux) == FAIL_1)
        return FAIL_1;
    int id;
    if(util_getInt(&id, CLIENTE_ASKID, CLIENTE_ASKIDFAIL, 0, clientesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayCliente_getIndexOfID(clientesAux, id);

    if(clientesAux.listClientes[index].isEmpty)
        return FAIL_2;
    else
        cliente_init(&clientesAux.listClientes[index]);

    *clientes = clientesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y edita los campos de esa cliente que este en listaClientes del ArrayCliente parametrizado.
 *
 * \param clientes ArrayCliente*
 * \return int
 *
 */
int arrayCliente_edit(ArrayCliente * clientes){
    ArrayCliente clientesAux = *clientes;
    if(arrayCliente_showList(clientesAux) == FAIL_1)
        return FAIL_1;

    int id;
    if(util_getInt(&id, CLIENTE_ASKID, CLIENTE_ASKIDFAIL, 0, clientesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayCliente_getIndexOfID(clientesAux, id);

    if(clientesAux.listClientes[index].isEmpty)
        return FAIL_2;
    else if(cliente_constructor(&clientesAux.listClientes[index], FALSE) == FAIL_1)
        return FAIL_3;

    *clientes = clientesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las clientes que esten activas en el listaClientes del ArrayClientes parametrizado.
 *
 * \param clientes ArrayCliente
 * \return int
 *
 */
int arrayCliente_showList(ArrayCliente clientes){
    int ret = FAIL_1;
    int i;
    sortArray(&clientes);
    showSeparator(4);
    printf("%s\n", CLIENTE_ENTITY);
    for(i = 0; i < clientes.length; i++){
        if(!clientes.listClientes[i].isEmpty){
            cliente_showData(clientes.listClientes[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Pide una opcion por parametro y ejecuta esa accion, obteniendo la respuesta de cada uno y sus posibles errores
 *
 * \param clientes ArrayCliente*
 * \param option int
 * \return int
 *
 */
int arrayCliente_showResp(ArrayCliente * clientes, int option){
	int resp = 1;

	ArrayCliente clientesAux = *clientes;
	switch(option){
        case CLIENTE_RAND:
			arrayCliente_randomInit(&clientesAux);
            break;
        case CLIENTE_SHOWL:
			resp = arrayCliente_showList(clientesAux);
            break;
        case CLIENTE_ADD:
            resp = arrayCliente_add(&clientesAux);
            break;
        case CLIENTE_DEL:
            resp = arrayCliente_del(&clientesAux);
            break;
        case CLIENTE_EDIT:
            resp = arrayCliente_edit(&clientesAux);
            break;
		default:
			return FAIL_1;
	}
	*clientes = clientesAux;
	showMsg(option, resp);
	return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra las opciones que se pueden realizar sobre un ArrayCliente
 *
 * \param void
 * \return void
 *
 */
void arrayCliente_showOptions(void){
    tab(TABSIZE);
    printf("%d : CARGAR ALEATOREAMENTE %s \n", CLIENTE_RAND, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("%d : AGREGAR %s \n", CLIENTE_ADD, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("%d : BORRAR %s \n", CLIENTE_DEL, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("%d : EDITAR %s \n", CLIENTE_EDIT, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR LISTA DE  %s \n", CLIENTE_SHOWL, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR GRAFICO DE EDAD DE %s \n", CLIENTE_SHOWGR, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("%d : VOLVER \n", CLIENTE_RETURN);
    tab(TABSIZE);
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una cliente parametrizada dentro del campo listaClientes del ArrayCliente
 *
 * \param clientes ArrayCliente
 * \param id int
 * \return int
 *
 */
int arrayCliente_getIndexOfID(ArrayCliente clientes, int id){
    int i;
    for(i = 0; i < clientes.length; i++){
        if(!clientes.listClientes[i].isEmpty && clientes.listClientes[i].id == id)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una clientes parametrizada dentro del campo listaClientes del ArrayProducto
 *
 * \param clientes ArrayProducto
 * \param id int
 * \return int
 *
 */
int arrayCliente_getLastID(ArrayCliente clientes){
    int i;
    int idMax = 0;
    for(i = 0; i < clientes.length; i++){
        if(!clientes.listClientes[i].isEmpty && clientes.listClientes[i].id > idMax)
            idMax = clientes.listClientes[i].id;
    }
    return idMax;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Devuelve el primer indice que este disponible para cargar clientes.
 *
 * \param clientes ArrayCliente
 * \return int
 *
 */
static int firstIndexAvailable(ArrayCliente clientes){
    int i;
    for(i = 0; i < clientes.length; i++){
        if(clientes.listClientes[i].isEmpty)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Ordena el campo listaClientes por el nombre de cada elemento, del ArrayCliente paramtrizado
 *
 * \param clientes ArrayCliente*
 * \return int
 *
 */
static int sortArray(ArrayCliente * clientes){
	ArrayCliente clientesAux = *clientes;
    int flagSwap;
    int i;
    if(clientesAux.length < 1)
        return FAIL_1;
    do{
        flagSwap = FALSE;
        for(i=0; i < clientesAux.length-1; i++) {
            if(strcmp(clientesAux.listClientes[i].name, clientesAux.listClientes[i+1].name) > 0){
                cliente_swap(&clientesAux.listClientes[i], &clientesAux.listClientes[i+1]);
                flagSwap = TRUE;
            }
        }
    }while(flagSwap);
    *clientes = clientesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra el mensaje que haya respondido la funcion pedida.
 *
 * \param option int
 * \param resp int
 * \return int
 *
 */
static int showMsg(int option, int resp){
	switch(resp){
		case SUCCESS:
				if(option == CLIENTE_SHOWL)
					printf(CLIENTE_SHWLMSGOK);
				else if(option == CLIENTE_ADD)
					printf(CLIENTE_ADDMSGOK);
				else if(option == CLIENTE_DEL)
					printf(CLIENTE_DELMSGOK);
				else if(option == CLIENTE_EDIT)
					printf(CLIENTE_EDITMSGOK);
				else
					return FAIL_1;
				break;
		case FAIL_1:
				if(option == CLIENTE_SHOWL || option == CLIENTE_DEL ||option == CLIENTE_EDIT)
					printf(CLIENTE_SHWLMSGF1);
				else if(option == CLIENTE_ADD)
					printf(CLIENTE_ADDMSGF1, CLIENTE_DEL);
				else
					return FAIL_1;
				break;
		case FAIL_2:
				if(option == CLIENTE_DEL || option == CLIENTE_EDIT)
					printf(CLIENTE_EDITDELMSGF1, CLIENTE_ADD);
				else
					return FAIL_1;
				break;
		case FAIL_3:
				if(option == CLIENTE_DEL || option == CLIENTE_EDIT || option == CLIENTE_ADD)
					printf(CLIENTE_GENERICMSGFAIL);
				else
					return FAIL_1;
				break;
		default:
				return FAIL_1;
				break;
	}
	return SUCCESS;
}
