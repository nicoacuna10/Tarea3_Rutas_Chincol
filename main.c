#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int id;
	int x;
	int y;
}Entrega;

void menu();

void importarArchivoDeCoordenadas(char *nombre_archivo, Entrega *E, int numeroEntregas);
//void distanciaEntreEntregas();
//void mostrar5EntregasMasCercanas();
//void crearRuta();
//void generarRutaAleatoria();
//void mejorarRuta();
//void mostrarRutas();
//void mejorRuta();


int main(){

char nombre_archivo[100];
int opcion, numeroEntregas;

printf("\n\nIngrese numero de entregas: ");
scanf("%d", &numeroEntregas);

printf("\n\n");

Entrega *E = (Entrega*) malloc(numeroEntregas * sizeof(Entrega));



	do{
		menu(&opcion);
		if(opcion == 0) break;
		if(opcion == 1) importarArchivoDeCoordenadas(nombre_archivo, E, numeroEntregas);
		//if(opcion == 2) distanciaEntreEntregas();
		//if(opcion == 3) mostrar5EntregasMasCercanas();
		//if(opcion == 4) crearRuta();
		//if(opcion == 5) generarRutaAleatoria();
		//if(opcion == 6) mejorarRuta();
		//if(opcion == 7) mostrarRutas();
		//if(opcion == 8) mejorRuta();
	}while(opcion != 0);

	printf(" ----------------------------\n");
	printf("| Adios !                    |\n");
	printf("| Que tenga buen dia.        |\n");
	printf(" ----------------------------\n\n");
	return 0;

	return 0;
}