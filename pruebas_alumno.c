#include <string.h>
#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>

int intcmp(const void *a, const void *b) {
	if(*(int*) a < *(int*) b)
		return -1;
	else if(*(int*) a > *(int*) b)
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

static void prueba_heap_insertar_enteros()
{
	printf("\n~~~ PRUEBAS HEAP INSERTAR ENTEROS ~~~\n");
    heap_t* heap = heap_crear(intcmp);

    int valor1 = 3, valor2 = 2;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba insertar valor1", heap_encolar(heap, &valor1));
    print_test("Prueba la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba ver MAX es valor1", heap_ver_max(heap) == &valor1);
    print_test("Prueba desencolar, es valor1", heap_desencolar(heap) == &valor1);
    print_test("Prueba la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Inserta otros 2res y no los borra (se destruyen con el heap) */
    print_test("Prueba encolar valor2", heap_encolar(heap, &valor2));
    print_test("Prueba la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba ver MAX es valor2", heap_ver_max(heap) == &valor2);

    heap_destruir(heap, NULL);
}

void pruebas_heap_alumno(){
    prueba_crear_heap_vacio();
    prueba_heap_insertar_enteros();
    //TODO: seguir implementando sets
    /*prueba_heap_reemplazar();
    prueba_heap_reemplazar_con_destruir();
    prueba_heap_desencolar();
    prueba_heap_clave_vacia();
    prueba_heap_valor_null();
    prueba_heap_volumen(5000, true);
    prueba_heap_iterar();
    prueba_heap_iterar_volumen(5000);*/
}
