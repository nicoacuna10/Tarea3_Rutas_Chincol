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

typedef struct{
    char nombre[100];
    int *idEntregas;
    float distanciaTotal;
}Ruta;

void menu();

void importarArchivoDeCoordenadas(char *nombre_archivo, Map **Entregas_id, int *numeroEntregas);
void distanciaEntreEntregas(Map *Entregas_id, int numeroEntregas);
void mostrar3EntregasMasCercanas(Map *Entregas_id, int numeroEntregas);
void crearRuta(Map *Entregas_id, List *ListaDeRutasCreadas, int numeroEntregas, int *numeroRutas);
void generarRutaAleatoria(Map *Entregas_id, List *ListaDeRutasCreadas, int numeroEntregas, int *numeroRutas);
//void mejorarRuta();
void mostrarRutas(List* ListaDeRutasCreadas, int numeroRutas);
//void mejorRuta();


int main(){

char nombre_archivo[100];
int opcion, numeroEntregas = 0, numeroRutas = 0;

// Inicialización del mapa en NULL. //
Map *Entregas_id = NULL;
	
/* Creación de Lista que almacena las rutas creadas o modificadas por el usuario, o generadas aleatoriamente.
   Almacena datos "Ruta" que contienen el nombre de la ruta, un arreglo que almacena los id's de las entregas
   en relación del recorrido, y la distancia total.*/
List *ListaDeRutasCreadas = createList();



	do{
		menu(&opcion);
		if(opcion == 0) break;
		if(opcion == 1) importarArchivoDeCoordenadas(nombre_archivo, &Entregas_id, &numeroEntregas);
		if(opcion == 2) distanciaEntreEntregas(Entregas_id, numeroEntregas);
		if(opcion == 3) mostrar3EntregasMasCercanas(Entregas_id, numeroEntregas);
		if(opcion == 4) crearRuta(Entregas_id, ListaDeRutasCreadas, numeroEntregas, &numeroRutas);
		if(opcion == 5) generarRutaAleatoria(Entregas_id, ListaDeRutasCreadas, numeroEntregas, &numeroRutas);
		//if(opcion == 6) mejorarRuta();
		if(opcion == 7) mostrarRutas(ListaDeRutasCreadas, numeroRutas);
		//if(opcion == 8) mejorRuta();
	}while(opcion != 0);

	printf(" ----------------------------\n");
	printf("| Adios !                    |\n");
	printf("| Que tenga buen dia.        |\n");
	printf(" ----------------------------\n\n");
	return 0;

	return 0;
}
