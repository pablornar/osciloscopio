/*============================================================================
 * Autor: Pablo Narvaez
 * Licencia:
 * Fecha: 20/10/2020
 *===========================================================================*/

// Bibliotecas
#include "sapi.h"        // <= Biblioteca sAPI
#include "inicio.h"
#include "secuencialed.h"
#include "lectura.h"
#include "semaforo.h"         // <= Su propia cabecera



/* Variables Globales*/



//Prototipos de funciones---------------
void borrarleds(void);

void lecturateclado(void);


// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */
   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delay;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
    (500ms = 0,5s) */
   delayConfig(&delay, 100);

   /*Variables locales al mani*/
   band1 = 1;
   band2 = 0;
   band3 = 0;
   valor1 = 0;
   valor2 = 0;
   valor3 = 0;
   cont=0;
   tempo = 0;


   borrarleds();
   /* ------------- REPETIR POR SIEMPRE ------------- */
   while (1) {
      if (delayRead(&delay)) { // delayRead retorna TRUE cuando se cumple el tiempo de retardo
         cont = cont + 1;
         /*
         if (tempo == 0) {
         	delayConfig(&delay, 100);
         } else if (tempo == 1) {
         	delayConfig(&delay, 100);
         } else if (tempo == 2) {
         	delayConfig(&delay, 100);
         }
          */
         lecturateclado();
         secuencialed();
      }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
    por ningun S.O. */
   return 0;
}


//-----------------Funciones------------------------------
void borrarleds()
{
   gpioWrite(LEDB, OFF);
   gpioWrite(LED3, OFF);
   gpioWrite(LED2, OFF);
   gpioWrite(LED1, OFF);
}



