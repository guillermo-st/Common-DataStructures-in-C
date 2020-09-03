#include "cola.h"
#include <stdio.h>

int main(){
  cola_t* cola = cola_crear();

  int a=1, b=2, c=3, d=4;

  printf("Encolo el elemento %i\n", a);
  cola_encolar(cola, (void*)&a);

  printf("Encolo el elemento %i\n", b);
  cola_encolar(cola, (void*)&b);

  printf("Encolo el elemento %i\n", c);
  cola_encolar(cola, (void*)&c);

  printf("Encolo el elemento %i\n", d);
  cola_encolar(cola, (void*)&d);
  printf("La cola tiene %i elementos\n", cola_cantidad(cola));
    
  printf("Desencolo un elemento\n");
  cola_desencolar(cola);
  printf("La cola tiene %i elementos\n", cola_cantidad(cola));
  printf("El primer elemento de la cola es: %i\n", *(int*)cola_primero(cola));
  

  printf("¿La cola está vacía?: %s\n", cola_vacia(cola)?"SI":"NO");
  printf("Desencolo un elemento\n");
  cola_desencolar(cola);
  printf("El primer elemento de la cola es: %i\n", *(int*)cola_primero(cola));

  cola_destruir(cola);

  return 0;
}
