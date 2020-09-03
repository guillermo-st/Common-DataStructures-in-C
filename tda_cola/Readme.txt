TDA_COLA:
En el presente archivo .zip se incluyen los archivos necesarios para la comcolación de un TDA(tipo de dato abstracto) representando una cola de elementos. La misma puede ser utilizada en cualquier programa escrito en C mediante la inclusión de "cola.h". Además se incluyen los archivo pruebas_cola.c y pruebas_cola.h para poder realizar pruebas sobre la cola, ya sean las predeterminadas o agregar nuevas. Un ejemplo de main() se encuentra en ejemplo_testeo_cola.c.

COMPILACIÓN:
Para la compilación de la cola junto a sus pruebas, se utiliza GCC: 
gcc *.c -o cola_vd
O bien con los siguientes flags para evitar comportamiento indeseado o errores de conversión:
gcc *.c -o cola_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

EJECUCIÓN:
Luego para su ejecución:
./cola_vd
O bien con valgrind para comprobar posibles pérdidas de memoria:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./cola_vd

AÑADIR PRUEBAS:
Para agregar tests adicionales, añadir las firmas de las mismas en pruebas_cola.h, y luego implementarlas en pruebas_cola.c, preferentemente siguiendo las siguientes indicaciones:
-Seguir la convención DADO_CUANDO_ENTONCES() para el nombrado de las pruebas.
-Utilizar interrupcion_prueba() para los casos en los cuales una prueba no se pudo concretar (usualmente por falta de memoria, al chequear el retorno de las funciones que afectan al heap). Esto no implica el mal funcionamiento del TDA sinó la inconclusión de la ejecución normal de la prueba.
-Utilizar verificar_test() para aquellas pruebas que comprueben enteros o caracteres, enviando el nombre de la prueba, el resultado esperado y el obtenido para mostrar por pantalla el resultado del testing.
Una vez agregadas las pruebas deseadas, pueden ser llamadas desde cualquier archivo .c que incluya pruebas_cola.h (siempre y cuando se tenga acceso a la libreria de la cola y a los archivos objeto/.c correspondientes). Se incluye el archivo ejemplo_testeo_cola.c para llamar a dichas pruebas.  

PRUEBAS PREDETERMINADAS:
Por defector se incluyen las siguientes pruebas, de las cuales se da una breve descripción:

- ConColaVacia_EncolarYDesencolar_CambiaCantidades();
	Corrobora el funcionamiento correcto de las primitivas cola_encolar(), cola_desencolar(), cola_cantidad(), cola_vacia() y cola_primero(),  en un caso estandar de encolar y desencolar elementos, sin probar posibles casos bordes. Para esto, la prueba se divide en 8 subetapas que verifican diferentes estados de las primitivas mencionadas.

- ConColaNull_IntentarEncolar_DevuelveError();
	Comprueba el correcto funcionamiento de la primitiva cola_encolar() en el caso de que la Cola sea NULL.	

- ConColaNull_IntentarDesencolar_DevuelveError();
	Comprueba el correcto funcionamiento de la primitiva cola_desencolar() en el caso de que la Cola sea NULL.	

- ConColaNull_PreguntarSiVacia_DevuelveError();
	Comprueba el correcto funcionamiento de la primitiva cola_vacia() en el caso de que la Cola sea NULL.

- ConColaNull_PrimerElemento_DevuelveNULL();
	Comprueba el correcto funcionamiento de la primitiva cola_primero() en el caso de que la Cola sea NULL.

- ConColaNULL_PreguntarCantidad_DevuelveCero();
	Comprueba el correcto funcionamiento de la primitiva cola_cantidad() en el caso de que la Cola sea NULL.

- ConColaVacia_IntentarDesencolar_DevuelveError();
	Comprueba el correcto funcionamiento de la primitiva cola_desencolar() en el caso de que la Cola esté vacía.

- ConColaVacia_PrimerElemento_DevuelveNULL();
	Comprueba el correcto funcionamiento de la primitiva cola_primero() en el caso de que la Cola esté vacía.
