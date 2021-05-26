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

int ordenar(const void *a, const void *b)
{
    float *ptrA = (float *)a;
    float *ptrB = (float *)b;

    return *ptrA - *ptrB;
}

void crearRuta(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int *numeroRutas){

    // Si no se encuentra inicializado el mapa, se cierra la función. //
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

    /* Se dimensiona otro arreglo y se hace una copia de las distancias, esto se hace para no perder
       la información de la entrega asociada a la distancia.*/
    float *CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasEP[i] = DistanciasEP[i];
    }

    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
    qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenar);

    int opcionesRestantes = numeroEntregas, id, l;
    int espacios, j, k;
    char num[10];

    /* Se dimesiona un arreglo para marcar los id´s ocpuados para construir la ruta.
       Se inicializan todas las casillas del arreglo cero para indicar que no se han
       ocupado. */
    int *marcador = (int*)malloc(numeroEntregas * sizeof(int));

    for(i = 0; i < numeroEntregas; i++) marcador[i] = 0;
	
    // Se inicializa la variable ruta y se inicializa las variables que contiene. //
    Ruta *R = (Ruta*)malloc(sizeof(Ruta));
    R->idEntregas = (int*)malloc(numeroEntregas * sizeof(int));
    R->distanciaTotal = 0;
    R->x = x;
    R->y = y;

    l = 0;

    printf(" -------------------------------------------\n");
    printf("| ID  | DISTANCIA A POSICION ACTUAL         |\n");
    printf(" -------------------------------------------\n");

    for( i = 0; i < numeroEntregas; i++){

        for(j = 0; j < numeroEntregas; j++){

            if(CopiaDistanciasEP[i] == DistanciasEP[j]){

                printf("| %d", j + 1);
                sprintf(num, "%d", j+1);
                espacios = 3 - strlen(num);
                for( k = 0; k < espacios; k++) printf(" ");

                printf(" | %.2f", DistanciasEP[j]);
                sprintf(num, "%f", DistanciasEP[j]);
                espacios = 39 - strlen(num);
                for ( k = 0; k < espacios; k++) printf(" ");

                printf(" |\n -------------------------------------------\n");

            }
        }
    }

    // Se pide al usuario que ingrese id de entrega.//
    printf("\nIngrese id de entrega: ");
    scanf("%d", &id);

    while(id < 1 || id > numeroEntregas){
        printf("\nIngrese id valido: ");
        printf("%d", &id);
    }

    // En la posición id menos 1 se indica con un número 1 que ya se utilizó. //
    marcador[id-1] = 1;

    // Se almacena en el arreglo el id ingresado y se suma la distancia acumulada. //
    R->idEntregas[l] = id;
    R->distanciaTotal += DistanciasEP[id-1];

    opcionesRestantes--;
    l++;

    while(opcionesRestantes > 0){
	
	// Se dimensiona el arreglo para almacenar las distancias. //
        float *DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));

	/* Se busca la información de la id escogida en el mapa y se almacenan
	   sus distancias en el arreglo. */
        Entrega *registro1 = (Entrega*) searchMap(Entregas_id, &id);

        for(i = 0; i < numeroEntregas; i++){
            if(marcador[i] == 0){
                DistanciasEP[i] = registro1->distancia[i];
            }else DistanciasEP[i] = -1;
            printf("%.2f\n", DistanciasEP[i]);
        }

	/* Se dimensiona otro arreglo y se hace una copia de las distancias, esto se hace para no perder
           la información de la entrega asociada a la distancia. */
        float *CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

        for(i = 0; i < numeroEntregas; i++){
            CopiaDistanciasEP[i] = DistanciasEP[i];
        }

	// Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
        qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenar);
	    
	// Se imprime por pantlla las distancias hacia las entregas disponibles. //

        if( id < 10){
            printf(" ------------------------------------\n");
            printf("| ID  | DISTANCIA DESDE ENTREGRA %d   |\n", id);
            printf(" ------------------------------------\n");
        }else{
            printf(" ------------------------------------\n");
            printf("| ID  | DISTANCIA DESDE ENTREGRA %d  |\n", id);
            printf(" ------------------------------------\n");
        }

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

	// Se pide al usuario que ingrese un id de entrega. //
        printf("\nIngrese id de entrega: ");
        scanf("%d", &id);
	    
	/* Si se encuentra disponible (0 almacenado en la casilla), se "marca" con un 1
	   para indicar con que se ocupó. */
        if(marcador[id-1] == 0){
            marcador[id-1] = 1;
        }else{
            do{
                printf("\nIngrese otro id: ");
                scanf("%d", &id);
            }while(marcador[id-1] == 1 || id < 1 || id > numeroEntregas);
            marcador[id-1] = 1;
        }

        // Se almacena en el arreglo el id ingresado y se suma la distancia acumulada. //	
        R->idEntregas[l] = id;
        R->distanciaTotal += DistanciasEP[id-1];
	    
        opcionesRestantes--;
        l++;
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
    if(numeroEntregas < 10){
        espacios = (numeroEntregas*2 - 1);
    }else espacios = (numeroEntregas-9)*3 + 17;
    printf(" ");
    for( k = 0; k < espacios + 30; k++) printf("-");
    printf("\n");

    printf("| RUTA");
    for( k = 0; k < espacios - 4; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n");

    printf(" ");
    for( k = 0; k < espacios + 30; k++) printf("-");
    printf("\n| ");

    for( i = 0; i < numeroEntregas; i++){
        printf("%d", R->idEntregas[i]);
        if(i < numeroEntregas-1) printf("-");
    }

    printf(" | %.2f", R->distanciaTotal);
    sprintf(num, "%f", R->distanciaTotal);
    int espacios2 = 29 - strlen(num);
    for( k = 0; k < espacios2; k++) printf(" ");
    printf(" |\n");
    
    printf(" ");
    for( k = 0; k < espacios + 30; k++) printf("-");
    printf("\n");

    // Se pide al usuario que ingrese un nombre para la ruta. //
    printf("\nIngrese nombre de ruta: ");
    scanf("%s", R->nombre);

    // Se agrega la ruta al mapa de rutas. //
    insertMap(Rutas_nombre, R->nombre, R);

    (*numeroRutas)++;

    free(DistanciasEP);
    free(CopiaDistanciasEP);

    getchar();

    return;
}
