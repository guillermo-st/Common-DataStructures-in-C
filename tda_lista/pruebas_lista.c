#include "lista.h"
#include "pruebas_lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ERROR -1
#define EXITO 0
#define NUMINSERTAR 10 //cantidad de veces que se enlistara en la prueba de funcionamiento estandar
#define MAXRAND 101

void mostrar_elemento_entero(void* elemento){
	if(elemento)
		printf("%i, ", *(int*)elemento);

}

//genera un entero aleatorio para enlistar o desenlistar, entre 0 y MAXRAND.
int entero_aleatorio(){
	return (rand() % MAXRAND); 
}


void ConListaVacia_PreguntarCantidad_DevuelveCero(){

	char* nombre_prueba = " Lista recien creada tiene 0 elementos";
	lista_t* lista = lista_crear();
	if(lista == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, 0, (int)lista_elementos(lista));
	lista_destruir(lista);
}

void ConListaVacia_PreguntarSiVacia_DevuelveTrue(){

	char* nombre_prueba = " Lista recien creada es vacia";
	lista_t* lista = lista_crear();
	if(lista == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, true, lista_vacia(lista));
	lista_destruir(lista);
}

void ConListaVacia_InsertarUnElementoYBorrarlo_AumentaLaCantidadEnUnoSeVuelveElUltimoElementoYAlBorrarseLaListaQuedaVacia(){
	int flag = EXITO;
	char* nombre_prueba = " Al insertar una 'a' al final de la lista la cantidad es 1";
	char elemento_char = 'a';

	lista_t* lista = lista_crear();
	if(lista == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}

	flag = lista_insertar(lista, &elemento_char);
	if (flag == ERROR){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, 1 , (int)lista_elementos(lista));

	nombre_prueba = " El último elemento de la lista es la 'a'";
	verificar_test(nombre_prueba, 'a', *(char*)lista_ultimo(lista));

	nombre_prueba = " Al borrar el último elemento de la lista, esta vuelve a estar vacia";
	flag = lista_borrar(lista);
	if (flag == ERROR){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, true, lista_vacia(lista));
	lista_destruir(lista);
}

