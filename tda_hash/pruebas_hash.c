#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testing.h"
#include "hash.h"
#include "hash_iterador.h"
#include "pruebas_hash.h"

#include "time.h"

#define NUMINSERTAR 7
#define ERROR -1
#define EXITO 0
#define MAXRAND  101
#define LEN_CLAVE_ALEATORIA  5

const char* CHARS_SET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        

//genera un entero aleatorio para insertar entre 0 y MAXRAND.
int entero_aleatorio(){
	return (rand() % MAXRAND); 
}

char* clave_aleatoria() {
	char* clave = malloc(sizeof(char) * (LEN_CLAVE_ALEATORIA + 1));
	for(int i=0; i< LEN_CLAVE_ALEATORIA; i++){
		clave[i] = CHARS_SET[(size_t)rand() % strlen(CHARS_SET)];
		clave[LEN_CLAVE_ALEATORIA] = '\0';
	}
	return clave;
}

int comparador_booleanos(void* elemento1, void* elemento2){
	if(*(bool*)elemento1 == *(bool*)elemento2)
		return 0;
	else return 1;
}

int comparador_enteros(void* elemento1, void* elemento2){
	if(*(size_t*)elemento1 == *(size_t*)elemento2)
		return 0;
	else if(*(int*)elemento1 < *(int*) elemento2)
		return -1;
	else return 1;
}

int ConHashVacio_IntentarQuitar_DevuelveERROR(hash_t* hash){
	char* nombre_prueba = "Intentar quitar una clave de un hash vacío debe devolver error.";
	if(!hash)
		return interrupcion_prueba(nombre_prueba);
	bool esperado = false;
	char* clave_aux = ":^)";
	bool obtenido = (hash_quitar(hash, clave_aux ) == EXITO);
	return verificar_test(nombre_prueba, &esperado, &obtenido, &comparador_booleanos);
}

int ConHashVacio_ObtenerUnElemento_DevuelveNULL(hash_t* hash){
	char* nombre_prueba = "Intentar obtener elementos de un hash vacío devuelve NULL";
	if(!hash)
		return interrupcion_prueba(nombre_prueba);
	char* clave_aux = ":^)";
	return verificar_test(nombre_prueba, NULL, hash_obtener(hash, clave_aux), NULL); 
}

int ConHashVacio_PreguntarCantidadDeElementos_DevuelveCero(hash_t* hash){
	char* nombre_prueba = "Preguntar la cantidad de elementos en un hash vacío devuelve 0";
	if(!hash)
		return interrupcion_prueba(nombre_prueba);
	size_t esperado = 0;
	size_t obtenido = hash_cantidad(hash);
	return verificar_test(nombre_prueba, &esperado, &obtenido, &comparador_enteros); 
}

int ConHashVacio_PreguntarSiContieneClave_DevuelveFalso(hash_t* hash){
	char* nombre_prueba = "Preguntar si un hash vacío contiene una clave devuelve falso";
	if(!hash)
		return interrupcion_prueba(nombre_prueba);
	char* clave_aux = ":^)";
	bool esperado = false;
	bool obtenido = hash_contiene(hash, clave_aux);
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_booleanos);
}

int ConHashVacio_InsertarYVerificarElementos_EncuentraTodos(hash_t* hash){
	char* nombre_prueba = "Al verificar todos los elementos insertados en un hash previamente vacío, deben encontrarse todos";
	int v_elementos[NUMINSERTAR];
	char* claves[NUMINSERTAR];
	bool esperado = true;
	bool todos_encontrados = true;
	int flag_insertar = EXITO;	
	int j = 0;

	while(j<NUMINSERTAR && flag_insertar != ERROR){
		v_elementos[j] = entero_aleatorio();
		claves[j] = clave_aleatoria();
		flag_insertar = hash_insertar(hash, claves[j], &v_elementos[j]);
		j++;
	}
	if(flag_insertar == ERROR){
		for(int i = 0; i<hash_cantidad(hash); i++){		
			hash_quitar(hash, claves[i]);
			free(claves[i]);	
		}
		return interrupcion_prueba(nombre_prueba);
	}

	for(int k = 0; k<NUMINSERTAR; k++){
		if (hash_contiene(hash, claves[k]) == false){
			todos_encontrados = false;
		}
	}

	for(int i = 0; i<NUMINSERTAR; i++){		
		hash_quitar(hash, claves[i]);
		free(claves[i]);	
	}

	return verificar_test(nombre_prueba, &esperado , &todos_encontrados, comparador_booleanos);
}

int ConHashVacio_Iterar_NoRecorreElementos(hash_t* hash){
	char* nombre_prueba = "Intentar usar el iterador externo de un hash vacio, resulta en no recorrer nada";
	hash_iterador_t* it = hash_iterador_crear(hash);	
	size_t iterados = 0;
	size_t iteraciones_esperadas = 0; 
	while(hash_iterador_tiene_siguiente(it)){
		iterados ++;
		hash_iterador_siguiente(it);
	}
	hash_iterador_destruir(it);
	return verificar_test(nombre_prueba, &iteraciones_esperadas, &iterados, comparador_enteros);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ConHashNULL_IntentarQuitar_DevuelveERROR(hash_t* hash){
	char* nombre_prueba = "Intentar quitar una clave de un hash NULL debe devolver ERROR";
	char* clave = ":^)";	
	bool esperado = false;
	bool obtenido = (hash_quitar(hash, clave) == EXITO);
	return verificar_test(nombre_prueba, &esperado, &obtenido, &comparador_booleanos);
}

int ConHashNULL_IntentarInsertar_DevuelveERROR(hash_t* hash){
	char* nombre_prueba = "Intentar Insertar en un hash NULL devuelve ERROR";
	int aux = entero_aleatorio();
	char* clave = ":^)";	
	bool esperado = false;
	bool obtenido = (hash_insertar(hash,clave,&aux) == EXITO);
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_booleanos);
}

