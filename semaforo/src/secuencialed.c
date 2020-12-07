
// Bibliotecas
#include "sapi.h"        // <= Biblioteca sAPI
#include "inicio.h"
#include "secuencialed.h"

const gpioMap_t secuencia[]=  { LEDB, LED1, LED2, LED3 };

void secuencialed(void)
{
   if (band1==1) {
      if ((cont > 0) && (cont < 30)) {
         gpioWrite(secuencia[1], OFF);
         gpioWrite(secuencia[2], ON);
         gpioWrite(secuencia[3], OFF);
      } else if ((cont > 29) && (cont < 36)) {
         gpioWrite(secuencia[1], ON);
         gpioWrite(secuencia[2], OFF);
         gpioWrite(secuencia[3], OFF);
      } else if ((cont > 35) && (cont < 46)) {
         gpioWrite(secuencia[1], OFF);
         gpioWrite(secuencia[2], OFF);
         gpioWrite(secuencia[3], ON);
         if (cont == 45) {
            cont=0;
         }
      }
   } else if (band2==1) {
      if ((cont > 0) && (cont < 5)) {
         gpioWrite(secuencia[1], ON);
         gpioWrite(secuencia[2], OFF);
         gpioWrite(secuencia[3], OFF);
      } else if ((cont > 4) && (cont < 10)) {
         gpioWrite(secuencia[1], OFF);
         gpioWrite(secuencia[2], OFF);
         gpioWrite(secuencia[3], OFF);
         if (cont==9) {
            cont=0;
         }
      }
   } else if (band3==1) {
      if ((cont > 0) && (cont < 10)) {
         gpioWrite(secuencia[1], ON);
         gpioWrite(secuencia[2], ON);
         gpioWrite(secuencia[3], OFF);
      } else if ((cont > 9) && (cont < 20)) {
         gpioWrite(secuencia[1], OFF);
         gpioWrite(secuencia[2], OFF);
         gpioWrite(secuencia[3], OFF);
         if (cont==19) {
            cont=0;
         }
      }
   }
}