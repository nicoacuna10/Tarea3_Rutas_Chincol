#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int x;
	int y;
	float *distancia;
}Entrega;

void menu();

Entrega *importarArchivoDeCoordenadas(char *nombre_archivo, Entrega *E, int *numeroEntregas);
void distanciaEntreEntregas(Entrega *E);
void mostrar3EntregasMasCercanas(Entrega *E, int numeroEntregas);
//void crearRuta();
//void generarRutaAleatoria();
//void mejorarRuta();
//void mostrarRutas();
//void mejorRuta();


int main(){

char nombre_archivo[100];
int opcion, numeroEntregas = 0;
Entrega *E = NULL;



	do{
		menu(&opcion);
		if(opcion == 0) break;
		if(opcion == 1) E = importarArchivoDeCoordenadas(nombre_archivo, E, &numeroEntregas);
		if(opcion == 2) distanciaEntreEntregas(E);
		if(opcion == 3) mostrar3EntregasMasCercanas(E, numeroEntregas);
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