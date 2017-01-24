// Tri-state registers
#define LEDTRIS		TRISA
#define LED1_TRIS	TRISAbits.TRISA4
#define LED2_TRIS	TRISAbits.TRISA5
#define LED3_TRIS	TRISAbits.TRISA9
#define LED4_TRIS	TRISAbits.TRISA10
#define LED5_TRIS	TRISAbits.TRISA0

// Port registers using predefined structs
#define LEDPORT		PORTA
#define	LED1_PORT	PORTAbits.RA4
#define	LED2_PORT	PORTAbits.RA5
#define LED3_PORT	PORTAbits.RA9
#define LED4_PORT	PORTAbits.RA10
#define LED5_PORT	PORTAbits.RA0

// LEDPORT Bitwise definitions
#define LED1	4
#define LED2	5
#define LED3	9
#define LED4	10
#define LED5	0
//LED init
#define led_initialize() \
	CLEARLED(LED1_TRIS); \
	CLEARLED(LED2_TRIS); \
	CLEARLED(LED3_TRIS); \
	CLEARLED(LED4_TRIS); \
	CLEARLED(LED5_TRIS);

        











