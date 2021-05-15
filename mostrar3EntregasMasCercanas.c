#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Map.h"

typedef struct{
    int id;
	int x;
	int y;
	float *distancia;
}Entrega;

int ordenarDeMenorAMayor(const void *a, const void *b)
{
    float *ptrA = (float *)a;
    float *ptrB = (float *)b;

    return *ptrA - *ptrB;
}

void mostrar3EntregasMasCercanas(Map *Entregas_id, int numeroEntregas){
	
    // Si no se encuentra inicializado del mapa, se cierra la función. //
    if(Entregas_id == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }

    // Declaración de variables //
    int x, y;
    int i, diferenciaX, diferenciaY;
    
    // Se pide al usuario que ingrese las coordenadas de su ubicación actual. //
    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);
	
    /* Se incializa un arreglo para almacenar las distancias entre las entregas
       y la posición actual. */
    float *DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));
    
    /* Se calculan las distancias entre las entregas y la posción actual. Se almacenan
       en cada casilla en relación al id, considerando que el primer elemento del mapa
       es el id mayor.*/
    i = 0;
    Entrega *registro1 = (Entrega*) firstMap(Entregas_id);
    while(registro1 != NULL){
        diferenciaX = x - registro1->x;
        diferenciaY = y - registro1->y;
        DistanciasEP[(numeroEntregas-1) - i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
        printf("%.2f\n", DistanciasEP[(numeroEntregas-1) - i]);
        registro1 = (Entrega*) nextMap(Entregas_id);
        i++;
    }
    
    /* Se dimensiona otro arreglo y se hace una copia de las distancias, esto se hace para no perder
       la información de la entrega asociada a la distancia.*/
    float *CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasEP[i] = DistanciasEP[i];
    }

    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
    qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenarDeMenorAMayor);

    // Se imprime por pantalla las 3 entregas más cercanas a la posición actual. //
    printf(" ------------------------------------\n");
    printf("| ID  | DISTANCIA A POSICION ACTUAL  |\n");
    printf(" ------------------------------------\n");

    int espacios, j, k;
    char num[10];

    if( numeroEntregas >= 3){

        for( i = 0; i < 3; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j]){

                    printf("| %d", j + 1);
                    sprintf(num, "%d", j+1);
                    espacios = 3 - strlen(num);
                    for( k = 0; k < espacios; k++) printf(" ");

                    printf(" | %.2f", DistanciasEP[j]);
                    sprintf(num, "%f", DistanciasEP[j]);
                    espacios = 32 - strlen(num);
                    for ( k = 0; k < espacios; k++) printf(" ");

                    printf(" |\n ------------------------------------\n");

                }
            }
        }
    }else{

        for( i = 0; i < numeroEntregas; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j]){

                    printf("| %d", j + 1);
                    sprintf(num, "%d", j+1);
                    espacios = 3 - strlen(num);
                    for( k = 0; k < espacios; k++) printf(" ");

                    printf(" | %.2f", DistanciasEP[j]);
                    sprintf(num, "%f", DistanciasEP[j]);
                    espacios = 32 - strlen(num);
                    for ( k = 0; k < espacios; k++) printf(" ");

                    printf(" |\n ------------------------------------\n");

                }
            }
        }
    }

    // Se libera memoria de los arreglos dinámicos. //
    free(DistanciasEP);
    free(CopiaDistanciasEP);

    return;

}
