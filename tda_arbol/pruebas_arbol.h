#ifndef __PRUEBAS_ARBOL_H
#define __PRUEBAS_ARBOL_H
#include "abb.h"

//devuelve un int aleatorio
int entero_aleatorio();

//Comprueba el correcto funcionamiento de la primitiva arbol_borrar() cuando el arbol está vacio
int ConArbolVacio_IntentarBorrar_DevuelveERROR(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_raiz() cuando el arbol está vacio
int ConArbolVacio_PreguntarRaiz_DevuelveNULL(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_vacio() cuando el arbol está vacio
int ConArbolVacio_PreguntarSiVacio_DevuelveTrue(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_buscar() cuando el arbol está vacio
int ConArbolVacio_IntentarBuscar_DevuelveNULL(abb_t* arbol);

//Comprueba el correcto funcionamiento de las primitivas arbol_buscar y arbol_insertar cuando el arbol esta vacio. 
int ConArbolVacio_InsertarYBuscarElementos_EncuentraTodos(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_borrar() cuando el arbol es null 
int ConArbolNULL_IntentarBorrar_DevuelveERROR(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_vacio() cuando el arbol es null 
int ConArbolNULL_PreguntarSiVacio_DevuelveTrue(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_raiz() cuando el arbol es null 
int ConArbolNULL_PreguntarRaiz_DevuelveNULL(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_insertar() cuando el arbol es null 
int ConArbolNULL_IntentarInsertar_DevuelveERROR(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_buscar() cuando el arbol es null 
int ConArbolNULL_IntentarBuscar_DevuelveNULL(abb_t* arbol);

//Comprueba el correcto funcionamiento de los iteradores internos cuando el arbol es null 
int ConArbolNULL_IntentarUsarIteradorInternoConUnOrden_NoMuestraNadaPorPantalla(abb_t* arbol, int orden);

//Comprueba el correcto funcionamiento de la primitiva arbol_vacio() cuando el arbol tiene elementos
int ConArbolLleno_PreguntarSiVacio_DevuelveFalse(abb_t* arbol);

//Comprueba el correcto funcionamiento de la primitiva arbol_raiz() cuando el arbol tiene elementos
int ConArbolLleno_PreguntarPorRaiz_DevuelvePrimerElementoInsertado(abb_t* arbol, void* primer_elemento);

//Comprueba el correcto funcionamiento del iterador interno cuando el arbol tiene elementos
int ConArbolLleno_RecorrerEnUnOrdenConIteradorInterno_LosMuestraEnEseOrden(abb_t* arbol, int orden);

//Comprueba el correcto funcionamiento de las funciones de recorrer cuando el arbol tiene elementos. 
int ConArbolLleno_RecorrerEnCualquierOrden_DebeRecorrerTodosLosElementos(abb_t* arbol, int orden, int insertados);

#endif /*__PRUEBAS_ARBOL_H*/
