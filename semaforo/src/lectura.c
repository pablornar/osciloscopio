// Bibliotecas
#include "sapi.h"        // <= Biblioteca sAPI
#include "inicio.h"
#include "lectura.h"


void lecturateclado(void)
{
   valor1 = !gpioRead(TEC1);
   valor2 = !gpioRead(TEC2);
   valor3 = !gpioRead(TEC3);

   if ((valor1 == 1) && (band1 == 0)) {
      band1 = 1;
      band2 = 0;
      band3 = 0;
      cont=0;
      tempo=0;
   } else if ((valor2 == 1) && (band2 == 0)) {
      band2 = 1;
      band1 = 0;
      band3 = 0;
      tempo=1;
      cont=0;
   } else if ((valor3 == 1) && (band3 == 0)) {
      cont=0;
      tempo=2;
      band3 = 1;
      band2 = 0;
      band1 = 0;
   }
}