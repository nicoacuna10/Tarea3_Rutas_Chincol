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

    /*Creación de mapa que almacena el id de la entrega, las coordenadas x e y, y un arreglo dinámico
      con las distancias entre las otras entregas. La clave utilizada para acceder a cada entrega es
      el id*/
    *Entregas_id = createMap(is_equal_int);
	
    // Declaración de variables. //
    char *leer_linea, auxX[6], auxY[6], linea[11];
    Entrega *E;
    int i, j, l, posicion;
    
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
	
    // Se realiza una copia del mapa que se utilizará posteriormente para calcular las distancias. //
    Map *CopiaEntregas_id = createMap(is_equal_int);
    E = (Entrega*)firstMap(*Entregas_id);
    while(E){
        insertMap(CopiaEntregas_id, &E->id, E);
        E = (Entrega*)nextMap(*Entregas_id);
    }
    
    /* Se Calcula la distancia entre las entregas, para eso se necesita recorrer el mapa con la
       información de las entregas y su copia (creada anteriormente). En cada nueva interación
       del recorrido del primer mapa, se dimensiona el arreglo distancia con tamaño el numero de
       entregas. En cada iteración del recorrido de la copia, se compara si las entregas tienen
       distinto id, si se cumple, se calcula la distancia y se almacena en una determinada
       posición del arreglo. La posición es respecto del id de la entrega a la que se dirige menos
       1. Por ejemplo, se calcula la distancia entre las entrega id 1 - 4, el valor debe almacenarse
       en la casilla 3 del arreglo de la entrega 1. En el caso que los id's sean iguales se almacena
       el valor cero en la casilla correspondiente.*/
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
    
    // Se libera la copia del mapa- //
    free(CopiaEntregas_id);

    printf("\n\n");

    return;
}
