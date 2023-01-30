/*
 * TIMER.c
 *
 */

#include "../include.h"

extern void Configurar_TIMER1B(uint32_t carga){
    //vamos a configurar el modulo 1 sub modulo B() con precision de 16 bits
    //y modo periodico con reloj acendente de sistema de 50MHz y con interrupción y la frecuencia del temporizador es de 125 Hz
    SYSCTL->RCGCTIMER |= (1<<1); //habilitar el modulo 1 del timer pag 338
    TIMER1->CTL =  0x0000;//Limpiar el registro
    TIMER1->CFG = 0x04; //si es el modulo b se traba a 16 bits.
    TIMER1->TBMR = 0x2; //configura el timer 1 sub modulo B en forma periodica carga baja pag 722
    TIMER1->TBILR = carga - 1; //Este registro es para configurar la carga del timer 16 bits
    TIMER1->TBPR = 50 - 1; //el prescalado de 50 veces que se dividio - 1 porque cuenta el 0
    habilitar_IntTimer1B();

    TIMER1->CTL = (1<<8);//Habilitar el registro TnEN en este caso pin 8
    //para ver el numero de interrupción ver 104
}

extern void habilitar_IntTimer1B(void){
    TIMER1->ICR = (1<<8);
    TIMER1->IMR |=(1<<8); //pag 746, hay muhcos tipos de interrupción, en este caso sera para cuando termine el tiempo de carga (bit 8)
    //numero de interrupción del Timer 1B 16/32 bits es 22, ver pag 104
    //para saber que prioridad toca ver pag 135, (para la interrupción 20-23 es prioridad 5)
    //[4n+3] [4n+2] [4n+1] [4n] vectores
    // 23      22     21    20
    // FF      00     FF    FF
    //Como el no. de int es 22, entonces se limpia ISPR de la siguiente forma
    NVIC->IP[5] = (NVIC->IP[5] & 0xFF00FFFF) | (0x00040000); // el 0x004000 coresponde a la jerarquía en este caso jerarquía 4
    NVIC->ISER[0] = (1<<22);//0x400000; //este registro es el enable, ver pag 134, despues se pone un 1 en el bit del no de interrupción en este caso 1 en bit 22
}

extern void Timer1B_ISR(void){
    TIMER1->ICR = (1<<8); //limpia la interrupción para que vueleva a interrumpir
    uint16_t i = 1;
    GPIOF->DATA ^= (i<<2);
    i = i + 1;
}
