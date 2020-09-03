#include<stdio.h>
#include "abb.h"

#define ERROR -1
#define EXITO 0

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if (comparador == NULL)
		return NULL;
	abb_t* arbol = malloc(sizeof(abb_t));
	if(!arbol)
		return NULL;
	arbol->nodo_raiz = NULL;	
	arbol->comparador = comparador;
	arbol->destructor = destructor;
	return arbol;
}

bool arbol_vacio(abb_t* arbol){
	return (!arbol || !arbol->nodo_raiz);
}

void* arbol_raiz(abb_t* arbol){
	return arbol_vacio(arbol)?NULL:arbol->nodo_raiz->elemento;
}

//busca un nodo de manera recursiva en el caso de que el arbol no haya estado vacio.
void* arbol_buscar_rec(nodo_abb_t* actual, void* elemento, abb_comparador comparador, nodo_abb_t** padre, nodo_abb_t** buscado){
	*padre = actual;	
	if(comparador(elemento, actual->elemento) == 1){
		if(!(actual->derecha))
			return NULL;
		if(comparador(elemento, actual->derecha->elemento) == 0){
			*buscado = actual->derecha;	
			return actual->derecha->elemento;
		}
		else
			return arbol_buscar_rec(actual->derecha, elemento, comparador, padre, buscado);
	}
	else if(comparador(elemento, actual->elemento) == -1){
		if(!(actual->izquierda))
			return NULL;
		if(comparador(elemento, actual->izquierda->elemento) == 0){
			*buscado = actual->izquierda;
			return actual->izquierda->elemento;
		}
		else 
			return arbol_buscar_rec(actual->izquierda, elemento, comparador, padre, buscado);

	}
	*buscado = actual;
	return actual->elemento;
}


void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol))
		return NULL;	
	nodo_abb_t* padre = arbol->nodo_raiz;
	nodo_abb_t* buscado = NULL;
	return arbol_buscar_rec(arbol->nodo_raiz, elemento, arbol->comparador, &padre, &buscado);		
}

//retorna un puntero al menor nodo de un subarbol
nodo_abb_t* menor_nodo(nodo_abb_t* nodo, nodo_abb_t** padre){
	if(!nodo->izquierda)
		return nodo;	
	if(!nodo->izquierda->izquierda){
		*padre = nodo;
		return nodo->izquierda;
	}
	return menor_nodo(nodo->izquierda, padre);
}

int arbol_borrar(abb_t* arbol, void* elemento){
	if(arbol_vacio(arbol))
		return ERROR;	
	nodo_abb_t* padre = arbol->nodo_raiz;
	nodo_abb_t* nodo_buscado = NULL;
	bool buscado_es_raiz = false;
	arbol_buscar_rec(arbol->nodo_raiz, elemento, arbol->comparador, &padre, &nodo_buscado);
	if (nodo_buscado == NULL)
		return ERROR;
	
	buscado_es_raiz = (nodo_buscado == arbol->nodo_raiz);

	if(!nodo_buscado->derecha || !nodo_buscado->izquierda){
	    	nodo_abb_t* hijo = nodo_buscado->derecha ? nodo_buscado->derecha:nodo_buscado->izquierda;
	    	if(!buscado_es_raiz){ 
	    		if(padre->izquierda == nodo_buscado)
		    		padre->izquierda = hijo;
	    		else padre->derecha = hijo;
		}
	    	else		    
			arbol->nodo_raiz = hijo;
	    	if(arbol->destructor)
	       		arbol->destructor(nodo_buscado->elemento);
	    	free(nodo_buscado);
	}
	else{
		nodo_abb_t* padre_menor_nodo_derecho = nodo_buscado;
		nodo_abb_t* menor_nodo_derecho = menor_nodo(nodo_buscado->derecha, &padre_menor_nodo_derecho); 
		if(arbol->destructor)
			arbol->destructor(nodo_buscado->elemento);	
		nodo_buscado->elemento = menor_nodo_derecho->elemento;
		if(menor_nodo_derecho->derecha){  //si el menor nodo del subarbol derecho tiene hijo derecho
			if(padre_menor_nodo_derecho->derecha == menor_nodo_derecho)
				padre_menor_nodo_derecho->derecha = menor_nodo_derecho->derecha;
			else	
				padre_menor_nodo_derecho->izquierda = menor_nodo_derecho->derecha;
			free(menor_nodo_derecho);
		}	
		else{
			if(menor_nodo_derecho == padre_menor_nodo_derecho->derecha)
				padre_menor_nodo_derecho->derecha = NULL;
			else
				padre_menor_nodo_derecho->izquierda = NULL;
			free(menor_nodo_derecho);
		}
	}
	return EXITO;
}

// inserta un nuevo nodo de manera recursiva en el caso de que el arbol no haya estado vacío.
int arbol_insertar_rec(nodo_abb_t* padre, nodo_abb_t* nuevo, abb_comparador comparador){
	int resultado_comparacion = comparador(nuevo->elemento, padre->elemento);
	if(resultado_comparacion == 0 || resultado_comparacion == 1){
		if(padre->derecha == NULL){
			padre->derecha = nuevo;
			return EXITO;
		}
		return arbol_insertar_rec(padre->derecha , nuevo, comparador);
	}
	else{
		if(padre->izquierda == NULL){
			padre->izquierda = nuevo;
			return EXITO;
		}
		return arbol_insertar_rec(padre->izquierda , nuevo, comparador);
	}
}

