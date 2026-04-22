/*
 * pwm_lib.c
 *
 * Created: 22/04/2026 08:38:17
 *  Author: sames
 */ 
#include <avr/interrupt.h>
#include "pwm_lib.h"

//configuracion timer 1

void PWM1_init(void){
	DDRB |= (1<<PB1);
	
	ICR1 = ICR1_50HZ;      // 20ms
	OCR1A = SERVO1_MIN;     // posicion inicil (0°)
	
	TCCR1A = (1<<COM1A1)|(1<<WGM11);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);   //prescaler de 8
}

void PWM1_setServo(uint8_t angulo){
	if (angulo > 180) angulo = 180;
	uint16_t pulso = SERVO1_MIN + (uint16_t)((uint32_t)angulo * (SERVO1_MAX - SERVO1_MIN)/180);
	OCR1A = pulso;
}

//configuacion timer 2

void PWM2_init(void){
	DDRB |= (1<<PB3);
	
	OCR2A = SERVO2_MIN;  //posicion inicial 0°
	
	TCCR2A = (1<<COM2A1)|(1<<WGM21)|(1<<WGM20);
	TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);  //prescaler 1024
}

void PWM2_setServo(uint8_t angulo){
	if (angulo > 180) angulo = 180;
	uint8_t pulso = (uint8_t)(SERVO2_MIN + ((uint16_t)angulo * (SERVO2_MAX - SERVO2_MIN))/180);
	OCR2A = pulso;
}

void PWM2_setServoADC(uint16_t adc){
	uint8_t pulso = (uint8_t)(SERVO2_MIN + (uint32_t)adc * (SERVO2_MAX-SERVO2_MIN)/1023);
	OCR2A = pulso;
}

//configuracion timer 0

volatile uint8_t pwm_counter = 0;
volatile uint8_t pwm_duty = 0;

void PWM_LED_init(void){
	PWM_LED_DDR |= (1<<PWM_LED_PIN);
	PWM_LED_PORT &= ~(1<<PWM_LED_PIN);
	
	//timer modo normal prescaler 1024
	TCCR0A = 0x00;
	TCCR0B = (1<<CS01)|(1<<CS00);
	TIMSK0 = (1<<TOIE0);     //interrupcion por overflow
}

void PWM_LED_setDuty(uint8_t duty){
	pwm_duty = duty;
}

ISR(TIMER0_OVF_vect){
	pwm_counter++;
	
	if (pwm_counter ==0){
		//poner salida en alto si duty > 0
		if (pwm_duty > 0){
			PWM_LED_PORT |= (1 << PWM_LED_PIN);
		}
	}
	if (pwm_counter == pwm_duty){
		//poner salida en bajo 
		PWM_LED_PORT &= ~(1 << PWM_LED_PIN);
	}
}