#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include <string.h>			/* for strcmp */
#include "stdio.h"
#include <mmu_lda.h>			/* MMU page management */

//Inicializacion del MCU

void MCU_Init(void) {
 SOPT1 = 0x23;      /* Watchdog disable. Stop Mode Enable. Background Pin enable. RESET pin enable */  
 SCGC1 = 0x11;     /* Se activa el Bus Clock del ADC y del SCI */
 SCGC2 = 0x00;     /* Disable Bus clock to unused peripherals */
}

//Inicializacion del PTC
void GPIO_Init(void) { 
  PTCDD = 0x3F;          			/* Configracion de los leds del puerto C como salida */
  PTCD = 0x3F;          			/* Se apagan los LEDs del puerto C */
}

//Inicializacion del SCI
void SCI_configuration (void) {		 // Configuracion del SCI
  SCI1C1 = 0x00  ;		/* caracteres de 8 bits, sin bits de paridad */
  SCI1C2 = 0x2C  ;		/* Se activa la transmisión y recepción, se activa la interrupción por recepción */
  SCI1C3 = 0x00  ;		/* Se desactivan todas las interrupciones por ERROR */
  SCI1BDL = 0x1A  ;	/* Este registro junto son el SCI1BDH se usan para configurar  Baud Rate = 9600bps               */
  SCI1BDH = 0x00; 	/*                                  	           BUSCLK               4MHz                      */                      
			/* Velocidad de transmision = -------------------- = ------------ = 9600bps   */
 } 	  	  	/*                              	   [SBR12:SBR0] x 16     26 x 16                     */



/*********************************************************************/
/*  Main Function                                                    */
/*********************************************************************/
void main(void) {
  MCU_Init();       		/* Function que inicializa el MCU */
  GPIO_Init();      			/* Function que inicializa los puertos del MCU */
  SCI_configuration();     		 /* Function que inicializa el modulo SCI */

  EnableInterrupts; 		/* Habilita las interrupciones */

}
//Recepcion
//vector de interrupción por sci para recibir
interrupt VectorNumber_Vsci1rx SCI_RX_ISR(void) {
    char dato;      //Se declaran las variables que recibe el dato que se escribe.
	SCI1S1_RDRF = 0;
    dato = SCI1D;  //El registro SCI1D es donde se guarda el dato que se manda por puerto serial, dicho dato se le asigna a la variable dato.
    while(SCI1S1_TDRE == 0);
    SCI1D = dato;
    
    
    	
}
