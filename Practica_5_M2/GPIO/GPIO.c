/*
 * GPIO.c
 *
 */
#include "../include.h"

extern void Configurar_GPIO(void){
    SYSCTL->RCGCGPIO |= (1<<5);
    GPIOF->LOCK = 0x4C4F434B; //desbloquea el puerto F
    GPIOF_CR = (1<<0); //el pin 0 desbloque
    GPIOF->DIR |= (0<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0); //Entradas 0 y salidas 1
                // BTON1   LEDV  LEDA    LEDR  BTON2
                //   0      1      1       1     0
    //Desactivar función alternativa
    GPIOF->AFSEL |= 0x00; //quiero que all el puerto f sea configurado con el gpio para habiliar las resisntancias internas
    GPIOF->PUR = (1<<4) | (1<<0); // BTON1&2 resistencias pull up
    //Activamos el funcionamiento digital
    GPIOF->DEN = (1<<4) | (1<<3) | (1<<2) | (1<<1) |(1<<0);
    //desactivamos la funcion analogica
    GPIOF->AMSEL |= 0x00;
    //desactivamos las funciones alternativas
    GPIOF->PCTL |= 0x00;
    //habilitar_IntGPIO();
}

extern void habilitar_IntGPIO(void){
    //ver la tabla de vectores de interrupción (Registros NVIC
    //el numero de interrupción del GPIOF es: 30 PAG 104
    //Cada registro PRI configura 4 vectores
    //La prioridad es 30/4 = 7 Pag 152
    //NIVIC_PRI7_R 31 30 28 29
    //Ademas acepta 8 niveles (0 más, 7 menos)
    //[4n+3] [4n+2] [4n+1] [4n]
    // FF      00     FF    FF /el que quiero 4*7+2=30 30=numero de interrupcuóin puerto f
    NVIC->IP[7] = (NVIC->IP[7] & 0xFF00FFFF) | (0x00800000); //prioridad 4
    //Para habilitar el número de interrupcion se cuenta con 4 registros
    //registros de 32 bits, como es el numero 30 necesitamos 1 registro
    //para poder decirle al micro que es la numero 30
    NVIC->ISER[0] = 0x40000000; //(Prende 1 el bit 30) si se excede, restar la cantidad que se exceden
    //Configuración del modo de interrupcion del gpio
    //usar registros IS,IBE,IEV,RIS(son el tipo de interrupción)
    //IS: Interrupt Sense // 0 = Edge Interrupt // 1 = Level Interrupt
    //IBE: Interrupt Both Edge //
    //0 = El borde de interrupción es controlado por IEV //
    //1 = La interrupcion detecta borde de subida y borde de bajada
    //IEV: Interrup Event
    //0 = borde de bajada o nivel bajo
    //1 = borde de subida o nivel alto
    //Fuente de la interrupción, se limpia el registro
    GPIOF->IM |= (0<<4) | (0<<0);  //desactivamos el envio de la interrupción al micro
    GPIOF->IS |= (0<<4) | (0<<0);  //interrumpe cuando sea sensible al borde
    GPIOF->IBE |= (0<<4) | (0<<0); //Lo que genere la interrupcion esta controlada por IEV
    GPIOF->IEV |= (1<<4) | (1<<0); //(detecta los bordes de subida
    GPIOF->RIS |= (0<<4) | (0<<0);   //registro de estado
    GPIOF->IM |= (1<<4) | (1<<0);    //Se le ordena enviar la interrupción al micro
}





