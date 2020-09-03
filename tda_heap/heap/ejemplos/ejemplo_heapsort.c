#include <stdio.h>
#include <stdbool.h>
#include "heap.h"

#define EXITO 0 
#define ERROR 0 
#define CAPACIDAD_INICIAL 5
#define NUMINSERTAR 11

int comparador_enteros(void* e1, void* e2){
	int* i1 = (int*)e1;
	int* i2 = (int*)e2;

	if(*i1 < *i2)
		return -1;
	else if(*i1 == *i2)
		return 0;
	return 1;
}

void mostrar_array_enteros(int** array_enteros, int tope){
	for(int i = 0; i<tope; i++)
		printf("%i, ",*array_enteros[i]);
}

int main(){

	int flag = EXITO;

	int enteros[] = { 1 , 4 , 5 , 8 , 7 , 65, 12 , 29, 50 , 21 , 43};
	int* p_enteros[NUMINSERTAR];

	for(int i = 0; i<NUMINSERTAR; i++)
		p_enteros[i] = &(enteros[i]);
	
	printf("\n");
	mostrar_array_enteros(p_enteros, NUMINSERTAR);	
	printf("\n");

	flag = heapsort((void**)p_enteros, NUMINSERTAR, NULL, comparador_enteros);
	
	printf("\n");
	mostrar_array_enteros(p_enteros, NUMINSERTAR);	
	printf("\n");
	
	for(int j = 0; j<NUMINSERTAR; j++){
		if(p_enteros[j])
			free(p_enteros[j]);
		p_enteros[j] = NULL;
	}


	if(flag == EXITO)
		
	return 0;
}
