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

void mostrarRutas(Map *Rutas_nombre, int numeroEntregas, int numeroRutas){

    // Si no se ha creado al menos una ruta, se cierra la función. //
    if(numeroRutas == 0){
        printf(" --------------------------------------------------------------------------------------------------------\n");
        printf("| Cree al menos una ruta con la funcion \"Crear ruta\" (opcion 4) o \"Generar ruta aleatoria\" (opcion 5)    |\n");
        printf(" --------------------------------------------------------------------------------------------------------\n\n");
        return;
    }

    float *DistanciasTotalesRutas = NULL;
    int i, caracteres, espacios, k;
    char num[10];
    Ruta *aux = NULL;

    // Se dimensiona un arreglo para almacenar las distancias totales de cada una de las rutas. //
    DistanciasTotalesRutas = (float*) malloc(numeroRutas * sizeof(float));
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
    qsort( DistanciasTotalesRutas, numeroRutas, sizeof(float), ordenarRutas);

    if(numeroEntregas == 1 || numeroEntregas == 2){
        caracteres = 4;
    }else if(numeroEntregas > 2 && numeroEntregas < 10){
        caracteres = (numeroEntregas*2 - 1);
    }else caracteres = (numeroEntregas-9)*3 + 17;
    
    printf(" ");
    for( k = 0; k < caracteres + 62; k++) printf("-");

    
    printf("\n| NOMBRE                        | RUTA");
    for(k = 0; k < caracteres - 4; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n ");
    
    for( k = 0; k < caracteres + 62; k++) printf("-");
    printf("\n");

    i = 0;
    aux = (Ruta*) firstMap(Rutas_nombre);
    while(i < numeroRutas){
        if(DistanciasTotalesRutas[i] == aux->distanciaTotal){
            printf("| %s", aux->nombre);
            espacios = 30 - strlen(aux->nombre);
            for(k = 0; k < espacios; k++) printf(" ");
            printf("| ");

            for(k = 0; k < numeroEntregas; k++){
                printf("%d", aux->idEntregas[k]);
                if(k < numeroEntregas - 1) printf("-");
            }

            printf(" | %.4f", aux->distanciaTotal);
            sprintf(num, "%f", aux->distanciaTotal);
            espacios = 27 - strlen(num);
            for(k = 0; k < espacios; k++) printf(" ");
            printf(" |\n ");

            for( k = 0; k < caracteres + 62; k++) printf("-");
            printf("\n");
            i++;
        }
        aux = (Ruta*) nextMap(Rutas_nombre);
        if(aux == NULL) aux = (Ruta*) firstMap(Rutas_nombre);
    }

    free(DistanciasTotalesRutas);

    return;

}