#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char c[6];
}Coordenadas;

typedef struct{
	int id;
	int x;
	int y;
}Entrega;

void importarArchivoDeCoordenadas(char *nombre_archivo, Entrega *E, int numeroEntregas){

    printf("Ingrese nombre archivo .txt: ");
    scanf("%[^\n]s", nombre_archivo);
    getchar();

    FILE *fp = fopen(nombre_archivo, "r");
    if(fp == NULL){
        printf("\nArchivo no encontrado\n");
        return;
    }

    char *aux, linea[21];
    Coordenadas auxCoordenada[2]; 

    int i, j, k, l, posicion;
    for(i = 0; i < numeroEntregas; i++){
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
        E[i].id = i+1; 
        printf("Entrega %d: %d %d\n", E[i].id, E[i].x, E[i].y);
    }

    return;


}