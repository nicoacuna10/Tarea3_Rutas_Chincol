#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct{
	int id;
	int x;
	int y;
	float *distancia;
}Entrega;

typedef struct{
    char nombre[100];
    int *idEntregas;
    float distanciaTotal;
    int x;
	int y;
}Ruta;

int ordenarRutas(const void *a, const void *b)
{
    float *ptrA = (float *)a;
    float *ptrB = (float *)b;

    return *ptrA - *ptrB;
}

void mostrarRutas(Map *Rutas_nombre, int numeroRutas){

    // Si no se ha creado al menos una ruta, se cierra la función. //
    if(numeroRutas == 0){
        printf("Cree al menos una ruta con la funcion \"Crear ruta\" (opcion 4) o \"Generar ruta aleatoria\" (opcion 5)\n");
        return;
    }

    float *DistanciasTotalesRutas = (float*)malloc(numeroRutas * sizeof(float));
    int i = 0, espacios, k;
    char num[10];

    // Se almacenan en un arreglo cada una de las distancias totales de las rutas. // 
    Ruta *aux = (Ruta*) firstMap(Rutas_nombre);
    while(aux != NULL){
        DistanciasTotalesRutas[i] = aux->distanciaTotal;
        aux = (Ruta*) nextMap(Rutas_nombre);
        i++;
    }

    // Se ordena de la mejor a la peor (menor a mayor) //
    qsort( DistanciasTotalesRutas, numeroRutas, sizeof(float), ordenarRutas);

    printf(" --------------------------------------------------\n");
    printf("| NOMBRE                         | DISTANCIA TOTAL |\n");
    printf(" --------------------------------------------------\n");

    i = 0;
    aux = (Ruta*) firstMap(Rutas_nombre);
    while(i < numeroRutas){
        if(DistanciasTotalesRutas[i] == aux->distanciaTotal){
            printf("| %s", aux->nombre);
            espacios = 30 - strlen(aux->nombre);
            for(k = 0; k < espacios; k++) printf(" ");

            printf(" | %.2f", aux->distanciaTotal);
            sprintf(num, "%f", aux->distanciaTotal);
            espacios = 19 - strlen(num);
            for(k = 0; k < espacios; k++) printf(" ");
            printf(" |\n --------------------------------------------------\n");
            i++;
        }
        aux = (Ruta*) nextMap(Rutas_nombre);
        if(aux == NULL) aux = (Ruta*) firstMap(Rutas_nombre);
    }

    free(DistanciasTotalesRutas);

    return;

}