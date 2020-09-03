CONTENIDO:
	En el presente archivo zip se hace la entrega de un tda_heap, el cuál también posee una primitiva heap_sort().


ESTRUCTURA DEL HEAP:	
	El heap es implementado en forma de un vector dinámico, dónde cada elemento ocupa una posicion. Además, el padre y los hijos del elemento en la posicion son:
		-Padre: (posicion - 1)/2
		-Hijo Izquierdo: (posicion * 2) + 1
		-Hijo Derecho: (posicion * 2) + 2
	Para cumplir con la representación en array de un heap. 


CRITERIOS TOMADOS:
	1.Pudiendo ser un heap minimal o maximal, se decidió hacer el heap maximal. 
	2.El heap parte con una capacidad inicial indicada por el usuario, y en caso de que se supere dicha capacidad, se redimensiona el array del heap según un
		coeficiente de redimensión (por defecto el doble).
	3.El heap recibe un comparador y un destructor para manipular cualquier tipo de dato, y no sólo enteros o caracteres. 
	4.Heapsort recibe un comparador (por razones obvias) y un destructor, pues lo que se termina guardando en el array son copias creadas en memoria dinámica 
		de los punteros, en lugar de los punteros originales (que pasan a ser destruidos).

COMPILACIÓN:
	Para la compilación del tda junto a sus pruebas, se utiliza GCC:
	gcc *.c -o heapexe
	O bien con los siguientes flags para evitar comportamiento indeseado o errores de conversión:
	gcc *.c -o heapexe  -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

EJECUCIÓN:
	Luego para su ejecución:
	./heapexe
	O bien con valgrind para comprobar posibles pérdidas de memoria:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./heapexe

PRIMITIVAS DEL HEAP:

	//devuelve un puntero a un heap creado, de la capacidad inicial provista y con el comparador y el destructor dado. En caso de error devuelve NULL.
	heap_t* heap_crear(size_t capacidad_inicial, heap_destructor_t destructor, heap_comparador_t comparador);
	
	//inserta un elemento en el heap, y reacomoda el heap correctamente para que se mantenga la condición de heap maximal.
	int heap_insertar(heap_t* heap, void* elemento);
	
	//elimina la raíz del heap, y reacomoda el heap correctamente para que se mantenga la condición de heap maximal.
	int heap_borrar_raiz(heap_t* heap);
	
	//devuelve un puntero a la raíz del heap, que por ser un heap maximal es a su vez el máximo.
	void* heap_raiz(heap_t* heap);
	
	//devuelve true si el heap no tiene elementos, de lo contrario devuelve false.
	bool heap_vacio(heap_t* heap);
	
	//ordena un array dado mediante el método heap_sort() con el comparador provisto. Los punteros originales son destruidos, y se crean copias de ellos
	//en memoria dinámica. Pasa a ser responsabilidad del usuario destruirlos.
	int heapsort(void** array, size_t tope, heap_destructor_t destructor, heap_comparador_t comparador);
	
	//itera internamente los elementos del heap, ejecutando la función con cada uno de ellos.
	void heap_con_cada_elemento(heap_t* heap, void (*funcion)(void*, void*), void* extra);
	
	//destruye el heap y a todos sus elementos mediante el destructor provisto en la creación.
	void heap_destruir(heap_t* heap);


