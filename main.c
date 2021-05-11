#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(int *opcion);

//void importarArchivoDeCoordenadas();
//void distanciaEntreEntregas();
//void mostrar5EntregasMasCercanas();
//void crearRuta();
//void generarRutaAleatoria();
//void mejorarRuta();
//void mostrarRutas();
//void mejorRuta();


int main(){
	int opcion;

	do{
		menu(&opcion);
		if(opcion == 0) break;
		//if(opcion == 1) importarArchivoDeCoordenadas();
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
}