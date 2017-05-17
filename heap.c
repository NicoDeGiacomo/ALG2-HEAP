#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */
#include <stdlib.h>
#include "heap.h"

#define TAMANIO_INICIAL 500
#define PADRE(i) (i-1)/2
#define HIJO_IZQ(i) (2*i)+1
#define HIJO_DER(i) (2*i)+2


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
void up_heap(heap_t* heap);
void down_heap(heap_t* heap);
void swap(heap_t* heap, size_t indice1, size_t indice2);

//TODO: Implement me!
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	
}

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo) {
    void** tabla = realloc(heap->tabla, tam_nuevo * sizeof(void*));
    if (!tabla)
        return false;

    heap->tabla = tabla;
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
	heap_t* heap = heap_crear(cmp);

	for(int i = 0; i < n; i++) {
		heap_encolar(heap, arreglo[i]);
	}

	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {

	while(!heap_esta_vacio(heap)) {
        void* buffer = heap_desencolar(heap);
		if(destruir_elemento)
			destruir_elemento(buffer);
	}

	free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
	return !heap_cantidad(heap);
}

bool heap_encolar(heap_t *heap, void *elem) {
    //TODO: Controlar la redimension
    heap->tabla[heap->cantidad] = elem;
    heap->cantidad++;
    up_heap(heap);
	return true;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap))
        return NULL;

	return heap->tabla[0];
}

void *heap_desencolar(heap_t *heap) {
    if(heap_esta_vacio(heap))
        return NULL;

    //TODO: Controlar la redimension
    void* buffer = heap->tabla[0];
    heap->tabla[0] = heap->tabla[heap->cantidad-1];
    heap->tabla[heap->cantidad-1] = NULL;
    heap->cantidad--;
    down_heap(heap);

    return buffer;
}

void up_heap(heap_t* heap){
    size_t actual = heap->cantidad-1;
    size_t padre = PADRE(actual);
    while(heap->comparador(heap->tabla[actual], heap->tabla[padre]) < 0){
        swap(heap, actual, padre);
        actual = padre;
        padre = PADRE(actual);
    }
}

void down_heap(heap_t* heap){
    size_t actual = 0;
    size_t hijo_izq = HIJO_IZQ(actual);
    size_t hijo_der = HIJO_DER(actual);
    while(true){
        if ( hijo_izq < heap->cantidad &&heap->comparador(heap->tabla[actual], heap->tabla[hijo_izq]) > 0){
            swap(heap, actual, hijo_izq);
            actual = hijo_izq;
            hijo_izq = HIJO_IZQ(actual);
            hijo_der = HIJO_DER(actual);
        }
        else if( hijo_der < heap->cantidad && heap->comparador(heap->tabla[actual], heap->tabla[hijo_der]) > 0){
            swap(heap, actual, hijo_der);
            actual = hijo_der;
            hijo_izq = HIJO_IZQ(actual);
            hijo_der = HIJO_DER(actual);
        }
        else
            break;
    }
}

void swap(heap_t* heap, size_t indice1, size_t indice2){
    void* buffer = heap->tabla[indice1];
    heap->tabla[indice1] = heap->tabla[indice2];
    heap->tabla[indice2] = buffer;
    return;
}