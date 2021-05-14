#include <stdio.h>
#include <string.h>

void menu(int *opcion){
    char entrada[5000];

    do{
        memset(entrada, '\0', 5000);
        printf(" ------------------------------------------\n");
        printf("|       Menu principal del programa        |\n");
        printf(" ------------------------------------------\n");
        printf("| Opcion 1: Importar archivo de coordeandas|\n");
        printf("| Opcion 2: Distancia entre entregas       |\n");
        printf("| Opcion 3: Mostrar 3 entregas mas cercanas|\n");
        printf("| Opcion 4: Crear ruta                     |\n");
        printf("| Opcion 5: Generar ruta aleatoria         |\n");
        printf("| Opcion 6: Mejorar ruta                   |\n");
        printf("| Opcion 7: Mostrar rutas                  |\n");
        printf("| Opcion 8: Mejor ruta                     |\n");
        printf("| Opcion 0: Salir del programa             |\n");
        printf(" ------------------------------------------\n\n");

        //Lectura de opción//
        printf(" Elija una opcion:  ");
        scanf("%[^\n]s", entrada);
        getchar();

        if(entrada[1] != '\0' || entrada[0] > '8'){
            printf(" ---------------------\n");
            printf("| Entrada no valida!! |\n");
            printf(" ---------------------\n\n");
            printf(" -----------------------\n");
            printf("| ingrese opcion valida |\n");
            printf(" -----------------------\n\n");
        }
    }while( (entrada[0] < '0' || entrada[0] > '8') && (entrada[1] != '\0') );

    //Se entrega valor a int por referencia//
    *opcion = entrada[0] - 48;

    return;
}