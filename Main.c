/********************************************************************/
/* Project Name:Practica 5													*/
/* Gabriel Olivieri 13-11002 Grupo 4													*/
/********************************************************************/
/********************************************************************/
/* Date: 2/28/2017															*/
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

int i,j,k;					// Variable contador.
int estado = 1;	   			// Variable para designar el estado en que se encuentre el programa.
int temp;
int n=1;
int numcontrol=0;
char num[2];
char c1='1';
char c2='0';

UINT8 MENU[7][31]={
"¿Que desea hacer?              ",
"M:  Mostrar este menú          ",
"I:  Mostrar iniciales del grupo",
"F:  Calculo de Fibonaci        ",
"L:  Calculo de p por Leibniz   ",
"!:  Calculo de Factorial       ",
"E:  Mostrar Numero Introducido "
};

UINT8 ECHO[1][26]= {
		"El numero introducido es: "
};

UINT8 INICIALES[40][47]={
"             dddddddd                         ",
"             d::::::d                         ",
"             d::::::d                         ",
"             d::::::d                         ",
"              d:::::d                         ",
"     ddddddddd:::::d    mmmmmmm    mmmmmmm    ",
"   dd::::::::::::::d  mm:::::::m  m:::::::mm  ",
"  d::::::::::::::::d m::::::::::mm::::::::::m ",
" d:::::::ddddd:::::d m::::::::::::::::::::::m ",
" d::::::d    d:::::d m:::::mmm::::::mmm:::::m ",
" d:::::d     d:::::d m::::m   m::::m   m::::m ",
" d:::::d     d:::::d m::::m   m::::m   m::::m ",
" d:::::d     d:::::d m::::m   m::::m   m::::m ",
" d:::::d     d:::::d m::::m   m::::m   m::::m ",
" d::::::ddddd::::::ddm::::m   m::::m   m::::m ",
" d::::::ddddd::::::ddm::::m   m::::m   m::::m ",
"  d:::::::::::::::::dm::::m   m::::m   m::::m ",
"   d:::::::::ddd::::dm::::m   m::::m   m::::m ",
"    ddddddddd   dddddmmmmmm   mmmmmm   mmmmmm ",
"  ggggggggg   ggggg   ooooooooooo             ",
"  g:::::::::ggg::::g oo:::::::::::oo          ",
" g:::::::::::::::::go:::::::::::::::o         ",
"g::::::ggggg::::::ggo:::::ooooo:::::o         ",
"g:::::g     g:::::g o::::o     o::::o         ",
"g:::::g     g:::::g o::::o     o::::o         ",
"g:::::g     g:::::g o::::o     o::::o         ",
"g::::::g    g:::::g o::::o     o::::o         ",
"g:::::::ggggg:::::g o:::::ooooo:::::o         ",
" g::::::::::::::::g o:::::::::::::::o         ",
"  gg::::::::::::::g  oo:::::::::::oo          ",
"    gggggggg::::::g    ooooooooooo            ",
"            g:::::g                           ",
"gggggg      g:::::g                           ",
 "g:::::gg   gg:::::g                          ",
" g::::::ggg:::::::g                           ",
"  gg:::::::::::::g                            ",
"    ggg::::::ggg                              ",
"       gggggg                                 ",
};

