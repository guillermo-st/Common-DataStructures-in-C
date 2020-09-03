#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include "pila.h"

const int ERROR = -1;
const int EXITO = 0;
const int PROP_ACHICAR = 4; // si tope < tamanio/PROP_ACHICAR , se redimensiona con COEF_ACHICAR
const int COEF_ACHICAR = 2;
const int COEF_AGRANDAR = 2;
const int TAM_MIN = 10;

pila_t* pila_crear(){

	pila_t* pila = malloc(sizeof(pila_t));
	if(pila == NULL)
		return pila;
	void** elementos_aux = calloc((long unsigned)TAM_MIN, sizeof(void*));
	if(elementos_aux == NULL)
		return NULL;
	pila->elementos = elementos_aux;	
	pila->tope = 0;	
	pila->tamanio = TAM_MIN;
	return pila;
}

void* pila_tope(pila_t* pila){
	if(pila == NULL)
		return pila;
	if(pila->tope > 0)
		return pila->elementos[pila->tope - 1];	
	return pila->elementos[pila->tope];
}

bool pila_vacia(pila_t* pila){
	if(pila == NULL)
		return true;
	return(pila->tope == 0);
}

int pila_cantidad(pila_t* pila){
	if(pila == NULL)
		return 0;
	return pila->tope;
}

int redimensionar_pila(pila_t* pila,  int coef_redimension){

	void** pila_aux = realloc(pila->elementos, sizeof(void*) * (long unsigned int)coef_redimension);
	if(pila_aux == NULL)
		return ERROR;
	pila->elementos = pila_aux;
	pila->tamanio = coef_redimension;
	return EXITO;
}

int pila_apilar(pila_t* pila, void* elemento){
	
	if(pila == NULL)
		return ERROR;
	if(pila->tope + 1 > pila->tamanio){
		int flag = redimensionar_pila(pila, pila->tamanio * COEF_AGRANDAR);
		if (flag == ERROR)
			return flag;
	}
	pila->elementos[pila->tope] = elemento;
	pila->tope += 1;
	return EXITO;
}

int pila_desapilar(pila_t* pila){
	if (pila == NULL)
		return ERROR;
	if(pila_vacia(pila))
		return ERROR;
	if(pila->tope <= pila->tamanio/PROP_ACHICAR && pila->tamanio > TAM_MIN){
		int flag = redimensionar_pila(pila, pila->tamanio/COEF_ACHICAR);
		if(flag == ERROR)
			return flag;
	}
	if(pila->tope >0)	
		pila->tope -= 1;
	pila->elementos[pila->tope] = NULL;
	return EXITO;
}

void pila_destruir(pila_t* pila){
	if(pila == NULL)
		return;
	free(pila->elementos);
	free(pila);
}
