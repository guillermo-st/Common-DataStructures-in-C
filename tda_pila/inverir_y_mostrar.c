#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

void mostrar_uno_y_uno_rec(pila_t*);
void invertir_pila(pila_t*, pila_t*);

void invertir_y_mostrar_rec(pila_t* pila){
	
	if(pila_vacia(pila))
		return;	
	int elemento = *(int*)pila_tope(pila);
	int flag = pila_desapilar(pila);
	if (flag == -1);
		return;
	invertir_y_mostrar_rec(pila);
	printf("%i \n", elemento);
}

// muestra el elemento en el tope y en el fondo de la pila, hasta llegar al centro
void mostrar_uno_y_uno_rec(pila_t* pila){
	if(pila_vacia(pila))
		return;
	int elemento = *(int*)pila_tope(pila);	
	printf("%i \n", elemento);
	pila_desapilar(pila);
	pila_t* pila_aux = pila_crear();
	invertir_pila(pila, pila_aux);
}

void invertir_pila(pila_t* pila_original, pila_t* pila_nueva){
		
	if(pila_vacia(pila_original)){
		pila_destruir(pila_original);	
		mostrar_uno_y_uno_rec(pila_nueva);
	}		
	pila_apilar(pila_nueva, pila_tope(pila_original));
	pila_desapilar(pila_original);
	invertir_pila(pila_original, pila_nueva);
}


