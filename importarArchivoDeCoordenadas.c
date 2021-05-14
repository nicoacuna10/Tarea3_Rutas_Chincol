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

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

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

    printf("Ingrese nombre archivo .txt: ");
    scanf("%[^\n]s", nombre_archivo);
    getchar();

    FILE *fp = fopen(nombre_archivo, "r");
    if(fp == NULL){
        printf("\nArchivo no encontrado\n");
        return;
    }

    printf("\nIngrese numero de entregas: ");
    scanf("%d", &(*numeroEntregas) );

    *Entregas_id = createMap(is_equal_int);

    char *leer_linea, auxX[6], auxY[6], linea[11];
    Entrega *E;
    

    int i, j, l, posicion;
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
        
        printf("%s", leer_linea);
        E->x = atoi(auxX);
        E->y = atoi(auxY);
        E->id = i + 1;
        printf("Entrega %d: %d %d\n", E->id, E->x, E->y);

        insertMap(*Entregas_id, &E->id, E);
    }

    // TESTING //
    Entrega *test = (Entrega*) firstMap(*Entregas_id);
    while(test != NULL){
        printf("Entrega %d : (%d , %d)\n", test->id, test->x, test->y);
        test = (Entrega*) nextMap(*Entregas_id);
    }
    // FIN TESTING //

    Map *CopiaEntregas_id = createMap(is_equal_int);
    
    E = (Entrega*)firstMap(*Entregas_id);
    while(E){
        insertMap(CopiaEntregas_id, &E->id, E);
        E = (Entrega*)nextMap(*Entregas_id);
    }
    

    int diferenciaX, diferenciaY;

    Entrega *registro1 = (Entrega*) firstMap(*Entregas_id);

    while(registro1){

        registro1->distancia = (float*)malloc(*numeroEntregas * sizeof(float));

        Entrega *registro2 = (Entrega*) firstMap(CopiaEntregas_id);

        while(registro2){

            if(registro1->id != registro2->id){
                diferenciaX = registro2->x - registro1->x;
                diferenciaY = registro2->y - registro1->y;
                registro1->distancia[registro2->id-1] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

            }else registro1->distancia[registro2->id-1] = 0;

            printf("%d - %d : %.2f\n", registro1->id, registro2->id, registro1->distancia[registro2->id-1]);
            registro2 = (Entrega*) nextMap(CopiaEntregas_id);
        }
        registro1 = (Entrega*) nextMap(*Entregas_id);
        
    }

    free(CopiaEntregas_id);
    


    printf("\n\n");

    return;
}