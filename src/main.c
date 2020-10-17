 /*==================[inclusions]=============================================*/
#include "sapi.h"              // <= sAPI header
#include "chip_lpc43xx.h"              // <= sAPI header
#include "si5351a.h"

/*==================[macros and definitions]=================================*/
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main(void){

      /* Inicializar la placa */
   boardConfig();
   
   si5351aInit();
   si5351aSetFrequency(10000000);
   while(TRUE)
   {
	   if (!gpioRead(TEC1))
		   si5351aSetFrequency(10000000);
	   if (!gpioRead(TEC2))
		   si5351aSetFrequency(25000000);
	   if (!gpioRead(TEC3))
		   si5351aSetFrequency(50000000);
	   if (!gpioRead(TEC4))
		   si5351aSetFrequency(100000000);
   }


   return 0 ;
}

/*==================[end of file]============================================*/
