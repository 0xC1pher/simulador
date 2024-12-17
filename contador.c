#include <htc.h>  // Incluimos librería del micro a usar

__CONFIG(WRT_OFF & WDTE_OFF & PWRTE_OFF & FOSC_XT & LVP_OFF);

#define _XTAL_FREQ 4000000  // Oscilador Interno de 4MHz

unsigned char numero[] = {0, 0, 0, 0};  // Número de 1 dígito a mostrar
unsigned int contador = 0;              // Contador que se mostrará en los displays

void timer1_init(void) {
    T1CON = 0x00;  // Configurar TMR1: pre-divisor 1:1, reloj interno, TMR1 apagado
    TMR1H = 0xEC;  // Cargar el valor inicial para un retardo de 5ms
    TMR1L = 0x78;
    TMR1ON = 1;    // Encender TMR1
}

static void interrupt isr(void) {
    static unsigned int contador_interrupciones = 0;

    if (TMR1IF == 1) {  // Comprobar si la interrupción es del TMR1
        TMR1IF = 0;     // Limpiar bandera de interrupción
        TMR1H = 0xEC;   // Recargar el valor inicial
        TMR1L = 0x78;

        contador_interrupciones++;
        if (contador_interrupciones >= 200) {  // 200 interrupciones = 1 segundo (5ms * 200 = 1000ms)
            contador_interrupciones = 0;
            contador++;  // Incrementar el contador cada segundo
            if (contador > 9999) {
                contador = 0;  // Reiniciar el contador si supera 9999
            }
            procesar_digitos(contador);  // Actualizar los dígitos a mostrar
        }
    }
}

void procesar_digitos(unsigned int num) {  // Cambiar int a unsigned int
    // Descomponemos el número en sus dígitos
    numero[0] = num / 1000;           // Dígito de las miles
    numero[1] = (num / 100) % 10;     // Dígito de las centenas
    numero[2] = (num / 10) % 10;      // Dígito de las decenas
    numero[3] = num % 10;             // Dígito de las unidades
}

void main() {
    // Tabla con el código 7 segmentos complementado
    unsigned char codigo[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98};

    // INICIALIZACIONES PARA EL PIC
    ADCON1 = 0b00000110;  // Desactivamos PORTA como entrada analógica
    TRISA = 0x00;         // Terminal RA0 como terminal de salida
    TRISD = 0x00;         // Todos los terminales del Puerto D como salida

    GIE = 1;              // Interrupciones Globales Activadas
    PEIE = 1;             // Interrupciones de los Periféricos Activadas
    TMR1IE = 1;           // Habilitar interrupción del TMR1
    T1CKPS1 = 0;          // Pre-divisor 1:1
    T1CKPS0 = 0;

    timer1_init();        // Inicializar el temporizador TMR1

    procesar_digitos(contador);  // Inicializar los dígitos a mostrar
    while (1) {
        // Bucle infinito
        for (int i = 0; i < 4; i++) {
            PORTD = codigo[numero[i]];  // Enviamos el código 7 segmentos del número a mostrar
            switch (i) {
                case 0: RA2 = 1; break;  // Activamos el display 1
                case 1: RA3 = 1; break;  // Activamos el display 2
                case 2: RA4 = 1; break;  // Activamos el display 3
                case 3: RA5 = 1; break;  // Activamos el display 4
            }
            __delay_ms(5);  // Retardo de 5ms
            switch (i) {
                case 0: RA2 = 0; break;  // Desactivamos el display 1
                case 1: RA3 = 0; break;  // Desactivamos el display 2
                case 2: RA4 = 0; break;  // Desactivamos el display 3
                case 3: RA5 = 0; break;  // Desactivamos el display 4
            }
        }
    }
}
