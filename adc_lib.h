/*
 * adc_lib.h
 *
 * Created: 22/04/2026 08:39:41
 *  Author: sames
 */ 


#ifndef ADC_LIB_H_
#define ADC_LIB_H_

#include <avr/io.h>
#include <stdint.h>

#define ADC_CANALES 3u  //numero de canales que se utilizaran

//iniciar el ADC modo libre con interrupciones
void ADC_init(void);


#endif /* ADC_LIB_H_ */