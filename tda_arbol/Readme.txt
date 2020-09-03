TDA_ARBOL:
En el presente archivo .zip se incluyen los archivos necesarios para la compilación de un TDA(tipo de dato abstracto) representando un arbol de elementos. El mismo puede ser utilizado en cualquier programa escrito en C mediante la inclusión de "arbol.h". Además se incluyen los archivo pruebas_arbol.c y pruebas_arbol.h para poder realizar pruebas sobre el abrol , ya sean las predeterminadas o agregar nuevas. Un ejemplo de main() se encuentra en ejemplo_testeo_arbol.c.

USO:
Para la utilización del arbol, es necesario incluir la libreria abb.h y poseer abb.c o su respectivo archivo objeto. Una vez incluida la libreria es posible llamar a cualquiera de las primitivas descriptas en la misma.

COMPILACIÓN:
Para la compilación de la lista junto a sus pruebas, se utiliza GCC: 
gcc *.c -o arbol_vd
O bien con los siguientes flags para evitar comportamiento indeseado o errores de conversión:
gcc *.c -o arbol_vd  -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

EJECUCIÓN:
Luego para su ejecución:
./arbol_vd
O bien con valgrind para comprobar posibles pérdidas de memoria:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./arbol_vd

PRUEBAS PREDETERMINADAS:
Por defecto se incluyen las siguientes pruebas:

	//Comprueba el correcto funcionamiento de la primitiva arbol_borrar() cuando el arbol está vacio
	int ConArbolVacio_IntentarBorrar_DevuelveERROR(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_raiz() cuando el arbol está vacio
	int ConArbolVacio_PreguntarRaiz_DevuelveNULL(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_vacio() cuando el arbol está vacio
	int ConArbolVacio_PreguntarSiVacio_DevuelveTrue(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_buscar() cuando el arbol está vacio
	int ConArbolVacio_IntentarBuscar_DevuelveNULL(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de las primitivas arbol_buscar y arbol_insertar cuando el arbol esta vacio. 
	int ConArbolVacio_InsertarYBuscarElementos_EncuentraTodos(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_borrar() cuando el arbol es null 
	int ConArbolNULL_IntentarBorrar_DevuelveERROR(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_vacio() cuando el arbol es null 
	int ConArbolNULL_PreguntarSiVacio_DevuelveTrue(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_raiz() cuando el arbol es null 
	int ConArbolNULL_PreguntarRaiz_DevuelveNULL(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_insertar() cuando el arbol es null 
	int ConArbolNULL_IntentarInsertar_DevuelveERROR(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_buscar() cuando el arbol es null 
	int ConArbolNULL_IntentarBuscar_DevuelveNULL(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de los iteradores internos cuando el arbol es null 
	int ConArbolNULL_IntentarUsarIteradorInternoConUnOrden_NoMuestraNadaPorPantalla(abb_t* arbol, int orden);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_vacio() cuando el arbol tiene elementos
	int ConArbolLleno_PreguntarSiVacio_DevuelveFalse(abb_t* arbol);
	
	//Comprueba el correcto funcionamiento de la primitiva arbol_raiz() cuando el arbol tiene elementos
	int ConArbolLleno_PreguntarPorRaiz_DevuelvePrimerElementoInsertado(abb_t* arbol, void* primer_elemento);

	//Comprueba el correcto funcionamiento del iterador interno cuando el arbol tiene elementos
	int ConArbolLleno_RecorrerEnUnOrdenConIteradorInterno_LosMuestraEnEseOrden(abb_t* arbol, int orden);
	
	//Comprueba el correcto funcionamiento de las funciones de recorrer cuando el arbol tiene elementos. 
	int ConArbolLleno_RecorrerEnCualquierOrden_DebeRecorrerTodosLosElementos(abb_t* arbol, int orden, int insertados);

**NOTA: Aquellas pruebas que solo muestren contenido por stdout, siempre resultarán exitosas, queda en el usuario verificar su correcto output.		
		
		
