#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*puntero doble solo necesito cuando tengo que modificar 
el inicio de mi lista, por ejemplo en la 
funcion BUSCAR no lo necesito*/
struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;//no se si va así
}typedef Nodo;

int contadorID = 1000;///////////////////// no se q onda esto
// Función para crear una tarea
struct Nodo* crearTarea(char *desc, int duracion) {
    struct Nodo *nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
    nuevo->T.TareaID = contadorID++;
    nuevo->T.Descripcion = strdup(desc);
    nuevo->T.Duracion = duracion;
    nuevo->Siguiente = NULL;
    return nuevo;
}

// Agrega una tarea al principio de la lista
void agregarTarea(struct Nodo **lista, struct Nodo *tarea) {
    tarea->Siguiente = *lista;
    *lista = tarea;
}

// Busca una tarea por ID y la mueve a la lista de realizadas
void marcarComoRealizada(struct Nodo **pendientes, struct Nodo **realizadas, int id) {
    struct Nodo *actual = *pendientes, *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id) {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual == NULL) {
        printf("Tarea no encontrada.\n");
        return;
    }

    if (anterior == NULL) {
        *pendientes = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }

    actual->Siguiente = NULL;
    agregarTarea(realizadas, actual);
    printf("Tarea %d marcada como realizada.\n", id);
}

// Muestra todas las tareas de una lista
void mostrarLista(struct Nodo *lista, char *titulo) {
    printf("== %s ==\n", titulo);
    while (lista != NULL) {
        printf("ID: %d, Desc: %s, Duración: %d\n", lista->T.TareaID, lista->T.Descripcion, lista->T.Duracion);
        lista = lista->Siguiente;
    }
}

int main() {
    struct Nodo *pendientes = NULL;
    struct Nodo *realizadas = NULL;

    agregarTarea(&pendientes, crearTarea("Armar pedido", 30));
    agregarTarea(&pendientes, crearTarea("Enviar factura", 45));
    mostrarLista(pendientes, "Tareas Pendientes");

    marcarComoRealizada(&pendientes, &realizadas, 1000);
    mostrarLista(pendientes, "Tareas Pendientes");
    mostrarLista(realizadas, "Tareas Realizadas");

    return 0;
}