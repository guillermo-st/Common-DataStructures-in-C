#include "cola.h"
#include "pruebas_cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERROR -1
#define EXITO 0
#define NUMENCOLAR 50 //cantidad de veces que se encolara en la prueba de funcionamiento estandar
#define MAXRAND 101

//genera un entero aleatorio para encolar o desencolar, entre 0 y MAXRAND.
int entero_aleatorio(){
	return (rand() % MAXRAND); 
}

//recibiendo el nombre de una prueba, su resultado esperado y su resultado obtenido, muestra por stdout si la prueba fue exitosa.
void verificar_test(char* nombre_prueba, int resultado_esperado, int resultado_obtenido){
	char* resultado_prueba = "FAIL!";	
	if(resultado_esperado == resultado_obtenido)
		resultado_prueba = "OK!";	
	printf("\n TEST: %s ... %s \n", nombre_prueba, resultado_prueba);
}

//muestra por pantalla que la prueba falló por falta de memoria, y que no se pudo concretar.
//Es decir, ocurre cuando no necesariamente hay errores en el TDA testeado, sinó que la prueba fue interrumpida.
void interrupcion_prueba(char* nombre_prueba){
	verificar_test(nombre_prueba, EXITO , ERROR);
	printf("\n (No se pudo concretar la prueba %s, posible falta de memoria, pasando a la siguiente...) \n", nombre_prueba);

}

void ConColaVacia_EncolarYDesencolar_CambiaCantidades(){
	
	int flag = EXITO;
	int i=0;	
	int val_aleatorios[NUMENCOLAR];

	char* nombre_prueba = " [1/8] Cola recien creada tiene 0 elementos";
	cola_t* cola = cola_crear();
	if(cola == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, 0, cola_cantidad(cola));
	
	nombre_prueba = " [2/8] Cola recien creada es vacia";
	verificar_test(nombre_prueba, true, cola_vacia(cola));
	
	nombre_prueba = " [3/8] Al encolar una 'a' la cantidad es 1";
	char elemento = 'a';
	flag = cola_encolar(cola, &elemento);
	if (flag == ERROR){
		cola_destruir(cola);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, 1 , cola_cantidad(cola));
	
	nombre_prueba = " [4/8] El primer elemento en la cola es la 'a'";
	verificar_test(nombre_prueba, 'a', *(char*)cola_primero(cola));

	nombre_prueba = " [5/8] Al desencolar la 'a' la cola vuelve a estar vacia";
	flag = cola_desencolar(cola);
	if (flag == ERROR){
		cola_destruir(cola);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, true, cola_vacia(cola));

	nombre_prueba = " [6/8] Encolar NUMENCOLAR elementos resulta en cantidad NUMENCOLAR";
	
	while(flag == EXITO && i<NUMENCOLAR){	
		val_aleatorios[i]= entero_aleatorio();
		flag = cola_encolar(cola, &(val_aleatorios[i]));
		i++;	
	}
	if (flag == ERROR){
		cola_destruir(cola);
		interrupcion_prueba(nombre_prueba);
		return;
	}
	verificar_test(nombre_prueba, NUMENCOLAR, cola_cantidad(cola));

	nombre_prueba = " [7/8] Desencolar NUMENCOLAR elementos resulta en cantidad final 0";
	i=0;	
	while(flag == EXITO && i<NUMENCOLAR){	
		flag = cola_desencolar(cola);
		i++;
	}	
	if(flag == ERROR){
		interrupcion_prueba(nombre_prueba);
		cola_destruir(cola);
		return;
	}	
	verificar_test(nombre_prueba, 0, cola_cantidad(cola));	
	
	nombre_prueba = " [8/8] La cola queda vacía";
	verificar_test(nombre_prueba, true, cola_vacia(cola));	
	cola_destruir(cola);
	return;
}

void ConColaNull_IntentarEncolar_DevuelveError(){
	char* nombre_prueba = "Encolar con Cola NULL debe devolver error";
	cola_t* cola = NULL;
	int elemento_aux = entero_aleatorio();
	verificar_test(nombre_prueba, ERROR, cola_encolar(cola, &elemento_aux));		
}

void ConColaNull_IntentarDesencolar_DevuelveError(){
	char* nombre_prueba = "Desencolar con cola NULL debe devolver error";
	cola_t* cola = NULL;
	verificar_test(nombre_prueba, ERROR, cola_desencolar(cola));		
}

void ConColaNull_PreguntarSiVacia_DevuelveTrue(){
	char* nombre_prueba = "Preguntar si una cola NULL es vacia debe devolver true";
	cola_t* cola = NULL;
	verificar_test(nombre_prueba,true, cola_vacia(cola));
}

void ConColaNULL_PrimerElemento_DevuelveNULL(){
	char* nombre_prueba = "El primer elemento de una cola NULL debe ser NULL"; 
	cola_t* cola = NULL;
	
	int primero_es_NULL = ERROR;
	if(cola_primero(cola) == NULL)
		primero_es_NULL = EXITO;	
	verificar_test(nombre_prueba, 0, primero_es_NULL);
	cola_destruir(cola);
}

void ConColaNULL_PreguntarCantidad_DevuelveCero(){
	char* nombre_prueba = "La cantidad de una cola NULL debe ser 0";	
	cola_t* cola = NULL;
	verificar_test(nombre_prueba, 0 , cola_cantidad(cola));	
}

void ConColaVacia_IntentarDesencolar_DevuelveError(){
	char* nombre_prueba = "Desencolar con cola vacia debe devolver error";
	cola_t* cola = cola_crear();
	if(!cola){
		interrupcion_prueba(nombre_prueba);
		return;
	}

	verificar_test(nombre_prueba, ERROR, cola_desencolar(cola));		
	cola_destruir(cola);
}

void ConColaVacia_PrimerElemento_DevuelveNULL(){
	char* nombre_prueba = "El primer elemento de una cola vacía debe ser NULL"; 
	cola_t* cola = cola_crear();
	if(!cola){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	int primero_es_NULL = ERROR;
	if(cola_primero(cola) == NULL)
		primero_es_NULL = EXITO;	
	verificar_test(nombre_prueba, 0, primero_es_NULL);	
	cola_destruir(cola);
}
