#include <stdio.h>
#include <stdbool.h>
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

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

void importarArchivoDeCoordenadas(char *nombre_archivo, Map **Entregas_id, int *numeroEntregas){

    if(*Entregas_id != NULL) return;

    // Declaración de variables //
    FILE *fp;
    bool entradaValida;
    int contador, i, j, l, posicion, diferenciaX, diferenciaY;
    char cadena[60], *leer_linea, auxX[6], auxY[6], linea[11];
    Entrega *E = NULL, *registro1 = NULL, *registro2 = NULL;
    Map *CopiaEntregas_id = NULL;
	
    printf("Ingrese nombre archivo .txt: ");
    scanf("%[^\n]s", nombre_archivo);
    getchar();

    fp = fopen(nombre_archivo, "r");
    //Caso donde no se encuentra el archivo//
    if(fp == NULL){
        printf("\n");
        printf(" -----------------------\n");
        printf("| Archivo no encontrado |\n");
        printf(" -----------------------\n\n");
        return;
    }

    entradaValida = false;
    //Se lee entregas por usuario a procesar//
    while(entradaValida == false){
        printf("\n\nIngrese numero de entregas: ");
        scanf("%d", &(*numeroEntregas) );
        getchar();
        if( *numeroEntregas > 0)
            entradaValida = true;
        else{
            printf("\n -------------------------------------\n");
            printf("|Entrada no valida!                   |\n");
            printf("|Se debe ingresar numero mayor a cero |\n");
            printf(" -------------------------------------\n\n");
        }
    }

    //Se corrobora que el archivo ingresado tenga mayor o igual entregas a 'numeroEntregas'//
    contador = 1;
    while( (fgets(cadena,60, fp) ) != NULL){
        contador++;
        memset(cadena, '\0', 60);
    }

    //Se quita contador menos uno por el salto de linea al final del archivo, implementado para correcta lectura//
    contador = contador - 1;
    //Si contador es mayor, usuari@ está entregand entrada errada//
    if( (*numeroEntregas) > contador){
        printf(" \n ---------------------------------------------------------------------------------\n");
        printf("|Numero de entregas es mayor al numero que posee el archivo txt ingresado: %d - %d|\n",*numeroEntregas, contador);
        printf("|Ingrese de nuevo a la funcion y coloque archivo txt adecuado.                    |\n");
        printf(" ---------------------------------------------------------------------------------\n\n");
        rewind(fp);
        fclose(fp);
        return;
    }

    //Se vuelve al inicio el indicador de lecutra del archivo txt, con el fin de procesar datos//
    rewind(fp);

    /*Creación de mapa que almacena el id de la entrega, las coordenadas x e y, y un arreglo dinámico
      con las distancias entre las otras entregas. La clave utilizada para acceder a cada entrega es
      el id*/
    *Entregas_id = createMap(is_equal_int);
    
    /*Se lee cada una de las lineas del archivo de texto, se guarda la coordena x e y, y el id respecto
      de la iteración. Se tiene en consideración los saltos de espacios antes del primer número y entre
      los números. Al final de cada iteración se guarda en el mapa.*/
    for(i = 0; i < *numeroEntregas; i++){

        E = (Entrega*)malloc(sizeof(Entrega));

        leer_linea = fgets(linea, 11, fp);

        j = 0;
        while(leer_linea[j] == ' '){
            j++;
        } 

        l = 0;
        for(j ; leer_linea[j] != ' '; j++){
            auxX[l] = leer_linea[j];
            l++;
        }
        if(leer_linea[j] == ' ') auxX[l] = '\0';

        j = 4;
        while(leer_linea[j] == ' '){
            j++;
        } 

        l = 0;
        for(j ; leer_linea[j] != '\0'; j++){
            auxY[l] = leer_linea[j];
            l++;
        }
        
        E->x = atoi(auxX);
        E->y = atoi(auxY);
        E->id = i + 1;

        insertMap(*Entregas_id, &E->id, E);
    }

    fclose(fp);
	
    // Se realiza una copia del mapa que se utilizará posteriormente para calcular las distancias. //
    CopiaEntregas_id = createMap(is_equal_int);
    E = (Entrega*)firstMap(*Entregas_id);
    while(E){
        insertMap(CopiaEntregas_id, &E->id, E);
        E = (Entrega*)nextMap(*Entregas_id);
    }
    
    /* Se Calcula la distancia entre las entregas, para eso se necesita recorrer el mapa con la
       información de las entregas y su copia (creada anteriormente). En cada nueva interación
       del recorrido del primer mapa, se dimensiona el arreglo 'distancia' con tamaño el numero de
       entregas. En cada iteración del recorrido de la copia, se compara si las entregas tienen
       distinto id, si se cumple, se calcula la distancia y se almacena en una determinada
       posición del arreglo. La posición es respecto del id de la entrega a la que se dirige menos
       1. Por ejemplo, se calcula la distancia entre las entrega id 1 - 4, el valor debe almacenarse
       en la casilla 3 del arreglo distancia de la entrega 1. En el caso que los id's sean iguales
       se almacena el valor cero en la casilla correspondiente.*/

    registro1 = (Entrega*) firstMap(*Entregas_id);

    while(registro1){

        registro1->distancia = (double*)malloc(*numeroEntregas * sizeof(double));

        registro2 = (Entrega*) firstMap(CopiaEntregas_id);

        while(registro2){

            if(registro1->id != registro2->id){
                diferenciaX = registro2->x - registro1->x;
                diferenciaY = registro2->y - registro1->y;
                registro1->distancia[registro2->id-1] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

            }else registro1->distancia[registro2->id-1] = 0;

            registro2 = (Entrega*) nextMap(CopiaEntregas_id);
        }
        registro1 = (Entrega*) nextMap(*Entregas_id);
        
    }
    
    // Se libera la copia del mapa. //
    free(CopiaEntregas_id);
    printf("\n");
    printf(" ---------------------------------\n");
    printf("| Importacion realizada con exito |\n");
    printf(" ---------------------------------\n\n");

    return;
}
