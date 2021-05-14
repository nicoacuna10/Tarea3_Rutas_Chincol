#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	int x;
	int y;
	float *distancia;
}Entrega;

int ordenarDeMenorAMayor(const void *a, const void *b)
{
    float *ptrA = (float *)a;
    float *ptrB = (float *)b;

    return *ptrA - *ptrB;
}

void mostrar3EntregasMasCercanas(Entrega *E, int numeroEntregas){

    if(E == NULL){
        printf("Primero importar un archivo .txt !\n\n");
        return;
    }

    int x, y;

    printf("Ingrese coordenada x: ");
    scanf("%d", &x);

    printf("Ingrese coordenada y: ");
    scanf("%d", &y);

    float *DistanciasEP = (float*)malloc(numeroEntregas * sizeof(float));
    int i, diferenciaX, diferenciaY;

    for(i = 0; i < numeroEntregas; i++){

        diferenciaX = x - E[i].x;
        diferenciaY = y - E[i].y;
        DistanciasEP[i] = sqrt( pow(diferenciaX, 2) + pow(diferenciaY, 2) );
        printf("%d | %.2f\n", i+1, DistanciasEP[i]);
    }

    float *CopiaDistanciasEP = (float *)malloc(numeroEntregas * sizeof(float));

    for(i = 0; i < numeroEntregas; i++){
        CopiaDistanciasEP[i] = DistanciasEP[i];
    }


    qsort( CopiaDistanciasEP, numeroEntregas, sizeof(float), ordenarDeMenorAMayor);


    printf(" ------------------------------------\n");
    printf("| ID  | DISTANCIA A POSICION ACTUAL  |\n");
    printf(" ------------------------------------\n");

    int espacios, j, k;
    char num[10];

    if( numeroEntregas >= 3){

        for( i = 0; i < 3; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j]){

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
    }else{

        for( i = 0; i < numeroEntregas; i++){

            for(j = 0; j < numeroEntregas; j++){

                if(CopiaDistanciasEP[i] == DistanciasEP[j]){

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
    }

    return;

}