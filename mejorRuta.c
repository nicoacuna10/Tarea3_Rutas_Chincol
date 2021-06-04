#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

int comparar(const void *a, const void *b){
    float *PtrA = (float *)a, *PtrB = (float *)b;
    return *PtrA - *PtrB;
}

void mejorRuta(Map *entregas_id, Map *rutas_nombre, int *numeroRutas, int numeroEntregas){
    //Si no se entra a la función de importación se cierra función//
    if(numeroEntregas == 0 || entregas_id == NULL){
        printf(" ----------------------------------------------------------------------------------------------\n");
        printf("| Por favor ingrese a la funcion de importar para tener entregas para crear mejor ruta posible |\n");
        printf(" ----------------------------------------------------------------------------------------------\n\n");
        return;
    }

    //Lista de variables//
    Entrega *aux = NULL;
    float distancia;
    float *distanciaEP = NULL;
    int i, j,k , x, y, idEntrega, contRecorrido;
    int diferenciaX = 0, diferenciaY = 0;
    int *entregasVisitadas = NULL; 
    Ruta *distanciaMasCorta = NULL;

    int caracteres, espacios;
    char num[15];

    // Se pide al usuario que ingrese las coordenadas de su posición actual.//
    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    //REVISAR SI ES MEJOR AMPLIAR EL RANGO O NO//
    while(x < -9999 || x > 9999){
        printf("\nIngrese valor de coordenada x valido: ");
        scanf("%d", &x);
    }

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);

    while(y < -9999 || y > 9999){
        printf("\nIngrese valor de coordenada y valido: ");
        scanf("%d", &y);
    }

    //Se dimensiona Variables de tipo puntero//
    distanciaEP = (float *) malloc(numeroEntregas * sizeof(float ));
    assert(distanciaEP != NULL);

    entregasVisitadas = (int *) malloc(numeroEntregas * sizeof(int) );
    assert(entregasVisitadas != NULL);

    distanciaMasCorta = (Ruta *) malloc(numeroEntregas * sizeof(Ruta) );
    assert(distanciaMasCorta != NULL);


    for(i = 0; i < numeroEntregas; i++){
        distanciaMasCorta[i].idEntregas = (int *) malloc(numeroEntregas * sizeof(int) );
        assert(distanciaMasCorta[i].idEntregas != NULL);

        //Se inicialza entregas visitadas en cero//
        for(j = 0; j < numeroEntregas; j++){
            entregasVisitadas[j] = 0;
        }

        distanciaMasCorta[i].distanciaTotal = 0;
        idEntrega = i + 1;
        aux = (Entrega *) searchMap(entregas_id, &idEntrega);
        assert(aux != NULL);

        diferenciaX = x - aux->x;
        diferenciaY = y - aux->y;

        //REVISAR SI DEBEMOS CASTEAR A DOUBLE !!!!!!!!!//
        distancia = sqrt(pow(diferenciaX,2) + pow(diferenciaY,2) );
        distanciaMasCorta[i].distanciaTotal += distancia;
        distanciaMasCorta[i].idEntregas[0] = i + 1;

        contRecorrido = 1;
        k = i;
        
        while(contRecorrido < numeroEntregas){
            entregasVisitadas[k] = 1;
            idEntrega = k + 1;
            aux = (Entrega *) searchMap(entregas_id, &idEntrega);
            assert(aux != NULL);

            //Se guarda todas las distnacias en relación a 'idEntrega'//
            for(j = 0; j < numeroEntregas; j++){
               if(entregasVisitadas[j] == 1){
                   distanciaEP[j] = -1;
               }else{
                   distanciaEP[j] = aux->distancia[j];

               } 
            }

            //Se ordena de manera creciente 'distnaciasEp'//
            qsort(distanciaEP, numeroEntregas, sizeof(float), comparar);

            for(j = 0; j < numeroEntregas; j++){
                if( (distanciaEP[contRecorrido] == aux->distancia[j]) && (entregasVisitadas[j] != 1) ){
                    idEntrega = j+1;
                    break;
                }
            }

            distanciaMasCorta[i].distanciaTotal += aux->distancia[j];
            distanciaMasCorta[i].idEntregas[contRecorrido] = idEntrega;

            k = j;
            contRecorrido++;
        }


        idEntrega = k + 1;
        aux = (Entrega *) searchMap(entregas_id, &idEntrega);
        assert(aux != NULL);

        diferenciaX = x - aux->x;
        diferenciaY = y - aux->y;

        //REVISAR SI DEBEMOS CASTEAR A DOUBLE !!!!!!!!!//
        distancia = sqrt(pow(diferenciaX,2) + pow(diferenciaY,2) );
        distanciaMasCorta[i].distanciaTotal += distancia;
       
        //TESTING//
        for(j = 0; j < numeroEntregas; j++){
            printf("%d ", distanciaMasCorta[i].idEntregas[j]);
        }

        printf("%.4f\n", distanciaMasCorta[i].distanciaTotal);

        //FIN TESTING :D//
    }


    distanciaEP = (float*)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        distanciaEP[i] = distanciaMasCorta[i].distanciaTotal;
    }

    qsort( distanciaEP, numeroEntregas, sizeof(float), comparar);

    for(i = 0; i < numeroEntregas; i++){
        if(distanciaEP[0] == distanciaMasCorta[i].distanciaTotal){
            if(i > 0){
                distanciaMasCorta[0].distanciaTotal = distanciaMasCorta[i].distanciaTotal;

                for(j = 0; j < numeroEntregas; j++){
                    distanciaMasCorta[0].idEntregas[j] = distanciaMasCorta[i].idEntregas[j];
                }
            }

            distanciaMasCorta[0].x = x;
            distanciaMasCorta[0].y = y;

            strcpy( distanciaMasCorta[0].nombre, "Mejor Ruta");

            distanciaMasCorta = (Ruta*) realloc(distanciaMasCorta, sizeof(Ruta));
        }
    }

    insertMap(rutas_nombre, distanciaMasCorta->nombre, distanciaMasCorta);

    // Se imprime por pantalla la ruta (secuencia de id's de cada entrega) y la distancia total recorrida. //
    if(numeroEntregas < 10){
        caracteres = (numeroEntregas*3 - 2);
    }else caracteres = (numeroEntregas-9)*4 +25;

    printf(" ");
    for(i = 0; i < caracteres + 28; i++) printf("-");

    printf("\n| Mejor Ruta | ");

    for(i = 0; i < numeroEntregas; i++){
        printf("%d", distanciaMasCorta->idEntregas[i]);
        if(i < numeroEntregas - 1) printf("->");
    }

    printf(" | %.4f |\n ", distanciaMasCorta->distanciaTotal);

    for(i = 0; i < caracteres + 28; i++) printf("-");
    printf("\n");


    (*numeroRutas)++;

    free(entregasVisitadas);
    free(distanciaEP);

    printf("\n\n");
    getchar();
    return;
}