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

void distanciaEntreEntregas(Map *Entregas_id, int numeroEntregas){
	
    // Si no se encuentra inicializado el mapa, se cierra la función. // 
    if(Entregas_id == NULL){
        printf("\n");
        printf(" ------------------------------------\n");
        printf("| Primero importar un archivo .txt ! |\n");
        printf(" ------------------------------------\n\n");
        return;
    }

    // Si el numero de entregas es 1, se muestra por pantalla un mensaje y se cierra la función. //
    if(numeroEntregas == 1){
        printf(" ---------------------------------------------------\n");
        printf("| No existen otras entregas para calcular distancia |\n");
        printf(" ---------------------------------------------------\n");
        return;
    }
    
    // Declaración de variables //
    int id1, id2, caracteres1, caracteres2, caracteres3, k;
    double distancia;
    char num[15];

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
       Se guarda en la variable 'distancia' la distancia entre la entrega del primer
       id y la entrega del segundo id. Finalmente se imprime por pantalla los numeros
       de id's y la distancia entre ellos.*/
    Entrega *registro1 = (Entrega*) searchMap(Entregas_id, &id1);

    distancia = registro1->distancia[id2-1];

    sprintf(num, "%d", id1);
    caracteres1 = strlen(num);

    sprintf(num, "%d", id2);
    caracteres2 = strlen(num);
    
    sprintf(num, "%.4lf", distancia);
    caracteres3 = strlen(num);

    printf("\n");
    printf(" ");
    for(k = 0; k < caracteres1 + caracteres2 + caracteres3 + 40; k++) printf("-");

    printf("\n| La distancia entre la entrega %d y %d es: %.4lf |\n ", id1, id2, distancia);

    for(k = 0; k < caracteres1 + caracteres2 + caracteres3 + 40; k++) printf("-");
    printf("\n\n");

    getchar();

    return;
}
