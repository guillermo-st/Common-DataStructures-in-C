#include "lista.h"
#include "stdlib.h"

#define ERROR -1
#define EXITO 0

typedef struct nodo{
	void* elemento;
	struct nodo* siguiente;
}nodo_t;

struct lista{
	nodo_t* primer_nodo;
	nodo_t* ultimo_nodo;
	size_t cantidad;
};

struct lista_iterador{
	nodo_t* nodo_apuntado;
};

lista_t* lista_crear(){
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista)
		return NULL;
	lista->primer_nodo = NULL;
	lista->ultimo_nodo = NULL;
	lista->cantidad = 0;
	return lista;
}

bool lista_vacia(lista_t* lista){
	return (!lista || lista->cantidad == 0);
}

size_t lista_elementos(lista_t* lista){
	return lista? lista->cantidad: 0;
}

void* lista_ultimo(lista_t* lista){
	return lista_vacia(lista)? NULL: lista->ultimo_nodo->elemento;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!lista || posicion >= lista->cantidad)
		return NULL;
	
	nodo_t* nodo_actual = lista->primer_nodo;
	size_t i = 0;
	while(i < posicion){ 
		nodo_actual = nodo_actual->siguiente;
		i++;
	}
	return nodo_actual->elemento;
}


// devuelve un puntero al nodo de la lista que está en la posicion recibida por parámetro. La lista ya fue comprobada como distinta de NULL.
nodo_t* ptr_nodo_en_pos (lista_t* lista, size_t posicion){
	nodo_t* nodo_actual = lista->primer_nodo;
	size_t i = 0;
	while(i < posicion){
		nodo_actual = nodo_actual->siguiente;
		i++;
	}
	return nodo_actual;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista)
		return ERROR;
	
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo)
		return ERROR;
	nuevo_nodo->elemento = elemento;
	
	if(posicion >= lista->cantidad){  
		posicion = lista->cantidad;
		lista->ultimo_nodo = nuevo_nodo;
	}
	if(posicion == 0){
		nuevo_nodo->siguiente = lista->primer_nodo;	
		lista->primer_nodo = nuevo_nodo;
		lista->cantidad += 1;
		return EXITO;	
	}
	nodo_t* anterior = ptr_nodo_en_pos(lista, posicion -1);
	nuevo_nodo->siguiente = anterior->siguiente;
	anterior->siguiente = nuevo_nodo;
	lista->cantidad += 1;
	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista_vacia(lista))
		return ERROR;
	nodo_t* aux;
	if(posicion >= lista->cantidad)
		posicion = lista->cantidad - 1 ;
	if(posicion == 0){
		aux = lista->primer_nodo;
		lista->primer_nodo = lista->primer_nodo->siguiente;
	        free(aux);
		lista->cantidad -= 1;
		return EXITO;	
			
	}
	nodo_t* anterior = ptr_nodo_en_pos(lista, posicion -1);
	if(posicion == lista->cantidad -1)
		lista->ultimo_nodo = anterior;	
	aux = anterior->siguiente;
	anterior->siguiente = anterior->siguiente->siguiente;	
	free(aux);
	lista->cantidad -=1;
	return EXITO;
}

int lista_insertar(lista_t* lista, void* elemento){
	if(!lista)
		return ERROR;
	nodo_t* nuevo = malloc(sizeof(nodo_t));
	if(!nuevo)
		return ERROR;
	nuevo->elemento = elemento;
	nuevo->siguiente = NULL;
	if(lista->cantidad == 0)
		lista->primer_nodo = nuevo;
	if(lista->cantidad > 0)
		lista->ultimo_nodo->siguiente = nuevo;
	lista->ultimo_nodo = nuevo;
	lista->cantidad += 1;
	return EXITO;
}

int lista_borrar(lista_t* lista){
	if(!lista)
		return ERROR;
	return lista_borrar_de_posicion(lista, lista->cantidad -1);
}

void lista_destruir(lista_t* lista){
	while(!lista_vacia(lista))
		lista_borrar(lista);
	free(lista);
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	if(!lista)
		return;
	nodo_t* nodo_actual = lista->primer_nodo;
	for(int i = 0; i<lista->cantidad; i++){
		funcion(nodo_actual->elemento);
		nodo_actual = nodo_actual->siguiente;
	}	
}


lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista)
		return NULL;
	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;
	iterador->nodo_apuntado = lista->primer_nodo;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador)
		return false;	
	return(!(iterador->nodo_apuntado == NULL)); //|| iterador->nodo_apuntado->siguiente == NULL));
}


void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if(lista_iterador_tiene_siguiente(iterador)){
		void* elemento =  iterador->nodo_apuntado->elemento;
		iterador->nodo_apuntado = iterador->nodo_apuntado->siguiente;
		return elemento;
	}
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}
