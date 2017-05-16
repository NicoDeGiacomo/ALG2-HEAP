#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */

#define TAMANIO_INICIAL 8

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

 struct heap{
    void** tabla;
    size_t cantidad;
    cmp_func_t comparador;
};

/* ******************************************************************
 *                			FUNCIONES APARTE
 * *****************************************************************/

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	
}

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo) {
    void** tablaBuffer = realloc(heap->tabla, tam_nuevo * sizeof(void*));

    if (tam_nuevo && !datos_nuevo) {
        return false;
    }
	
    heap->tabla = tablaBuffer;
    heap->cantidad = tam_nuevo;
    return true;
}

/* ******************************************************************
 *                    	PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    heap->comparador = cmp;
    heap->tabla = malloc(sizeof(void*) * TAMANIO_INICIAL);
    heap->cantidad = 0;
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	heap_t* heap = heap_crear();
	
	for(int i = 0; i < n, i++) {
		heap_encolar(heap, arreglo[i]);
	}
	
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	void* buffer;
	
	while(heap->tabla[0]) {
		buffer = heap_desencolar(heap);
		if(destruir_elemento)
			destruir_elemento(buffer);
	}
}


size_t heap_cantidad(const heap_t *heap) {
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
	return (bool) heap->tabla[0];
}

//TODO: Implement me!
bool heap_encolar(heap_t *heap, void *elem) {
	return true;
}

void *heap_ver_max(const heap_t *heap) {
	return heap->tabla[0];
}

//TODO: Implement me!
void *heap_desencolar(heap_t *heap) {
	return NULL;
}