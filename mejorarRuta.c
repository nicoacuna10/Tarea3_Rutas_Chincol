#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Map.h"

void mejorarRuta(Map *Entregas_id, int numeroRutas){
    //Se corrobora que se ingresaron rutas//
    if(Entregas_id == NULL){
        printf("Por favor importe archivo .txt antes de ingresar a esta funcion\n\n");
        return;
    }

    //Lista de variables//
    int  idRuta = 0;
    int  selecionDeModificacionDeRuta = -1; 
    bool modificacionRutaManual = false;
    bool modificacionRutaAutomatica = false;

    //Se pide id de ruta//
    while(idRuta < 1 || idRuta > numeroRutas){
        printf("Por favor ingrese id de la ruta a mejorar: ");
        scanf("%d", &idRuta);
        if( (idRuta < 1) || (idRuta > numeroRutas) ){
            printf("Id no valida! Ingrese elemento valido a continuacion\n\n");
        }
    }

    //Se pide saber si se quiere modificar ruta automáticamente o maualmente//
    //si se entrega 0 es manual, si es 1 es automática///
    while( (selecionDeModificacionDeRuta < 0 ) || (selecionDeModificacionDeRuta > 1) ){
        printf("Por favor ingrese numero 0 si se quiere modificar manualmente o 1 si se quiere modificar aleatoriamente: ");
        scanf("%d", &selecionDeModificacionDeRuta);
        if( (selecionDeModificacionDeRuta < 0) || (selecionDeModificacionDeRuta > 1) ){
            printf("Opcion invalida!!\n");
            printf("Por favor ingrese opcion valida a continuacion!!\n\n");
        }
    }

    //Se asgina valor de verdad segun comportamiento de usuari@//
    if(selecionDeModificacionDeRuta == 0) modificacionRutaManual = true;
    if(selecionDeModificacionDeRuta == 1) modificacionRutaAutomatica = true;

    //Seccion donde se trabaja pensando en que modificacion es manual//
    if(modificacionRutaManual){







    }else if(modificacionRutaAutomatica){








    }


    return;
}