UINT8  fibarray[100][23] = {
		"                     1 ", "                     1 ", "                     2 ", 
		"                     3 ", "                     5 ", "                     8 ", "                    13 ",
		"                    21 ", "                    34 ", "                    55 ", "                    89 ", 
		"                   144 ", "                   233 ", "                   377 ", "                   610 ", 
		"                   987 ", "                  1597 ", "                  2584 ", "                  4181 ", 
		"                  6765 ", "                 10946 ", "                 17711 ", "                 28657 ", 
		"                 46368 ", "                 75025 ", "                121393 ", "                196418 ",
		"                317811 ", "                514229 ", "                832040 ", "               1346269 ", 
		"               2178309 ", "               3524578 ", "               5702887 ", "               9227465 ",
		"              14930352 ", "              24157817 ", "              39088169 ", "              63245986 ", 
		"             102334155 ", "             165580141 ", "             267914296 ", "             433494437 ", 
		"             701408733 ", "            1134903170 ", "            1836311903 ", "            2971215073 ", 
		"            4807526976 ", "            7778742049 ", "           12586269025 ", "           20365011074 ", 
		"           32951280099 ", "           53316291173 ", "           86267571272 ", "          139583862445 ", 
		"          225851433717 ", "          365435296162 ", "          591286729879 ", "          956722026041 ", 
		"         1548008755920 ", "         2504730781961 ", "         4052739537881 ", "         6557470319842 ", 
		"        10610209857723 ", "        17167680177565 ", "        27777890035288 ", "        44945570212853 ", 
		"        72723460248141 ", "       117669030460994 ", "       190392490709135 ", "       308061521170129 ", 
		"       498454011879264 ", "       806515533049393 ", "      1304969544928657 ", "      2111485077978050 ", 
		"      3416454622906707 ", "      5527939700884757 ", "      8944394323791464 ", "     14472334024676220 ", 
		"     23416728348467684 ", "     37889062373143904 ", "     61305790721611584 ", "     99194853094755488 ", 
		"    160500643816367070 ", "    259695496911122560 ", "    420196140727489660 ", "    679891637638612220 ", 
		"   1100087778366101900 ", "   1779979416004714000 ", "   2880067194370816000 ", "   4660046610375530500 ", 
		"   7540113804746346500 ", "  12200160415121877000 ", "  19740274219868226000 ", "  31940434634990100000 ", 
		"  51680708854858326000 ", "  83621143489848426000 ", " 135301852344706760000 ", " 218922995834555200000 "};

UINT8  leibarray[100][8] ={"4.000000","2.666667","3.466667","2.895238","3.339683","2.976046","3.283738","3.017072",
		                 "3.252366","3.041840","3.232316","3.058403","3.218403","3.070255","3.208186","3.079153",
		                 "3.200366","3.086080","3.194188","3.091624","3.189185","3.096162","3.185050","3.099944",
		                 "3.181577","3.103145","3.178617","3.105890","3.176065","3.108269","3.173842","3.110350",
		                 "3.171889","3.112187","3.170158","3.113820","3.168615","3.115281","3.167229","3.116597",
		                 "3.165979","3.117787","3.164845","3.118868","3.163812","3.119856","3.162867","3.120762",
		                 "3.161999","3.121595","3.161199","3.122364","3.160459","3.123076","3.159773","3.123737",
		                 "3.159135","3.124353","3.158541","3.124927","3.157985","3.125465","3.157465","3.125969",
		                 "3.156976","3.126442","3.156517","3.126888","3.156085","3.127308","3.155676","3.127704",
		                 "3.155291","3.128080","3.154925","3.128435","3.154579","3.128773","3.154250","3.129093",
		                 "3.153938","3.129398","3.153640","3.129688","3.153357","3.129965","3.153087","3.130229",
		                 "3.152828","3.130482","3.152581","3.130723","3.152345","3.130955","3.152119","3.131176",
		                 "3.151902","3.131389","3.151693" };

//Funcion para el cálculo del factorial
int multiply(int x, int res[], int res_size)
{
    int carry = 0;  // Initialize carry
    int i;
    // multiplicar n uno por uno con cada digito de res[]
    for ( i=0; i<res_size; i++)
    {
        int prod = res[i] * x + carry;
        res[i] = prod % 10;  // Guardar el ultimo digito de prod en res[i]
        carry  = prod/10;    // Colocar lo demás en el carry
    }

    // Poner el carry en res y aumentar el tamaño del resultado
    while (carry)
    {
        res[res_size] = carry%10;
        carry = carry/10;
        res_size++;
    }
    return res_size;
}

/********************************************************************/
/*					Function declarations							*/
/********************************************************************/

void Transmision(char dato){
	while(SCI1S1_TDRE == 0);
	SCI1D = dato;
	
}

void TransmisionI(int dato){
	while(SCI1S1_TDRE == 0);
	SCI1D = dato;
	
}

void TransmisionNum(int dato){
	char datoc;
	datoc=dato+'0';
	while(SCI1S1_TDRE == 0);
	SCI1D = datoc;
}

void ClearScreen(void){
	//Borrar pantalla
	TransmisionI(27);
	TransmisionI(91);
	TransmisionI(50);
	TransmisionI(74);
	//Mover Cursor
	TransmisionI(27);
	TransmisionI(91);
	TransmisionI(49);//1
	TransmisionI(59);
	TransmisionI(49);//1
	TransmisionI(72);
}



