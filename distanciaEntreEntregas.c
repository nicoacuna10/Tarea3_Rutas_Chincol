#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int x;
	int y;
    float *distancia;
}Entrega;

void distanciaEntreEntregas(Entrega *E){

    if(E == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }

    int id1, id2;
    float distancia; 

    printf("Ingrese id de entrega 1: ");
    scanf("%d", &id1);

    printf("Ingrese id de entrega 2: ");
    scanf("%d", &id2);

    while(id1 == id2){
        printf("Ingrese id distinto: ");
        scanf("%d", &id2);
    }

    printf("La distancia entre la entrega %d y %d es: %.2f\n\n", id1, id2, E[id1-1].distancia[id2-1]);

}