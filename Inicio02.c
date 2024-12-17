//Código de partida para los ejercicios propuestos en la Sesión 02

#include<htc.h> 			//Incluimos librería del micro a usar

__CONFIG(WRT_OFF & WDTE_OFF & PWRTE_OFF & FOSC_XT & LVP_OFF);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//WRT_OFF = Codigo no Potegido
//WDTE_OFF = Watch Dog Timer Desactivado
//PWRTE_OFF = Power Activado
//FOSC_XT = Osiclador cristal
//LVP_OFF = Low Voltage Porgramming Desactivado
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
#define _XTAL_FREQ 4000000 				//Oscilador Interno de 4MHZ	

	void timer1(int valor){
		TMR1= valor;
		TMR1ON=1;
		while(TMR1IF==0){}
		TMR1ON=0;
		TMR1IF=0;
		return;
		}

void main()
{
	// Tabla con el código 7segmentos complementado
	unsigned char codigo[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};
	unsigned char numero = 5;			//Número de 1 dígito a mostrar
	unsigned char display = 1;			//Indica el display a activar
	//INICIALIZACIONES PARA EL PIC
	ADCON1=0b00000110;					//Desactivamos PORTA como entrada analógica
	TRISA=0xfe;							//Terminal RA0 como terminal de salida
	TRISD=0x00;							//Todos los terminales del PuertoD como salida
	TRISB=0x00;
	GIE=0; 								//Interrupciones Globales Desactivadas
	PEIE=0;								//Interrupciones de los Periféricos Desactivadas
	T1CKPS1=0;
	T1CKPS0=0;
	int delay5=0xec78;
	int delay15=0xc568;			
	// Código del programa principal
	while(1)
	{
		//Bluque infinito
		PORTA = 1;			//Activamos el display
		timer1(delay5);
		PORTA = 0;			//Activamos el display
		timer1(delay15);
		PORTB=0x02;
		PORTD = codigo[numero];		//Enviamos el código 7 segmentos del número a mostrar
	}

}
