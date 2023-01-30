/*
 * ADC.h
 *
 */

#ifndef ADC_ADC_H_

    #define ADC_ADC_H_

    ///////////////////////////////////////////////////////////////////// ADC
    // Canal          0       1       2       3
    // pin          6 (E3)  7 (E2)  8 (E1)  9 (E0)
    // configurar modulo adc
    extern void ADC_config_modulo_0(void);

    // leer canal adc

    extern void ADC_leer_canal(uint16_t data[]);

#endif /* ADC_ADC_H_ */
