#include "arrayRelacion.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int firstIndexAvailable(ArrayRelacion relaciones);
static int sortArray(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones);
static int showMsg(int option, int resp);
static int getCantidadPublicacionesById(ArrayRelacion relaciones, int id, ArrayPublicacion publicaciones, int filter);
static int getCantidadRubroById(ArrayRelacion relaciones, int id, ArrayPublicacion publicaciones);
/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */

/** \brief
 *
 * \param relaciones ArrayRelacion*
 * \return void
 *
 */
void arrayRelacion_refresh(ArrayRelacion * relaciones, ArrayCliente clientes){
    ArrayRelacion relacionesAux = *relaciones;
    int i;
    for(i = 0; i < relacionesAux.length; i++){
        int id = relacionesAux.listRelaciones[i].idCliente;
        int index = arrayCliente_getIndexOfID(clientes, id);
        if(!relacionesAux.listRelaciones[i].isEmpty && clientes.listClientes[index].isEmpty)
                relacionesAux.listRelaciones[i].isEmpty = TRUE;
    }
    *relaciones = relacionesAux;
}
/** \brief
 *
 * \param relaciones ArrayRelacion*
 * \return void
 *
 */
void arrayRelacion_refreshClientes(ArrayRelacion * relaciones, ArrayPublicacion publicaciones, ArrayCliente * clientes){
    ArrayRelacion relacionesAux = *relaciones;
    ArrayCliente clientesAux = *clientes;
    int i;
    for(i = 0; i < relacionesAux.length; i++){
        int id = relacionesAux.listRelaciones[i].idCliente;
        int index = arrayCliente_getIndexOfID(clientesAux, id);
        if(!relacionesAux.listRelaciones[i].isEmpty)
            clientesAux.listClientes[index].publicaciones = getCantidadPublicacionesById(relacionesAux, id, publicaciones, PUBLICACION_ACTIVA);
    }
    *relaciones = relacionesAux;
    *clientes = clientesAux;
}
/** \brief Inicializa en vacio el campo listaRelaciones del ArrayRelaciones parametrizado.
 *
 * \param relaciones ArrayRelacion*
 * \return void
 *
 */
