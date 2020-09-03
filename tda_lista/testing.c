#include "testing.h"
#include <stdio.h>
#define ERROR -1
#define EXITO 0

void verificar_test(char* nombre_prueba, int resultado_esperado, int resultado_obtenido){
	char* resultado_prueba = "FAIL!";	
	if(resultado_esperado == resultado_obtenido)
		resultado_prueba = "OK!";	
	printf("\n TEST: %s ... %s \n", nombre_prueba, resultado_prueba);
}
void interrupcion_prueba(char* nombre_prueba){
	verificar_test(nombre_prueba, EXITO , ERROR);
	printf("\n (No se pudo concretar la prueba %s, posible falta de memoria, pasando a la siguiente...) \n", nombre_prueba);

}
