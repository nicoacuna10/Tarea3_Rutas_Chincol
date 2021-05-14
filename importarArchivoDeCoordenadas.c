#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    char c[6];
}Coordenadas;

typedef struct{
	int x;
	int y;
    float *distancia;
}Entrega;

Entrega *importarArchivoDeCoordenadas(char *nombre_archivo, Entrega *E, int *numeroEntregas){

    if(E != NULL){
        return E;
    }

    printf("Ingrese nombre archivo .txt: ");
    scanf("%[^\n]s", nombre_archivo);
    getchar();

    FILE *fp = fopen(nombre_archivo, "r");
    if(fp == NULL){
        printf("\nArchivo no encontrado\n");
        return E;
    }

    printf("\nIngrese numero de entregas: ");
    scanf("%d", &(*numeroEntregas) );

    E = (Entrega*)malloc( (*numeroEntregas) * sizeof(Entrega));

    char *aux, linea[21];
    Coordenadas auxCoordenada[2];

    int i, j, l, posicion;
    for(i = 0; i < *numeroEntregas; i++){
        aux = fgets(linea, 21, fp);

        j = 0;
        while(aux[j] == ' '){
            j++;
        } 

        l = 0;
        for(j ; aux[j] != ' '; j++){
            auxCoordenada[0].c[l] = aux[j];
            l++;
        }
        if(aux[j] == ' ') auxCoordenada[0].c[l] = '\0';

        j = 4;
        while(aux[j] == ' '){
            j++;
        } 

        l = 0;
        for(j ; aux[j] != '\0'; j++){
            auxCoordenada[1].c[l] = aux[j];
            l++;
        }
        
        printf("%s", aux);
        E[i].x = atoi(auxCoordenada[0].c);
        E[i].y = atoi(auxCoordenada[1].c);
        printf("Entrega %d: %d %d\n", i+1, E[i].x, E[i].y);
    }

    int diferenciaX, diferenciaY;

    for(i = 0; i < *numeroEntregas; i++){
        E[i].distancia = (float*)malloc( *numeroEntregas *sizeof(float));

        for(j = 0; j < *numeroEntregas; j++){
            
            if(i != j){
                diferenciaX = E[j].x - E[i].x;
                diferenciaY = E[j].y - E[i].y;
                E[i].distancia[j] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );

            }else E[i].distancia[j] = 0;
        } 
    }


    printf("\n\n");

    return E;
}