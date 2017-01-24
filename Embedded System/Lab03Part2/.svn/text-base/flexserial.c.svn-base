#include "flexserial.h"



void uart2_init(uint16_t baud){
    CLEARBIT(U2MODEbits.UARTEN); //Disable UART2 for config
    /* Disable Interrupts */
    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;

    /* Clear Interrupt flag bits */
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;


    /* Set IO pins */
    TRISFbits.TRISF2 = 1; //set as input UART2 RX pin
    TRISFbits.TRISF3 = 0; //set as output UART2 TX pin


    /* baud rate */
    // use the following equation to compute the proper
    // setting for a specific baud rate
    U2MODEbits.BRGH = 0; //Set low speed baud rate
    U2BRG = (uint32_t)800000/baud-1; // don't safe ;' -1; //Set the baudrate to baud

    /* Operation settings and start port */
    U2MODE = 0; // 8-bit, no parity and, 1 stop bit
    U2MODEbits.RTSMD = 0; //select simplex mode
    U2MODEbits.UEN = 0; //select simplex mode
    U2MODE |= 0x00;
    U2MODEbits.UARTEN = 1; //enable UART
    U2STA = 0;
    U2STAbits.UTXEN = 1; //enable UART TX

}


int uart2_putc(uint8_t c){
    
    while (U2STAbits.UTXBF);
    U2TXREG = c;
    while(!U2STAbits.TRMT);
    return 1;

}

uint8_t uart2_getc(){

    //uint8_t* data;
    //while(1)
   // {
        
        if (U2STAbits.OERR) {
            //lcd_printf("reached first if!\n");
            
            U2STAbits.OERR = 0;
        }
        if (U2STAbits.URXDA) {
            //lcd_printf("reached second if!\n");
            //cd_printf("\nStart Get C\n")
            return U2RXREG & 0x00FF;

        }
        return -1;
   // }//lcd_printf("data = %c\n", *data);
    //return -1;

}

