/*
 * pwm_lib.h
 *
 * Created: 22/04/2026 08:39:04
 *  Author: sames
 */ 


#ifndef PWM_LIB_H_
#define PWM_LIB_H_

#include <avr/io.h>
#include <stdint.h>

//timer 1 con servo 1
#define ICR1_50HZ 39999u
#define SERVO1_MIN 2000u
#define SERVO1_MAX 4000U

void PWM1_init(void);
void PWM1_setServo(uint8_t angulo); //angulo de 0-180°

//timer 2 con servo 2
#define SERVO2_MIN 12u
#define SERVO2_MAX 32u

void PWM2_init(void);
void PWM2_setServo(uint8_t angulo);     //0-180°
void PWM2_setServoADC(uint16_t adc);    //0-1023

//timer 0 con led 
#define PWM_LED_PIN PD6
#define PWM_LED_DDR DDRD
#define PWM_LED_PORT PORTD 

void PWM_LED_init(void);
void PWM_LED_setDuty(uint8_t duty);  //0-255

#endif /* PWM_LIB_H_ */