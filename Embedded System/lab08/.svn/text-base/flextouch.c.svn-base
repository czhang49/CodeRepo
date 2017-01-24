#include "flextouch.h"




void adc_init()
{
        /* INIT ADC */
        //disable ADC
	CLEARBIT(AD2CON1bits.ADON);
	//initialize PIN
	SETBIT(TRISBbits.TRISB9); //set TRISB B4 to input
        SETBIT(TRISBbits.TRISB15); // Set trisb b5 to input
        CLEARBIT(AD2PCFGLbits.PCFG9);
        CLEARBIT(AD2PCFGLbits.PCFG15);

	//Configure AD2CON1
	SETBIT(AD2CON1bits.AD12B); //set 12b Operation Mode
	AD2CON1bits.FORM = 0; //set integer output
	AD2CON1bits.SSRC = 0x7; //set automatic conversion
	AD2CON2 = 0; //not using scanning sampling
	//Configure AD1CON3
	CLEARBIT(AD2CON3bits.ADRC); //internal clock source
	AD2CON3bits.SAMC = 0x1F; //sample-to-conversion clock = 31Tad
	AD2CON3bits.ADCS = 0x2; //Tad = 3Tcy (Time cycles)
	//enable ADC
	SETBIT(AD2CON1bits.ADON);
}


void touch_init()
{
    //set up the I/O pins E1, E2, E3 to be output pins
    CLEARBIT(TRISEbits.TRISE1); //I/O pin set to output
    CLEARBIT(TRISEbits.TRISE2); //I/O pin set to output
    CLEARBIT(TRISEbits.TRISE3); //I/O pin set to output

}





void touch_select_dim(uint8_t dim)
{
    if(dim==0){ // x-dim
        //set up the I/O pins E1, E2, E3 so that the touchscreen X-coordinate pin
        //connects to the ADC
        CLEARBIT(LATEbits.LATE1);
        SETBIT(LATEbits.LATE2);
        SETBIT(LATEbits.LATE3);
    }
    else if(dim==1){ //y-dim
        //set up the I/O pins E1, E2, E3 so that the touchscreen Y-coordinate pin
        //connects to the ADC
        SETBIT(LATEbits.LATE1);
        CLEARBIT(LATEbits.LATE2);
        CLEARBIT(LATEbits.LATE3);
    }
    else{
        SETBIT(LATEbits.LATE1);
        SETBIT(LATEbits.LATE2);
        CLEARBIT(LATEbits.LATE3);
    }

}



uint16_t touch_adc()
{
    SETBIT(AD2CON1bits.SAMP); //start to sample
    while(!AD2CON1bits.DONE); //wait for conversion to finish
    CLEARBIT(AD2CON1bits.DONE); //MUST HAVE! clear conversion done bit
    return ADC2BUF0; //return sample
}

