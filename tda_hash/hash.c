#include "hash.h"
#include "hash_iterador.h"
#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ERROR -1
#define EXITO 0
#define COCIENTE_REHASH 5

extern char* strdup(const char*);

struct hash{
	lista_t** listas;
	size_t cantidad_elementos;
	size_t cantidad_listas;
	size_t tamanio_hash;
	hash_destruir_dato_t destructor;
};

typedef struct elemento_hash{
	char* clave;
	void* elemento;	
}elemento_hash_t;

struct hash_iter{
	hash_t* hash;
	lista_iterador_t* iterador_lista;
	size_t pos_hash;
};

size_t hashear(const char* clave , size_t capacidad){
	int sum = 0;
	for(int i=0; i<strlen(clave); i++)
		sum += clave[i];		
	return ((size_t)sum) % capacidad;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
	if(capacidad < 1)
		return NULL;
	hash_t* hash = malloc(sizeof(hash_t));
	if(!hash)
		return NULL;
	
	hash->destructor = destruir_elemento;
	hash->tamanio_hash = capacidad;
	hash->cantidad_elementos = 0;
	hash->cantidad_listas = 0;	

	hash->listas = calloc(capacidad , sizeof(lista_t*));
	if(!hash->listas){
		free(hash);
		return NULL;
	}
	return hash;
}

//devuelve la posicion de un elemento en la lista de un indice del hash.
int hash_buscar_en_indice(lista_t* lista, const char* clave){
	int pos_actual = -1;	
	int pos_buscado = -1;
	bool encontrado = false;
	
	if(!lista || !clave)
		return pos_buscado;

	elemento_hash_t* actual;
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	if(!iterador)
		return pos_buscado;

	while(!encontrado && lista_iterador_tiene_siguiente(iterador)){
		actual = lista_iterador_siguiente(iterador);
		if (strcmp(actual->clave, clave) == 0)
			encontrado = true;
		pos_actual++;
	}
	if(encontrado)
		pos_buscado = pos_actual;

	lista_iterador_destruir(iterador);
	return pos_buscado;
}


int hash_rehash(hash_t* hash){
	hash_t* hash_aux = hash_crear(hash->destructor, hash->tamanio_hash * 2 +1);	
	if(!hash_aux)
		return ERROR;
	hash_iterador_t* it = hash_iterador_crear(hash);
	if(!it){
		hash_destruir(hash_aux);
		return ERROR;
	}
	while(hash_iterador_tiene_siguiente(it)){
		char* clave = hash_iterador_siguiente(it);
		hash_insertar(hash_aux, clave, hash_obtener(hash, clave));
	}
	hash_t hash_p = *hash; 
	*hash = *hash_aux;
	*hash_aux = hash_p;

	hash_aux->destructor = NULL;
	hash_iterador_destruir(it);
	hash_destruir(hash_aux);
	return EXITO;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){ 
	if(!hash || !clave)
		return ERROR;
	
	size_t pos_lista = hashear(clave, hash->tamanio_hash);

	if(hash_contiene(hash, clave)){       //si la clave ya se encontraba almacenada en el hash.
		hash_quitar(hash, clave);
	}	
	
	elemento_hash_t* nuevo = malloc(sizeof(elemento_hash_t));
	if(!nuevo)
		return ERROR;

	nuevo->clave = malloc(sizeof(char)* strlen(clave)+1);
	if(!nuevo->clave)
		return ERROR;

	strcpy(nuevo->clave, clave);
	nuevo->elemento = elemento;
	
	if(hash->listas[pos_lista] == NULL){
		hash->listas[pos_lista] = lista_crear();
		hash->cantidad_listas ++;
	}
	lista_insertar(hash->listas[pos_lista], nuevo);
	hash->cantidad_elementos ++;

	if(hash->cantidad_elementos == hash->cantidad_listas * COCIENTE_REHASH)
		return hash_rehash(hash);

	return EXITO;
}

bool hash_contiene(hash_t* hash, const char* clave){
	if(!hash)
		return false;
	size_t pos_lista = hashear(clave, hash->tamanio_hash);
	int pos_buscado = hash_buscar_en_indice(hash->listas[pos_lista], clave);	
	return (pos_buscado >= 0);
}

size_t hash_cantidad(hash_t* hash){
	return hash? hash->cantidad_elementos : 0;	
}


void* hash_obtener(hash_t* hash, const char* clave){
	if(!hash)
		return NULL;
	size_t pos_lista = hashear(clave, hash->tamanio_hash);
	int pos_buscado = hash_buscar_en_indice(hash->listas[pos_lista], clave);	
	elemento_hash_t* buscado = lista_elemento_en_posicion(hash->listas[pos_lista], pos_buscado);	
	return buscado? buscado->elemento : NULL;
}

int hash_quitar(hash_t* hash, const char* clave){
	if(!hash || hash->cantidad_elementos == 0)
		return ERROR;
	size_t pos_lista = hashear(clave, hash->tamanio_hash);
	int pos_buscado = hash_buscar_en_indice(hash->listas[pos_lista], clave);	
	elemento_hash_t* buscado = lista_elemento_en_posicion(hash->listas[pos_lista], pos_buscado);	
	
	if(buscado){
		free(buscado->clave);
		if(hash->destructor)
			hash->destructor(buscado->elemento);
		free(buscado);
		hash->cantidad_elementos--;
		return lista_borrar_de_posicion(hash->listas[pos_lista], pos_buscado);
	}
	return ERROR;
}

void hash_destruir(hash_t* hash){
	if(hash){
		hash_iterador_t* it = hash_iterador_crear(hash);

		while(hash_iterador_tiene_siguiente(it))
			hash_quitar(hash, hash_iterador_siguiente(it));

		for(int i = 0; i<hash->tamanio_hash; i++){
			lista_destruir(hash->listas[i]);
		}
		free(hash->listas);
		hash_iterador_destruir(it);
		free(hash);
	}
}


hash_iterador_t* hash_iterador_crear(hash_t* hash){
	if(!hash)
		return NULL;	
	hash_iterador_t* it = malloc(sizeof(hash_iterador_t));	
	if(it){
		it->hash = hash;
		it->pos_hash = 0;
		it->iterador_lista = lista_iterador_crear(hash->listas[0]);
	}	
	return it;
}

bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
	if(!iterador || iterador->hash->cantidad_elementos == 0)
		return false;
	bool hay_siguiente_en_lista = false;
	while(!hay_siguiente_en_lista && iterador->pos_hash < iterador->hash->tamanio_hash){
		hay_siguiente_en_lista = lista_iterador_tiene_siguiente(iterador->iterador_lista);
		if(!hay_siguiente_en_lista){
			iterador->pos_hash++;
			lista_iterador_destruir(iterador->iterador_lista);	
			iterador->iterador_lista = NULL;
			if(iterador->pos_hash < iterador->hash->tamanio_hash)
				iterador->iterador_lista = lista_iterador_crear(iterador->hash->listas[iterador->pos_hash]);
		}
	}
	return hay_siguiente_en_lista;
}

void* hash_iterador_siguiente(hash_iterador_t* iterador){
	if(!iterador)
		return NULL;
	if(hash_iterador_tiene_siguiente(iterador)){
		elemento_hash_t* aux = lista_iterador_siguiente(iterador->iterador_lista);
		return (void*)aux->clave;
	}
	return NULL;
}

void hash_iterador_destruir(hash_iterador_t* iterador){
	if(iterador){
		lista_iterador_destruir(iterador->iterador_lista);	
		free(iterador);
	}
}
