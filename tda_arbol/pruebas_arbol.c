#include <stdio.h>
#include "testing.h"
#include "abb.h"
#include "pruebas_arbol.h"
#include "time.h"
#define NUMINSERTAR 7
#define ERROR -1
#define EXITO 0
#define MAXRAND  101

// función para utilizar en el iterador interno del arbol. Muestra un entero por stdout.
bool mostrar_entero(void* elemento, void* extra){
	extra=extra; 
	if(elemento)
  		printf("%i ",*(int*)elemento);
  	return false;
}

//genera un entero aleatorio para enlistar o desenlistar, entre 0 y MAXRAND.
int entero_aleatorio(){
	return (rand() % MAXRAND); 
}

int comparador_booleanos(void* elemento1, void* elemento2){
	if(*(bool*)elemento1 == *(bool*)elemento2)
		return 0;
	else return 1;
}

int comparador_enteros(void* elemento1, void* elemento2){
	if(*(int*)elemento1 == *(int*)elemento2)
		return 0;
	else if(*(int*)elemento1 < *(int*) elemento2)
		return -1;
	else return 1;
}

int ConArbolVacio_IntentarBorrar_DevuelveERROR(abb_t* arbol){
	char* nombre_prueba = "Intentar borrar en un árbol vacío debe devolver error.";
	if(!arbol || !arbol_vacio(arbol))
		return interrupcion_prueba(nombre_prueba);
	int esperado = ERROR;
	int obtenido = arbol_borrar(arbol, 0);
	return verificar_test(nombre_prueba, &esperado, &obtenido, &comparador_enteros);
}

int ConArbolVacio_PreguntarRaiz_DevuelveNULL(abb_t* arbol){
	char* nombre_prueba = "Preguntar la raíz de un arbol vacío devuelve NULL";
	if(!arbol || !arbol_vacio(arbol))
		return interrupcion_prueba(nombre_prueba);
	return verificar_test(nombre_prueba, NULL, arbol_raiz(arbol), NULL); 
}

int ConArbolVacio_PreguntarSiVacio_DevuelveTrue(abb_t* arbol){
	char* nombre_prueba = "Preguntar si un arbol vacío es vacio devuelve true";
	if(!arbol)
		return interrupcion_prueba(nombre_prueba);
	bool esperado = true;
	bool obtenido = arbol_vacio(arbol);
	return verificar_test(nombre_prueba, &esperado, &obtenido, &comparador_booleanos); 
}

int ConArbolVacio_IntentarBuscar_DevuelveNULL(abb_t* arbol){
	char* nombre_prueba = "Buscar un elemento en un arbol vacío devuelve NULL";
	if(!arbol || !arbol_vacio(arbol))
		return interrupcion_prueba(nombre_prueba);
	int aux = entero_aleatorio();
	return verificar_test(nombre_prueba, NULL, arbol_buscar(arbol, &aux), NULL);
}

int ConArbolVacio_InsertarYBuscarElementos_EncuentraTodos(abb_t* arbol){
	char* nombre_prueba = "Buscar todos los elementos insertados en un arbol previamente vacío, debe encontrarlos todos";
	int v_elementos[NUMINSERTAR];
	bool esperado = true;
	bool todos_encontrados = true;
	for (int j = 0; j<NUMINSERTAR; j++){
		v_elementos[j] = entero_aleatorio();
		arbol_insertar(arbol, &v_elementos[j]);
	}
	for(int k = 0; k<NUMINSERTAR; k++){
		if (arbol_buscar(arbol, &v_elementos[k]) == NULL){
			todos_encontrados = false;
		}
		
	}
	while(!arbol_vacio(arbol))
		arbol_borrar(arbol, arbol->nodo_raiz->elemento);	
	return verificar_test(nombre_prueba, &esperado , &todos_encontrados, comparador_booleanos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ConArbolNULL_IntentarBorrar_DevuelveERROR(abb_t* arbol){
	char* nombre_prueba = "Intentar borrar en un arbol NULL debe devolver ERROR";
	int aux = entero_aleatorio();
	int esperado = ERROR;
	int obtenido = arbol_borrar(arbol, &aux);
	return verificar_test(nombre_prueba, &esperado, &obtenido, &comparador_enteros);
}

int ConArbolNULL_PreguntarSiVacio_DevuelveTrue(abb_t* arbol){
	char* nombre_prueba = "Preguntar si un arbol NULL es vacío devuelve true";
	bool esperado = true;
	bool obtenido = arbol_vacio(arbol);
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_booleanos);
}

int ConArbolNULL_PreguntarRaiz_DevuelveNULL(abb_t* arbol){
	char* nombre_prueba = "Preguntar la raíz de un arbol NULL devuelve NULL";
	return verificar_test(nombre_prueba, NULL, arbol_raiz(arbol), NULL); 
}

int ConArbolNULL_IntentarInsertar_DevuelveERROR(abb_t* arbol){
	char* nombre_prueba = "Intentar Insertar en un arbol NULL devuelve ERROR";
	int aux = entero_aleatorio();
	int esperado = ERROR;
	int obtenido = arbol_insertar(arbol, &aux);
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_enteros);
}

