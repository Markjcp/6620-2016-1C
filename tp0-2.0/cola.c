#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"

/*******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 ******************************************************************/
 typedef struct nodo_cola{
    void *dato;
    struct nodo_cola *siguiente;
 }nodo_cola_t;

 struct cola{
    nodo_cola_t *primero;
    nodo_cola_t *ultimo;
 };

 /*******************************************************************
 *                      FUNCIONES AUXILIARES
 ******************************************************************/

 nodo_cola_t *nodo_cola_crear(void *valor)
 {
    nodo_cola_t *creado = malloc(sizeof(nodo_cola_t));
    if (!creado) return false;
    (creado -> dato) = valor;
    (creado -> siguiente) = NULL;
    return creado;  
 }

/*******************************************************************
 *                        IMPLEMENTACION
 ******************************************************************/
// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t* cola_crear()
{
    cola_t *cola = malloc(sizeof(cola_t));
    if (cola == NULL) return NULL;
    (cola -> primero) = NULL;
    (cola -> ultimo) = NULL;
    return cola;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void destruir_dato(void* dato))
{
    while (!cola_esta_vacia(cola))
    {
        void *desencolado = cola_desencolar(cola);
        if (destruir_dato)
            destruir_dato(desencolado);
    }
    free(cola);
}

// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola)
{
    return ((cola -> primero) == NULL);
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void* valor)
{
    nodo_cola_t *encolado = nodo_cola_crear(valor);
    if (!encolado) return false;
    if (cola_esta_vacia(cola))
        (cola -> primero) = encolado;
    else
        ((cola -> ultimo) -> siguiente) = encolado;
    (cola -> ultimo) = encolado;
    return true;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(const cola_t *cola)
{
    if (cola_esta_vacia(cola))
        return NULL;
    return (cola -> primero) -> dato;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_t *cola)
{
    if (cola_esta_vacia(cola))
        return NULL;
    nodo_cola_t *desencolado = (cola -> primero);
    void *desencolado_dato = ((cola -> primero) -> dato);
    (cola -> primero) = (desencolado -> siguiente);
    if (!cola -> primero)
        cola -> ultimo = NULL;
    free(desencolado);
    return desencolado_dato;
}

size_t cola_tamanio(cola_t *cola)
{
    size_t tam = 0;
    void *desencolado;
    cola_t *cola_aux = cola_crear();
    while (!cola_esta_vacia(cola))
    {
        desencolado = cola_desencolar(cola);
        cola_encolar(cola_aux, desencolado);
        tam ++;
    }
    while (!cola_esta_vacia(cola_aux))
    {
        desencolado = cola_desencolar(cola_aux);
        cola_encolar(cola, desencolado);
    }
    cola_destruir(cola_aux,NULL);
    return tam;
}
