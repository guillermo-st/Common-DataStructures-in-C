#include<stdio.h>
#include "pruebas_lista.h"
#include "lista.h"

int main(){
	ConListaVacia_PreguntarCantidad_DevuelveCero();
	ConListaVacia_PreguntarSiVacia_DevuelveTrue();
	ConListaVacia_InsertarYBorrarNUMINSERTARelementos_ResultaEnCantidadNUMINSERTARYCantidadCero();
	ConListaVacia_InsertarUnElementoYBorrarlo_AumentaLaCantidadEnUnoSeVuelveElUltimoElementoYAlBorrarseLaListaQuedaVacia();
	ConListaOcupada_InsertarElementoEnPosicionYpreguntarElementoEnPosicion_DevuelveEseElemento();
	ConListaOcupada_IteradorInternoYExterno_MuestranLoMismo();
	ConListaNull_IntentarInsertar_DevuelveError();
	ConListaNull_IntentarBorrar_DevuelveError();
	ConListaNull_IntentarInsertarEnPosicion_DevuelveError();
	ConListaNull_IntentarBorrarDePosicion_DevuelveError();
	ConListaNull_PreguntarSiVacia_DevuelveTrue();
	ConListaNULL_UltimoElemento_DevuelveNULL();
	ConListaNULL_PreguntarCantidad_DevuelveCero();
	ConListaVacia_IntentarBorrar_DevuelveError();
	ConListaVacia_IntentarBorrarDePosicion_DevuelveError();
	ConListaVacia_UltimoElemento_DevuelveNULL();
return 0;
}

