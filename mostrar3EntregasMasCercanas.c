#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Map.h"

typedef struct{
    int id;
	int x;
	int y;
	double *distancia;
}Entrega;

int ordenarDeMenorAMayor(const void *a, const void *b){
    //Funcion que se usa para comparar en qsort//
    double *ptrA = (double *)a;
    double *ptrB = (double *)b;

    return *ptrA - *ptrB;
}

void mostrar3EntregasMasCercanas(Map *Entregas_id, int numeroEntregas){
	
    // Si no se encuentra inicializado del mapa, se cierra la función. //
    if(Entregas_id == NULL){
        printf("\n");
        printf(" ------------------------------------\n");
        printf("| Primero importar un archivo .txt ! |\n");
        printf(" ------------------------------------\n\n");
        return;
    }

    // Declaración de variables //
    int x, y, i, diferenciaX, diferenciaY, espacios, j, k;
    int caracteres1, caracteres2;
    double *DistanciasEP = NULL, *CopiaDistanciasEP = NULL;
    char num[15];
    
    // Se pide al usuario que ingrese las coordenadas de su ubicación actual. //
    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    while(x < -32767|| x > 32767){
        printf("\nIngrese valor de coordenada x valido: ");
        scanf("%d", &x);
    }

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);

    while(y < -32767|| y > 32767){
        printf("\nIngrese valor de coordenada y valido: ");
        scanf("%d", &y);
    }
	
    /* Se incializa un arreglo para almacenar las distancias entre las entregas
       y la posición actual. */
    DistanciasEP = (double*)malloc(numeroEntregas * sizeof(double));
    if(DistanciasEP == NULL){
        printf("Error en la inicializacion de arreglo en funcion mostrar3EntregasMasCeranas.\n\n");
        exit (1);
    }
    
    /* Se calculan las distancias entre las entregas y la posción actual. Se almacenan
       en cada casilla en relación al id, considerando que el primer elemento del mapa
       es el id mayor.*/
    i = 0;
    Entrega *registro1 = (Entrega*) firstMap(Entregas_id);
    while(registro1 != NULL){
        diferenciaX = x - registro1->x;
        diferenciaY = y - registro1->y;
        DistanciasEP[(numeroEntregas-1) - i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
        registro1 = (Entrega*) nextMap(Entregas_id);
        i++;
    }
    
    /* Se dimensiona otro arreglo y se hace una copia de las distancias, esto se hace para no perder
       la información de la entrega asociada a la distancia.*/
    CopiaDistanciasEP = (double *)malloc(numeroEntregas * sizeof(double));
    if(CopiaDistanciasEP == NULL){
        printf("Error en la inicializacion de arreglo en funcion mostrar3EntregasMasCercanas.\n\n");
        exit (1);
    }

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasEP[i] = DistanciasEP[i];
    }

    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
    qsort( CopiaDistanciasEP, numeroEntregas, sizeof(double), ordenarDeMenorAMayor);

    // Se imprime por pantalla las 3 entregas más cercanas a la posición actual. //
    sprintf(num, "%d", x);
    caracteres1 = strlen(num);

    sprintf(num, "%d", y);
    caracteres2 = strlen(num);
    
    printf(" ");
    for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");

    printf("\n| ID  | DISTANCIA DESDE POSICION ACTUAL ( %d , %d ) |\n ", x, y);

    for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");
    printf("\n");

    //Caso donde entregas es mayor a 3//
    if( numeroEntregas >= 3){

        for( i = 0; i < 3; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j]){

                    printf("| %d", j + 1);
                    sprintf(num, "%d", j+1);
                    espacios = 3 - strlen(num);
                    for( k = 0; k < espacios; k++) printf(" ");

                    printf(" | %.4lf", DistanciasEP[j]);
                    sprintf(num, "%.4lf", DistanciasEP[j]);
                    espacios = 40 + caracteres1 + caracteres2 - strlen(num);
                    for ( k = 0; k < espacios; k++) printf(" ");
                    printf("|\n ");

                    for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");
                    printf("\n");

                }
            }
        }
    //Caso donde entregas es menor a 3//
    }else{
    
        for( i = 0; i < numeroEntregas; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j]){

                    printf("| %d", j + 1);
                    sprintf(num, "%d", j+1);
                    espacios = 3 - strlen(num);
                    for( k = 0; k < espacios; k++) printf(" ");

                    printf(" | %.4lf", DistanciasEP[j]);
                    sprintf(num, "%.4lf", DistanciasEP[j]);
                    espacios = 40 + caracteres1 + caracteres2 - strlen(num);
                    for ( k = 0; k < espacios; k++) printf(" ");
                    printf("|\n ");

                    for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");
                    printf("\n");

                }
            }
        }
    }

    // Se libera memoria de los arreglos dinámicos. //
    free(DistanciasEP);
    free(CopiaDistanciasEP);

    getchar();
    printf("\n\n");
    return;

}
