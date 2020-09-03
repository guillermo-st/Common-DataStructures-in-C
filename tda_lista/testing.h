#ifndef __TESTING_H__
#define __TESTING_H__


//recibiendo el nombre de una prueba, su resultado esperado y su resultado obtenido, muestra por stdout si la prueba fue exitosa.
void verificar_test(char* nombre_prueba, int resultado_esperado, int resultado_obtenido);

//muestra por pantalla que la prueba falló por falta de memoria, y que no se pudo concretar.
//Es decir, ocurre cuando no necesariamente hay errores en el TDA testeado, sinó que la prueba fue interrumpida.
void interrupcion_prueba(char* nombre_prueba);

#endif /*__TESTING_H__*/
