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

    // Declaración de variables. //
    int x, y, i, diferenciaX, diferenciaY, opcionesRestantes, id, l;
    float *DistanciasEP = NULL, *CopiaDistanciasEP = NULL, distancia;
    int espacios, j, k, caracteres1, caracteres2, *marcador = NULL;
    char num[15];
    Ruta *R = NULL;
    Entrega *registro = NULL;


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

    /* Se dimensiona otro arreglo y se hace una copia de las distancias, esto se hace para no perder
       la información de la entrega asociada a la distancia.*/
    CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasEP[i] = DistanciasEP[i];
    }

    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
    qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenar);

    /* Se dimesiona un arreglo para marcar los id´s ocpuados para construir la ruta.
       Se inicializan todas las casillas del arreglo cero para indicar que no se han
       ocupado. */
    marcador = (int*)malloc(numeroEntregas * sizeof(int));
    if(marcador == NULL){
        printf("Error en la inicializacion...\n\n");
        exit (1);
    }

    for(i = 0; i < numeroEntregas; i++) marcador[i] = 0;
	
    // Se inicializa la variable ruta y se inicializa las variables que contiene. //
    R = (Ruta*)malloc(sizeof(Ruta));
    R->idEntregas = (int*)malloc(numeroEntregas * sizeof(int));
    R->distanciaTotal = 0;
    R->x = x;
    R->y = y;

    opcionesRestantes = numeroEntregas;
    l = 0;

    sprintf(num, "%d", x);
    caracteres1 = strlen(num);

    sprintf(num, "%d", y);
    caracteres2 = strlen(num);

    printf(" ");
    for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");

    printf("\n| ID  | DISTANCIA DESDE POSICION ACTUAL ( %d , %d ) |\n ", x, y);

    for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");
    printf("\n");

    for( i = 0; i < numeroEntregas; i++){

        for(j = 0; j < numeroEntregas; j++){

            if(CopiaDistanciasEP[i] == DistanciasEP[j]){

                printf("| %d", j + 1);
                sprintf(num, "%d", j+1);
                espacios = 3 - strlen(num);
                for( k = 0; k < espacios; k++) printf(" ");

                printf(" | %.4f", DistanciasEP[j]);
                sprintf(num, "%.4f", DistanciasEP[j]);
                espacios = 40 + caracteres1 + caracteres2 - strlen(num);
                for ( k = 0; k < espacios; k++) printf(" ");
                printf("|\n ");

                for(k = 0; k < caracteres1 + caracteres2 + 47; k++) printf("-");
                printf("\n");

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
	
	    /* Se busca la información de la id escogida en el mapa y se almacenan
	       sus distancias en el arreglo. */
        registro = (Entrega*) searchMap(Entregas_id, &id);

        for(i = 0; i < numeroEntregas; i++){
            if(marcador[i] == 0){
                DistanciasEP[i] = registro->distancia[i];
            }else DistanciasEP[i] = -1;
            printf("%.4f\n", DistanciasEP[i]);
        }

        // Se copian las distancias en otro arreglo para ordenar de menor a mayor. //
        for(i = 0; i < numeroEntregas; i++){
            CopiaDistanciasEP[i] = DistanciasEP[i];
        }

	    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
        qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenar);
	    
	    // Se imprime por pantlla las distancias hacia las entregas disponibles. //


        sprintf(num, "%d", id);
        caracteres1 = strlen(num);

        printf(" ");
        for(k = 0; k < caracteres1 + 33; k++) printf("-");

        printf("\n| ID  | DISTANCIA DESDE ENTREGRA %d |\n ", id);

        for(k = 0; k < caracteres1 + 33; k++) printf("-");
        printf("\n");

        for( i = 0; i < numeroEntregas; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j] && DistanciasEP[j] != -1){

                    printf("| %d", j + 1);
                    sprintf(num, "%d", j+1);
                    espacios = 3 - strlen(num);
                    for( k = 0; k < espacios; k++) printf(" ");

                    printf(" | %.4f", DistanciasEP[j]);
                    sprintf(num, "%f", DistanciasEP[j]);
                    espacios = 28 + caracteres1 - strlen(num);
                    for ( k = 0; k < espacios; k++) printf(" ");
                    printf("|\n ");
                    
                    for(k = 0; k < caracteres1 + 33; k++) printf("-");
                    printf("\n");

                }
            }
        }

	    // Se pide al usuario que ingrese un id de entrega. //
        printf("\nIngrese id de entrega: ");
        scanf("%d", &id);

        while( marcador[id - 1] == 1 || id < 1 || id > numeroEntregas ){
            if( marcador[id - 1] == 1) printf("\nId seleccionado anteriormente, ingrese otro: ");
            if( id < 1 || id > numeroEntregas) printf("\nIngrese id valido: ");
            scanf("%d", &id);
        }

        /* Si se encuentra disponible (0 almacenado en la casilla), se "marca" con un 1
	       para indicar con que se ocupó. */
        marcador[id - 1] = 1;

        // Se almacena en el arreglo el id ingresado y se suma la distancia acumulada. //	
        R->idEntregas[l] = id;
        R->distanciaTotal += DistanciasEP[id-1];
	    
        opcionesRestantes--;
        l++;
    }

    /* Se busca el último id ingresado para acceder a la información de sus coordenadas.
       Luego se calcula la distancia entre la entrega con último id y la posición actual. */
    registro = (Entrega*)searchMap(Entregas_id, &id);

    diferenciaX = x - registro->x;
    diferenciaY = y - registro->y;
    distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

    // Se suma la distancia calculada a la distancia acumulada. //
    R->distanciaTotal += distancia;

    // Se imprime por pantalla la ruta (secuencia de id's de cada entrega) y la distancia total recorrida. //
    if(numeroEntregas == 1 || numeroEntregas == 2){
        caracteres1 = 4;
    }else if(numeroEntregas > 2 && numeroEntregas < 10){
        caracteres1 = (numeroEntregas*2 - 1);
    }else caracteres1 = (numeroEntregas-9)*3 + 17;
    
    printf(" ");
    for( k = 0; k < caracteres1 + 30; k++) printf("-");
    printf("\n");

    printf("| RUTA");
    for( k = 0; k < caracteres1 - 4; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n ");

    for( k = 0; k < caracteres1 + 30; k++) printf("-");
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
    
    for( k = 0; k < caracteres1 + 30; k++) printf("-");
    printf("\n");

    // Se pide al usuario que ingrese un nombre para la ruta. //
    printf("\nIngrese nombre de ruta: ");
    scanf("%s", R->nombre);

    // Se agrega la ruta al mapa de rutas. //
    insertMap(Rutas_nombre, R->nombre, R);

    (*numeroRutas)++;

    free(DistanciasEP);
    free(CopiaDistanciasEP);
    free(marcador);

    getchar();

    return;
}
