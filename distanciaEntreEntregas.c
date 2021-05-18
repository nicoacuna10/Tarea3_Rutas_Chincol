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

void distanciaEntreEntregas(Map *Entregas_id, int numeroEntregas){
	
    // Si no se encuentra inicializado el mapa, se cierra la función. // 
    if(Entregas_id == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }
    
    // Declaración de variables //
    int id1, id2;
    float distancia = 0; 

    // Se pide al usuario que ingrese id's de dos entregas. //
    printf("Ingrese id de entrega 1: ");
    scanf("%d", &id1);

    while(id1 < 1 || id1 > numeroEntregas){
        printf("\nIngrese id valido: ");
        scanf("%d", &id1);
    }

    printf("\nIngrese id de entrega 2: ");
    scanf("%d", &id2);

    while( id1 == id2 || id2 < 1 || id2 > numeroEntregas ){
        printf("\nIngrese id valido: ");
        scanf("%d", &id2);
    }

    /* Se busca en el mapa la información de la entrega del primer id ingresado.
       Se guarda en la variable distancia la distancia entre la entrega del primer
       id y la entrega del segundo id. Finalmente se imprime por pantalla los numeros
       de id's y la distancia entre ellos.*/
    Entrega *registro1 = (Entrega*) searchMap(Entregas_id, &id1);

    distancia = registro1->distancia[id2-1];

    printf("La distancia entre la entrega %d y %d es: %.2f\n\n", id1, id2, distancia);

}