int ConArbolNULL_IntentarBuscar_DevuelveNULL(abb_t* arbol){
	char* nombre_prueba = "Intentar buscar un elemento en un arbol NULL devuelve NULL";
	int aux = entero_aleatorio();
	return verificar_test(nombre_prueba, NULL, arbol_buscar(arbol, &aux), NULL);
}

int ConArbolNULL_IntentarUsarIteradorInternoConUnOrden_NoMuestraNadaPorPantalla(abb_t* arbol, int orden){
	char* nombre_prueba = "Intentar usar el iterador interno de un arbol NULL mostrando elementos, no muestra nada";
	abb_con_cada_elemento(arbol, orden, mostrar_entero, NULL);
	int resultado = EXITO;
	return verificar_test(nombre_prueba, &resultado, &resultado, comparador_enteros);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ConArbolLleno_PreguntarSiVacio_DevuelveFalse(abb_t* arbol){
	char* nombre_prueba = "Preguntar si un arbol con elementos es vacío devuelve falso.";
	bool esperado = false;
	bool resultado = arbol_vacio(arbol);
	return verificar_test(nombre_prueba, &esperado, &resultado, comparador_booleanos);
}

int ConArbolLleno_PreguntarPorRaiz_DevuelvePrimerElementoInsertado(abb_t* arbol, void* primer_elemento){
	char* nombre_prueba = "Preguntar por la raíz de un arbol con elementos, devuelve el primer elemento insertado";
	return verificar_test(nombre_prueba, primer_elemento, arbol_raiz(arbol), arbol->comparador);
}

int ConArbolLleno_RecorrerEnCualquierOrden_DebeRecorrerTodosLosElementos(abb_t* arbol, int orden, int cant_insertados){
	char* nombre_prueba = "Recorrer un arbol con una cantidad de elementos en cualquier orden, debe llenar esa misa cantidad de posiciones de un array";
	void* aux[cant_insertados];
	int cantidad_recorridos = 0;
	switch(orden){
		case ABB_RECORRER_INORDEN: 
    			printf("\nRecorriendo Inorden ");
    			cantidad_recorridos = arbol_recorrido_inorden(arbol, (void**)aux, cant_insertados);
			break;	
		case ABB_RECORRER_PREORDEN: 
    			printf("\nRecorriendo preorden ");
    			cantidad_recorridos = arbol_recorrido_preorden(arbol, (void**)aux, cant_insertados);
			break;
		case ABB_RECORRER_POSTORDEN: 
    			printf("\nRecorriendo postorden ");
    			cantidad_recorridos = arbol_recorrido_postorden(arbol, (void**)aux, cant_insertados);
			break;
	}
	for(int i=0 ; i<cantidad_recorridos ; i++)
        	printf("%i ", *(int*)aux[i]);
    	printf("\n");
	return verificar_test(nombre_prueba, &cant_insertados, &cantidad_recorridos, comparador_enteros);
}

int ConArbolLleno_RecorrerEnUnOrdenConIteradorInterno_LosMuestraEnEseOrden(abb_t* arbol, int orden){
	char* nombre_prueba = "Recorrer un arbol lleno en un orden con iterador interno los muestra todos y en ese orden";
    	abb_con_cada_elemento(arbol, orden, mostrar_entero, NULL);
	int resultado = EXITO;
	return verificar_test(nombre_prueba, &resultado, &resultado, comparador_enteros);
}
