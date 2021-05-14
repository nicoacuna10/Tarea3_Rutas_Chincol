#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "list.h"

typedef struct{
	int id;
	int x;
	int y;
	float *distancia;
}Entrega;

void menu();

void importarArchivoDeCoordenadas(char *nombre_archivo, Map **Entregas_id, int *numeroEntregas);
void distanciaEntreEntregas(Map *Entregas_id);
void mostrar3EntregasMasCercanas(Map *Entregas_id, int numeroEntregas);
void crearRuta(Map *Entregas_id, List *ListaDeRutasCreadas, int numeroEntregas);
//void generarRutaAleatoria();
//void mejorarRuta();
//void mostrarRutas();
//void mejorRuta();


int main(){

char nombre_archivo[100];
int opcion, numeroEntregas = 0;
Map *Entregas_id = NULL;
List *ListaDeRutasCreadas = createList();



	do{
		menu(&opcion);
		if(opcion == 0) break;
		if(opcion == 1) importarArchivoDeCoordenadas(nombre_archivo, &Entregas_id, &numeroEntregas);
		if(opcion == 2) distanciaEntreEntregas(Entregas_id);
		if(opcion == 3) mostrar3EntregasMasCercanas(Entregas_id, numeroEntregas);
		if(opcion == 4) crearRuta(Entregas_id, ListaDeRutasCreadas, numeroEntregas);
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