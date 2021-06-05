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

int ordenar(const void *a, const void *b){
    //Función de comparación para qsort//
    double *ptrA = (double *)a;
    double *ptrB = (double *)b;

    return *ptrA - *ptrB;
}

void crearRuta(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int *numeroRutas){

    // Si no se encuentra inicializado el mapa, se cierra la función. //
    if(Entregas_id == NULL){
        printf("\n");
        printf(" ------------------------------------\n");
        printf("| Primero importar un archivo .txt ! |\n");
        printf(" ------------------------------------\n\n");
        return;
    }

    // Declaración de variables. //
    int x, y, i, diferenciaX, diferenciaY, opcionesRestantes, id, l;
    double *DistanciasAEntregas = NULL, *CopiaDistanciasAEntregas = NULL, distancia;
    int espacios, j, k, caracteres, caracteresCoordenadaX, caracteresCoordenadaY;
    int *marcador = NULL;
    char num[15];
    Ruta *R = NULL, *registroNombreRuta = NULL;
    Entrega *registro = NULL;


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
    

    /* Se calculan las distancias entre las entregas y la posición actual y se almacenan
       en el arreglo. */
    for(i = 0; i < numeroEntregas; i++){
        id = i + 1;
        registro = (Entrega*) searchMap(Entregas_id, &id);
        diferenciaX = x - registro->x;
        diferenciaY = y - registro->y;
        DistanciasAEntregas[i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
    }

    /* Se dimensiona otro arreglo y se hace una copia de las distancias, esto se hace para no perder
       la información de la entrega asociada a la distancia.*/
    CopiaDistanciasAEntregas = (double *)malloc(numeroEntregas * sizeof(double));

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasAEntregas[i] = DistanciasAEntregas[i];
    }

    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
    qsort( CopiaDistanciasAEntregas, numeroEntregas, sizeof(double), ordenar);

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
    caracteresCoordenadaX = strlen(num);

    sprintf(num, "%d", y);
    caracteresCoordenadaY = strlen(num);

    printf(" ");
    for(k = 0; k < caracteresCoordenadaX + caracteresCoordenadaY + 47; k++) printf("-");

    printf("\n| ID  | DISTANCIA DESDE POSICION ACTUAL ( %d , %d ) |\n ", x, y);

    for(k = 0; k < caracteresCoordenadaX + caracteresCoordenadaY + 47; k++) printf("-");
    printf("\n");

    for( i = 0; i < numeroEntregas; i++){

        for(j = 0; j < numeroEntregas; j++){

            if(CopiaDistanciasAEntregas[i] == DistanciasAEntregas[j]){

                printf("| %d", j + 1);
                sprintf(num, "%d", j+1);
                espacios = 3 - strlen(num);
                for( k = 0; k < espacios; k++) printf(" ");

                printf(" | %.4lf", DistanciasAEntregas[j]);
                sprintf(num, "%.4lf", DistanciasAEntregas[j]);
                espacios = 40 + caracteresCoordenadaX + caracteresCoordenadaY - strlen(num);
                for ( k = 0; k < espacios; k++) printf(" ");
                printf("|\n ");

                for(k = 0; k < caracteresCoordenadaX + caracteresCoordenadaY + 47; k++) printf("-");
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
    R->distanciaTotal += DistanciasAEntregas[id-1];

    opcionesRestantes--;
    l++;

    while(opcionesRestantes > 0){
	
	    /* Se busca la información de la id escogida en el mapa y se almacenan
	       sus distancias en el arreglo. */
        registro = (Entrega*) searchMap(Entregas_id, &id);

        for(i = 0; i < numeroEntregas; i++){
            if(marcador[i] == 0){
                DistanciasAEntregas[i] = registro->distancia[i];
            }else DistanciasAEntregas[i] = -1;

        }

        // Se copian las distancias en otro arreglo para ordenar de menor a mayor. //
        for(i = 0; i < numeroEntregas; i++){
            CopiaDistanciasAEntregas[i] = DistanciasAEntregas[i];
        }

	    // Se ordena el arreglo de menor a mayor (distancias más cortas a las más lejanas). //
        qsort( CopiaDistanciasAEntregas, numeroEntregas, sizeof(double), ordenar);
	    
	    // Se imprime por pantlla las distancias hacia las entregas disponibles. //


        sprintf(num, "%d", id);
        caracteres = strlen(num);

        printf(" ");
        for(k = 0; k < caracteres + 33; k++) printf("-");

        printf("\n| ID  | DISTANCIA DESDE ENTREGRA %d |\n ", id);

        for(k = 0; k < caracteres + 33; k++) printf("-");
        printf("\n");

        for( i = 0; i < numeroEntregas; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasAEntregas[i] == DistanciasAEntregas[j] && DistanciasAEntregas[j] != -1){

                    printf("| %d", j + 1);
                    sprintf(num, "%d", j+1);
                    espacios = 3 - strlen(num);
                    for( k = 0; k < espacios; k++) printf(" ");

                    printf(" | %.4lf", DistanciasAEntregas[j]);
                    sprintf(num, "%.4lf", DistanciasAEntregas[j]);
                    espacios = 28 + caracteres - strlen(num);
                    for ( k = 0; k < espacios; k++) printf(" ");
                    printf("|\n ");
                    
                    for(k = 0; k < caracteres + 33; k++) printf("-");
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
        R->distanciaTotal += DistanciasAEntregas[id-1];
	    
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
    if(numeroEntregas < 10){
        caracteres = (numeroEntregas*3 + 2);
    }else caracteres = (numeroEntregas-9)*4 + 29;
    
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

    // Se agrega la ruta al mapa de rutas. //
    insertMap(Rutas_nombre, R->nombre, R);

    (*numeroRutas)++;

    free(DistanciasAEntregas);
    free(CopiaDistanciasAEntregas);
    free(marcador);

    getchar();
    printf("\n\n");
    printf(" -------------------------\n");
    printf("| Ruta creada con exito ! |\n");
    printf(" -------------------------\n\n");
    return;
}
