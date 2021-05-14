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

void distanciaEntreEntregas(Map *Entregas_id){

    if(Entregas_id == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }

    int id1, id2;
    float distancia = 0; 

    printf("Ingrese id de entrega 1: ");
    scanf("%d", &id1);

    printf("Ingrese id de entrega 2: ");
    scanf("%d", &id2);

    while(id1 == id2){
        printf("Ingrese id distinto: ");
        scanf("%d", &id2);
    }

    Entrega *registro1 = (Entrega*) searchMap(Entregas_id, &id1);

    distancia = registro1->distancia[id2-1];

    printf("La distancia entre la entrega %d y %d es: %.2f\n\n", id1, id2, distancia);

}