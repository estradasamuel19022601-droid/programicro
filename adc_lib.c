/*
 * adc_lib.c
 *
 * Created: 22/04/2026 08:40:27
 *  Author: sames
 */ 
#include "adc_lib.h"
#include "pwm_lib.h"
#include <avr/interrupt.h>

static volatile uint8_t canal = 0; //Servira para cambiar de pot 0 1 y 2

void ADC_init(){
	ADMUX = (1<<REFS0)|0x00; // para referencia a 5V y que inicie ne ADC0
	//PORTB ^= (1 << PB5);
	
	//hablitar ADC con interrupciones y prescaler de 128
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	//desactivar entrada digitales de los A0-A2
	DIDR0 = (1<<ADC0D)|(1<<ADC1D)|(1<<ADC2D);
	
	ADCSRA |= (1<<ADSC); //primera conversion
	
	sei(); //hablitar interrupciones
}

ISR(ADC_vect){
	uint16_t valor = ADC;   //leer los resoltados de los 10 bits 
	
	switch (canal){
		case 0:
		{
			//potenciometro 1 con servo 1 (timer1 y fastPWM)
			uint16_t pulso = SERVO1_MIN + (uint16_t)((uint32_t)valor * (SERVO1_MAX-SERVO1_MIN)/1023);
			OCR1A = pulso;
		}
		break;
		
		case 1:
		//potenciometro 2 con servo 2 (timer2 y fastPWM)
		PWM2_setServoADC(valor);
		break;
		
		case 2: 
		//potenciometro 3 PWM manual para led (timer0)
		PWM_LED_setDuty((uint8_t)(valor >> 2));
		break;
		
		default:
		canal = 0;
		break;
	}
	//avanza al siguiente canal
	canal = (canal + 1 < ADC_CANALES) ? (canal + 1) : 0;
	
	//seleccionar siguiente canal en ADMUX (mantener REFS0)
	ADMUX = (1<< REFS0)| canal;
	
	//siguiente conversion
	ADCSRA |= (1<<ADSC);
}