int ConHashNULL_PreguntarCantidad_DevuelveCero(hash_t* hash){
	char* nombre_prueba = "Preguntar la cantidad de un hash NULL devuelve cero";
	size_t esperado = 0;
	size_t obtenido = hash_cantidad(hash);
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_enteros);
}

int ConHashNULL_PreguntarSiContieneClave_DevuelveFalso(hash_t* hash){
	char* nombre_prueba = "Preguntar si un hash NULL contiene una clave devuelve falso";
	bool esperado = false;
	bool obtenido = hash_contiene(hash, ":^)");	
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_booleanos); 
}

int ConHashNULL_IntentarObtenerElemento_DevuelveNULL(hash_t* hash){
	char* nombre_prueba = "Intentar obtener un elemento en un hash NULL devuelve NULL";
	char* clave = ":^)";	
	return verificar_test(nombre_prueba, NULL, hash_obtener(hash, clave), NULL);
}

int ConHashNULL_Iterar_NoRecorreElementos(hash_t* hash){
	char* nombre_prueba = "Intentar usar el iterador externo de un hash NULL, resulta en no recorrer nada";
	hash_iterador_t* it = hash_iterador_crear(hash);	
	size_t iterados = 0;
	size_t iteraciones_esperadas = 0; 
	while(hash_iterador_tiene_siguiente(it)){
		iterados ++;
		hash_iterador_siguiente(it);
	}
	hash_iterador_destruir(it);
	return verificar_test(nombre_prueba, &iteraciones_esperadas, &iterados, comparador_enteros);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ConHashCargado_PreguntarCantidad_DevuelveLaCantidadEsperada(hash_t* hash, size_t cantidad_esperada){
	char* nombre_prueba = "Preguntar la cantidad de elementos en un hash previamente cargado, devuelve la cantidad correcta de elementos.";
	size_t cantidad_hash = hash_cantidad(hash);
	return verificar_test(nombre_prueba, &cantidad_esperada, &cantidad_hash, comparador_enteros);
}
	
int ConHashCargado_PreguntarSiContieneClavesCargadas_DevuelveVerdaderoParaTodas(hash_t* hash, size_t cantidad_cargados, char** claves){
	char* nombre_prueba = "Verificar si un hash previamente cargado con elementos los contiene a todos, devuelve true para todos ellos.";
	bool todos_encontrados = true;
	bool esperado = true;

	for(int i = 0; i<cantidad_cargados; i++){
		if(!hash_contiene(hash, claves[i]))
			todos_encontrados = false;
	}	
	return verificar_test(nombre_prueba, &esperado, &todos_encontrados, comparador_booleanos);
}

int ConHashCargado_ObtenerElElementoDeUnaClave_DevuelveElElementoCorrecto(hash_t* hash, char* clave, void* elemento_esperado){
	char* nombre_prueba = "Obtener el elemento de una clave cargada, debe devolver el elemento correcto";
	void* elemento_obtenido = hash_obtener(hash, clave);
	return verificar_test(nombre_prueba, elemento_esperado, elemento_obtenido, NULL);	
}

int ConHashCargado_QuitarClave_ReduceCantidad(hash_t* hash, char* clave){
	char* nombre_prueba = "Quitar una clave de un hash reduce la cantidad";
	size_t cantidad_esperada = hash_cantidad(hash) -1;

	int flag = hash_quitar(hash, clave);
	if(flag == ERROR)
		return interrupcion_prueba(nombre_prueba);
	
	size_t cantidad_final = hash_cantidad(hash);
	
	return verificar_test(nombre_prueba, &cantidad_esperada, &cantidad_final, comparador_enteros);
}

int ConHashCargado_QuitarClave_HashDejaDeContenerla(hash_t* hash, char* clave){
	char* nombre_prueba = "Quitar una clave de un hash hace que la deje de contener";
	
	int flag = hash_quitar(hash, clave);
	if(flag == ERROR)
		return interrupcion_prueba(nombre_prueba);
	
	bool esperado = false;
	bool obtenido = hash_contiene(hash,clave);
	return verificar_test(nombre_prueba, &esperado, &obtenido, comparador_booleanos);
}

int ConHashCargado_Iterar_RecorreTodosLosElementos(hash_t* hash){
	char* nombre_prueba = "Iterar sobre un Hash que tiene elementos debe recorrer todos.";
	size_t iterados = 0;
	size_t iteraciones_esperadas = hash_cantidad(hash); 
	
	hash_iterador_t* it = hash_iterador_crear(hash);
	if(!it)
		return interrupcion_prueba(nombre_prueba);

	while(hash_iterador_tiene_siguiente(it)){
		iterados ++;
		hash_iterador_siguiente(it);
	}
	hash_iterador_destruir(it);
	return verificar_test(nombre_prueba, &iteraciones_esperadas, &iterados, comparador_enteros);
}

