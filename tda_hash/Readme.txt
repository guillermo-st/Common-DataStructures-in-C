TDA_HASH:
En el presente archivo .zip se incluyen los archivos necesarios para la compilación de un TDA(tipo de dato abstracto) representando un hash de elementos. El mismo puede ser utilizado en cualquier programa escrito en C mediante la inclusión de "hash.h". Además se incluyen los archivo pruebas_hash.c y pruebas_hash.h para poder realizar pruebas sobre el abrol , ya sean las predeterminadas o agregar nuevas. Un ejemplo de main() se encuentra en ejemplo_testeo_hash.c.

USO:
Para la utilización del hash, es necesario incluir la libreria hash.h y poseer hash.c o su respectivo archivo objeto. Una vez incluida la libreria es posible llamar a cualquiera de las primitivas descriptas en la misma.

COMPILACIÓN:
Para la compilación del tda junto a sus pruebas, se utiliza GCC: 
gcc *.c -o hash_vd
O bien con los siguientes flags para evitar comportamiento indeseado o errores de conversión:
gcc *.c -o hash_vd  -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

EJECUCIÓN:
Luego para su ejecución:
./hash_vd
O bien con valgrind para comprobar posibles pérdidas de memoria:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash_vd

PRUEBAS PREDETERMINADAS:
Por defecto se incluyen las siguientes pruebas:

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