/********************************************************************/
/*					Estados							*/
/********************************************************************/

void Estado_INI(void){		// Funcion para mostrar por el Terminal Las iniciales del grupo (ESTADO 2).
	PTCD = 0x3D;
	ClearScreen();
	k=0;
	for (i=0;i<40;i++){
		//Backspace
		TransmisionI(13);
		TransmisionI(10);
		for(j=0;j<47;j++){
			Transmision(INICIALES[i][j]);

		}	
	}
	

	estado = 0;
	numcontrol=0;
}

void Estado_NUM(void){		// Funcion para leer el numero N de terminos (ESTADO 6).
	PTCD = 0x39;
	if (numcontrol==1) {
		c2 = SCI1D;
		numcontrol=2;
	}
	
	if (numcontrol==0){ 
		c1 = SCI1D;
		numcontrol=1;
	}
	
	SCI1D=0;

	estado=0;

}



void Estado_ENT(){		// Funcion para procesar N y pasarlo a la funcion correspondiente (ESTADO 7).
	int a;
	int b;
	PTCD = 0x38;
	a= c1-'0';
	b = c2-'0';
	c1='0';
	c2='0';
	if (numcontrol==1){
		n = a;
	}
	if (numcontrol==2){
		n= 10*a+b;
	}
	
	
	estado = 0;
	numcontrol=0;
}


void Estado_MENU(void){ //Funcion para mostrar el menu
	PTCD = 0x3E;
	ClearScreen();
	k=0;
	for (i=0;i<7;i++){
		//Backspace
		TransmisionI(13);
		TransmisionI(10);
		for(j=0;j<31;j++){
			Transmision(MENU[i][j]);

		}	
	}
	
	estado = 0;
	numcontrol=0;
}
	

void Estado_ECHO (void){ //Funcion para mostrar el número introducido (ESTADO 8)
	char datoa,datob;
	int a,b;
	ClearScreen();
	for(j=0;j<26;j++){
		Transmision(ECHO[0][j]);
	}	
	a=n%10;
	b=n/10;
	datoa = a+'0';
	datob = b+'0';
	Transmision(datob);
	Transmision(datoa);
	estado = 0;
}

void Estado_FIB(int n){		// Funcion para mostrar por el Terminal la serie de FIBONACCI (ESTADO 3).
	PTCD = 0x3C;
	ClearScreen();
	for(i=0;i<n;i++){
		for (j=0;j<23;j++){
			Transmision(fibarray[i][j]);
		}
		TransmisionI(44);
		TransmisionI(32);
	}

	estado = 0;
	numcontrol=0;
}

void Estado_LEI(int n){   	
   PTCD = 0x3B;
   ClearScreen();
   for(i=0;i<n;i++){
  	 for (j=0;j<8;j++){
  		 Transmision(leibarray[i][j]);
  	 }
  	 TransmisionI(44);
  	 TransmisionI(32);
   }
   estado = 0;
   numcontrol=0;
}


void Estado_FAC(int n){		// Funcion para mostrar por el Terminal la serie Factorial (ESTADO 5).
    	int res[500];
    	int i;
	int res_size = 1;
	int x;
	ClearScreen();
	// Inicializar el resultado
	res[0] = 1;
	// Aplicar la formula del factorial
	for (x=2; x<=n; x++)
		res_size = multiply(x, res, res_size);

	for (i=res_size-1; i>=0; i--) //Transmitir el resultado digito pot digito
		TransmisionNum(res[i]);


	estado = 0;
	numcontrol=0;
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
		  	  Estado_FIB(n);
		  
		  if(estado == 4)
			  Estado_LEI(n);
		  
		  if(estado == 5)
		  	  Estado_FAC(n);
		  
		  if(estado == 6)
			  Estado_NUM();

		  if(estado == 7)
		  	  Estado_ENT();
		  	  
		  if(estado == 8)
			  Estado_ECHO();
		  PTCD = 0x3F;
  } 							/* Lazo infinito */
}


/********************************************************************/
/*  					Interrupt Vectors							*/
/********************************************************************/

interrupt VectorNumber_Vsci1rx void SCI_RX_ISR(void) {
	char dato;
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
		    estado=7;
	if (SCI1D == 101 || SCI1D==69)	// se comprueba si se recibio "E" o "e" para cambiar el valor de la variable estado a 8.
		    estado=8;


}


