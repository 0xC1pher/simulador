//C�digo de partida para los ejercicios propuestos en la Sesi�n 02
#include<htc.h> 			//Incluimos librer�a del micro a usar

__CONFIG(WRT_OFF & WDTE_OFF & PWRTE_OFF & FOSC_XT & LVP_OFF);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//WRT_OFF = Codigo no Potegido
//WDTE_OFF = Watch Dog Timer Desactivado
//PWRTE_OFF = Power Activado
//FOSC_XT = Osiclador cristal
//LVP_OFF = Low Voltage Porgramming Desactivado
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
#define _XTAL_FREQ 4000000 				//Oscilador Interno de 4MHZ	
unsigned char numero []= {0, 0, 0, 0};			//N�mero de 1 d�gito a mostrar

	void timer1(int valor){
		TMR1= valor;
		TMR1ON=1;
		while(TMR1ON==1){}
		return;
		}

static void interrupt isr(void)
{ //C�digo de atenci�n a la interrupci�n 
	if(TMR1IF=1){
		TMR1ON=0;
		TMR1IF=0;
		TMR1= 0xec78;
	}
	return;
}

void procesar_digitos(int num) {
    int miles = num / 1000;             // D�gito de las miles
    int centenas = (num / 100) % 10;    // D�gito de las centenas
    int decenas = (num / 10) % 10;      // D�gito de las decenas
    int unidades = num % 10;            // D�gito de las unidades
	numero[3]=unidades;
	numero[2]=decenas;
	numero[1]=centenas;
	numero[0]=miles;
}
void main()
{
	// Tabla con el c�digo 7segmentos complementado
	unsigned char codigo[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};
	unsigned char display = 1;			//Indica el display a activar
	unsigned int num = 1234;
	//INICIALIZACIONES PARA EL PIC
	ADCON1=0b00000110;					//Desactivamos PORTA como entrada anal�gica
	TRISA=0x00;							//Terminal RA0 como terminal de salida
	TRISD=0x00;							//Todos los terminales del PuertoD como salida
	GIE=1; 								//Interrupciones Globales Desactivadas
	PEIE=1;								//Interrupciones de los Perif�ricos Desactivadas
	TMR1IE=1;
	T1CKPS1=0;
	T1CKPS0=0;
	int delay5=0xec78;
	int delay15=0xc568;			
	unsigned char i =0;

	// C�digo del programa principal
	procesar_digitos(num);


	while(1)
	{
		//Bluque infinito
		PORTD = codigo[numero[i]];		//Enviamos el c�digo 7 segmentos del n�mero a mostrar
		RA2 = 1;			//Activamos el display
		timer1(delay5);
		RA2 = 0;
		i++;
		PORTD = codigo[numero[i]];		//Enviamos el c�digo 7 segmentos del n�mero a mostrar
		RA3 = 1;
		timer1(delay5);
		RA3 = 0;
		i++;
		PORTD = codigo[numero[i]];		//Enviamos el c�digo 7 segmentos del n�mero a mostrar
		RA4 = 1;
		timer1(delay5);
		RA4 = 0;
		i++;
		PORTD = codigo[numero[i]];		//Enviamos el c�digo 7 segmentos del n�mero a mostrar
		RA5 = 1;
		timer1(delay5);
		RA5 = 0;

		i=0;
	}

}