int arbol_insertar(abb_t* arbol, void* elemento){
	if (!arbol)
		return ERROR;
	nodo_abb_t* nuevo = malloc(sizeof(nodo_abb_t));
	if(!nuevo)
		return ERROR;
	nuevo->izquierda = NULL;
	nuevo->derecha = NULL;
	nuevo->elemento = elemento;
	if (arbol_vacio(arbol)){
		arbol->nodo_raiz = nuevo;
		return EXITO;
	}
	return arbol_insertar_rec(arbol->nodo_raiz , nuevo, arbol->comparador);
}

//recorrido postorden recursivo
int arbol_recorrido_postorden_rec(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
	int cant = 0;	
	if(nodo->izquierda)
		cant += arbol_recorrido_postorden_rec(nodo->izquierda, array, tamanio_array, posarray);
	if(nodo->derecha)
		cant += arbol_recorrido_postorden_rec(nodo->derecha, array, tamanio_array, posarray);
	if(*posarray < tamanio_array){
		array[*posarray] = nodo->elemento;
		cant += 1;
       		*posarray += 1;
	}	
	return cant;
}

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol)
		return 0;
	int pos_array = 0;
	return arbol_recorrido_postorden_rec(arbol->nodo_raiz, array, tamanio_array, &pos_array);
}

//recorrido inorden recursivo
int arbol_recorrido_inorden_rec(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
	int cant = 0;	
	if(nodo->izquierda)
		cant += arbol_recorrido_inorden_rec(nodo->izquierda, array, tamanio_array, posarray);
	
	if(*posarray < tamanio_array){
		array[*posarray] = nodo->elemento;
		cant += 1;
       		*posarray += 1;
	}	
	if(nodo->derecha)
		cant += arbol_recorrido_inorden_rec(nodo->derecha, array, tamanio_array, posarray);

	return cant;
}


int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol)
		return 0;
	int pos_array = 0;
	return arbol_recorrido_inorden_rec(arbol->nodo_raiz, array, tamanio_array, &pos_array);
}

//recorrido preorden recursivo
int arbol_recorrido_preorden_rec(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
	int cant = 0;	
	if(*posarray < tamanio_array){
		array[*posarray] = nodo->elemento;
		cant += 1;
       		*posarray += 1;
	}
	if(nodo->izquierda)
		cant += arbol_recorrido_preorden_rec(nodo->izquierda, array, tamanio_array, posarray);
	if(nodo->derecha)
		cant += arbol_recorrido_preorden_rec(nodo->derecha, array, tamanio_array, posarray);
	return cant;
}

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol)
		return 0;
	int pos_array = 0;
	return arbol_recorrido_preorden_rec(arbol->nodo_raiz, array, tamanio_array, &pos_array);
}

//iterador interno recursivo de manera postorden
void abb_con_cada_elemento_postorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* extra, bool* corte){
	if(*corte || !nodo)
		return;	
	if(nodo->izquierda)
		abb_con_cada_elemento_postorden(nodo->izquierda, funcion, extra, corte);
	
	if(*corte) return;
	if(nodo->derecha)
		abb_con_cada_elemento_postorden(nodo->derecha, funcion, extra, corte);
	if(*corte) return;
	
	*corte = funcion(nodo->elemento, extra);		
}

//iterador interno recursivo de manera inorden
void abb_con_cada_elemento_inorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* extra, bool* corte){
	if(*corte || !nodo)
		return;	
	if(nodo->izquierda)
		abb_con_cada_elemento_inorden(nodo->izquierda, funcion, extra, corte);
	
	if(*corte) return;
	*corte = funcion(nodo->elemento, extra);		
	if(nodo->derecha)
		abb_con_cada_elemento_inorden(nodo->derecha, funcion, extra, corte);
}

//iterador interno recursivo de manera preorden
void abb_con_cada_elemento_preorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* extra, bool* corte){
	if(*corte || !nodo)
		return;	
	*corte = funcion(nodo->elemento, extra);		
	
	if(nodo->izquierda)
		abb_con_cada_elemento_preorden(nodo->izquierda, funcion, extra, corte);
	if(nodo->derecha)
		abb_con_cada_elemento_preorden(nodo->derecha, funcion, extra, corte);
}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol_vacio(arbol))
		return;	
	bool flag_corte = false;
	switch(recorrido){
		case ABB_RECORRER_POSTORDEN:
			abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, extra, &flag_corte);
			break;
		case ABB_RECORRER_INORDEN:
			abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, extra, &flag_corte);
			break;
		case ABB_RECORRER_PREORDEN:
			abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, extra, &flag_corte);
			break;
	}
}

void arbol_destruir(abb_t* arbol){
	while(!arbol_vacio(arbol))
		arbol_borrar(arbol, arbol->nodo_raiz->elemento);
	free(arbol);
}
