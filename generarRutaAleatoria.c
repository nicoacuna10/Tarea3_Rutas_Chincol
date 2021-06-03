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

typedef struct{
    char nombre[100];
    int *idEntregas;
    float distanciaTotal;
    int x;
	int y;
}Ruta;

void generarRutaAleatoria(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int *numeroRutas){

    // Si el mapa no se encuentra inicializado, se cierra la función //
    if(Entregas_id == NULL){
        printf("\n");
        printf(" ------------------------------------\n");
        printf("| Primero importar un archivo .txt ! |\n");
        printf(" ------------------------------------\n\n");
        return;
    }

    // Declaración de variables. //
    int x, y, i, diferenciaX, diferenciaY, opcionesRestantes, numeroAleatorio, id;
    float *DistanciasEP = NULL, distancia;
    int *marcador = NULL, espacios, caracteres, k;
    Ruta *R = NULL;
    Entrega *registro = NULL;
    char num[10];

    // Se pide al usuario que ingrese las coordenadas de su posición actual. //
    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

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

    /* Se dimensiona un arreglo para almacenar las distancias entre la entrega y la
       posición actual. */
    DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));
    

    /* Se calculan las ditancias entre las entregas y la posición actual y se almacenan
       en el arreglo. */
    i = 0;
    registro = (Entrega*) firstMap(Entregas_id);

    while(registro != NULL){
        diferenciaX = x - registro->x;
        diferenciaY = y - registro->y;
        DistanciasEP[(numeroEntregas-1) - i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
        printf("( %d , %d ) - %d : %.4f\n", x, y, registro->id, DistanciasEP[(numeroEntregas-1) - i]);
        registro = (Entrega*) nextMap(Entregas_id);
        i++;
    }

    /* Se dimesiona un arreglo para marcar los id´s ocpuados para construir la ruta.
       Se inicializan todas las casillas del arreglo cero para indicar que no se han
       ocupado. */
    marcador = (int*)malloc(numeroEntregas * sizeof(int));

    for(i = 0; i < numeroEntregas; i++) marcador[i] = 0;
	
    // Se inicializa la variable ruta y se inicializa las variables que contiene. //
    R = (Ruta*)malloc(sizeof(Ruta));
    R->idEntregas = (int*)malloc(numeroEntregas * sizeof(int));
    R->distanciaTotal = 0;
    R->x = x;
    R->y = y;
    
    opcionesRestantes = numeroEntregas;
    numeroAleatorio = rand() % numeroEntregas;
    i = 0;

    marcador[numeroAleatorio] = 1;

    R->distanciaTotal += DistanciasEP[numeroAleatorio];
    R->idEntregas[i] = numeroAleatorio + 1;

    id = numeroAleatorio + 1;
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
    registro = (Entrega*)searchMap(Entregas_id, &id);

    diferenciaX = x - registro->x;
    diferenciaY = y - registro->y;
    distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

    // Se suma la distancia calculada a la distancia acumulada. //
    R->distanciaTotal += distancia;

    // Se imprime por pantalla la ruta (secuencia de id's de cada entrega) y la distancia total recorrida. //

    if(numeroEntregas == 1 || numeroEntregas == 2){
        caracteres = 4;
    }else if(numeroEntregas > 2 && numeroEntregas < 10){
        caracteres = (numeroEntregas*2 - 1);
    }else caracteres = (numeroEntregas-9)*3 + 17;
    
    printf(" ");
    for( k = 0; k < caracteres + 30; k++) printf("-");
    printf("\n");

    printf("| RUTA");
    for( k = 0; k < caracteres - 4; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n ");

    for( k = 0; k < caracteres + 30; k++) printf("-");
    printf("\n| ");

    for( i = 0; i < numeroEntregas; i++){
        printf("%d", R->idEntregas[i]);
        if(i < numeroEntregas-1) printf("-");
    }

    if(numeroEntregas == 1) for(k = 0; k < 3; k++) printf(" ");
    if(numeroEntregas == 2) printf(" ");

    printf(" | %.4f", R->distanciaTotal);
    sprintf(num, "%f", R->distanciaTotal);
    espacios = 27 - strlen(num);
    for( k = 0; k < espacios; k++) printf(" ");
    printf(" |\n ");
    
    for( k = 0; k < caracteres + 30; k++) printf("-");
    printf("\n");

    // Se pide al usuario que ingrese un nombre para la ruta. //
    printf("\nIngrese nombre de ruta: ");
    scanf("%s", R->nombre);

    // Se agrega la ruta al mapa. //
    insertMap(Rutas_nombre, R->nombre, R);

    (*numeroRutas)++;

    free(DistanciasEP);
    free(marcador);

    getchar();

    return; 

}