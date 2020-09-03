#include <stdio.h>
#include <stdbool.h>
#include "heap.h"

#define EXITO 0 
#define ERROR 0 
#define CAPACIDAD_INICIAL 6
#define NUMINSERTAR 5 

int comparador_enteros(void* e1, void* e2){
	int i1 = *(int*)e1;
	int i2 = *(int*)e2;

	if(i1 < i2)
		return -1;
	else if(i1 == i2)
		return 0;
	return 1;
}

void mostrar_entero(void* entero, void* extra){
		printf("%i ", *(int*)entero);
}

int main(){

	heap_t* heap = heap_crear(CAPACIDAD_INICIAL, NULL, comparador_enteros);
	if(!heap)
		return ERROR;	

	int entero1 = 1;
	int entero2 = 2;
	int entero3 = 3;
	int entero4 = 4;
	int entero5 = 5;
	int entero6 = 6;
	int entero7 = 7;

	if(heap_vacio(heap))
		printf(" \n El heap comienza vacio \n");	

	printf(" \n Insertando el numero %i el heap resulta: \n", entero1);	
	heap_insertar(heap, &entero1);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");
	
	printf(" \n Insertando el numero %i el heap resulta: \n", entero2);	
	heap_insertar(heap, &entero2);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");
	
	printf(" \n Insertando el numero %i el heap resulta: \n", entero3);	
	heap_insertar(heap, &entero3);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");
	
	printf(" \n Insertando el numero %i el heap resulta: \n", entero4);	
	heap_insertar(heap, &entero4);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");
	
	printf(" \n Insertando el numero %i el heap resulta: \n", entero5);	
	heap_insertar(heap, &entero5);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");

	printf(" \n Insertando el numero %i el heap resulta: \n", entero6);	
	heap_insertar(heap, &entero6);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");
	
	printf(" \n Insertando el numero %i el heap resulta: \n", entero7);	
	heap_insertar(heap, &entero7);
	heap_con_cada_elemento(heap, mostrar_entero, NULL );
	printf("\n");
	
	printf(" \n Borrando elementos \n");	
	while(!heap_vacio(heap)){
		printf("la raiz es %i, borrandola el heap resulta: \n ", *(int*)heap_raiz(heap));
		heap_borrar_raiz(heap);
		heap_con_cada_elemento(heap, mostrar_entero, NULL );
		printf("\n");
	}

	if(heap_vacio(heap))
		printf(" \n El heap termina vacio \n");	
	
	heap_destruir(heap);
		
	return 0;
}
