#include "flexmotor.h"

void motor_init(uint8_t chan)
{
	//setup Timer 2
	CLEARBIT(T2CONbits.TON); // Disable Timer
	CLEARBIT(T2CONbits.TCS); // Select internal instruction cycle clock
	CLEARBIT(T2CONbits.TGATE); // Disable Gated Timer mode
	TMR2 = 0x00; // Clear timer register
	T2CONbits.TCKPS = 0b10; // Select 1:64 Prescaler
	CLEARBIT(IFS0bits.T2IF); // Clear Timer2 interrupt status flag
	CLEARBIT(IEC0bits.T2IE); // Disable Timer2 interrupt enable control bit
	PR2 = 4000; // Set timer period 20ms:
	// 4000= 20*10^-3 * 12.8*10^6 * 1/64
	//setup OC8
	if(chan==0){
		CLEARBIT(TRISDbits.TRISD8); /* Set OC8 as output */
		OC8R = 3700; /* Set the initial duty cycle to 0.9ms*/
		OC8RS = 3700; /* Load OC8RS: next pwm duty cycle */
		OC8CON = 0x0006; /* Set OC8: PWM, no fault check, Timer2 */	
	}
	else{
		CLEARBIT(TRISDbits.TRISD7); /* Set OC7 as output */
		OC7R = 3700; /* Set the initial duty cycle to 0.9ms*/
		OC7RS = 3700; /* Load OC7RS: next pwm duty cycle */
		OC7CON = 0x0006; /* Set OC7: PWM, no fault check, Timer2 */
	}
	SETBIT(T2CONbits.TON); /* Turn Timer 2 on */

}



void motor_set_duty(uint8_t chan, uint16_t duty_us)
{
	duty_us = duty_us*200;
	if(chan==0)
		OC8RS = 4000-duty_us; /* Load OC8RS: next pwm duty cycle */
	else
		OC7RS = 4000-duty_us; /* Load OC7RS: next pwm duty cycle */
}

