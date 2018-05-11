#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "styles.h"
#include "arrayRelacion.h"


/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define EXIT 2

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static void showEntities(void);
static int showOptions(int entity);

/* ------------------------------------------------------------------ */
/**                     MAIN                                          */
/* ------------------------------------------------------------------ */
int main()
{
    int seguir = TRUE;
    int option = -1;
	int entity = -1;
	ArrayCliente clientes;
	ArrayPublicacion publicaciones;
	ArrayRelacion relaciones;
	arrayCliente_init(&clientes);
	arrayPublicacion_init(&publicaciones);
	arrayRelacion_init(&relaciones);

    while(seguir == TRUE){
        fflush(stdin);
		showEntities();
		if(util_getInt(&entity, "Ingrese que desea modificar: ", "Ingrese una opcion valida. \n", 0, EXIT, 1) == FAIL_1)
            continue;

		if(entity == EXIT){
			seguir = FALSE;
			break;
		}

		int volver = showOptions(entity);
		if(util_getInt(&option, "Ingrese la opcion a realizar: ", "Ingrese una opcion valida. \n", 0, volver, 1) == FAIL_1)
            continue;

		if(option == volver)
            continue;

		switch(entity){
			case CLIENTE_ID:
                    arrayCliente_showResp(&clientes, option);
					break;
			case RELACION_ID:
                    arrayRelacion_showResp(&relaciones, option, clientes, &publicaciones);
					break;
		}
        printf("\n");

        arrayRelacion_refresh(&relaciones, clientes);
        arrayRelacion_refreshClientes(&relaciones, &clientes);
        //arrayPublicacion_showListFilterGreaterCantidad(publicaciones, 50);
        //arrayPublicacion_showListFilterLesserCantidad(publicaciones, 50);
        //arrayPublicacion_showListFilterGreaterPrecio(publicaciones);
        //arrayPublicacion_showListFilterLesserPrecio(publicaciones);
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
static void showEntities(void){
    showHeader(6);
    tab(TABSIZE);
    printf("#%d: %s \n", CLIENTE_ID, CLIENTE_ENTITY);
    tab(TABSIZE);
    printf("#%d: %s \n", PUBLICACION_ID, PUBLICACION_ENTITY);
    tab(TABSIZE);
    printf("#%d: SALIR \n", EXIT);
    tab(TABSIZE);
}

static int showOptions(int entity){
    switch(entity){
		case CLIENTE_ID:
				   arrayCliente_showOptions();
				   return CLIENTE_RETURN;
				   break;
		case RELACION_ID:
				   arrayRelacion_showOptions();
				   return RELACION_RETURN;
				   break;

	}
	return FAIL_1;
}
