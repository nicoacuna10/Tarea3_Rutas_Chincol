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

typedef struct{
    char nombre[100];
    int *idEntregas;
    double distanciaTotal;
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
    double *DistanciasAEntregas = NULL, distancia;
    int *marcador = NULL, espacios, caracteres, caracteresCoordenadaX, caracteresCoordenadaY, k;
    Ruta *R = NULL, *registroNombreRuta = NULL;
    Entrega *registro = NULL;
    char num[10];

    // Se pide al usuario que ingrese las coordenadas de su posición actual. //
    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    while(x < -32767 || x > 32767){
        printf("\nIngrese valor de coordenada x valido: ");
        scanf("%d", &x);
    }

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);

    while(y < -32767 || y > 32767){
        printf("\nIngrese valor de coordenada y valido: ");
        scanf("%d", &y);
    }

    /* Se dimensiona un arreglo para almacenar las distancias entre la entrega y la
       posición actual. */
    DistanciasAEntregas = (double *)malloc(numeroEntregas * sizeof(double));
    

    /* Se calculan las ditancias entre las entregas y la posición actual y se almacenan
       en el arreglo. */
    for(i = 0; i < numeroEntregas; i++){
        id = i + 1;
        registro = (Entrega*)searchMap(Entregas_id, &id);
        diferenciaX = x - registro->x;
        diferenciaY = y - registro->y;
        DistanciasAEntregas[(numeroEntregas-1) - i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
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

    R->distanciaTotal += DistanciasAEntregas[numeroAleatorio];
    R->idEntregas[i] = numeroAleatorio + 1;

    id = numeroAleatorio + 1;
    i++;
    opcionesRestantes--;

    //Se busca por fuerza bruta y de manera aleateoria, los puntos para crear la ruta aleatoria//
    while(opcionesRestantes > 0){

        Entrega *aux = (Entrega*) searchMap(Entregas_id, &id);

        //Se busca número aleatorio//
        do{
            numeroAleatorio = rand() % numeroEntregas;
        }while(marcador[numeroAleatorio] == 1);

        //Se marca casilla como ocupada con un uno//
        marcador[numeroAleatorio] = 1;
        
        //Se concatenan los puntos para crear ruta aleatoria//
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

    // Se imprime por pantalla la ruta (secuencia de id's de cada entrega) y la distancia total recorrida. //
    if(numeroEntregas < 10){
        caracteres = (numeroEntregas*3 + 2);
    }else caracteres = (numeroEntregas-9)*4 + 29;

    sprintf(num, "%d", R->x);
    caracteresCoordenadaX = strlen(num);

    sprintf(num, "%d", R->y);
    caracteresCoordenadaY = strlen(num);
    
    printf(" ");
    for( k = 0; k < caracteres + 2 * (caracteresCoordenadaX + caracteresCoordenadaY) + 44; k++) printf("-");
    printf("\n");

    printf("| RUTA");
    for( k = 0; k < caracteres + 2 *(caracteresCoordenadaX + caracteresCoordenadaY) + 10; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n ");

    for( k = 0; k < caracteres + 2 *(caracteresCoordenadaX + caracteresCoordenadaY) + 44; k++) printf("-");

    printf("\n| ( %d , %d )->", R->x, R->y);

    for( i = 0; i < numeroEntregas; i++){
        printf("%d->", R->idEntregas[i]);
    }

    printf("( %d , %d )", R->x, R->y);

    printf(" | %.4lf", R->distanciaTotal);
    sprintf(num, "%.4lf", R->distanciaTotal);
    espacios = 25 - strlen(num);
    for( k = 0; k < espacios; k++) printf(" ");
    printf(" |\n ");
    
    for( k = 0; k < caracteres + 2 * (caracteresCoordenadaX + caracteresCoordenadaY) + 44; k++) printf("-");
    printf("\n");

    // Se pide al usuario que ingrese un nombre para la ruta. //
    printf("\nIngrese nombre de ruta: ");
    scanf("%s", R->nombre);

    /* Se busca si existe otra ruta con el nombre ingresado. Si existe se pide al usuario
    que ingrese otro hasta que ingrese un nombre no existente en el mapa. */
    registroNombreRuta = (Ruta*) searchMap(Rutas_nombre, R->nombre);

    while( registroNombreRuta != NULL){
        caracteres = strlen(R->nombre);
        printf(" ");
        for(k = 0; k < caracteres + 27; k++) printf("-");
        printf("\n| Existe ruta con nombre \"%s\" |\n ", R->nombre);
        for(k = 0; k < caracteres + 27; k++) printf("-");
        printf("\n\nIngrese otro nombre: ");
        scanf("%s", R->nombre);

        registroNombreRuta = (Ruta *) searchMap(Rutas_nombre, R->nombre);
    }

    // Se agrega la ruta al mapa. //
    insertMap(Rutas_nombre, R->nombre, R);

    (*numeroRutas)++;

    free(DistanciasAEntregas);
    free(marcador);

    printf(" -----------------------------------\n");
    printf("| Ruta Aleatoria creada con exito ! |\n");
    printf(" -----------------------------------\n\n");
    getchar();

    return; 

}