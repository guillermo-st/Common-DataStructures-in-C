TDA_PILA:
En el presente archivo .zip se incluyen los archivos necesarios para la compilación de un TDA(tipo de dato abstracto) representando una pila de elementos. La misma puede ser utilizada en cualquier programa escrito en C mediante la inclusión de "pila.h". Además se incluye el archivo pruebas.c para el testeo de sus funcionalidades.

COMPILACIÓN:
Para la compilación de la pila junto a sus pruebas, se utiliza CC o GCC: 
gcc *.c -o pila_vd
O bien con los siguientes flags para evitar comportamiento indeseado o errores de conversión:
gcc *.c -o pila_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

EJECUCIÓN:
Luego para su ejecución:
./pila_vd
O bien con valgrind para comprobar posibles pérdidas de memoria:
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pila_vd

AÑADIR PRUEBAS:
Para agregar tests adicionales, escribirlas en el archivo .c, preferentemente siguiendo las siguientes indicaciones:
-Seguir la convención DADO_CUANDO_ENTONCES() para el nombrado de las pruebas
-Utilizar interrupcion_prueba() para los casos en los cuales una prueba no se pudo concretar (usualmente por falta de memoria, al chequear el retorno de las funciones que afectan al heap). Esto no implica el mal funcionamiento del TDA sinó que evitó la ejecución normal de la prueba.
-Utilizar verificar_test para aquellas pruebas que comprueben enteros o caracteres, enviando el nombre de la prueba, el resultado esperado y el obtenido para mostrar por pantalla el resultado del testing.

