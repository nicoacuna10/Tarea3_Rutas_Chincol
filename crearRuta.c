#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

int ordenar(const void *a, const void *b)
{
    float *ptrA = (float *)a;
    float *ptrB = (float *)b;

    return *ptrA - *ptrB;
}

void crearRuta(Map *Entregas_id, List *ListaDeRutasCreadas, int numeroEntregas){

    if(Entregas_id == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }

    int x, y;

    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);

    
    float *DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));
    int i, diferenciaX, diferenciaY;

    i = 0;
    Entrega *registro1 = (Entrega*) firstMap(Entregas_id);

    while(registro1 != NULL){
        diferenciaX = x - registro1->x;
        diferenciaY = y - registro1->y;
        DistanciasEP[i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
        printf("%.2f\n", DistanciasEP[i]);
        registro1 = (Entrega*) nextMap(Entregas_id);
        i++;
    }

    float *CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasEP[i] = DistanciasEP[i];
    }


    qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenar);

    int opcionesRestantes = numeroEntregas, id, l;
    int espacios, j, k;
    char num[10];

    int *marcador = (int*)malloc(numeroEntregas * sizeof(int));

    for(i = 0; i < numeroEntregas; i++) marcador[i] = 0;

    Ruta *R = (Ruta*)malloc(sizeof(Ruta));
    R->idEntregas = (int*)malloc(numeroEntregas * sizeof(int));
    R->distanciaTotal = 0;

    l = 0;

    printf(" ------------------------------------\n");
    printf("| ID  | DISTANCIA A POSICION ACTUAL  |\n");
    printf(" ------------------------------------\n");

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

    printf("\nIngrese id de entrega: ");
    scanf("%d", &id);
    if(marcador[id-1] == 0){
        marcador[id-1] = 1;
    }else{
        do{
            printf("\nIngrese otro id: ");
            scanf("%d", &id);
        }while(marcador[id-1] == 1);
    }


    R->idEntregas[l] = id;
    R->distanciaTotal += DistanciasEP[id-1];

    opcionesRestantes--;
    l++;

    while(opcionesRestantes > 0){

        float *DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));

        Entrega *registro1 = (Entrega*) searchMap(Entregas_id, &id);

        for(i = 0; i < numeroEntregas; i++){
            if(marcador[i] == 0){
                DistanciasEP[i] = registro1->distancia[i];
            }else DistanciasEP[i] = -1;
            printf("%.2f\n", DistanciasEP[i]);
        }

        float *CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

        for(i = 0; i < numeroEntregas; i++){
            CopiaDistanciasEP[i] = DistanciasEP[i];
        }

        qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenar);

        printf(" ------------------------------------\n");
        printf("| ID  | DISTANCIA A POSICION ACTUAL  |\n");
        printf(" ------------------------------------\n");

        for( i = 0; i < numeroEntregas; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j] && DistanciasEP[j] != -1){

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

        printf("\nIngrese id de entrega: ");
        scanf("%d", &id);
        if(marcador[id-1] == 0){
            marcador[id-1] = 1;
        }else{
            do{
                printf("\nIngrese otro id: ");
                scanf("%d", &id);
            }while(marcador[id-1] == 1);
        }

        R->idEntregas[l] = id;
        R->distanciaTotal += DistanciasEP[id-1];
        opcionesRestantes--;
        l++;
    }

    Entrega *aux = (Entrega*)searchMap(Entregas_id, &id);

    // Calcular Distancia a Posicion //
    diferenciaX = x - aux->x;
    diferenciaY = y - aux->y;
    int distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

    R->distanciaTotal += distancia;

    printf(" ------------------------------------------------------------\n");
    printf("| RUTA                           | DISTANCIA TOTAL RECORRIDA |\n");
    printf(" ------------------------------------------------------------\n| ");

    for( i = 0; i < numeroEntregas; i++){
        printf("%d", R->idEntregas[i]);
        if(i < numeroEntregas-1) printf(" - ");
    }

    printf("          %.2f |", R->distanciaTotal);

    printf("\nIngrese nombre de ruta: ");
    scanf("%s", R->nombre);

    pushBack(ListaDeRutasCreadas, R);

    return;
}