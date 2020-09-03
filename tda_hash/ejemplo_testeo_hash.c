#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"
#include "pruebas_hash.h"
#define CAPACIDAD_INICIAL 3
#define CANT_PRUEBAS 18 
#define NUMINSERTAR 7
#define ERROR -1


int main(){
	srand((unsigned)time(NULL)); 
   	
	hash_t* hash = NULL; 
	int pruebas_erradas = 0;
	pruebas_erradas -= ConHashNULL_IntentarQuitar_DevuelveERROR(hash);
	pruebas_erradas -= ConHashNULL_IntentarInsertar_DevuelveERROR( hash);
	pruebas_erradas -= ConHashNULL_PreguntarCantidad_DevuelveCero( hash);
	pruebas_erradas -= ConHashNULL_PreguntarSiContieneClave_DevuelveFalso( hash);
	pruebas_erradas -= ConHashNULL_IntentarObtenerElemento_DevuelveNULL( hash);
	pruebas_erradas -= ConHashNULL_Iterar_NoRecorreElementos(hash);

	hash = hash_crear(NULL, CAPACIDAD_INICIAL);
	
	if(!hash){
       		printf("\n Error al crear el arbol \n");		
		return ERROR;
	}

	pruebas_erradas -= ConHashVacio_IntentarQuitar_DevuelveERROR(hash);
	pruebas_erradas -= ConHashVacio_ObtenerUnElemento_DevuelveNULL(hash);
	pruebas_erradas -= ConHashVacio_PreguntarCantidadDeElementos_DevuelveCero(hash);
	pruebas_erradas -= ConHashVacio_PreguntarSiContieneClave_DevuelveFalso(hash);
	pruebas_erradas -= ConHashVacio_InsertarYVerificarElementos_EncuentraTodos(hash);
	pruebas_erradas -= ConHashVacio_Iterar_NoRecorreElementos(hash);
	
	
	char* v_claves[NUMINSERTAR];
	int v_elementos[NUMINSERTAR];
	int j=0;
	bool flag_error_insertar = false;
	while(j<NUMINSERTAR && !flag_error_insertar){
		v_elementos[j] = entero_aleatorio();
		v_claves[j] = clave_aleatoria();
		flag_error_insertar = (hash_insertar(hash, v_claves[j], &v_elementos[j]) == ERROR);
		j++;	
	}

	if(flag_error_insertar){
       		printf("\n Error al insertar elementos en el hash \n");		
		return ERROR;
	}

	pruebas_erradas -= ConHashCargado_PreguntarCantidad_DevuelveLaCantidadEsperada(hash, NUMINSERTAR);
	pruebas_erradas -= ConHashCargado_PreguntarSiContieneClavesCargadas_DevuelveVerdaderoParaTodas( hash, NUMINSERTAR, v_claves);
	pruebas_erradas -= ConHashCargado_ObtenerElElementoDeUnaClave_DevuelveElElementoCorrecto(hash, v_claves[0], &v_elementos[0]);
	pruebas_erradas -= ConHashCargado_QuitarClave_ReduceCantidad(hash, v_claves[0]);
	pruebas_erradas -= ConHashCargado_QuitarClave_HashDejaDeContenerla(hash, v_claves[1]);
	pruebas_erradas -= ConHashCargado_Iterar_RecorreTodosLosElementos(hash);


	for(int i=0; i<NUMINSERTAR; i++){
		free(v_claves[i]);
	}	
      	
	printf("\n Has fallado %i de %i pruebas \n", pruebas_erradas, CANT_PRUEBAS);		
    	hash_destruir(hash);
    	return 0;
}
