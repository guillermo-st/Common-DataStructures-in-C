#include "testing.h"
#include <stdio.h>
#include <string.h>
const int EXITO = 0;
const int ERROR = -1;

int comparador_default(void* elemento_1, void* elemento_2){
	if(elemento_1 == elemento_2)
		return 0;
	else
		return -1;	
}

int verificar_test(char* nombre_prueba, void* resultado_esperado, void* resultado_obtenido, int (*comparador)(void*, void*)){
	char* resultado_prueba;	
	if(comparador != NULL)	
		resultado_prueba = (comparador(resultado_esperado, resultado_obtenido) == 0) ? "OK":"FAIL";	
	else
		resultado_prueba = (comparador_default(resultado_esperado, resultado_obtenido) == 0) ? "OK":"FAIL";	
	
	printf("\n [%s] %s .\n", resultado_prueba, nombre_prueba);

	if(strcmp(resultado_prueba, "OK") == 0)
		return EXITO;
	else return ERROR;
}
int interrupcion_prueba(char* nombre_prueba){
	printf("\n TEST: %s ... %s \n", nombre_prueba, "FAIL");
	printf("\n (No se pudo concretar la prueba %s, posible falta de memoria o incumplimiento de precondicion en test, pasando a la siguiente...) \n", nombre_prueba);
	return ERROR;
}
