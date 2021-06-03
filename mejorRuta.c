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

comparar(const void *a, const void *b);

void mejorRuta(Map *entregas_id, Map *rutas_nombre, int *numeroRutas, int numeroEntregas){
    //Si no se entra a la función de importación se cierra función//
    if(numeroEntregas == 0){
        printf(" ----------------------------------------------------------------------------------------------\n");
        printf("| Por favor ingrese a la funcion de importar para tener entregas para crear mejor ruta posible |\n");
        printf(" ----------------------------------------------------------------------------------------------\n\n");
        return;
    }

    //Lista de variables//
    Entrega *aux = NULL;
    float distancia;
    float *distanciaEp = NULL;
    int i, j,k , x, y, idEntrega, contRecorrido;
    int diferenciaX = 0, diferenciaY = 0;
    int *entregasVisitadas = NULL; 
    Ruta *ristanciaMasCorta = NULL;
    /*
    float **matriz = NULL;//Se crea matríz dinámica para revisar las distancias entre todas las entregas//
    matriz = (float **) malloc(numeroEntregas * sizeof(float *) );
    assert(matriz != NULL);
    for(i = 0; i < numeroEntregas; i++){
        matriz[i] = (float *) malloc(numeroEntregas * sizeof(float ) );
        assert(matriz[i] != NULL);
    }
    */

    // Se pide al usuario que ingrese las coordenadas de su posición actual. //
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
                   distanciaEp[j] = -1;
               }else{
                   distanciaEp[j] = aux->distancia[j];

               } 
            }

            //Se ordena de manera creciente 'distnaciasEp'//
            qsort(distanciaEp, numeroEntregas, sizeof(float), comparar);

            for(j = 0; j < numeroEntregas; j++){
                if( (distanciaEp[contRecorrido] == aux->distancia[j]) && (entregasVisitas[j] != 1) ){
                    idEntrega = j+1;
                    break;
                }
            }

            distnaciaMasCorta[i].distnaciaTotal += aux->distancia[j];
            distnaciaMasCorta[i].idEntregas[contRecorrido] = idEntrega;

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

        printf("%.4f", distanciaMasCorta[i].distnaciaTotal);
        //FIN TESTING :D//
    }


    distanciasEP = (float*)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        distanciasEP[i] = distanciasMasCorta[i].distanciaTotal;
    }

    qsort( distanciasEP, numeroEntregas, sizeof(float), ordenarDistanciasDeMenorAMayor);

    for(i = 0; i < numeroEntregas; i++){
        if(distanciasEP[0] == distanciasMasCorta[i].distanciaTotal){
            if(i > 0){
                distanciasMasCorta[0].distanciaTotal = distanciasMasCorta[i].distanciaTotal;

                for(j = 0; j < numeroEntregas; j++){
                    distanciasMasCorta[0].idEntregas[j] = distanciasMasCorta[i].idEntregas[j];
                }
            }

            distanciasMasCorta[0].x = x;
            distanciasMasCorta[0].y = y;

            strcpy( distanciasMasCorta[0].nombre, "Mejor Ruta");

            distanciasMasCortas = (Ruta*) realloc(distanciasMasCorta, sizeof(Ruta));
        }
    }

    insertMap(rutas_nombre, distanciasMasCorta->nombre, distanciasMasCorta);

    (*numeroRutas)++;

    free(entregasVisitadas);
    free(distanciasEP);

    return;
}