#include <p33Fxxxx.h>
//do not change the order of the following 3 definitions
#define FCY 12800000UL 
#include <stdio.h>
#include <libpic30.h>

#include "lcd.h"
#include "led.h"
#include "flextouch.h"
#include "flexmotor.h"


void debounce(void);
int sort(int *arr);
void timer2_init();

/* Initial configuration by EE */
// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);

// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystal
_FOSC(OSCIOFNC_OFF & POSCMD_XT); 

// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);

// Disable Code Protection
_FGS(GCP_OFF);  


volatile int flag = 0;

void __attribute__ ((__interrupt__,auto_psv)) _T3Interrupt(void)
{
    flag = 1;
    CLEARBIT(IFS0bits.T3IF); // Clear Timer3 interrupt status flag


}



void timer3_init()
{
	//setup Timer 2
	CLEARBIT(T3CONbits.TON); // Disable Timer
	CLEARBIT(T3CONbits.TCS); // Select internal instruction cycle clock
	CLEARBIT(T3CONbits.TGATE); // Disable Gated Timer mode
	TMR3 = 0x00; // Clear timer register
	T3CONbits.TCKPS = 0b10; // Select 1:64 Prescaler
	CLEARBIT(IFS0bits.T3IF); // Clear Timer3 interrupt status flag
        IPC2bits.T3IP = 0x01; // Set Timer3 Interrupt Priority Level
	PR3 = 10000; // Set timer period 50ms:
        SETBIT(IEC0bits.T3IE);
	//SETBIT(T3CONbits.TON); /* Turn Timer 2 on */

}



int sort(int arr[])
{
    int swap;
    int i,j;
    for(i=0;i<4;i++){
        for(j=0; j<4-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swap;
            }
        }
    }
    return arr[2];
}



int main(){
	//Init LCD
	__C30_UART=1;	
	lcd_initialize();
	lcd_clear();
        led_initialize();

        lcd_locate(0,0);
        lcd_printf("---lab07---");

       int medX, medY,i;
       double setX = 1655, setY = 1550;
       double maxX = 3000, minX = 310, maxY = 2700, minY = 400;
       double oldX = 0, oldY = 0;
       double iX=0, dX=0, iY=0, dY=0, uX=0, uY=0;
       double duty_usX, duty_usY;
       double kDX=0.2, kPX=1.0, kIX=0.001;//single axis KdX=0.2, kPX=1.0, kIX=0.001
       double kDY=0.2, kPY=0.5, kIY=0.0005;
       double newX = 0, newY = 0;
       int count = 0;
       int X[5],Y[5];
       timer3_init();
       motor_init(1);
       motor_init(0);
       
       adc_init();
       touch_init();
       touch_select_dim(2); 
        
       //motor_set_duty(0,(uint16_t)(2100));
       //motor_set_duty(1,(uint16_t)(900));
        while(1){
            count++;
            
            AD2CHS0bits.CH0SA = 0x00F; // x-values
            touch_select_dim(0); // choose x-dim
            TMR3 = 0x0;
            SETBIT(T3CONbits.TON);
            while(!flag);
            flag = 0;
            for(i=0;i<5;i++){
                X[i]=touch_adc();
            }

            AD2CHS0bits.CH0SA = 0x009; // y-values
            touch_select_dim(1); // choose y-dim
            TMR3 = 0x0;
            SETBIT(T3CONbits.TON);
            while(!flag);
            flag = 0;
            for(i=0;i<5;i++){
                Y[i]=touch_adc();
            }
            
            medX = sort(X);
            medY = sort(Y);
         
            newX = setX - medX;
            dX = (newX - oldX)/0.05;
            iX += newX*0.05;
            uX = kPX*newX+kDX*dX+kIX*iX;
            duty_usX = (setX+uX)/(maxX-minX)*1.2 + 0.9;
            if(duty_usX>2.1){
                duty_usX = 2.1;
            }
            else if(duty_usX<0.9){
                duty_usX = 0.9;
            }
            duty_usX *= 1000;
            oldX = newX;

            newY = setY - medY;
            dY = (newY - oldY)/0.05;
            iY += newY*0.05;
            uY = kPY*newY+kDY*dY+kIY*iY;
            duty_usY = (setY+uY)/(maxY-minY)*1.2 + 0.9;
            if(duty_usY>2.1){
                duty_usY = 2.1;
            }
            else if(duty_usY<0.9){
                duty_usY = 0.9;
            }
            duty_usY *= 1000;
            oldY = newY;

            motor_set_duty(0,(uint16_t)(duty_usX));
            __delay_ms(15);
            motor_set_duty(1,(uint16_t)(1500));
            if(count==4)
            {
                lcd_clear();
                lcd_locate(0,1);
                lcd_printf("Median X: %4d", medX);
                lcd_locate(0,2);
                lcd_printf("Median Y: %4d", medY);
                //lcd_locate(0,3);
                //lcd_printf("duty X: %f", duty_usX);
                lcd_locate(0,4);
                lcd_printf("uY: %f", uY);
                //lcd_locate(0,5);
                //lcd_printf("uint : %d", (uint16_t)duty_usX);
                //lcd_locate(0,6);
                //lcd_printf("med X: %f", medX);
                count=0;
            }
            
            
        }


        return 0;

}

