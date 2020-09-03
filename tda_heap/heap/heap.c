#include "heap.h"
#include <stdio.h>
#include <string.h>


#define EXITO 0
#define ERROR -1
#define COEF_REDIMENSION 2


struct heap{
	void** elementos;
	size_t cantidad;
	size_t capacidad;
	heap_destructor_t destructor;
	heap_comparador_t comparador;
};

//devuelve la posicion del padre de un elemento.
size_t padre(heap_t* heap, size_t pos){
	if(!heap || pos == 0)
		return pos;
	return (pos-1)/2;
}

//devuelve la posicion del hijo izquierdo de un elemento, o su propia posicion de no tener hijo izquierdo.
size_t hijo_izq(heap_t* heap, size_t pos){
	if(!heap || (pos * 2 + 1) >= heap->cantidad)
		return pos;
	return pos * 2 + 1;
}

//devuelve la posicion del hijo derecho de un elemento, o su propia posicion de no tener hijo derecho.
size_t hijo_der(heap_t* heap, size_t pos){
	if(!heap || (pos * 2 + 2) >= heap->cantidad)
		return pos;
	return pos * 2 + 2;
}

//intercambia dos elementos del heap.
void swap(void** elemento1, void** elemento2){
	void* aux = *elemento1;
	*elemento1 = *elemento2;
	*elemento2 = aux;	
}

heap_t* heap_crear(size_t capacidad_inicial, heap_destructor_t destructor, heap_comparador_t comparador){

	if(capacidad_inicial <= 0 || !comparador)
		return NULL;	
	
	heap_t* heap = malloc(sizeof(heap_t));	
	if(!heap)
		return NULL;
	
	heap->elementos = calloc(capacidad_inicial, sizeof(void*));
	if(!heap->elementos){
		free(heap);
		return NULL;
	}

	heap->cantidad = 0;
	heap->capacidad = capacidad_inicial;
	heap->destructor = destructor;
	heap->comparador = comparador;
	return heap;
}

// redimensiona el heap cuando se supera la capacidad inicial. Devuelve EXITO en caso de haber logrado la redimension, de lo contrario ERROR.
int redimensionar_heap(heap_t* heap){
	void** elementos_aux = realloc(heap->elementos, heap->capacidad * COEF_REDIMENSION * sizeof(void*));
	if(!elementos_aux)
		return ERROR;
	heap->elementos = elementos_aux;
	heap->capacidad *= COEF_REDIMENSION;
	return EXITO;	
}

//mueve un elemento hacia arriba en el heap en el caso de que sea mayor a a su padre (por ser heap maximal).
//Se llama recursivamente hasta lograr la condición de heap maximal.
void sift_up(heap_t* heap, size_t pos){
	if(pos <= 0 || heap->comparador(heap->elementos[pos] , heap->elementos[padre(heap, pos)]) <= 0) 
		return;
	swap(&heap->elementos[pos], &heap->elementos[padre(heap,pos)]);
	sift_up(heap, (pos-1)/2);	
}

//mueve un elemento hacia abajo en el heap en caso de que alguno de sus hijos sea mayor (por ser heap maximal).
//Se llama recursivamente hasta lograr la condición de heap maximal.
void sift_down(heap_t* heap, size_t pos){
	if(hijo_izq(heap, pos) == pos)
		return;
	
	size_t pos_hijo_mayor = hijo_izq(heap, pos);

	if(hijo_der(heap, pos) != pos && heap->comparador(heap->elementos[hijo_izq(heap, pos)], heap->elementos[hijo_der(heap, pos)]) <= 0){
		pos_hijo_mayor = hijo_der(heap,pos);
	}

	
	if(heap->comparador(heap->elementos[pos], heap->elementos[pos_hijo_mayor]) >= 0)
		return;
	swap(&heap->elementos[pos], &heap->elementos[pos_hijo_mayor]); 
	sift_down(heap, pos_hijo_mayor);
}

bool heap_vacio(heap_t* heap){
	return (!heap || heap->cantidad == 0);
}

void* heap_raiz(heap_t* heap){
	if(heap_vacio(heap))
		return NULL;
	return heap->elementos[0];
}

int heap_insertar(heap_t* heap, void* elemento){
	if(!heap || !elemento)
		return ERROR;

	if(heap->cantidad == heap->capacidad)
		redimensionar_heap(heap);

	heap->elementos[heap->cantidad] = elemento;
	heap->cantidad++;
	sift_up(heap, heap->cantidad - 1);
	return EXITO;
}

int heap_borrar_raiz(heap_t* heap){
	if(!heap)
		return ERROR;
	if(!heap_vacio(heap)){
		swap(&heap->elementos[0], &(heap->elementos[heap->cantidad - 1]));
		if(heap->destructor)
			heap->destructor(heap->elementos[heap->cantidad - 1]);
		
		heap->elementos[heap->cantidad - 1] = NULL;
		heap->cantidad --;
		sift_down(heap, 0);
	}
	return EXITO;
}

void heap_destruir(heap_t* heap){
	if(!heap)
		return;
	
	while(!heap_vacio(heap))
		heap_borrar_raiz(heap);
	
	free(heap->elementos);
	free(heap);
}

int heapsort(void** array, size_t tope, heap_destructor_t destructor, heap_comparador_t comparador){
	heap_t* heap = heap_crear(tope, NULL, comparador);	
	if(!heap)
		return ERROR;	

	int flag_operacion = EXITO;
	int i = 0;

	while(flag_operacion == EXITO && i<tope){
		void* nuevo = malloc(sizeof(void*));
		nuevo = array[i];
		flag_operacion = heap_insertar(heap, nuevo);
		i++;
	}

	if(flag_operacion == ERROR){
		heap_destruir(heap);
		return ERROR;
	}

	while(flag_operacion == EXITO && !heap_vacio(heap)){
		if(destructor)
			destructor(array[i-1]);
		array[i-1] = heap_raiz(heap);
		heap_borrar_raiz(heap);
		i--;
	}

	heap_destruir(heap);
	return EXITO;
}

void heap_con_cada_elemento(heap_t* heap, void (*funcion)(void*, void*), void* extra){
	if(!heap || !funcion)
		return;	
	for(int i = 0; i< heap->cantidad; i++)
		funcion(heap->elementos[i], extra);
}


