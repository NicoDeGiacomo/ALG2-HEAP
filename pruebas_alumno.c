//Nombres: Nicolás De Giácomo - Gastón N. Ponce
//Padrones: 99702 - 99723
//DNIs: 39.490.629 - 40.393.064
#include <string.h>
#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int intcmp(const void *a, const void *b) {
	if(*(int*) a < *(int*) b)
		return -1;
	else if(*(int*) a > *(int*) b)
		return 1;
	return 0;
}

int pointcmp(const void *a, const void *b) {
	if(a < b)
		return -1;
	else if(a > b)
		return 1;
	return 0;
}

static void prueba_crear_heap_vacio() {
	printf("\n~~~ PRUEBAS HEAP VACIO ~~~\n");
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba crear heap vacio", (bool) heap);
    print_test("Prueba la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba ver MAX, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba desencolar, es NULL, no existe", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_insertar_arreglo_enteros()
{
	printf("\n~~~ PRUEBAS HEAP INSERTAR ARRAY DE ENTEROS ~~~\n");

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int* elementos[] = { &a, &b ,&c, &d};

    heap_t* heap = heap_crear_arr((void **) elementos, 4, intcmp);

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba insertar 4 valores", (bool) heap);
    print_test("Prueba la cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Prueba ver MAX es d", heap_ver_max(heap) == &d);
    print_test("Prueba desencolar, es d", heap_desencolar(heap) == &d);
    print_test("Prueba ver MAX es c", heap_ver_max(heap) == &c);
    print_test("Prueba la cantidad de elementos es 3", heap_cantidad(heap) == 3);

    heap_destruir(heap, NULL);
}

void prueba_heap_insertar_enteros(void) {
    printf("\n~~~ PRUEBAS HEAP INSERTAR ENTEROS ~~~\n");
    heap_t* heap = heap_crear(intcmp);

    int valor1 = 1, valor2 = 2, valor3 = 3;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba insertar valor1", heap_encolar(heap, &valor1));
    print_test("Prueba la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba ver MAX es valor1", heap_ver_max(heap) == &valor1);
    print_test("Prueba desencolar, es valor1", heap_desencolar(heap) == &valor1);
    print_test("Prueba la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el heap) */
    print_test("Prueba encolar valor2", heap_encolar(heap, &valor2));
    print_test("Prueba la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba ver MAX es valor2", heap_ver_max(heap) == &valor2);

    print_test("Prueba encolar valor3", heap_encolar(heap, &valor3));
    print_test("Prueba la cantidad de elementos es 1", heap_cantidad(heap) == 2);
    print_test("Prueba ver MAX es valor3", heap_ver_max(heap) == &valor3);

    heap_destruir(heap, NULL);
}

static void prueba_heap_desencolar()
{
	printf("\n~~~ PRUEBAS HEAP DESENCOLAR CADENAS ~~~\n");
    heap_t* heap = heap_crear(intcmp);

    int valor1 = 1;
    int valor2 = 2;
    int valor3 = 3;

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba heap insertar valor1", heap_encolar(heap, &valor1));
    print_test("Prueba heap insertar valor2", heap_encolar(heap, &valor3));
    print_test("Prueba heap insertar valor3", heap_encolar(heap, &valor2));

    /* Al borrar cada elemento comprueba que respeta la prioridad de MAX. */
    print_test("Prueba heap desencolar, es valor3", heap_desencolar(heap) == &valor3);
    print_test("Prueba heap esta vacio, es FALSE", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);

    print_test("Prueba heap desencolar, es valor2", heap_desencolar(heap) == &valor2);
    print_test("Prueba heap esta vacio, es FALSE", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);

    print_test("Prueba heap desencolar, es valor1", heap_desencolar(heap) == &valor1);
    print_test("Prueba heap esta vacio, es TRUE", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_valores_dinamicos()
{
	printf("\n~~~ PRUEBAS HEAP VALORES DINAMICOS ~~~\n");
    heap_t* heap = heap_crear(pointcmp);

    int *valor1 = malloc(sizeof(int));
    *valor1 = 1;
	
    print_test("Prueba heap insertar valor dinamico", heap_encolar(heap, valor1));
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 1);

    heap_destruir(heap, free);
	
	print_test("Prueba heap borrar con destructor", true);
}

static void prueba_heap_valor_null()
{
    heap_t* heap = heap_crear(intcmp);

    char *valor = NULL;

    print_test("Prueba heap insertar valor NULL", heap_encolar(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap desencolar, es valor NULL", heap_desencolar(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap desencolar vacio, es lo mismo que valor NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap la cantidad de elementos sigue siendo", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_volumen(size_t largo, bool debug)
{
    heap_t* heap = heap_crear(intcmp);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el heap */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        *valores[i] = i;
        ok = heap_encolar(heap, valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba heap almacenar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = !heap_esta_vacio(heap);
        if (!ok) break;
    }

    if (debug) print_test("Prueba heap esta vacio muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = largo; i > 0; i--) {
        void * a = heap_desencolar(heap);
        ok = ( a == valores[i-1]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba heap borrar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
		
	
    /* Destruye el heap y crea uno nuevo que sí libera */
    heap_destruir(heap, free);
    heap = heap_crear(intcmp);

    /* Inserta 'largo' parejas en el heap */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = heap_encolar(heap, valores[i]);
        if (!ok) break;
    }

    /* Destruye el heap - debería liberar los enteros */
    heap_destruir(heap, free);

}

void prueba_heap_sort(void){
    int* elementos0[] = {};
    heap_sort((void **) elementos0, 0, intcmp);
    print_test("Prueba heap sort 0 elementos", true);

    int a = 1;
    int* elementos[] = { &a};
    heap_sort((void **) elementos, 1, intcmp);
    print_test("Prueba heap sort 1 elemento", elementos[0] == &a);

    int b = 2;
    int c = 3;
    int d = 4;
    int* elementos2[] = { &a, &b ,&c, &d};
    heap_sort((void **) elementos2, 4, intcmp);
    print_test("Prueba heap sort 4 elementos", elementos2[0] == &a);
}

void pruebas_heap_alumno(){
    prueba_crear_heap_vacio();
    prueba_heap_insertar_enteros();
    prueba_heap_insertar_arreglo_enteros();
    prueba_heap_desencolar();
    prueba_heap_valores_dinamicos();
    prueba_heap_valor_null();
    prueba_heap_volumen(5000, true);
    prueba_heap_sort();
}
