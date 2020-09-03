#include<stdio.h>
#include "pruebas_cola.h"
#include "cola.h"

int main(){
	printf("\nEjecutando pruebas varias de cantidades...\n");
 	ConColaVacia_EncolarYDesencolar_CambiaCantidades();
	
	printf("\nEjecutando pruebas varias de casos bordes...\n");
 	ConColaNull_PreguntarSiVacia_DevuelveTrue();
	ConColaNULL_PrimerElemento_DevuelveNULL();
 	ConColaNull_IntentarEncolar_DevuelveError();
 	ConColaNull_IntentarDesencolar_DevuelveError();
	ConColaNULL_PreguntarCantidad_DevuelveCero();
	ConColaVacia_IntentarDesencolar_DevuelveError();
	ConColaVacia_PrimerElemento_DevuelveNULL();

	return 0;
}

