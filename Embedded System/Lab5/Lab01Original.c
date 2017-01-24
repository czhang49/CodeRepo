#include <p33Fxxxx.h>
//do not change the order of the following 3 definitions
#define FCY 12800000UL 
#include <stdio.h>
#include <libpic30.h>

#include "lcd.h"
#include "led.h"

/* Initial configuration by EE */
// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);

// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystal
_FOSC(OSCIOFNC_OFF & POSCMD_XT); 

// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);

// Disable Code Protection
_FGS(GCP_OFF);  


void main(){
        TRISEbits.TRISE8 = 1; //PortE Pin 8 I/O Configuration
        AD1PCFGHbits.PCFG20 = 1; //ADC1 Port Configuration Register High Channel 20
        PORTEbits.RE8; //PortE Pin 8 value
        IEC1bits.INT1IE; //Interrupt Enable Control Register 1
        //External Interrupt 1 Enable bit
        IPC5bits.INT1IP; //Interrupt Priority Control Register 5
        //External Interrupt 1 Priority bits
        IFS1bits.INT1IF; //Interrupt Flag Status Register 1
        INTCON2bits.INT1EP; /*Interrupt Control Register 2 External
        Interrupt 1 Edge Detect Polarity Select bit*/

        TRISDbits.TRISD10; //PortD Pin 10 I/O C
        PORTDbits.RD10 = 1 ; //PortD Pin 10 value

        
	//Init LCD
	__C30_UART=1;	
	lcd_initialize();
	lcd_clear();
        lcd_locate(0,0);
        lcd_printf("Deepak Shine\n");
        lcd_printf("Chen Zhang\n");
        led_initialize();

        int T_down = 0;
        int T_up = 0;

        int count_button1 = 0;
        int i;
	while(1){
             TOGGLELED(LED4_PORT);

            //Pressing down button #1.
            if (PORTEbits.RE8 == 0) {
                T_down++;
                SETLED(LED1_PORT);
            }
            else {
                CLEARLED(LED1_PORT);
                T_up++;
            }

            //Pressing down button #2.
            if (PORTDbits.RD10 == 0) {
                SETLED(LED2_PORT);
            }
            else {
                CLEARLED(LED2_PORT);
            }

            //For turning on LED3.
            if ((PORTDbits.RD10==0&&PORTEbits.RE8==1) || (PORTDbits.RD10==1&&PORTEbits.RE8==0)) {
                SETLED(LED3_PORT);
            }
            else {
                 CLEARLED(LED3_PORT);
            }
       
           if (T_down == 50) {
                SETLED(LED1_PORT);
                count_button1++;
                lcd_clear();
                lcd_locate(0,0);
                lcd_printf("Deepak Shine\n");
                lcd_printf("Chen Zhang\n");
                led_initialize();
                lcd_printf("%d\n",count_button1);
                T_up = 0;

            }

            if (T_up == 50) {
                CLEARLED(LED1_PORT);
                T_down = 0;
            }  
        }
}