void arrayRelacion_init(ArrayRelacion * relaciones){
    ArrayRelacion relacionesAux;
    relacionesAux.length = ARRAYRELACION_LENGTH;
    int i;
    for(i = 0; i < relacionesAux.length; i++){
        relacion_init(&relacionesAux.listRelaciones[i]);
    }
    *relaciones = relacionesAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa de manera aleatoria el campo listaRelaciones del ArrayRelacion parametrizado
 *
 * \param relaciones ArrayRelacion*
 * \return void
 *
 */
void arrayRelacion_randomInit(ArrayRelacion * relaciones){
    ArrayRelacion relacionesAux;
    relacionesAux.length = ARRAYRELACION_LENGTH;
    int i;
    for(i = 0; i < relacionesAux.length; i++){
        relacion_randomInit(&relacionesAux.listRelaciones[i]);
    }
    *relaciones = relacionesAux;
}
/* ------------------------------------------------------------------ */
/** \brief Agrega una relacion al campo listaRelaciones del ArrayRelacion parametrizado.
 *
 * \param relaciones ArrayRelacion*
 * \return int
 *
 */
int arrayRelacion_add(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion * publicaciones){
    ArrayRelacion relacionesAux = *relaciones;
    ArrayPublicacion publicacionesAux = *publicaciones;
    int index = firstIndexAvailable(relacionesAux);
    if(index == FAIL_1)
        return FAIL_1;
    if(relacion_constructor(&relacionesAux.listRelaciones[index], TRUE, clientes, &publicacionesAux) == FAIL_1)
        return FAIL_3;
    *relaciones = relacionesAux;
    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y borra una relacion del campo listaRelaciones del ArrayRelacion parametrizado.
 *
 * \param relaciones ArrayRelacion*
 * \return int
 *
 */
int arrayRelacion_del(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones){
    ArrayRelacion relacionesAux = *relaciones;
    if(arrayRelacion_showList(relacionesAux, clientes, publicaciones) == FAIL_1)
        return FAIL_1;
    int id;
    if(util_getInt(&id, RELACION_ASKID, RELACION_ASKIDFAIL, 0, relacionesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayRelacion_getIndexOfID(relacionesAux, id);

    if(relacionesAux.listRelaciones[index].isEmpty)
        return FAIL_2;
    else
        relacion_init(&relacionesAux.listRelaciones[index]);

    *relaciones = relacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y edita los campos de esa relacion que este en listaRelaciones del ArrayRelacion parametrizado.
 *
 * \param relaciones ArrayRelacion*
 * \return int
 *
 */
int arrayRelacion_edit(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion * publicaciones){
    ArrayRelacion relacionesAux = *relaciones;
    ArrayPublicacion publicacionesAux = *publicaciones;
    if(arrayRelacion_showList(relacionesAux, clientes, *publicaciones) == FAIL_1)
        return FAIL_1;

    int id;
    if(util_getInt(&id, RELACION_ASKID, RELACION_ASKIDFAIL, 0, relacionesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayRelacion_getIndexOfID(relacionesAux, id);

    if(relacionesAux.listRelaciones[index].isEmpty)
        return FAIL_2;
    else if(relacion_constructor(&relacionesAux.listRelaciones[index], FALSE, clientes, &publicacionesAux) == FAIL_1)
        return FAIL_3;

    *relaciones = relacionesAux;
    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las relaciones que esten activas en el listaRelaciones del ArrayRelaciones parametrizado.
 *
 * \param relaciones ArrayRelacion
 * \return int
 *
 */
int arrayRelacion_showList(ArrayRelacion relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones){
    int ret = FAIL_1;
    int i;
    sortArray(&relaciones, clientes, publicaciones);
    showSeparator(4);
    printf("%s\n", RELACION_ENTITY);
    for(i = 0; i < relaciones.length; i++){
        int id = relaciones.listRelaciones[i].idPublicacion;
        int index = arrayPublicacion_getIndexOfID(publicaciones, id);
        if(!relaciones.listRelaciones[i].isEmpty && publicaciones.listPublicaciones[index].state == PUBLICACION_ACTIVA){
            int cliente = arrayCliente_getIndexOfID(clientes, relaciones.listRelaciones[i].idCliente);
            int publicacion = arrayPublicacion_getIndexOfID(publicaciones, relaciones.listRelaciones[i].idPublicacion);
            relacion_showData(relaciones.listRelaciones[i], clientes.listClientes[cliente], publicaciones.listPublicaciones[publicacion]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las relaciones que esten activas en el listaRelaciones del ArrayRelaciones parametrizado.
 *
 * \param relaciones ArrayRelacion
 * \return int
 *
 */
int arrayRelacion_showClienteConMasAvisosFilter(ArrayRelacion relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones, int filter){
    int ret = FAIL_1;
    int i;
    int maxAvisos = 0;
    int maxCliente = 0;
    sortArray(&relaciones, clientes, publicaciones);
    showSeparator(4);
    printf("%s\n", RELACION_ENTITY);
    for(i = 0; i < relaciones.length; i++){
        int id = relaciones.listRelaciones[i].idPublicacion;
        int index = arrayPublicacion_getIndexOfID(publicaciones, id);

        if(!relaciones.listRelaciones[i].isEmpty && (publicaciones.listPublicaciones[index].state == filter || filter == PUBLICACION_ALL)){
            int cliente = arrayCliente_getIndexOfID(clientes, relaciones.listRelaciones[i].idCliente);
            if(getCantidadPublicacionesById(relaciones, cliente, publicaciones, filter) > maxAvisos){
                maxAvisos = getCantidadPublicacionesById(relaciones, cliente, publicaciones, filter);
                maxCliente = cliente;
                ret = SUCCESS;
            }
        }
    }
    if(ret == SUCCESS)
        cliente_showData(clientes.listClientes[maxCliente]);
    showSeparator(4);
    return ret;
}
/** \brief Muestra los datos de todas las relaciones que esten activas en el listaRelaciones del ArrayRelaciones parametrizado.
 *
 * \param relaciones ArrayRelacion
 * \return int
 *
 */
int arrayRelacion_showRubrosConMasAvisosFilter(ArrayRelacion relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones){
    int ret = FAIL_1;
    int i;
    int maxAvisos = 0;
    int maxRubro = 0;
    sortArray(&relaciones, clientes, publicaciones);
    showSeparator(4);
    printf("RUBRO\n");
    for(i = 0; i < PUBLICACION_rubro_MAX; i++){
       if(getCantidadRubroById(relaciones, i, publicaciones) > maxAvisos){
            maxAvisos = getCantidadRubroById(relaciones, i, publicaciones);
            maxRubro = i;
       }
    }
    if(ret == SUCCESS)
        printf("El rubro con mas publicaciones activas es %d con %d", maxRubro, getCantidadRubroById(relaciones, i, publicaciones));
    showSeparator(4);
    return ret;
}
/** \brief Muestra los datos de todas las relaciones que esten activas en el listaRelaciones del ArrayRelaciones parametrizado.
 *
 * \param relaciones ArrayRelacion
 * \return int
 *
 */
int arrayRelacion_showRubrosConMenosAvisosFilter(ArrayRelacion relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones){
    int ret = FAIL_1;
    int i;
    int minRubro = 0;
    int minAvisos = 0;
    sortArray(&relaciones, clientes, publicaciones);
    showSeparator(4);
    printf("RUBRO\n");
    for(i = 0; i < PUBLICACION_rubro_MAX; i++){
       if(getCantidadRubroById(relaciones, i, publicaciones) < minRubro){
            minRubro = getCantidadRubroById(relaciones, i, publicaciones);
            ret = SUCCESS;
       }
    }
    if(ret == SUCCESS)
        printf("El rubro con mas publicaciones activas es %d con %d", minRubro, getCantidadRubroById(relaciones, i, publicaciones));
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Pide una opcion por parametro y ejecuta esa accion, obteniendo la respuesta de cada uno y sus posibles errores
 *
 * \param relaciones ArrayRelacion*
 * \param option int
 * \return int
 *
 */
int arrayRelacion_showResp(ArrayRelacion * relaciones, int option, ArrayCliente clientes, ArrayPublicacion * publicaciones){
	int resp = 1;

	ArrayRelacion relacionesAux = *relaciones;
	ArrayPublicacion publicacionesAux = *publicaciones;
	switch(option){
        case RELACION_RAND:
			arrayRelacion_randomInit(&relacionesAux);
            break;
        case RELACION_SHOWL:
			resp = arrayRelacion_showList(relacionesAux, clientes, publicacionesAux);
            break;
        case RELACION_ADD:
            resp = arrayRelacion_add(&relacionesAux, clientes, &publicacionesAux);
            break;
        case RELACION_DEL:
            resp = arrayRelacion_del(&relacionesAux, clientes, publicacionesAux);
            break;
        case RELACION_EDIT:
            resp = arrayRelacion_edit(&relacionesAux, clientes, &publicacionesAux);
            break;
        case RELACION_STOP:
            resp = arrayPublicacion_changeState(&publicacionesAux, PUBLICACION_PAUSA);
            break;
        case RELACION_REINIT:
            resp = arrayPublicacion_changeState(&publicacionesAux, PUBLICACION_ACTIVA);
            break;
		default:
			return FAIL_1;
	}
	*relaciones = relacionesAux;
    *publicaciones = publicacionesAux;
	showMsg(option, resp);
	return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra las opciones que se pueden realizar sobre un ArrayRelacion
 *
 * \param void
 * \return void
 *
 */
void arrayRelacion_showOptions(void){
    tab(TABSIZE);
    printf("%d : CARGAR ALEATOREAMENTE %s \n", RELACION_RAND, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : AGREGAR %s \n", RELACION_ADD, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : BORRAR %s \n", RELACION_DEL, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : EDITAR %s \n", RELACION_EDIT, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : PAUSAR %s \n", RELACION_STOP, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : REANUDAR %s \n", RELACION_REINIT, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR LISTA DE  %s \n", RELACION_SHOWL, RELACION_ENTITY);
    tab(TABSIZE);
    printf("%d : VOLVER \n", RELACION_RETURN);
    tab(TABSIZE);
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una relacion parametrizada dentro del campo listaRelaciones del ArrayRelacion
 *
 * \param relaciones ArrayRelacion
 * \param id int
 * \return int
 *
 */
int arrayRelacion_getIndexOfID(ArrayRelacion relaciones, int id){
    int i;
    for(i = 0; i < relaciones.length; i++){
        if(!relaciones.listRelaciones[i].isEmpty && relaciones.listRelaciones[i].id == id)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Devuelve el primer indice que este disponible para cargar relaciones.
 *
 * \param relaciones ArrayRelacion
 * \return int
 *
 */
static int firstIndexAvailable(ArrayRelacion relaciones){
    int i;
    for(i = 0; i < relaciones.length; i++){
        if(relaciones.listRelaciones[i].isEmpty)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Ordena el campo listaRelaciones por el nombre de cada elemento, del ArrayRelacion paramtrizado
 *
 * \param relaciones ArrayRelacion*
 * \return int
 *
 */
static int sortArray(ArrayRelacion * relaciones, ArrayCliente clientes, ArrayPublicacion publicaciones){
	ArrayRelacion relacionesAux = *relaciones;
    int flagSwap;
    int i;
    if(relacionesAux.length < 1)
        return FAIL_1;
    do{
        flagSwap = FALSE;
        for(i=0; i < relacionesAux.length-1; i++) {
            int clienteA = arrayCliente_getIndexOfID(clientes, relacionesAux.listRelaciones[i].idCliente);
            int publicacionA = arrayPublicacion_getIndexOfID(publicaciones, relacionesAux.listRelaciones[i].idPublicacion);
            int clienteB = arrayCliente_getIndexOfID(clientes, relacionesAux.listRelaciones[i+1].idCliente);
            int publicacionB = arrayPublicacion_getIndexOfID(publicaciones, relacionesAux.listRelaciones[i+1].idPublicacion);
            if(strcmp(clientes.listClientes[clienteA].name, clientes.listClientes[clienteB].name) > 0  /*||
               (strcmp(clientes.listClientes[clienteA].name, clientes.listClientes[clienteB].name) == 0   &&
                publicaciones.listPublicaciones[publicacionA].precio > publicaciones.listPublicaciones[publicacionB].precio)*/){
                relacion_swap(&relacionesAux.listRelaciones[i], &relacionesAux.listRelaciones[i+1]);
                flagSwap = TRUE;
            }
        }
    }while(flagSwap);
    *relaciones = relacionesAux;
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
				if(option == RELACION_SHOWL)
					printf(RELACION_SHWLMSGOK);
				else if(option == RELACION_ADD)
					printf(RELACION_ADDMSGOK);
				else if(option == RELACION_DEL)
					printf(RELACION_DELMSGOK);
				else if(option == RELACION_EDIT)
					printf(RELACION_EDITMSGOK);
				else
					return FAIL_1;
				break;
		case FAIL_1:
				if(option == RELACION_SHOWL || option == RELACION_DEL ||option == RELACION_EDIT)
					printf(RELACION_SHWLMSGF1);
				else if(option == RELACION_ADD)
					printf(RELACION_ADDMSGF1, RELACION_DEL);
				else
					return FAIL_1;
				break;
		case FAIL_2:
				if(option == RELACION_DEL || option == RELACION_EDIT)
					printf(RELACION_EDITDELMSGF1, RELACION_ADD);
				else
					return FAIL_1;
				break;
		case FAIL_3:
				if(option == RELACION_DEL || option == RELACION_EDIT || option == RELACION_ADD)
					printf(RELACION_GENERICMSGFAIL);
				else
					return FAIL_1;
				break;
		default:
				return FAIL_1;
				break;
	}
	return SUCCESS;
}



/* ------------------------------------------------------------------ */
/**                     UTILS                                      */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
static int getCantidadPublicacionesById(ArrayRelacion relaciones, int id, ArrayPublicacion publicaciones, int filter){
    int i;
    int ret = 0;
    for(i = 0; i < relaciones.length; i++){
        int idPublicacion = relaciones.listRelaciones[i].idPublicacion;
        int index = arrayPublicacion_getIndexOfID(publicaciones, idPublicacion);
        if(!relaciones.listRelaciones[i].isEmpty && relaciones.listRelaciones[i].idCliente == id && (publicaciones.listPublicaciones[index].state == filter || filter == PUBLICACION_ALL))
            ret++;
    }
    return ret;
}
static int getCantidadRubroById(ArrayRelacion relaciones, int id, ArrayPublicacion publicaciones){
    int i;
    int ret = 0;
    for(i = 0; i < relaciones.length; i++){
        int idPublicacion = relaciones.listRelaciones[i].idPublicacion;
        int index = arrayPublicacion_getIndexOfID(publicaciones, idPublicacion);
        if(!relaciones.listRelaciones[i].isEmpty && publicaciones.listPublicaciones[index].rubro == id)
            ret++;
    }
    return ret;
}
