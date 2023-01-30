/*
 * ADC.c
 *
 */
#include "../include.h"




extern void ADC_config_modulo_0(void)
{
    /////////////// lit todo el puerto E
    // 1. RCGCADC
    SYSCTL->RCGCADC |= (1<<0);
    // 2. RCGCGPIO
    SYSCTL->RCGCGPIO |= (1<<4);
    // 3. GPIOFSEL
    GPIOE->AFSEL |= 0x0e;
    // 4. GPIODEN
    GPIOE->DEN &= ~0x0e;
    // 5. GPIOAMSEL
    GPIOE->AMSEL |= 0x0e;

    /////////////// SECUENCIADOR 0
    // 1. ADCACTSS
    ADC0->ACTSS &= ~(0x0f);
    // 2. ADCEMUX
    ADC0->EMUX |= 0x0000;
    // 3. ADCSSMUXn
    ADC0->SSMUX0 |= 0x00000210;
    // 4. ADCSSCTLn
    ADC0->SSCTL0 |= 0x00000644;
    // 5. ADCIM
    ADC0->IM |= (0xf<<16) | (0xf<<0);
    // 6. ADCPP y ADCPC
    //ADC0_PP_R |= 0x7
    ADC0->PC |= 0x3;
    // 7. ADCACTSS
    ADC0->ACTSS |= (1<<0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////// RECIBIR CHAR UART
extern void ADC_leer_canal(uint16_t data[])
{
    ADC0->PSSI |= (1<<0);
    SysTick_espera(.001);

    while (ADC0->RIS & 0x01 == 0);
    SysTick_espera(.001);

    while(ADC0->SSOP0 & (1<<0) == (1<<0));
    data[0] = ADC0->SSFIFO0 & 0xfff;
    SysTick_espera(.001);
    while(ADC0->SSOP0 & (1<<4) == (1<<4));
    data[1] = ADC0->SSFIFO0 & 0xfff;
    SysTick_espera(.001);
    while(ADC0->SSOP0 & (1<<8) == (1<<8));
    data[2] = ADC0->SSFIFO0 & 0xfff;
    SysTick_espera(.001);

    ADC0->ISC |= (1<<0);
    SysTick_espera(.001); ///en mi styc tengo multiplicado por 100 así que .001*1000=1
}



