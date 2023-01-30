

/**
 * main.c
 */
#include "include.h"


uint16_t adc_data[4] = {0};// arreglo para datos del adc
uint32_t duty=0;
uint32_t dc=0;
uint32_t dc0=0;
uint32_t dc1=0;
uint32_t dc2=0;
int main(void)
 {

    SetSystemClock_MHz(_20MHZ); //_50 para el 1 20 para 2 y 3
    Configurar_PWM0();  ///PB6
    Configurar_PWM3(); /// PB5 <-- EXP 1 5000-1
    Configurar_PWM5(); /// PE5

    char data_str[4] ;


    duty0 = 10;  //%% para EXP1
    duty1 = 0;  //%%
    duty2 = 100;  //%%

  //EXP2des
  //ADC_config_modulo_0();  /// E1-3

  ///EXP3des
    Configurar_UART3(19200,_20MHZ);
    Configurar_GPIO();


	while(1U){
	    ///PRUEBA RGB
	/*    dc=100;  ///de 0% a  100%
	    PWM0->_1_CMPB = PWM0->_1_LOAD - (249.99*dc) -1;
*/
 	///EXP2 des
   //ADC_leer_canal(adc_data);

   /// EXP1 para los 50MHz a 10Khz --> para variar el CT se varia el comparador que va de bajada por lo tanto se necesita resta

///   PWM0->_1_CMPB = PWM0->_1_LOAD - (PWM0->_1_CMPB*(duty0/100.0))+1; ////// 5000/16 <--- 10kHz a 50Mh


   ////////////////EXP2
/*
     duty1 =  adc_data[0] ;   ///guarda los datos del adc en arreglo para usarlo como int en el pwm
      duty2 =  adc_data[1] ;       //depende de como se ocnecten lso cables es el que lee de E3-1
        duty0 =  adc_data[2] ;

    //////   PRUEBA
        PWM0->_0_CMPA = PWM0->_0_LOAD - (PWM0->_0_LOAD*(duty0/100.0))+1; ////// 400000/16 <---50 hz a 20M
        PWM0->_1_CMPB = PWM0->_1_LOAD - (PWM0->_1_LOAD*(duty1/100.0))+1; ////// 400000/16 <---50 hz a 20M
        PWM0->_2_CMPB = PWM0->_2_LOAD - (PWM0->_2_LOAD*(duty2/100.0))+1; ////// 400000/16 <---50 hz a 20M
////////el comparador, si es igual a la carga (load) será flanco bajo


/////////////SERVOS
 /////////////////////           .5ms    2.5ms  *  convercion de 0 a 4095
  PWM0->_0_CMPA = PWM0->_0_LOAD - 600 - 2550*((duty0/4095.0));      //PWM modulo0 gen0     ////////////// 20MHz son 25000 para 50 Hz por lo que serpian 20ms y un servo va de .5 a 2.5 ms
  PWM0->_1_CMPB = PWM0->_1_LOAD - 600 - 2550*((duty1/4095.0));  //PWM modulo0 gen1         /////para .5 ms equivale a 600 ceuntas qeu serpia pos0
  PWM0->_2_CMPB = PWM0->_2_LOAD - 600 - 2550*((duty2/4095.0)); //PWM modulo0 gen2
*/
//  char  a_string = malloc(adc_data[0]);
//Tx_string(a_string);

 /////////////EXP3

	    char c;
      c= Rx_char();

        switch(c)
        {

        case 'r': {  ///led r
            data_str[0] = Rx_char();

            data_str[1] = Rx_char();

            data_str[2] = Rx_char();

           data_str[3] = '\0';
           uint32_t duty0= atoi(data_str);

            dc1= (100*duty0)/255.0;

 PWM0->_0_CMPA = PWM0->_0_LOAD - (249.99*dc1) -1;  /// 0

            break;
                   }

        case 'g': {  ///led g

            data_str[0] = Rx_char();

            data_str[1] = Rx_char();

            data_str[2] = Rx_char();

           data_str[3] = '\0';
           uint32_t duty1= atoi(data_str);

            dc2= (100*duty1)/255.0;


            PWM0->_1_CMPB = PWM0->_1_LOAD - (249.99*dc2) -1;////// 400000/16 <---50 hz a 20M

             break;
                   }

        case 'b': {   ////led b
            data_str[0] = Rx_char();

            data_str[1] = Rx_char();

            data_str[2] = Rx_char();

           data_str[3] = '\0';
           uint32_t duty2= atoi(data_str);

            dc2= (100*duty2)/255.0;

 PWM0->_2_CMPB = PWM0->_2_LOAD- (249.99*dc2) -1;  //5

           // duty2=255;
          //  PWM0->_2_CMPB = PWM0->_2_LOAD - 25000*((duty2/255.0));  //5
            break;
                   }
    default:

        dc=0;  ///0% en alto para que se apaguen leds
        PWM0->_0_CMPA =PWM0->_0_LOAD - (249.99*dc) -1;;
        PWM0->_1_CMPB =PWM0->_1_LOAD - (249.99*dc) -1;;
        PWM0->_2_CMPB = PWM0->_2_LOAD - (249.99*dc) -1;;

        break;

        }


 /// RGB --->  PWM0->_0_CMPA = PWM0->_0_LOAD - (PWM0->_0_LOAD*(duty0/4095.0))+1; ///con pot controla el rgb externo



	}
}
