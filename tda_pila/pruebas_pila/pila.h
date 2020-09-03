#ifndef __PILA_H__
#define __PILA_H__

#include <stdbool.h>

typedef struct pila {
	int tope;
	void** elementos;
	int tamanio;
} pila_t;

/* 
 * Crea una pila, reservando la memoria necesearia para almacenar la
 * estructura.
 * Devuelve un puntero a la estructura pila_t creada o NULL si no pudo
 * crearla.
 */
pila_t* pila_crear();

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int pila_apilar(pila_t* pila, void* elemento);

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o 1 si no pudo.
 */
int pila_desapilar(pila_t* pila);

/* 
 * Determina si la pila está vacia.
 * Devuelve true si está vacía, false en caso contrario.
 */
bool pila_vacia(pila_t* pila);

/* 
 * Devuelve la cantidad de elementos almacenados en la pila.
 */
int pila_cantidad(pila_t* pila);

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* pila_tope(pila_t* pila);

/* 
 * Destruye la pila liberando la memoria reservada para la misma.
 */
void pila_destruir(pila_t* pila);

#endif /* __PILA_H__ */
