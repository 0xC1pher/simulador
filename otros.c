//Código de partida para las practicas de SD2
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

	void timer2(int valor){
		TMR1= valor;
		TMR1ON=1;
		while(TMR1ON==1){}
		return;
		}
unsigned char m0,REG1, encendido = 0;
static void interrupt isr(void)
{ //Código de atención a la interrupción 
	if(m0!=9 && encendido==1 && TMR2IF==1){
		TMR2IF=0;
		m0++;}
	if(RBIF==1){
		RBIF=0;
		encendido=!encendido;}
	return;
}
void main()
{
	// Tabla con el código 7segmentos complementado
	unsigned char codigo[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};
	unsigned char display = 1;			//Indica el display a activar
	unsigned char m1,s0,s1=0;
	//INICIALIZACIONES PARA EL PIC
	ADCON1=0b00000110;					//Desactivamos PORTA como entrada analógica
	TRISA=0x00;							//Terminal RA0 como terminal de salida
	TRISD=0x00;							//Todos los terminales del PuertoD como salida
	GIE=1; 								//Interrupciones Globales activadas
	PEIE=1;								//Interrupciones de los Periféricos activadas
	RBIE=1
	TMR2IE=1;
	T2CON=0;	
	unsigned char i =0;

	// Código del programa principal
	TMR2=0x2710; //delay de 10m
	TMR2ON=1;

	while(1)
	{
		//Bluque infinito	
	PORTD = codigo[m0];		//Enviamos el código 7 segmentos del número a mostrar
	PORTA=1;

	PORTD = codigo[m1];
	PORTA=2;

	PORTD = codigo[s0];
	PORTA=4	;

	PORTD = codigo[s1];
	PORTA=8;
		if(s1==9){
		encendido=0;
		}

		while(encendido==1){
			if(m0==9){
			m1++;
			m0=0;}
	
			if(m1==9){
			s0++;
			m1=0;}

			if(s0==9){
			s1++;}
		}
	if(RA4==1){
		if(REG1==0){
     		 REG1=1;
			encendido=0;
			m0=0;
			m1=0;
			s0=0;
			s1=0;}
	  }else{
	    REG1=0;}

	}
}