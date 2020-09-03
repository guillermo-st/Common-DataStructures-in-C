#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct heap heap_t;
typedef void (*heap_destructor_t) (void*);	
typedef int (*heap_comparador_t) (void* , void*);

//devuelve un puntero a un heap creado, de la capacidad inicial provista y con el comparador y el destructor dado. En caso de error devuelve NULL.
heap_t* heap_crear(size_t capacidad_inicial, heap_destructor_t destructor, heap_comparador_t comparador);

//inserta un elemento en el heap, y reacomoda el heap correctamente para que se mantenga la condición de heap maximal.
int heap_insertar(heap_t* heap, void* elemento);

//elimina la raíz del heap, y reacomoda el heap correctamente para que se mantenga la condición de heap maximal.
int heap_borrar_raiz(heap_t* heap);

//devuelve un puntero a la raíz del heap, que por ser un heap maximal es a su vez el máximo.
void* heap_raiz(heap_t* heap);

//devuelve true si el heap no tiene elementos, de lo contrario devuelve false.
bool heap_vacio(heap_t* heap);

//ordena un array dado mediante el método heap_sort() con el comparador provisto. El array resulta ordenado inplace, pero los punteros pasan a estar en memoria
//dinamica. Es responsabilidad del usuario liberar dicha memoria.
int heapsort(void** array, size_t tope, heap_destructor_t destructor, heap_comparador_t comparador);

//itera internamente los elementos del heap, ejecutando la función con cada uno de ellos.
void heap_con_cada_elemento(heap_t* heap, void (*funcion)(void*, void*), void* extra);

//destruye el heap y a todos sus elementos mediante el destructor provisto en la creación.
void heap_destruir(heap_t* heap);

#endif /* __HEAP_H__ */