void ConListaVacia_InsertarYBorrarNUMINSERTARelementos_ResultaEnCantidadNUMINSERTARYCantidadCero(){
	
	int flag = EXITO;
	int i=0;	
	int val_aleatorios[NUMINSERTAR];

  	char* nombre_prueba = "Insertar NUMINSERTAR elementos resulta en cantidad NUMINSERTAR";

	lista_t* lista = lista_crear();
	if(lista == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	while(flag == EXITO && i<NUMINSERTAR){	
		val_aleatorios[i]= entero_aleatorio();
		flag = lista_insertar(lista, &(val_aleatorios[i]));
		i++;	
	}
	if (flag == ERROR){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, NUMINSERTAR, (int)lista_elementos(lista));
	
	i=0;	
	nombre_prueba = " Borrar el último elemento de la lista NUMINSERTAR veces resulta en cantidad final 0";
	while(flag == EXITO && i<NUMINSERTAR ){	
		flag = lista_borrar(lista);
		i++;
	}	
	if(flag == ERROR){
		interrupcion_prueba(nombre_prueba);
		lista_destruir(lista);
		return;
	}	
	verificar_test(nombre_prueba, 0, (int)lista_elementos(lista));	

	lista_destruir(lista);
	return;

}

void ConListaOcupada_InsertarElementoEnPosicionYpreguntarElementoEnPosicion_DevuelveEseElemento(){
	char* nombre_prueba = " Al insertar el 5 en la posicion 0 en una lista llena, lista_elemento_en_posicion(lista, 0) devuelve 5";
	int elemento_int = 5;
	int flag = EXITO;
	int i = 0;
	int val_aleatorios[NUMINSERTAR];
	lista_t* lista = lista_crear();
	if(lista == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	while(flag == EXITO && i<NUMINSERTAR){	
		val_aleatorios[i]= entero_aleatorio();
		flag = lista_insertar(lista, &(val_aleatorios[i]));
		i++;	
	}
	if (flag == ERROR){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	flag = lista_insertar_en_posicion(lista, &elemento_int, 0);
	if (flag == ERROR){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, 5 , *(int*)lista_elemento_en_posicion(lista, 0));
	lista_destruir(lista);
}

void ConListaOcupada_IteradorInternoYExterno_MuestranLoMismo(){
	char* nombre_prueba = " Imprimir elementos con iteradores"; 
	int flag = EXITO;
	int i = 0;
	int val_aleatorios[NUMINSERTAR];		
	lista_t* lista = lista_crear();
	if(lista == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	while(flag == EXITO && i<NUMINSERTAR){	
		val_aleatorios[i]= entero_aleatorio();
		flag = lista_insertar(lista, &(val_aleatorios[i]));
		i++;	
	}
	if (flag == ERROR){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	
	printf("\n (Imprimiendo elementos con iterador interno...) \n");
	lista_con_cada_elemento(lista, &mostrar_elemento_entero);
	printf("\n");

	lista_iterador_t* it_externo = lista_iterador_crear(lista);
	if(!it_externo){
		lista_destruir(lista);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	printf("\n (Imprimiendo elementos con iterador externo...) \n");
	while(lista_iterador_tiene_siguiente(it_externo))
		mostrar_elemento_entero( (int*)lista_iterador_siguiente(it_externo));
	printf("\n");
	lista_iterador_destruir(it_externo);	
	verificar_test(nombre_prueba, EXITO, EXITO);
	lista_destruir(lista);

}

void ConListaNull_IntentarInsertar_DevuelveError(){
	char* nombre_prueba = "Insertar con lista NULL debe devolver error";
	lista_t* lista = NULL;
	int elemento_aux = entero_aleatorio();
	verificar_test(nombre_prueba, ERROR, lista_insertar(lista, &elemento_aux));		
}

void ConListaNull_IntentarBorrar_DevuelveError(){
	char* nombre_prueba = "Borrar con lista NULL debe devolver error";
	lista_t* lista = NULL;
	verificar_test(nombre_prueba, ERROR, lista_borrar(lista));		
}

void ConListaNull_IntentarInsertarEnPosicion_DevuelveError(){
	char* nombre_prueba = "Insertar en cualquier posicion  con lista NULL debe devolver error";
	lista_t* lista = NULL;
	int elemento_aux = entero_aleatorio();
	verificar_test(nombre_prueba, ERROR, lista_insertar_en_posicion(lista, &elemento_aux, (size_t)entero_aleatorio()));		
}

void ConListaNull_IntentarBorrarDePosicion_DevuelveError(){
	char* nombre_prueba = "Borrar de cualquier posicion con lista NULL debe devolver error";
	lista_t* lista = NULL;
	verificar_test(nombre_prueba, ERROR, lista_borrar_de_posicion(lista, (size_t)entero_aleatorio()));		
}

void ConListaNull_PreguntarSiVacia_DevuelveTrue(){
	char* nombre_prueba = "Preguntar si una lista NULL es vacia debe devolver true";
	lista_t* lista = NULL;
	verificar_test(nombre_prueba,true, lista_vacia(lista));
}

void ConListaNULL_UltimoElemento_DevuelveNULL(){
	char* nombre_prueba = "El ultimo elemento de una lista NULL debe ser NULL"; 
	lista_t* lista = NULL;
	
	int ultimo_es_NULL = ERROR;
	if(lista_ultimo(lista) == NULL)
		ultimo_es_NULL = EXITO;	
	verificar_test(nombre_prueba, 0, ultimo_es_NULL);
	lista_destruir(lista);
}

void ConListaNULL_PreguntarCantidad_DevuelveCero(){
	char* nombre_prueba = "La cantidad de elementos de una lista NULL debe ser 0";	
	lista_t* lista = NULL;
	verificar_test(nombre_prueba, 0 , (int)lista_elementos(lista));	
}

void ConListaVacia_IntentarBorrar_DevuelveError(){
	char* nombre_prueba = "Borrar con lista vacia debe devolver error";
	lista_t* lista = lista_crear();
	if(!lista){
		interrupcion_prueba(nombre_prueba);
		return;
	}

	verificar_test(nombre_prueba, ERROR, lista_borrar(lista));		
	lista_destruir(lista);
}

void ConListaVacia_IntentarBorrarDePosicion_DevuelveError(){
	char* nombre_prueba = "Borrar de cualquier posición con lista vacia debe devolver error";
	lista_t* lista = lista_crear();
	if(!lista){
		interrupcion_prueba(nombre_prueba);
		return;
	}

	verificar_test(nombre_prueba, ERROR, lista_borrar_de_posicion(lista, (size_t)entero_aleatorio()));		
	lista_destruir(lista);
}

void ConListaVacia_UltimoElemento_DevuelveNULL(){
	char* nombre_prueba = "El ultimo elemento de una lista vacía debe ser NULL"; 
	lista_t* lista = lista_crear();
	if(!lista){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	int ultimo_es_NULL = ERROR;
	if(lista_ultimo(lista) == NULL)
		ultimo_es_NULL = EXITO;	
	verificar_test(nombre_prueba, 0, ultimo_es_NULL);	
	lista_destruir(lista);
}


