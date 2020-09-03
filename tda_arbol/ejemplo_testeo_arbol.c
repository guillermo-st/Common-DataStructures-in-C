#include "pruebas_arbol.h"
#include "abb.h"
#include <stdio.h>
#define CANT_PRUEBAS  21
#define NUMINSERTAR 7
#define ERROR -1

int comparar_enteros(void* elemento1, void* elemento2){

    if(*(int*)elemento1 > *(int*)elemento2)
	return 1;
    if(*(int*)elemento1 < *(int*)elemento2)
	return -1;
    return 0;
}

int main(){
   	abb_t* arbol = NULL; 
	int pruebas_erradas = 0;
	
	pruebas_erradas -= ConArbolNULL_PreguntarSiVacio_DevuelveTrue(arbol);
	pruebas_erradas -= ConArbolNULL_PreguntarRaiz_DevuelveNULL(arbol);
	pruebas_erradas -= ConArbolNULL_IntentarBorrar_DevuelveERROR(arbol);
	pruebas_erradas -= ConArbolNULL_IntentarInsertar_DevuelveERROR(arbol);
	pruebas_erradas -= ConArbolNULL_IntentarBuscar_DevuelveNULL(arbol);
	pruebas_erradas -= ConArbolNULL_IntentarUsarIteradorInternoConUnOrden_NoMuestraNadaPorPantalla(arbol, ABB_RECORRER_INORDEN);
	pruebas_erradas -= ConArbolNULL_IntentarUsarIteradorInternoConUnOrden_NoMuestraNadaPorPantalla(arbol, ABB_RECORRER_POSTORDEN);
	pruebas_erradas -= ConArbolNULL_IntentarUsarIteradorInternoConUnOrden_NoMuestraNadaPorPantalla(arbol, ABB_RECORRER_PREORDEN);
	
	arbol = arbol_crear(comparar_enteros, NULL);
	if(!arbol){
       		printf("\n Error al crear el arbol \n");		
		return 0;	
	}

	pruebas_erradas -= ConArbolVacio_IntentarBorrar_DevuelveERROR(arbol);
	pruebas_erradas -= ConArbolVacio_PreguntarRaiz_DevuelveNULL(arbol);
	pruebas_erradas -= ConArbolVacio_PreguntarSiVacio_DevuelveTrue(arbol);
	pruebas_erradas -= ConArbolVacio_IntentarBuscar_DevuelveNULL(arbol);
	pruebas_erradas -= ConArbolVacio_InsertarYBuscarElementos_EncuentraTodos(arbol);

	int v_elementos[NUMINSERTAR];
	int j=0;
	bool flag_error_insertar = false;
	while(j<NUMINSERTAR && !flag_error_insertar){
		v_elementos[j] = entero_aleatorio();
		flag_error_insertar = (arbol_insertar(arbol, &v_elementos[j]) == ERROR);
		j++;	
	}
	
	pruebas_erradas -= ConArbolLleno_PreguntarSiVacio_DevuelveFalse(arbol);
	pruebas_erradas -= ConArbolLleno_PreguntarPorRaiz_DevuelvePrimerElementoInsertado(arbol, &v_elementos[0]);
	pruebas_erradas -= ConArbolLleno_RecorrerEnCualquierOrden_DebeRecorrerTodosLosElementos(arbol, ABB_RECORRER_INORDEN, NUMINSERTAR);
	pruebas_erradas -= ConArbolLleno_RecorrerEnCualquierOrden_DebeRecorrerTodosLosElementos(arbol, ABB_RECORRER_POSTORDEN, NUMINSERTAR);
	pruebas_erradas -= ConArbolLleno_RecorrerEnCualquierOrden_DebeRecorrerTodosLosElementos(arbol, ABB_RECORRER_PREORDEN, NUMINSERTAR);
    	
	printf("\nRecorriendo Inorden ");
	pruebas_erradas -= ConArbolLleno_RecorrerEnUnOrdenConIteradorInterno_LosMuestraEnEseOrden(arbol, ABB_RECORRER_INORDEN);
	printf("\nRecorriendo Postorden ");
	pruebas_erradas -= ConArbolLleno_RecorrerEnUnOrdenConIteradorInterno_LosMuestraEnEseOrden(arbol, ABB_RECORRER_POSTORDEN);
	printf("\nRecorriendo Preorden ");
	pruebas_erradas -= ConArbolLleno_RecorrerEnUnOrdenConIteradorInterno_LosMuestraEnEseOrden(arbol, ABB_RECORRER_PREORDEN);
       	
	printf("\n Has fallado %i de %i pruebas \n", pruebas_erradas, CANT_PRUEBAS);		
    	arbol_destruir(arbol);
    	return 0;
}
