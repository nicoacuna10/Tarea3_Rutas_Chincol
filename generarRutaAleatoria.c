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

void generarRutaAleatoria(Map *Entregas_id, List *ListaDeRutasCreadas, int numeroEntregas){

    // Si el mapa no se encuentra inicializado, se cierra la función //
    if(Entregas_id == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }

    int x, y;

    // Se pide al usuario que ingrese las coordenadas de su posición actual. //
    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);

    /* Se dimensiona un arreglo para almacenar las distancias entre la entrega y la
       posición actual. */
    float *DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));
    int i, diferenciaX, diferenciaY;

    /* Se calculan las ditancias entre las entregas y la posición actual y se almacenan
       en el arreglo. */
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

    /* Se dimesiona un arreglo para marcar los id´s ocpuados para construir la ruta.
       Se inicializan todas las casillas del arreglo cero para indicar que no se han
       ocupado. */
    int *marcador = (int*)malloc(numeroEntregas * sizeof(int));

    for(i = 0; i < numeroEntregas; i++) marcador[i] = 0;
	
    // Se inicializa la variable ruta y se inicializa las variables que contiene. //
    Ruta *R = (Ruta*)malloc(sizeof(Ruta));
    R->idEntregas = (int*)malloc(numeroEntregas * sizeof(int));
    R->distanciaTotal = 0;

    int opcionesRestantes = numeroEntregas;
    int numeroAleatorio = rand() % numeroEntregas;
    i = 0;

    marcador[numeroAleatorio] = 1;

    R->distanciaTotal += DistanciasEP[numeroAleatorio];
    R->idEntregas[i] = numeroAleatorio + 1;

    int id = numeroAleatorio + 1;
    i++;
    opcionesRestantes--;

    while(opcionesRestantes > 0){

        Entrega *aux = (Entrega*) searchMap(Entregas_id, &id);

        do{
            numeroAleatorio = rand() % numeroEntregas;
        }while(marcador[numeroAleatorio] == 1);

        marcador[numeroAleatorio] = 1;

        R->distanciaTotal += aux->distancia[numeroAleatorio];
        R->idEntregas[i] = numeroAleatorio + 1;

        id = numeroAleatorio + 1;
        i++;
        opcionesRestantes--;
    }

     /* Se busca el último id ingresado para acceder a la información. Luego se calcula
       la distancia entre la entrega con último id y la posición actual. */
    Entrega *aux = (Entrega*)searchMap(Entregas_id, &id);

    diferenciaX = x - aux->x;
    diferenciaY = y - aux->y;
    int distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

    // Se suma la distancia calculada a la distancia acumulada. //
    R->distanciaTotal += distancia;

    // Se imprime por pantalla la ruta (secuencia de id's de cada entrega) y la distancia total recorrida. //
    printf(" ------------------------------------------------------------\n");
    printf("| RUTA                           | DISTANCIA TOTAL RECORRIDA |\n");
    printf(" ------------------------------------------------------------\n| ");

    for( i = 0; i < numeroEntregas; i++){
        printf("%d", R->idEntregas[i]);
        if(i < numeroEntregas-1) printf(" - ");
    }

    printf(" |          %.2f |\n", R->distanciaTotal);
    printf(" ------------------------------------------------------------\n");

    // Se pide al usuario que ingrese un nombre para la ruta. //
    printf("\nIngrese nombre de ruta: ");
    scanf("%s", R->nombre);

    // Se agrega la ruta a la lista. //
    pushBack(ListaDeRutasCreadas, R);

    return; 

}