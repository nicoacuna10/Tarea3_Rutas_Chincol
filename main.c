#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

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
	int x;
	int y;
}Ruta;

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

void menu();

void importarArchivoDeCoordenadas(char *nombre_archivo, Map **Entregas_id, int *numeroEntregas);
void distanciaEntreEntregas(Map *Entregas_id, int numeroEntregas);
void mostrar3EntregasMasCercanas(Map *Entregas_id, int numeroEntregas);
void crearRuta(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int *numeroRutas);
void generarRutaAleatoria(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int *numeroRutas);
void mejorarRuta(Map *Entregas_id, Map *Rutas_nombre, int numeroEntregas, int numeroRutas);
void mostrarRutas(Map *Rutas_nombre, int numeroEntregas, int numeroRutas);
void mejorRuta(Map *Entregas_id,Map *Rutas_nombre, int *numeroRutas, int numeroEntregas, int *contNumeroRutasCreadas);


int main(){

	char nombre_archivo[100];
	int opcion, numeroEntregas = 0, numeroRutas = 0, contMejorRutasCreadas = 0;;

	// Inicialización del mapa en NULL. //
	Map *Entregas_id = NULL;
	
	/* Creación de Mapa que almacena las rutas creadas o modificadas por el usuario, o generadas aleatoriamente.
   	   Almacena datos "Ruta" que contienen el nombre de la ruta, un arreglo que almacena los id's de las entregas
       en relación del recorrido, la distancia total, y las coordenadas de la posición inicial. La clave es el
	   nombre de la ruta. */
	Map *Rutas_nombre = createMap(is_equal_string);
	setSortFunction(Rutas_nombre, lower_than_string); //Comentario: Por que esta esto aqui ?//

	do{
		menu(&opcion);
		if(opcion == 0) break;
		if(opcion == 1) importarArchivoDeCoordenadas(nombre_archivo, &Entregas_id, &numeroEntregas);
		if(opcion == 2) distanciaEntreEntregas(Entregas_id, numeroEntregas);
		if(opcion == 3) mostrar3EntregasMasCercanas(Entregas_id, numeroEntregas);
		if(opcion == 4) crearRuta(Entregas_id, Rutas_nombre, numeroEntregas, &numeroRutas);
		if(opcion == 5) generarRutaAleatoria(Entregas_id, Rutas_nombre, numeroEntregas, &numeroRutas);
		if(opcion == 6) mejorarRuta(Entregas_id, Rutas_nombre, numeroEntregas, numeroRutas);
		if(opcion == 7) mostrarRutas(Rutas_nombre, numeroEntregas, numeroRutas);
		if(opcion == 8) mejorRuta(Entregas_id,Rutas_nombre, &numeroRutas, numeroEntregas, &contMejorRutasCreadas);
	}while(opcion != 0);

	printf("\n");
	printf(" ----------------------------\n");
	printf("| Adios !                    |\n");
	printf("| Que tenga buen dia.        |\n");
	printf(" ----------------------------\n\n");

	free(Entregas_id);
	free(Rutas_nombre);

	return 0;
}
