TDA_LISTA:
En el presente archivo .zip se incluyen los archivos necesarios para la compilación de un TDA(tipo de dato abstracto) representando una lista de elementos. La misma puede ser utilizada en cualquier programa escrito en C mediante la inclusión de "lista.h". Además se incluyen los archivo pruebas_lista.c y pruebas_lista.h para poder realizar pruebas sobre la lista, ya sean las predeterminadas o agregar nuevas. Un ejemplo de main() se encuentra en ejemplo_testeo_lista.c.

USO:
Para la utilización de la lista, es necesario incluir la libreria lista.h y poseer lista.c o su respectivo archivo objeto. Una vez incluida la libreria es posible llamar a cualquiera de las primitivas descriptas en la libreria.

COMPILACIÓN:
Para la compilación de la lista junto a sus pruebas, se utiliza GCC: 
gcc *.c -o lista_vd
O bien con los siguientes flags para evitar comportamiento indeseado o errores de conversión:
gcc *.c -o lista_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

EJECUCIÓN:
Luego para su ejecución:
./lista_vd
O bien con valgrind para comprobar posibles pérdidas de memoria:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_vd

PRUEBAS PREDETERMINADAS:
Por defecto se incluyen las siguientes pruebas, de las cuales se da una breve descripción:

	- ConListaVacia_PreguntarCantidad_DevuelveCero();
		Verifica el correcto funcionamiento de la primitiva lista_elementos() cuando la lista está vacía.

	- ConListaVacia_PreguntarSiVacia_DevuelveTrue();
		Verifica el correcto funcionamiento de la primitiva lista_vacia() cuando la lista está vacía.

	- ConListaVacia_InsertarYBorrarNUMINSERTARelementos_ResultaEnCantidadNUMINSERTARYCantidadCero();
		Verifica que después de insertar elementos al final de la lista la cantidad de veces que indica la constante, la cantidad de la lista sea la correcta.
		Luego Borra todos los elementos y comprueba que la cantidad de elementos en la lista sea efectivamente cero. 
	
	- ConListaVacia_InsertarUnElementoYBorrarlo_AumentaLaCantidadEnUnoSeVuelveElUltimoElementoYAlBorrarseLaListaQuedaVacia();
		Verifica que al insertar un elemento con la lista vacía, este se vuelva correctamente el último elemento, y que al borrarlo la lista este vacia denuevo.
	
	- ConListaOcupada_InsertarElementoEnPosicionYpreguntarElementoEnPosicion_DevuelveEseElemento();
		Verifica que al insertar un elemento en una posicion determinada, preguntar por el elemento en dicha posicion devuelva el elemento correcto.
	
	- ConListaOcupada_IteradorInternoYExterno_MuestranLoMismo();
		Imprime los contenidos de la lista por stdout. Esta prueba siempre se muestra como exitosa porque la implementación no lee qué se imprimió.
	
	- ConListaNull_IntentarInsertar_DevuelveError();
		Comprueba el correcto funcionamiento de la primitiva lista_insertar() cuando la lista es NULL.
	
	- ConListaNull_IntentarBorrar_DevuelveError();
		Comprueba el correcto funcionamiento de la primitiva lista_borrar() cuando la lista es NULL.
	
	- ConListaNull_IntentarInsertarEnPosicion_DevuelveError();
		Comprueba el correcto funcionamiento de la primitiva lista_insertar_en_posicion() cuando la lista es NULL.
	
	- ConListaNull_IntentarBorrarDePosicion_DevuelveError();
		Comprueba el correcto funcionamiento de la primitiva lista_borrar_de_posicion() cuando la lista es NULL.
	
	- ConListaNull_PreguntarSiVacia_DevuelveTrue();
		Comprueba el correcto funcionamiento de la primitiva lista_vacia() cuando la lista es NULL.
	
	- ConListaNULL_UltimoElemento_DevuelveNULL();
		Comprueba el correcto funcionamiento de la primitiva lista_ultimo() cuando la lista es NULL.
	
	- ConListaNULL_PreguntarCantidad_DevuelveCero();
		Comprueba el correcto funcionamiento de la primitiva lista_elementos() cuando la lista es NULL.
	
	- ConListaVacia_IntentarBorrar_DevuelveError();
		Comprueba el correcto funcionamiento de la primitiva lista_borrar() cuando la lista es vacia.
	
	- ConListaVacia_IntentarBorrarDePosicion_DevuelveError();
		Comprueba el correcto funcionamiento de la primitiva lista_borrar_de_posicion() cuando la lista es vacia.
	
	- ConListaVacia_UltimoElemento_DevuelveNULL();
		Comprueba el correcto funcionamiento de la primitiva lista_ultimo() cuando la lista es vacia.
