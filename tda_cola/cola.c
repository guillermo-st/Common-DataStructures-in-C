#include "cola.h"
#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>

#define ERROR -1
#define EXITO 0

cola_t* cola_crear(){
	cola_t* cola = malloc(sizeof(cola_t));
	if(!cola)
		return NULL;
	cola->cantidad = 0;
	cola->nodo_inicio = NULL;
	cola->nodo_fin = NULL;
	return cola;
}

int cola_encolar(cola_t* cola, void* elemento){
	if(!cola)
		return ERROR;
	nodo_t* nuevo = malloc(sizeof(nodo_t));
	if(!nuevo)
		return ERROR;
	nuevo->elemento = elemento;
	nuevo->siguiente = NULL;
	if(cola->cantidad == 0)
		cola->nodo_inicio = nuevo;
	if(cola->cantidad > 0)
		cola->nodo_fin->siguiente = nuevo;	
	cola->nodo_fin = nuevo;
	cola->cantidad += 1;
	return EXITO;
}

int cola_desencolar(cola_t* cola){
	if(!cola || cola->nodo_inicio == NULL)
		return ERROR;
	nodo_t* nodo_aux;	
	nodo_aux = cola->nodo_inicio;
	cola->nodo_inicio = cola->nodo_inicio->siguiente;
	free(nodo_aux);
	cola->cantidad -= 1;
	return EXITO;
}

bool cola_vacia(cola_t* cola){
	return(!cola || cola->cantidad == 0);
}

int cola_cantidad(cola_t* cola){
	return cola? cola->cantidad : 0;
}

void* cola_primero(cola_t* cola){
	return cola_vacia(cola) ? NULL : cola->nodo_inicio->elemento; 	
}

void cola_destruir(cola_t* cola){
	while(!cola_vacia(cola))
		cola_desencolar(cola);
	free(cola);
}
