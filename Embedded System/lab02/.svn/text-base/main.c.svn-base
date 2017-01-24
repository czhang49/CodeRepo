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

int seconds_counter=0;
int milli_counter=0;
int main_counter = 0;

int third_counter = 0;

// Interrupt Service Routine triggered when Timer2?s counter matches the timer period.
// Interrupts will be globally disabled during the ISR?s execution.
void __attribute__((__interrupt__)) _T2Interrupt(void)
{
    milli_counter=(milli_counter+20)%1000; // Increment a global counter
    
        TOGGLELED(LED1_PORT);

   
        
    
    IFS0bits.T2IF = 0; // clear the interrupt flag
}

// Interrupt Service Routine triggered when Timer1?s counter matches the timer period.
// Interrupts will be globally disabled during the ISR?s execution.
void __attribute__((__interrupt__)) _T1Interrupt(void)
{
    seconds_counter=(seconds_counter+1)%1000; // Increment a global counter
    //lcd_printf("Timer 1 interrupt\n");
    
   
    TOGGLELED(LED2_PORT);
    IFS0bits.T1IF = 0; // clear the interrupt flag
}

// Interrupt Service Routine triggered when Timer1?s counter matches the timer period.
// Interrupts will be globally disabled during the ISR?s execution.
void __attribute__((__interrupt__)) _T3Interrupt(void)
{
    third_counter++;

    IFS0bits.T3IF = 0; // clear the interrupt flag
}

void __attribute__((__interrupt__)) _INT1Interrupt(void)
{
     milli_counter = 0;
     seconds_counter = 0;

    IFS1bits.INT1IF = 0; // clear the interrupt flag
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
//        lcd_locate(0,0);
//        lcd_printf("Deepak Shine\n");
//        lcd_printf("Chen Zhang\n");
        led_initialize();

        int T_down = 0;
        int T_up = 0;

        int count_button1 = 0;
        int i;

 ///////////////////////////////////////////////////////////////////////////////

    CLEARBIT(T2CONbits.TON); // Disable Timer
    CLEARBIT(T2CONbits.TCS); // Select internal instruction cycle clock
    CLEARBIT(T2CONbits.TGATE); // Disable Gated Timer mode
    TMR2 = 0x00; // Clear timer register
    T2CONbits.TCKPS = 0b11; // Select 1:64 Prescaler
    PR2 = 100; // Load the period value
    IPC1bits.T2IP = 0x01; // Set Timer2 Interrupt Priority Level
    CLEARBIT(IFS0bits.T2IF); // Clear Timer2 Interrupt Flag
    SETBIT(IEC0bits.T2IE); // Enable Timer2 interrupt
    SETBIT(T2CONbits.TON); // Start Timer


   /////////////////////////////////////////////////////////////////////////////
//enable LPOSCEN
__builtin_write_OSCCONL(OSCCONL | 2);
T1CONbits.TON = 0; //Disable Timer
T1CONbits.TCS = 1; //Select external clock
T1CONbits.TSYNC = 0; //Disable Synchronization
T1CONbits.TCKPS = 0b00; //Select 1:1 Prescaler
TMR1 = 0x00; //Clear timer register
PR1 = 32767; //Load the period value
IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
IEC0bits.T1IE = 1;// Enable Timer1 interrupt
T1CONbits.TON = 1;// Start Timer


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
    SETBIT(T3CONbits.TON); // Start Timer


////////////////////////////////////////////////////////////////////////////////

       //lcd_clear();

	while(1){
             TMR3 = 0x00; // Clear timer register
             //third_counter  = 0;
             TOGGLELED(LED4_PORT);
             if(main_counter%2000==0 && main_counter != 0)
             {

                lcd_locate(0,0);
                lcd_printf("%2d:%2d:%3d\r",seconds_counter/60,seconds_counter%60,milli_counter );
                //main_counter=0;
             }


            //Pressing down button #1.
            if (PORTEbits.RE8 == 0) {

            }
            else {
               // CLEARLED(LED1_PORT);
                T_up++;
            }

            //Pressing down button #2.
            if (PORTDbits.RD10 == 0) {
                
            }


            //For turning on LED3.
            if ((PORTDbits.RD10==0&&PORTEbits.RE8==1) || (PORTDbits.RD10==1&&PORTEbits.RE8==0)) {
               
            }

       
           if (T_down == 50) {
                count_button1++;
                //lcd_clear();
               // lcd_locate(0,0);
//                lcd_printf("Deepak Shine\n");
//                lcd_printf("Chen Zhang\n");
//                led_initialize();
//                lcd_printf("%d\n",count_button1);
                T_up = 0;

            }

            if (T_up == 50) {
                
               // T_down = 0;
            }
             main_counter++;
             //lcd_clear_row(5);
             if(main_counter%2000==0){
                 float trial=TMR3;
                lcd_locate(10,5);
                lcd_printf("%d\r\n", TMR3);
		Nop();
                lcd_locate(10,7);
                lcd_printf("%.4f\r\n", trial);
             }
        }
}

