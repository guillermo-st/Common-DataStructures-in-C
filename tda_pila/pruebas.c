#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERROR -1
#define EXITO 0
#define NUMAPILAR 50 //cantidad de veces que se apilara en la prueba de funcionamiento estandar
#define MAXRAND 101

//genera un entero aleatorio para apilar o desapilar, entre 0 y MAXRAND.
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

void ConPilaVacia_ApilarYDesapilarNUMAPILARelementos_CantidadFinalEsCero(){
	char* nombre_prueba = "Apilar y desapilar la misma cantidad de elementos resulta en cantidad final 0";
	pila_t* pila = pila_crear();
	if(pila == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}
	int cant_inicial = pila_cantidad(pila);
	int flag = EXITO;
	int i=0;	
	int val_aleatorios[NUMAPILAR];

	while(flag == EXITO && i<NUMAPILAR){	
		val_aleatorios[i]= entero_aleatorio();
		flag = pila_apilar(pila, &(val_aleatorios[i]));
		i++;	
	}

	if (flag == ERROR){
		pila_destruir(pila);
		interrupcion_prueba(nombre_prueba);
		return;
	}

	i=0;	
	while(flag == EXITO && i<NUMAPILAR){	
		flag = pila_desapilar(pila);
		i++;
	}	
	if(flag == ERROR){
		interrupcion_prueba(nombre_prueba);
		pila_destruir(pila);
		return;
	}	
	verificar_test(nombre_prueba, cant_inicial, pila_cantidad(pila));	
	pila_destruir(pila);
	return;
}

void ConPilaNull_IntentarApilar_DevuelveError(){
	char* nombre_prueba = "Apilar con pila null debe devolver error";
	pila_t* pila = NULL;
	int elemento_aux = entero_aleatorio();
	verificar_test(nombre_prueba, pila_apilar(pila, &elemento_aux), ERROR);		
}

void ConPilaNull_IntentarDesapilar_DevuelveError(){
	char* nombre_prueba = "Desapilar con pila null debe devolver error";
	pila_t* pila = NULL;
	verificar_test(nombre_prueba, pila_desapilar(pila), ERROR);		
}

void ConPilaVacia_IntentarDesapilar_DevuelveError(){
	char* nombre_prueba = "Desapilar con pila vacia debe devolver error";
	pila_t* pila = pila_crear();
	if(pila == NULL){
		interrupcion_prueba(nombre_prueba);
		return;
	}

	verificar_test(nombre_prueba, pila_desapilar(pila), ERROR);		
	pila_destruir(pila);
}


void ConPilaNull_PreguntarSiVacia_DevuelveTrue(){
	char* nombre_prueba = "Preguntar si una pila null es vacia debe devolver true";
	pila_t* pila = NULL;
	verificar_test(nombre_prueba,true, pila_vacia(pila));
}

int main(){
	ConPilaVacia_ApilarYDesapilarNUMAPILARelementos_CantidadFinalEsCero();
	ConPilaNull_IntentarApilar_DevuelveError();
	ConPilaNull_IntentarDesapilar_DevuelveError();
	ConPilaVacia_IntentarDesapilar_DevuelveError();
	ConPilaNull_PreguntarSiVacia_DevuelveTrue();
	return 0;
}
