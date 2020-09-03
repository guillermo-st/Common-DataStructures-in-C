#ifndef __PRUEBAS_HASH_H
#define __PRUEBAS_HASH_H
#include "hash.h"

//devuelve un int aleatorio
int entero_aleatorio();

//genera un string aleatorio para usar de clave. Es necesario hacerle free finalizada su utilización.
char* clave_aleatoria();


//Comprueba el correcto funcionamiento de la primitiva hash_quitar() cuando el hash está vacio
int ConHashVacio_IntentarQuitar_DevuelveERROR(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_obtener() cuando el hash está vacio
int ConHashVacio_ObtenerUnElemento_DevuelveNULL(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_cantidad() cuando el hash está vacio
int ConHashVacio_PreguntarCantidadDeElementos_DevuelveCero(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_contiene() cuando el hash está vacio
int ConHashVacio_PreguntarSiContieneClave_DevuelveFalso(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_insertar() cuando el hash está vacio
int ConHashVacio_InsertarYVerificarElementos_EncuentraTodos(hash_t* hash);
//Comprueba el correcto funcionamiento del iterador del hash cuando el hash está vacio
int ConHashVacio_Iterar_NoRecorreElementos(hash_t* hash);


//Comprueba el correcto funcionamiento de la primitiva hash_quitar() cuando el hash está NULL
int ConHashNULL_IntentarQuitar_DevuelveERROR(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_insertar() cuando el hash está NULL
int ConHashNULL_IntentarInsertar_DevuelveERROR(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_cantidad() cuando el hash está NULL
int ConHashNULL_PreguntarCantidad_DevuelveCero(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_contiene() cuando el hash está NULL
int ConHashNULL_PreguntarSiContieneClave_DevuelveFalso(hash_t* hash);
//Comprueba el correcto funcionamiento de la primitiva hash_obtener() cuando el hash está NULL
int ConHashNULL_IntentarObtenerElemento_DevuelveNULL(hash_t* hash);
//Comprueba el correcto funcionamiento del iterador del hash cuando el hash está NULL
int ConHashNULL_Iterar_NoRecorreElementos(hash_t* hash);


//Comprueba el correcto funcionamiento de la primitiva hash_cantidad() cuando el hash tiene elementos.
int ConHashCargado_PreguntarCantidad_DevuelveLaCantidadEsperada(hash_t* hash, size_t cantidad_esperada);
//Comprueba el correcto funcionamiento de la primitiva hash_contiene() cuando el hash tiene elementos.
int ConHashCargado_PreguntarSiContieneClavesCargadas_DevuelveVerdaderoParaTodas(hash_t* hash, size_t cantidad_cargados, char** claves);
//Comprueba el correcto funcionamiento de la primitiva hash_obtener() cuando el hash tiene elementos.
int ConHashCargado_ObtenerElElementoDeUnaClave_DevuelveElElementoCorrecto(hash_t* hash, char* clave, void* elemento_esperado);
//Comprueba el correcto funcionamiento de la primitiva hash_quitar() y de hash_cantidad() cuando el hash tiene elementos.
int ConHashCargado_QuitarClave_ReduceCantidad(hash_t* hash, char* clave);
//Comprueba el correcto funcionamiento de la primitiva hash_quitar() y de hash_contiene() cuando el hash tiene elementos.
int ConHashCargado_QuitarClave_HashDejaDeContenerla(hash_t* hash, char* clave);
//Comprueba el correcto funcionamiento del iterador del hash cuando el hash tiene elementos.
int ConHashCargado_Iterar_RecorreTodosLosElementos(hash_t* hash);

#endif /*__PRUEBAS_HASH_H*/

