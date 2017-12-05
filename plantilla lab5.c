/********************************************************************/
/* Project Name:													*/
/* Source fle name:													*/
/********************************************************************/
/********************************************************************/
/* Date:															*/
/* 																	*/
/* 			Dpto de Electronica Universidad Simon Bolivar			*/
/********************************************************************/      


#include <hidef.h> 			/* for EnableInterrupts macro */
#include "derivative.h"		/* include peripheral declarations */
#include <string.h>			/* for strcmp */
#include "stdio.h"
#include <mmu_lda.h>		/* MMU page management */


/********************************************************************/
/*			Define a shortname for variable types					*/
/********************************************************************/

typedef unsigned char		UINT8;  		/*  8 bits */
typedef unsigned short int	UINT16; 		/* 16 bits */
typedef unsigned long int	UINT32; 		/* 32 bits */
typedef signed char			INT8;   		/*  8 bits */
typedef signed short int	INT16;  		/* 16 bits */
typedef signed long int		INT32;  		/* 32 bits */
typedef volatile UINT8		VUINT8;  		/*  8 bits */
typedef volatile UINT16		VUINT16; 		/* 16 bits */
typedef volatile UINT32		VUINT32; 		/* 32 bits */

//#define LCD_STROBE_E ((PTCD_PTCD6 = 1),(PTCD_PTCD6=0));
//void initLCD(void), LCDCmd(UINT8), LCDChar(UINT8), dsplyString(UINT8 *), chkLCDbusy(void);
//void delay(int);


/********************************************************************/
/*					Variables declarations							*/
/********************************************************************/

int i,j;					// Variable contador.
int estado = 1;	   			// Variable para designar el estado en que se encuentre el programa.
int temp;

char M_MENU[10]={'M',':',' ','M','E','N','U',13,10,'/0'};
int M_INICIALES[14]={'I',':',' ','I','N','I','C','I','A','L','E','S',13,10};
int M_FIBONACI[23]={70,58,32,67,97,108,99,117,108,97,114,32,70,73,66,79,78,65,67,67,73,13,10};
int M_FACTORIAL[23]={33,58,32,67,97,108,99,117,108,97,114,32,70,65,67,84,79,82,73,65,76,13,10};
int M_LEIBNIZ[21]={76,58,32,67,97,108,99,117,108,97,114,32,76,69,73,66,78,73,90,13,10};

UINT8 INICIALES[11][61]={
" .----------------.  .----------------.  .----------------. ",
"| .--------------. || .--------------. || .--------------. |",
"| |     _____    | || |   _______    | || |  _________   | |",
"| |    |_   _|   | || |  |_   __  |  | || | |_   ___  |  | |",
"| |      | |     | || |    | |__| |  | || |   | |_  |_|  | |",
"| |   _  | |     | || |    |  ___ |  | || |   |  _|      | |",
"| |  | |_' |     | || |   _| |_      | || |  _| |_       | |",
"| |  `.___.'     | || |  |_____|     | || | |_____|      | |",
"| |              | || |              | || |              | |",
"| '--------------' || '--------------' || '--------------' |",
" '----------------'  '----------------'  '----------------' "
};


/********************************************************************/
/*					Function declarations							*/
/********************************************************************/

void Estado_MENU(void){
	PTCD = 0x3E;
	
	
	
	
	estado = 0;
}

void Estado_INI(void){		// Funcion para mostrar por el Terminal Las iniciales del grupo (ESTADO 2).
	PTCD = 0x3D;
	
	
	
	
	estado = 0;
}

void Estado_FIB(void){		// Funcion para mostrar por el Terminal la serie de FIBONACCI (ESTADO 3).
	PTCD = 0x3C;
	
	
	
	
	estado = 0;	
}

void Estado_LEI(void){		// Funcion para mostrar por el Terminal la serie de LIEBNIZ (ESTADO 4).
	PTCD = 0x3B;
	
	
	
	
	estado = 0;	
}

void Estado_FAC(void){		// Funcion para mostrar por el Terminal la serie Factorial (ESTADO 5).
	PTCD = 0x3A;
	
	
	
	
	estado = 0;	
}

