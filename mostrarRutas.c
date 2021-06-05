#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct{
	int id;
	int x;
	int y;
	double *distancia;
}Entrega;

typedef struct{
    char nombre[100];
    int *idEntregas;
    double distanciaTotal;
    int x;
	int y;
}Ruta;

int ordenarRutas(const void *a, const void *b){
    //Funcion comparar para qsort//
    double *ptrA = (double *)a;
    double *ptrB = (double *)b;

    return *ptrA - *ptrB;
}

void mostrarRutas(Map *Rutas_nombre, int numeroEntregas, int numeroRutas){

    // Si no se ha creado al menos una ruta, se cierra la función. //
    if(numeroRutas == 0){
        printf(" --------------------------------------------------------------------------------------------------------\n");
        printf("| Cree al menos una ruta con la funcion \"Crear ruta\" (opcion 4) o \"Generar ruta aleatoria\" (opcion 5)    |\n");
        printf(" --------------------------------------------------------------------------------------------------------\n\n");
        return;
    }

    double *DistanciasTotalesRutas = NULL;
    int i, caracteres, espacios, caracteresCoordenadaX, caracteresCoordenadaY, k;
    char num[10];
    Ruta *aux = NULL;

    // Se dimensiona un arreglo para almacenar las distancias totales de cada una de las rutas. //
    DistanciasTotalesRutas = (double *) malloc(numeroRutas * sizeof(double));
    if(DistanciasTotalesRutas == NULL){
        printf("Error en la inicializacion...\n\n");
        exit (1);
    }

    // Se almacenan en un arreglo cada una de las distancias totales de las rutas. //
    i = 0;
    aux = (Ruta*) firstMap(Rutas_nombre);
    while(aux != NULL){
        DistanciasTotalesRutas[i] = aux->distanciaTotal;
        aux = (Ruta*) nextMap(Rutas_nombre);
        i++;
    }

    // Se ordena de la mejor a la peor (menor a mayor) //
    qsort( DistanciasTotalesRutas, numeroRutas, sizeof(double), ordenarRutas);

    //Se calcula la cantidad de caracteres tipo espacio que seran necesarios para impresión//
    if(numeroEntregas < 10){
        caracteres = (numeroEntregas*3 + 2);
    }else caracteres = (numeroEntregas-9)*4 + 29;
    
    printf(" ");
    for( k = 0; k < caracteres + 101; k++) printf("-");

    //Se imprime las rutas a continuación// 
    printf("\n| NOMBRE                         | RUTA");
    for(k = 0; k < caracteres + 34; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n ");
    
    for( k = 0; k < caracteres + 101; k++) printf("-");
    printf("\n");

    i = 0;
    aux = (Ruta*) firstMap(Rutas_nombre);
    while(i < numeroRutas){
        if(DistanciasTotalesRutas[i] == aux->distanciaTotal){
            printf("| %s", aux->nombre);
            espacios = 30 - strlen(aux->nombre);
            for(k = 0; k < espacios; k++) printf(" ");
            printf(" | ( %d , %d )->", aux->x, aux->y);

            for(k = 0; k < numeroEntregas; k++){
                printf("%d->", aux->idEntregas[k]);
            }

            printf("( %d , %d )", aux->x, aux->y);

            sprintf(num, "%d", aux->x);
            caracteresCoordenadaX = strlen(num);

            sprintf(num, "%d", aux->y);
            caracteresCoordenadaY = strlen(num);

            for(k = 0; k < 24 - 2*(caracteresCoordenadaX + caracteresCoordenadaY); k++) printf(" ");

            printf(" | %.4lf", aux->distanciaTotal);
            sprintf(num, "%.4lf", aux->distanciaTotal);
            espacios = 25 - strlen(num);
            for(k = 0; k < espacios; k++) printf(" ");
            printf(" |\n ");

            for( k = 0; k < caracteres + 101; k++) printf("-");
            printf("\n");
            i++;
        }
        aux = (Ruta*) nextMap(Rutas_nombre);
        if(aux == NULL) aux = (Ruta*) firstMap(Rutas_nombre);
    }

    free(DistanciasTotalesRutas);
    printf("\n\n");

    return;

}