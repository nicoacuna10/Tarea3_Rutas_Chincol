#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void mejorarRuta(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int numeroRutas){
    //Se corrobora que se ingresaron rutas//
    if(numeroRutas == 0){
        printf("Cree al menos una ruta con la funcion \"Crear ruta\" (opcion 4) o \"Generar ruta aleatoria\" (opcion 5)\n");
        return;
    }

    //Lista de variables//
    char nombre[50];
    int  selecionDeModificacionDeRuta = -1; 
    bool modificacionRutaManual = false;
    bool modificacionRutaAutomatica = false;
    Ruta *aux = NULL;
    Ruta rutaModificada;

    int id1, id2, i;
    int posicion1, posicion2;
    Entrega *buscadorID = NULL;
    float distancia;
    int diferenciaX, diferenciaY;
    int intercambio;

    //Se pide nombre de ruta//
    printf("Por favor ingrese nombre de la ruta a mejorar: ");
    scanf("%s", nombre);
    
    aux = (Ruta*) searchMap(Rutas_nombre, nombre);

    // En caso de que no encontrase nombre, se cierra función. //
    if(aux == NULL){
        printf(" ------------------------------------\n");
        printf("| No existe nombre de ruta ingresado |\n");
        printf(" ------------------------------------\n\n");
        getchar();
        return;
    }

    /* En el caso que la cantidad de entregas sea entre 1 y 2 se cierra la función,
       porque el intercambio no cambia la distancia total. */
    if(numeroEntregas == 1 || numeroEntregas == 2){
        printf("No existe distancia mas corta para la ruta \"%s\"\n", nombre);
        getchar();
        return;
    }

    rutaModificada = *aux;
    
    //Se pide saber si se quiere modificar ruta automáticamente o maualmente//
    //si se entrega 0 es manual, si es 1 es automática///
    while( (selecionDeModificacionDeRuta < 0 ) || (selecionDeModificacionDeRuta > 1) ){
        printf("Por favor ingrese numero 0 si se quiere modificar manualmente o 1 si se quiere modificar aleatoriamente: ");
        scanf("%d", &selecionDeModificacionDeRuta);
        if( (selecionDeModificacionDeRuta < 0) || (selecionDeModificacionDeRuta > 1) ){
            printf("Opcion invalida!!\n");
            printf("Por favor ingrese opcion valida a continuacion!!\n\n");
        }
    }

    //Se asgina valor de verdad segun comportamiento de usuari@//
    if(selecionDeModificacionDeRuta == 0) modificacionRutaManual = true;
    if(selecionDeModificacionDeRuta == 1) modificacionRutaAutomatica = true;

    //Seccion donde se trabaja pensando en que modificacion es manual//
    if(modificacionRutaManual){

        printf("\nIngrese primer id de entrega a intercambiar: ");
        scanf("%d", &id1);

        while(id1 < 0 || id1 > numeroEntregas){
            printf("\nIngrese id valido: ");
            scanf("%d", id1);
        }

        printf("\nIngrese segundo id de entrega a intercambiar: ");
        scanf("%d", &id2);

        while(id2 < 0 || id2 > numeroEntregas || id1 == id2){
            printf("\nIngrese id valido: ");
            scanf("%d", &id2);
        }

    }else if(modificacionRutaAutomatica){

        id1 = (rand() % numeroEntregas) + 1;

        do{
            id2 = (rand() % numeroEntregas) + 1;
        }while(id1 == id2);

        printf("\nSe hace intercambio de posiciones de id's %d y %d\n", id1, id2);
    }

    /* Se localiza la posicion de los id's en el arreglo. Se resta a la distancia total las distancias
           con las entregas anteriores y posteriores de los id's a intercambiar. Se consideran 3 casos:
           1.- El id no se encuentra en ninguno de los extremos de la ruta.
           2.- El id se encuentra en el final de la ruta.
           3.- El id se encuentra en el inicio de la ruta. */
    for(i = 0; i < numeroEntregas; i++){

        if(rutaModificada.idEntregas[i] == id1){
            posicion1 = i;
            buscadorID = (Entrega*) searchMap(Entregas_id, &id1);

            // CASO ID1 EN MEDIO DE LA RUTA. //
            if(i > 0 && i < numeroEntregas - 1){

                distancia = buscadorID->distancia[rutaModificada.idEntregas[i-1]-1];
                rutaModificada.distanciaTotal -=distancia;

                distancia = buscadorID->distancia[rutaModificada.idEntregas[i+1]-1];
                rutaModificada.distanciaTotal -=distancia;

                // CASO ID1 AL FINAL DE LA RUTA. //
            }else if(i > 0 && i == numeroEntregas - 1){

                distancia = buscadorID->distancia[rutaModificada.idEntregas[i-1]-1];
                rutaModificada.distanciaTotal -=distancia;

                diferenciaX = rutaModificada.x - buscadorID->x;
                diferenciaY = rutaModificada.y - buscadorID->y;
                distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

                rutaModificada.distanciaTotal -=distancia;

                // CASO ID1 AL INICIO DE LA RUTA. //
            }else if(i == 0 && i < numeroEntregas - 1){

                diferenciaX = rutaModificada.x - buscadorID->x;
                diferenciaY = rutaModificada.y - buscadorID->y;
                distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

                rutaModificada.distanciaTotal -=distancia;
                
                distancia = buscadorID->distancia[rutaModificada.idEntregas[i+1]-1];
                rutaModificada.distanciaTotal -=distancia;
            }
        }

        if(rutaModificada.idEntregas[i] == id2){
            posicion2 = i;
            buscadorID = (Entrega*) searchMap(Entregas_id, &id2);

            // CASO ID2 EN MEDIO DE LA RUTA. //
            if(i > 0 && i < numeroEntregas - 1){

                distancia = buscadorID->distancia[rutaModificada.idEntregas[i-1]-1];
                rutaModificada.distanciaTotal -=distancia;

                distancia = buscadorID->distancia[rutaModificada.idEntregas[i+1]-1];
                rutaModificada.distanciaTotal -=distancia;

                // CASO ID2 AL FINAL DE LA RUTA. //
            }else if(i > 0 && i == numeroEntregas - 1){

                distancia = buscadorID->distancia[rutaModificada.idEntregas[i-1]-1];
                rutaModificada.distanciaTotal -=distancia;

                diferenciaX = rutaModificada.x - buscadorID->x;
                diferenciaY = rutaModificada.y - buscadorID->y;
                distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

                rutaModificada.distanciaTotal -=distancia;

                // CASO ID2 AL INICIO DE LA RUTA. //
            }else if(i == 0 && i < numeroEntregas - 1){

                diferenciaX = rutaModificada.x - buscadorID->x;
                diferenciaY = rutaModificada.y - buscadorID->y;
                distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

                rutaModificada.distanciaTotal -=distancia;
                
                distancia = buscadorID->distancia[rutaModificada.idEntregas[i+1]-1];
                rutaModificada.distanciaTotal -=distancia;
            }
        }

    }

    // Se hace el intercambio. ID1 pasa a la posición de ID2. ID2 pasa a la posición de ID1.//
    intercambio = rutaModificada.idEntregas[posicion1];
    rutaModificada.idEntregas[posicion1] = rutaModificada.idEntregas[posicion2];
    rutaModificada.idEntregas[posicion2] = intercambio;

    // Se hace las sumas de las distancias luego del intercambio. //
    buscadorID = (Entrega*) searchMap(Entregas_id, &id2);
    if(posicion1 > 0 && posicion1 < numeroEntregas - 1){

        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion1 - 1]-1];
        rutaModificada.distanciaTotal +=distancia;

        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion1 + 1]-1];
        rutaModificada.distanciaTotal +=distancia;

    }else if(posicion1 > 0 && posicion1 == numeroEntregas - 1){

        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion1 - 1]-1];
        rutaModificada.distanciaTotal +=distancia;

        diferenciaX = rutaModificada.x - buscadorID->x;
        diferenciaY = rutaModificada.y - buscadorID->y;
        distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

        rutaModificada.distanciaTotal +=distancia;

    }else if(posicion1 == 0 && posicion1 < numeroEntregas - 1){

        diferenciaX = rutaModificada.x - buscadorID->x;
        diferenciaY = rutaModificada.y - buscadorID->y;
        distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

        rutaModificada.distanciaTotal +=distancia;
        
        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion1 + 1]-1];
        rutaModificada.distanciaTotal +=distancia;
    }

    buscadorID = (Entrega*) searchMap(Entregas_id, &id1);
    if(posicion2 > 0 && posicion2 < numeroEntregas - 1){

        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion2 - 1]-1];
        rutaModificada.distanciaTotal +=distancia;

        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion2 + 1]-1];
        rutaModificada.distanciaTotal +=distancia;

    }else if(posicion2 > 0 && posicion2 == numeroEntregas - 1){

        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion2 - 1]-1];
        rutaModificada.distanciaTotal +=distancia;

        diferenciaX = rutaModificada.x - buscadorID->x;
        diferenciaY = rutaModificada.y - buscadorID->y;
        distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

        rutaModificada.distanciaTotal +=distancia;

    }else if(posicion2 == 0 && posicion2 < numeroEntregas - 1){

        diferenciaX = rutaModificada.x - buscadorID->x;
        diferenciaY = rutaModificada.y - buscadorID->y;
        distancia = sqrt( pow(diferenciaX, 2) + pow(diferenciaY,2) );

        rutaModificada.distanciaTotal +=distancia;
        
        distancia = buscadorID->distancia[rutaModificada.idEntregas[posicion2 + 1]-1];
        rutaModificada.distanciaTotal +=distancia;
    }

    // Se hace la comparación con la distancia previa al intercambio //
    if(rutaModificada.distanciaTotal < aux->distanciaTotal){
        printf("Distancia Ruta \"%s\" antes del intercambio: %.2f\n", nombre, aux->distanciaTotal);

        aux->distanciaTotal = rutaModificada.distanciaTotal;
        aux->idEntregas[posicion1] = id2;
        aux->idEntregas[posicion2] = id1;
        
        printf("Distancia Ruta \"%s\" despues del intercambio: %.2f\n\n", nombre, aux->distanciaTotal);
        
        printf(" -----------------\n");
        printf("| Ruta modificada |\n");
        printf(" -----------------\n");
    }else{
        printf("Distancia Ruta \"%s\" antes del intercambio: %.2f\n", nombre, aux->distanciaTotal);
        printf("Distancia Ruta \"%s\" despues del intercambio: %.2f\n\n", nombre, rutaModificada.distanciaTotal);

        printf(" --------------------\n");
        printf("| Ruta no modificada |\n");
        printf(" --------------------\n");
    }

    getchar();
    return;
}