void Estado_NUM(void){		// Funcion para leer el numero N de terminos (ESTADO 6).
	PTCD = 0x39;

	
	
	
	estado = 0;	
}

void Estado_ENT(void){		// Funcion para procesar N y pasarlo a la funcion correspondiente (ESTADO 7).
	PTCD = 0x38;
	
	
	
	
	estado = 0;	
}


/********************************************************************/
/*  				Funciones de inicializacion						*/
/********************************************************************/

void MCU_Init(void) {
  
 SOPT1 = 0x23;          /* Watchdog disable. Stop Mode Enable. Background Pin enable. RESET pin enable */  
 SCGC1 = 0x11;          /* Se activa el Bus Clock del ADC y del SCI */
 SCGC2 = 0x00;          /* Disable Bus clock to unused peripherals */
 
}

void GPIO_Init(void) { 
  
  PTCDD = 0x3F;			/* Configracion de los leds del puerto C como salida */
  PTCD = 0x3F;			/* Se apagan los leds del puerto C */

}

void SCI_configuration (void) {		// Configuracion del SCI
  
  SCI1C1 = 0x00;	/* caracteres de 8 bits, sin bits de paridad 												*/
  SCI1C2 = 0x2C;	/* Se activa la transmicion y recepcion, se activa la interrupcion por recepcion 			*/
  SCI1C3 = 0x00;	/* Se desactivan todas las interrupcoines por ERROR											*/
  SCI1BDL = 0x1A;	/* Este registro junto son el SCI1BDH se usan para configurar la velocidad de transmision	*/
  SCI1BDH = 0x00;	/*                                   BUSCLK               4MHz                				*/                      
					/* Velocidad de transmision = -------------------- = ------------ = 9600bps   				*/
					/*                              [SBR12:SBR0] x 16        26 x 16              				*/
}

/********************************************************************/
/*  						Main Function							*/
/********************************************************************/

void main(void) {

  MCU_Init();					/* Function que initializa el MCU */
  GPIO_Init();					/* Function que initializa los puertos del MCU */
  SCI_configuration();			/* Function que initializa el modulo SCI */
  
  EnableInterrupts;				/* Habilita las interrupciones */

  for(;;) {	  					// Evalua constantemente si se cambia de estado
		  if(estado == 1)
			  Estado_MENU();
		  if(estado == 2)
		  	  Estado_INI();
		  if(estado == 3)
		  	  Estado_FIB();
		  if(estado == 4)
			  Estado_LEI();
		  if(estado == 5)
		  	  Estado_FAC();
		  if(estado == 6)
		  	  Estado_NUM();
		  if(estado == 7)
		  	  Estado_ENT();
		  PTCD = 0x3F;
  } 							/* Lazo infinito */
}


/********************************************************************/
/*  					Interrupt Vectors							*/
/********************************************************************/

interrupt VectorNumber_Vsci1rx void SCI_RX_ISR(void) {
 SCI1S1_RDRF = 0;				/* Receive interrupt disable */
	if (SCI1D == 77 | SCI1D == 109)	// se comprueba si se recibio "M" O "m" para cambiar el valor de la variable estado a 1.
			estado = 1;
	if (SCI1D == 73 | SCI1D == 105)	// se comprueba si se recibio "I" o "i"para cambiar el valor de la variable estado a 2.
			estado = 2;
	if (SCI1D == 70 | SCI1D == 102)	// se comprueba si se recibio "F" o "f" para cambiar el valor de la variable estado a 3.
			estado = 3;
	if (SCI1D == 76 | SCI1D == 108)	// se comprueba si se recibio "L" o "l"para cambiar el valor de la variable estado a 4.
			estado = 4;
	if (SCI1D == 33)	// se comprueba si se recibio "!" para cambiar el valor de la variable estado a 5.
			estado = 5;
	if (SCI1D >= 48 & SCI1D <= 57)	// se comprueba si se recibio un numero para cambiar el valor de la variable estado a 6.
			estado = 6;
	if (SCI1D == 13)	// se comprueba si se recibio <enter> para cambiar el valor de la variable estado a 7.
			estado = 7;
}
