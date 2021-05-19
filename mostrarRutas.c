#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "list.h"

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
}Ruta;

int ordenarRutas(const void *a, const void *b)
{
    float *ptrA = (float *)a;
    float *ptrB = (float *)b;

    return *ptrA - *ptrB;
}

void mostrarRutas(List *ListaDeRutasCreadas, int numeroRutas){

    // Si no se ha creado al menos una ruta, se cierra la función. //
    if(numeroRutas == 0){
        printf("Cree al menos una ruta con la función \"Crear ruta\" (opcion 4) o \"Generar ruta aleatoria\" (opcion 5)\n");
        return;
    }

    float *DistanciasTotalesRutas = (float*)malloc(numeroRutas * sizeof(float));
    int i = 0, espacios, k;
    char num[10];

    // Se almacenan en un arreglo cada una de las distancias totales de las rutas. // 
    Ruta *aux = first(ListaDeRutasCreadas);
    while(aux != NULL){
        DistanciasTotalesRutas[i] = aux->distanciaTotal;
        aux = next(ListaDeRutasCreadas);
        i++;
    }

    // Se ordena de la mejor a la peor (menor a mayor) //
    qsort( DistanciasTotalesRutas, numeroRutas, sizeof(float), ordenarRutas);

    printf(" --------------------------------------------------\n");
    printf("| NOMBRE                         | DISTANCIA TOTAL |\n");
    printf(" --------------------------------------------------\n");

    i = 0;
    aux = first(ListaDeRutasCreadas);
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
        aux = next(ListaDeRutasCreadas);
        if(aux == NULL) aux = first(ListaDeRutasCreadas);
    }

    free(DistanciasTotalesRutas);

    return;

}