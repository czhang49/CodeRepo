#include <p33Fxxxx.h>
//do not change the order of the following 3 definitions
#define FCY 12800000UL 
#include <stdio.h>
#include <libpic30.h>

#include "lcd.h"
#include "led.h"
#include "flexmotor.h"


void debounce(void);

/* Initial configuration by EE */
// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);

// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystal
_FOSC(OSCIOFNC_OFF & POSCMD_XT); 

// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);

// Disable Code Protection
_FGS(GCP_OFF);  


int state = 0;
int prev = 0;
int timeLow = 900;
int timeHigh = 2100;
int press = 0;
int count = 0;

/*
void __attribute__ ((__interrupt__)) _INT2Interrupt(void)
{
    CLEARBIT(IFS1bits.INT2IF);
    int down=0, up=0;
    while(up<2000){
        if(PORTEbits.RE8!= prev){
            down++;
        }
        up++;
    }
    if(down>200){
        prev = PORTEbits.RE8;
        state++;
    }
    up=0;
    down=0;
}

*/

void debounce(void)
{
    // do nothing

    if(press==0){
        count++;
        if(count>500){
            if(state==4){
                state = 5;
            }
            else if(state==5){
                state = 4;
            }
            else{
                state++;
            }
            count = 0;
            press = 1;
        }
    }
    else if(press==1){
        count++;
        if(count>500){
            count = 0;
            press = 0;
        }
   }

}

int main(){

    /* INIT ADC */
        //disable ADC
	CLEARBIT(AD2CON1bits.ADON);
	//initialize PIN
	SETBIT(TRISEbits.TRISE8); //set TRISE RE8 to input
	SETBIT(AD1PCFGHbits.PCFG20); //set AD2 AN20 input pin as analog
        CLEARBIT(AD2PCFGLbits.PCFG4);
        CLEARBIT(AD2PCFGLbits.PCFG5);
        SETBIT(TRISBbits.TRISB4); // Set trisb.b4 to input
	//Configure AD2CON1
	CLEARBIT(AD2CON1bits.AD12B); //set 10b Operation Mode
	AD2CON1bits.FORM = 0; //set integer output
	AD2CON1bits.SSRC = 0x7; //set automatic conversion
	//Configure AD2CON2
	AD2CON2 = 0; //not using scanning sampling
	//Configure AD1CON3
	CLEARBIT(AD2CON3bits.ADRC); //internal clock source
	AD2CON3bits.SAMC = 0x1F; //sample-to-conversion clock = 31Tad
	AD2CON3bits.ADCS = 0x2; //Tad = 3Tcy (Time cycles)
	//Leave AD1CON4 at its default value
	//enable ADC
	SETBIT(AD2CON1bits.ADON);
        prev = PORTEbits.RE8;
////////////////////////////////////////////////////////////
	//Init LCD
	__C30_UART=1;	
	lcd_initialize();
	lcd_clear();
        lcd_locate(0,0);
        led_initialize();

        // Initialize both channels (OC8, OC7)
        motor_init(0);
        motor_init(1);

        int xVal = 0;
        int yVal = 0;
        int xMax = 0;
        int yMax = 0;
        int xMin = 0;
        int yMin = 0;
        float duty_us = 0;

        
        while(state==0){
            AD2CHS0bits.CH0SA=0x04; // x dimension
            SETBIT(AD2CON1bits.SAMP); //start to sample
            while(!AD2CON1bits.DONE); //wait for conversion to finish
            CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
            xMax = ADC2BUF0; //return sample
            lcd_locate(0,0);
            lcd_printf("x max val: %d", xMax);
            if(!PORTEbits.RE8){
                debounce(); //wait
            }
        }



        while(state==1){
            AD2CHS0bits.CH0SA=0x04; // x dimension
            SETBIT(AD2CON1bits.SAMP); //start to sample
            while(!AD2CON1bits.DONE); //wait for conversion to finish
            CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
            xMin = ADC2BUF0; //return sample
            lcd_locate(0,1);
            lcd_printf("x min val: %d", xMin);
            if(!PORTEbits.RE8){
                debounce(); //wait
            }
        }



        while(state==2){
            AD2CHS0bits.CH0SA=0x05; // y dimension
            SETBIT(AD2CON1bits.SAMP); //start to sample
            while(!AD2CON1bits.DONE); //wait for conversion to finish
            CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
            yMax = ADC2BUF0; //return sample
            lcd_locate(0,2);
            lcd_printf("y max val: %d", yMax);
            if(!PORTEbits.RE8){
                debounce(); //wait
            }
        }



        while(state==3){
            AD2CHS0bits.CH0SA=0x05; // y dimension
            SETBIT(AD2CON1bits.SAMP); //start to sample
            while(!AD2CON1bits.DONE); //wait for conversion to finish
            CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
            yMin = ADC2BUF0; //return sample
            lcd_locate(0,3);
            lcd_printf("y min val: %d", yMin);
            if(!PORTEbits.RE8){
                debounce(); //wait
            }
        }
        while(1){
        while(state==4){
            AD2CHS0bits.CH0SA=0x04; // x dimension
            SETBIT(AD2CON1bits.SAMP); //start to sample
            while(!AD2CON1bits.DONE); //wait for conversion to finish
            CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
            xVal = ADC2BUF0; //return sample
            duty_us = (float)(xVal-xMin)/(xMax-xMin)*(timeHigh-timeLow)+timeLow;
            if(duty_us<=2100&&duty_us>=900){
                motor_set_duty(0,(uint16_t)duty_us);
            }
            if(!PORTEbits.RE8){
                debounce(); //wait
            }
        }



        while(state==5){
            AD2CHS0bits.CH0SA=0x05; // y dimension
            SETBIT(AD2CON1bits.SAMP); //start to sample
            while(!AD2CON1bits.DONE); //wait for conversion to finish
            CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
            yVal = ADC2BUF0; //return sample
            duty_us = (float)(yVal-yMin)/(yMax-yMin)*(timeHigh-timeLow)+timeLow;
            if(duty_us<=2100&&duty_us>=900){
                motor_set_duty(1,(uint16_t)duty_us);
            }
            if(!PORTEbits.RE8){
                debounce(); //wait
            }
        }
    }

        return 0;

}

