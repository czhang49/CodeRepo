#include <p33Fxxxx.h>
//do not change the order of the following 3 definitions
#define FCY 12800000UL 
#include <stdio.h>
#include <libpic30.h>
#include "flexserial.h"
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

int seconds_counter=0;
int milli_counter=0;
int main_counter = 0;

int third_counter = 0;
int flag_1sec;
int unsuccessful=0;



// Interrupt Service Routine triggered when Timer1?s counter matches the timer period.
// Interrupts will be globally disabled during the ISR?s execution.
void __attribute__((__interrupt__,auto_psv)) _T3Interrupt(void)
{
    third_counter++;
    //if(third_counter%10==0)
    flag_1sec=1;
    IFS0bits.T3IF = 0; // clear the interrupt flag
}



void main(){
        TRISEbits.TRISE8 = 1; //PortE Pin 8 I/O Configuration
        AD1PCFGHbits.PCFG20 = 1; //ADC1 Port Configuration Register High Channel 20
   
        PORTEbits.RE8; //PortE Pin 8 value
        IEC1bits.INT1IE = 1; //Interrupt Enable Control Register 1
        //External Interrupt 1 Enable bit
        IPC5bits.INT1IP = 1; //Interrupt Priority Control Register 5
        //External Interrupt 1 Priority bits
        IFS1bits.INT1IF = 0; //Interrupt Flag Status Register 1
        INTCON2bits.INT1EP = 1; /*Interrupt Control Register 2 External
        Interrupt 1 Edge Detect Polarity Select bit*/

        TRISDbits.TRISD10; //PortD Pin 10 I/O C
        PORTDbits.RD10 = 1 ; //PortD Pin 10 valu
       
	//Init LCD
	__C30_UART=1;	
	lcd_initialize();
	lcd_clear();
        led_initialize();

        //int T_down = 0;
        //int T_up = 0;

        // int count_button1 = 0;
        int i;


////////////////////////////////////////////////////////////////////////////////

    CLEARBIT(T3CONbits.TON); // Disable Timer
    CLEARBIT(T3CONbits.TCS); // Select internal instruction cycle clock
    CLEARBIT(T3CONbits.TGATE); // Disable Gated Timer mode
    TMR3 = 0x00; // Clear timer register
    T3CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
    PR3 = 12800; // Load the period value
    IPC2bits.T3IP = 0x01; // Set Timer2 Interrupt Priority Level
    CLEARBIT(IFS0bits.T3IF); // Clear Timer2 Interrupt Flag
    SETBIT(IEC0bits.T3IE); // Enable Timer2 interrupt
    

////////////////////////////////////////////////////////////////////////////////

       //lcd_clear();
        uint16_t crc_cycle;
        uint8_t startbyte;
        uint8_t crc_1;
        uint8_t crc_2;
        uint8_t data;
        uint8_t leng_m;
        int counter;
        uart2_init(9600);
	while(1){
            //float timer;
            lcd_printf("HELLO");
            startbyte =uart2_getc();
            lcd_printf("%c\n", startbyte);
            
            if(!startbyte)
            {
                lcd_locate(0,1);
                SETBIT(T3CONbits.TON); // Start Timer
                flag_1sec = 0;
                //timer = TMR3;
                while(!flag_1sec && (crc_1=uart2_getc())==-1);
                //lcd_printf("1");
                while(!flag_1sec && (crc_2=uart2_getc())==-1);
                
                //lcd_printf("2");
                while(!flag_1sec && (leng_m=uart2_getc())==-1);
                //lcd_printf("3");
                 if(flag_1sec){
                    unsuccessful++;
                    uart2_putc(0);
                }
                 else{
                    //lcd_locate(1,2);
                    //lcd_printf("reached!%c%c%c\n", crc_1, crc_2, leng_m);
                    //lcd_printf("leng_m = %d\n",leng_m);
                    //for(i=0; i<10000;i++);
                    crc_cycle=0;
                    lcd_locate(7,5);
                    for(counter=1;counter<=leng_m;counter++){

                        while(!flag_1sec && (data =uart2_getc())==-1);
                        if(flag_1sec){
                           unsuccessful++;
                           uart2_putc(0);
                           break;
                        }
                        //lcd_printf("177");
                        crc_cycle = crc_update(crc_cycle,data);
                        //lcd_printf("ACK should send");

                        //for(i=0; i<10000;i++);
                    }
                    if((crc_1==crc_cycle<<8) && (crc_2==(crc_cycle&0xFF)) && !flag_1sec){
                        uart2_putc(1);
                    }
                    CLEARBIT(T3CONbits.TON); // Disable Timer
                 }
            }

            

        }
        return;
    /////////////////////////////////////////////////////////
    
}

