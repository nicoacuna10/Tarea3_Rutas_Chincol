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
	double *distancia;
}Entrega;

typedef struct{
    char nombre[100];
    int *idEntregas;
    double distanciaTotal;
	int x;
	int y;
}Ruta;

int comparar(const void *a, const void *b){
    double *PtrA = (double *)a, *PtrB = (double *)b;
    return *PtrA - *PtrB;
}

void mejorRuta(Map *Entregas_id, Map *Rutas_nombre, int *numeroRutas, int numeroEntregas, int *contMejorRutasCreadas){
    //Si no se entra a la función de importación se cierra función//
    if(numeroEntregas == 0 || Entregas_id == NULL){
        printf(" ----------------------------------------------------------------------------------------------\n");
        printf("| Por favor ingrese a la funcion de importar para tener entregas para crear mejor ruta posible |\n");
        printf(" ----------------------------------------------------------------------------------------------\n\n");
        return;
    }

    //Lista de variables//
    Entrega *aux = NULL;
    double distancia;
    double *vectorDeDistancias = NULL;
    int i, j,k , x, y, idEntrega, contRecorrido;
    int diferenciaX = 0, diferenciaY = 0;
    int *entregasVisitadas = NULL; 
    Ruta *distanciaMasCorta = NULL, *registroNombreRuta = NULL;

    int caracteres, espacios, caracteresCoordenadaX, caracteresCoordenadaY;
    char num[15];

    // Se pide al usuario que ingrese las coordenadas de su posición actual.//
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

    //Se dimensiona Variables de tipo puntero//
    vectorDeDistancias = (double *) malloc(numeroEntregas * sizeof(double ));
    assert(vectorDeDistancias != NULL);

    entregasVisitadas = (int *) malloc(numeroEntregas * sizeof(int) );
    assert(entregasVisitadas != NULL);

    distanciaMasCorta = (Ruta *) malloc(numeroEntregas * sizeof(Ruta) );
    assert(distanciaMasCorta != NULL);

    /* Se obtienen las "numeroEntregas" mejores rutas, en donde lo que diferencia a cada una
       es el numero de entrega que al que se dirige después de la ubicación actual. Luego de
       la primera entrega por la que se pasa, se va construyendo la ruta dirigiendose a la
       entrega más cercana dependiendo de la entrega en la que se encuentra en el momento.
       También se considera que no se puede pasar por la misma entrega más de una vez.*/
    for(i = 0; i < numeroEntregas; i++){
        // Se dimensiona el arreglo que contiene la secuencia de ids de la ruta 'i' mejor. //
        distanciaMasCorta[i].idEntregas = (int *) malloc(numeroEntregas * sizeof(int) );
        assert(distanciaMasCorta[i].idEntregas != NULL);

        //Se inicialza entregas visitadas en cero//
        for(j = 0; j < numeroEntregas; j++){
            entregasVisitadas[j] = 0;
        }

        // Se inicializa la distancia total de la ruta 'i' mejor. //
        distanciaMasCorta[i].distanciaTotal = 0;

        // Se calcula la distancia entre la ubicación actual y la id que le sigue, y se suma a la distancia total. //
        idEntrega = i + 1;
        aux = (Entrega *) searchMap(Entregas_id, &idEntrega);

        diferenciaX = x - aux->x;
        diferenciaY = y - aux->y;

        distancia = sqrt(pow(diferenciaX,2) + pow(diferenciaY,2) );
        distanciaMasCorta[i].distanciaTotal += distancia;

        // Se agrega el id 'i' a la primera casilla del arreglo que contiene la secuencia de id's. //
        distanciaMasCorta[i].idEntregas[0] = i + 1;

        contRecorrido = 1;
        k = i;
        
        while(contRecorrido < numeroEntregas){
            /* Se asigna la casilla k del arreglo "entregasVisitadas para indicar que ya se visitó la entrega
               id de valor k + 1. */
            entregasVisitadas[k] = 1;

            // Se busca la información del id en el mapa "Entregas_id" para acceder a las distancias con otras entregas. //
            idEntrega = k + 1;
            aux = (Entrega *) searchMap(Entregas_id, &idEntrega);

            /* Se guarda todas las distancias en relación a 'idEntrega'. Si ya se visitó un id, en el vectorDeDistancias
            se marca un -1 en la casilla(s) correspondiente(s). */
            for(j = 0; j < numeroEntregas; j++){
                if(entregasVisitadas[j] == 1){
                   vectorDeDistancias[j] = -1;
                }else vectorDeDistancias[j] = aux->distancia[j];
            }

            //Se ordena de manera creciente 'vectorDeDistancias'//
            qsort(vectorDeDistancias, numeroEntregas, sizeof(double), comparar);

            /* Se recorre el arreglo del entrega id que contiene las distancias a otras entregas, y se busca la distancia
               validámente menor (disponible / no visitada con anterioridad)*/
            for(j = 0; j < numeroEntregas; j++){
                if( (vectorDeDistancias[contRecorrido] == aux->distancia[j]) && (entregasVisitadas[j] != 1) ){
                    idEntrega = j+1;
                    break;
                }
            }

            // Se suma la distancia menor a la distancia total y se agrega el siguiente id de la secuencia. //
            distanciaMasCorta[i].distanciaTotal += aux->distancia[j];
            distanciaMasCorta[i].idEntregas[contRecorrido] = idEntrega;

            k = j;
            contRecorrido++;
        }

        // Se calcula la distancia entre última entrega de la secuencia y la ubicación actual, y se suma a la distancia total. //
        idEntrega = k + 1;
        aux = (Entrega *) searchMap(Entregas_id, &idEntrega);

        diferenciaX = x - aux->x;
        diferenciaY = y - aux->y;

        distancia = sqrt(pow(diferenciaX,2) + pow(diferenciaY,2) );
        distanciaMasCorta[i].distanciaTotal += distancia;
       
    }

    //Se limpia 'vectorDeDistancias' con sus datos para usarlo para guardar las distancias totales de las mejores rutas//     
    for(i = 0; i < numeroEntregas; i++) vectorDeDistancias[i] = 0.00;

    //Se almancena distancia total de cada ruta//
    for(i = 0; i < numeroEntregas; i++){
        vectorDeDistancias[i] = distanciaMasCorta[i].distanciaTotal;
    }

    //Se ordenan de manera creciente las rutas en función de su distancia total//
    qsort( vectorDeDistancias, numeroEntregas, sizeof(double), comparar);

    /*
        Se busca la distancia más corta en el 'distanciaMasCorta' hasta encontrar la 
        distancia que tiene la ruta de la casilla cero del vector 'vectorDeDistancias'.
        Luego De eso se agrega a la posición cero de 'distanciaMasCorta', para lograr 
        tener en la primera casilla, la ruta más eficiente.
    */
    for(i = 0; i < numeroEntregas; i++){
        if(vectorDeDistancias[0] == distanciaMasCorta[i].distanciaTotal){
            if(i > 0){
                distanciaMasCorta[0].distanciaTotal = distanciaMasCorta[i].distanciaTotal;

                for(j = 0; j < numeroEntregas; j++){
                    distanciaMasCorta[0].idEntregas[j] = distanciaMasCorta[i].idEntregas[j];
                }
            }

            distanciaMasCorta[0].x = x;
            distanciaMasCorta[0].y = y;

            distanciaMasCorta = (Ruta*) realloc(distanciaMasCorta, sizeof(Ruta));
        }
    }

    // Se imprime por pantalla la ruta (secuencia de id's de cada entrega) y la distancia total recorrida. //
    if(numeroEntregas < 10){
        caracteres = (numeroEntregas*3 + 2);
    }else caracteres = (numeroEntregas-9)*4 + 29;

    sprintf(num, "%d", distanciaMasCorta->x);
    caracteresCoordenadaX = strlen(num);

    sprintf(num, "%d", distanciaMasCorta->y);
    caracteresCoordenadaY = strlen(num);
    
    printf(" ");
    for( k = 0; k < caracteres + 2 * (caracteresCoordenadaX + caracteresCoordenadaY) + 44; k++) printf("-");
    printf("\n");

    printf("| MEJOR RUTA");
    for( k = 0; k < caracteres + 2 *(caracteresCoordenadaX + caracteresCoordenadaY) + 4; k++) printf(" ");
    printf(" | DISTANCIA TOTAL RECORRIDA |\n ");

    for( k = 0; k < caracteres + 2 *(caracteresCoordenadaX + caracteresCoordenadaY) + 44; k++) printf("-");

    printf("\n| ( %d , %d )->", distanciaMasCorta->x, distanciaMasCorta->y);

    for( i = 0; i < numeroEntregas; i++){
        printf("%d->", distanciaMasCorta->idEntregas[i]);
    }

    printf("( %d , %d )", distanciaMasCorta->x, distanciaMasCorta->y);

    printf(" | %.4lf", distanciaMasCorta->distanciaTotal);
    sprintf(num, "%.4lf", distanciaMasCorta->distanciaTotal);
    espacios = 25 - strlen(num);
    for( k = 0; k < espacios; k++) printf(" ");
    printf(" |\n ");
    
    for( k = 0; k < caracteres + 2 * (caracteresCoordenadaX + caracteresCoordenadaY) + 44; k++) printf("-");
    printf("\n");

    printf("\nIngrese nombre a su nueva mejor ruta: ");
    scanf("%s", distanciaMasCorta->nombre);

    /* Se busca si existe otra ruta con el nombre ingresado. Si existe se pide al usuario
        que ingrese otro hasta que ingrese un nombre no existente en el mapa. */
    registroNombreRuta = (Ruta*) searchMap(Rutas_nombre, distanciaMasCorta->nombre);

    while( registroNombreRuta != NULL){
        caracteres = strlen(distanciaMasCorta->nombre);
        printf(" ");
        for(k = 0; k < caracteres + 27; k++) printf("-");
        printf("\n| Existe ruta con nombre \"%s\" |\n ", distanciaMasCorta->nombre);
        for(k = 0; k < caracteres + 27; k++) printf("-");
        printf("\n\nIngrese otro nombre: ");
        scanf("%s", distanciaMasCorta->nombre);

        registroNombreRuta = (Ruta *) searchMap(Rutas_nombre, distanciaMasCorta->nombre);
    }
    
    //Se inserta mejor ruta encontrada en el mapa//
    insertMap(Rutas_nombre, distanciaMasCorta->nombre, distanciaMasCorta);

    (*numeroRutas)++;

    free(entregasVisitadas);
    free(vectorDeDistancias);

    printf("\n\n\n");
    getchar();
    return;
}
