#include "arrayPublicacion.h"
/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int firstIndexAvailable(ArrayPublicacion publicaciones);
static int sortArray(ArrayPublicacion * publicaciones);
static int showMsg(int option, int resp);
static int getPrecioPromedio(ArrayPublicacion publicaciones);
static int getTotalPrecios(ArrayPublicacion publicaciones);
static int getCantidad(ArrayPublicacion publicaciones);
/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */

/** \brief Inicializa en vacio el campo listaPublicaciones del ArrayPublicaciones parametrizado.
 *
 * \param publicaciones ArrayPublicacion*
 * \return void
 *
 */
void arrayPublicacion_init(ArrayPublicacion * publicaciones){
    ArrayPublicacion publicacionesAux;
    publicacionesAux.length = ARRAYPUBLICACION_LENGTH;
    int i;
    for(i = 0; i < publicacionesAux.length; i++){
        publicacion_init(&publicacionesAux.listPublicaciones[i]);
    }
    *publicaciones = publicacionesAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa de manera aleatoria el campo listaPublicaciones del ArrayPublicacion parametrizado
 *
 * \param publicaciones ArrayPublicacion*
 * \return void
 *
 */
void arrayPublicacion_randomInit(ArrayPublicacion * publicaciones){
    ArrayPublicacion publicacionesAux;
    publicacionesAux.length = ARRAYPUBLICACION_LENGTH;
    int i;
    for(i = 0; i < publicacionesAux.length; i++){
        publicacion_randomInit(&publicacionesAux.listPublicaciones[i]);
    }
    *publicaciones = publicacionesAux;
}
/* ------------------------------------------------------------------ */
/** \brief Agrega una publicacion al campo listaPublicaciones del ArrayPublicacion parametrizado.
 *
 * \param publicaciones ArrayPublicacion*
 * \return int
 *
 */
int arrayPublicacion_add(ArrayPublicacion * publicaciones){
    ArrayPublicacion publicacionesAux = *publicaciones;
    int index = firstIndexAvailable(publicacionesAux);
    if(index == FAIL_1)
        return FAIL_1;

    if(publicacion_constructor(&publicacionesAux.listPublicaciones[index], TRUE) == FAIL_1)
        return FAIL_3;

    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y borra una publicacion del campo listaPublicaciones del ArrayPublicacion parametrizado.
 *
 * \param publicaciones ArrayPublicacion*
 * \return int
 *
 */
int arrayPublicacion_del(ArrayPublicacion * publicaciones){
    ArrayPublicacion publicacionesAux = *publicaciones;
    if(arrayPublicacion_showList(publicacionesAux) == FAIL_1)
        return FAIL_1;
    int id;
    if(util_getInt(&id, PUBLICACION_ASKID, PUBLICACION_ASKIDFAIL, 0, publicacionesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayPublicacion_getIndexOfID(publicacionesAux, id);

    if(publicacionesAux.listPublicaciones[index].isEmpty)
        return FAIL_2;
    else
        publicacion_init(&publicacionesAux.listPublicaciones[index]);

    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y edita los campos de esa publicacion que este en listaPublicaciones del ArrayPublicacion parametrizado.
 *
 * \param publicaciones ArrayPublicacion*
 * \return int
 *
 */
int arrayPublicacion_edit(ArrayPublicacion * publicaciones){
    ArrayPublicacion publicacionesAux = *publicaciones;
    if(arrayPublicacion_showList(publicacionesAux) == FAIL_1)
        return FAIL_1;

    int id;
    if(util_getInt(&id, PUBLICACION_ASKID, PUBLICACION_ASKIDFAIL, 0, publicacionesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayPublicacion_getIndexOfID(publicacionesAux, id);

    if(publicacionesAux.listPublicaciones[index].isEmpty)
        return FAIL_2;
    else if(publicacion_constructor(&publicacionesAux.listPublicaciones[index], FALSE) == FAIL_1)
        return FAIL_3;

    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y reanuda o pausa una publicacion.

 * \param publicaciones ArrayPublicacion*
 * \return int
 *
 */
int arrayPublicacion_changeState(ArrayPublicacion * publicaciones, int state){
    ArrayPublicacion publicacionesAux = *publicaciones;
    if(arrayPublicacion_showList(publicacionesAux) == FAIL_1)
        return FAIL_1;

    int id;
    if(util_getInt(&id, PUBLICACION_ASKID, PUBLICACION_ASKIDFAIL, 0, publicacionesAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayPublicacion_getIndexOfID(publicacionesAux, id);

    if(publicacionesAux.listPublicaciones[index].isEmpty)
        return FAIL_2;

    publicacionesAux.listPublicaciones[index].state = state;
    *publicaciones = publicacionesAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las publicaciones que esten activas en el listaPublicaciones del ArrayPublicaciones parametrizado.
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
int arrayPublicacion_showList(ArrayPublicacion publicaciones){
    int ret = FAIL_1;
    int i;
    sortArray(&publicaciones);
    showSeparator(4);
    printf("%s\n", PUBLICACION_ENTITY);
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty){
            publicacion_showData(publicaciones.listPublicaciones[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las publicaciones que esten activas que tengan una cantidad minima en el listaPublicaciones del ArrayPublicaciones parametrizado.
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
int arrayPublicacion_showListFilterGreaterCantidad(ArrayPublicacion publicaciones, int min){
    int ret = FAIL_1;
    int i;
    sortArray(&publicaciones);
    showSeparator(4);
    printf("arrayPublicacion_showListFilterGreaterCantidad\n");
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty /*&& publicaciones.listPublicaciones[i].cantidad > min*/){
            publicacion_showData(publicaciones.listPublicaciones[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las publicaciones que esten activas que tengan una cantidad maxima en el listaPublicaciones del ArrayPublicaciones parametrizado.
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
int arrayPublicacion_showListFilterLesserCantidad(ArrayPublicacion publicaciones, int max){
    int ret = FAIL_1;
    int i;
    sortArray(&publicaciones);
    showSeparator(4);
    printf("arrayPublicacion_showListFilterLesserCantidad\n");
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty /*&& publicaciones.listPublicaciones[i].cantidad < max*/){
            publicacion_showData(publicaciones.listPublicaciones[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las publicaciones que esten activas que tengan una cantidad minima en el listaPublicaciones del ArrayPublicaciones parametrizado.
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
int arrayPublicacion_showListFilterLesserPrecio(ArrayPublicacion publicaciones){
    int ret = FAIL_1;
    int i;
    sortArray(&publicaciones);
    showSeparator(4);
    printf("arrayPublicacion_showListFilterLesserPrecio\n");
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty /*&& publicaciones.listPublicaciones[i].precio < getPrecioPromedio(publicaciones)*/){
            publicacion_showData(publicaciones.listPublicaciones[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las publicaciones que esten activas que tengan una cantidad maxima en el listaPublicaciones del ArrayPublicaciones parametrizado.
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
int arrayPublicacion_showListFilterGreaterPrecio(ArrayPublicacion publicaciones){
    int ret = FAIL_1;
    int i;
    sortArray(&publicaciones);
    showSeparator(4);
    printf("arrayPublicacion_showListFilterGreaterPrecio\n");
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty /*&& publicaciones.listPublicaciones[i].precio > getPrecioPromedio(publicaciones)*/){
            publicacion_showData(publicaciones.listPublicaciones[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Pide una opcion por parametro y ejecuta esa accion, obteniendo la respuesta de cada uno y sus posibles errores
 *
 * \param publicaciones ArrayPublicacion*
 * \param option int
 * \return int
 *
 */
int arrayPublicacion_showResp(ArrayPublicacion * publicaciones, int option){
	int resp = 1;

	ArrayPublicacion publicacionesAux = *publicaciones;
	switch(option){
        case PUBLICACION_RAND:
			arrayPublicacion_randomInit(&publicacionesAux);
            break;
        case PUBLICACION_SHOWL:
			resp = arrayPublicacion_showList(publicacionesAux);
            break;
        case PUBLICACION_ADD:
            resp = arrayPublicacion_add(&publicacionesAux);
            break;
        case PUBLICACION_DEL:
            resp = arrayPublicacion_del(&publicacionesAux);
            break;
        case PUBLICACION_EDIT:
            resp = arrayPublicacion_edit(&publicacionesAux);
            break;
		default:
			return FAIL_1;
	}
	*publicaciones = publicacionesAux;
	showMsg(option, resp);
	return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra las opciones que se pueden realizar sobre un ArrayPublicacion
 *
 * \param void
 * \return void
 *
 */
void arrayPublicacion_showOptions(void){
    tab(TABSIZE);
    printf("%d : CARGAR ALEATOREAMENTE %s \n", PUBLICACION_RAND, PUBLICACION_ENTITY);
    tab(TABSIZE);
    printf("%d : AGREGAR %s \n", PUBLICACION_ADD, PUBLICACION_ENTITY);
    tab(TABSIZE);
    printf("%d : BORRAR %s \n", PUBLICACION_DEL, PUBLICACION_ENTITY);
    tab(TABSIZE);
    printf("%d : EDITAR %s \n", PUBLICACION_EDIT, PUBLICACION_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR LISTA DE  %s \n", PUBLICACION_SHOWL, PUBLICACION_ENTITY);
    tab(TABSIZE);
    printf("%d : VOLVER \n", PUBLICACION_RETURN);
    tab(TABSIZE);
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una publicacion parametrizada dentro del campo listaPublicaciones del ArrayPublicacion
 *
 * \param publicaciones ArrayPublicacion
 * \param id int
 * \return int
 *
 */
int arrayPublicacion_getIndexOfID(ArrayPublicacion publicaciones, int id){
    int i;
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty && publicaciones.listPublicaciones[i].id == id)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una publicacion parametrizada dentro del campo listaPublicaciones del ArrayPublicacion
 *
 * \param publicaciones ArrayPublicacion
 * \param id int
 * \return int
 *
 */
int arrayPublicacion_getLastID(ArrayPublicacion publicaciones){
    int i;
    int idMax = 0;
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty && publicaciones.listPublicaciones[i].id > idMax)
            idMax = publicaciones.listPublicaciones[i].id;
    }
    return idMax;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Devuelve el primer indice que este disponible para cargar publicaciones.
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
static int firstIndexAvailable(ArrayPublicacion publicaciones){
    int i;
    for(i = 0; i < publicaciones.length; i++){
        if(publicaciones.listPublicaciones[i].isEmpty)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Ordena el campo listaPublicaciones por el nombre de cada elemento, del ArrayPublicacion paramtrizado
 *
 * \param publicaciones ArrayPublicacion*
 * \return int
 *
 */
static int sortArray(ArrayPublicacion * publicaciones){
	ArrayPublicacion publicacionesAux = *publicaciones;
    int flagSwap;
    int i;
    if(publicacionesAux.length < 1)
        return FAIL_1;
    do{
        flagSwap = FALSE;
        for(i=0; i < publicacionesAux.length-1; i++) {
            if(strcmp(publicacionesAux.listPublicaciones[i].desc, publicacionesAux.listPublicaciones[i+1].desc) > 0){
                publicacion_swap(&publicacionesAux.listPublicaciones[i], &publicacionesAux.listPublicaciones[i+1]);
                flagSwap = TRUE;
            }
        }
    }while(flagSwap);
    *publicaciones = publicacionesAux;
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
				if(option == PUBLICACION_SHOWL)
					printf(PUBLICACION_SHWLMSGOK);
				else if(option == PUBLICACION_ADD)
					printf(PUBLICACION_ADDMSGOK);
				else if(option == PUBLICACION_DEL)
					printf(PUBLICACION_DELMSGOK);
				else if(option == PUBLICACION_EDIT)
					printf(PUBLICACION_EDITMSGOK);
				else
					return FAIL_1;
				break;
		case FAIL_1:
				if(option == PUBLICACION_SHOWL || option == PUBLICACION_DEL ||option == PUBLICACION_EDIT)
					printf(PUBLICACION_SHWLMSGF1);
				else if(option == PUBLICACION_ADD)
					printf(PUBLICACION_ADDMSGF1, PUBLICACION_DEL);
				else
					return FAIL_1;
				break;
		case FAIL_2:
				if(option == PUBLICACION_DEL || option == PUBLICACION_EDIT)
					printf(PUBLICACION_EDITDELMSGF1, PUBLICACION_ADD);
				else
					return FAIL_1;
				break;
		case FAIL_3:
				if(option == PUBLICACION_DEL || option == PUBLICACION_EDIT || option == PUBLICACION_ADD)
					printf(PUBLICACION_GENERICMSGFAIL);
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
/** \brief Muestra la cantidad de Publicaciones activos
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
static int getCantidad(ArrayPublicacion publicaciones){
    int ret = 0;
    int i;
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty)
            ret++;
    }
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra el precio acumulado de Publicaciones activos
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
static int getTotalPrecios(ArrayPublicacion publicaciones){
    int ret = 0;
    int i;
    for(i = 0; i < publicaciones.length; i++){
        if(!publicaciones.listPublicaciones[i].isEmpty){}
          //  ret+=publicaciones.listPublicaciones[i].precio;
    }
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra el promedio de precios
 *
 * \param publicaciones ArrayPublicacion
 * \return int
 *
 */
static int getPrecioPromedio(ArrayPublicacion publicaciones){
    return getCantidad(publicaciones) == 0 ? 0 : getTotalPrecios(publicaciones) / getCantidad(publicaciones);
}
