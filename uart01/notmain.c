
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );


//TX 24
//RX 25


#define GPIOBASE 0x50000000
#define GPIO_OUTSET (GPIOBASE+0x508)
#define GPIO_OUTCLR (GPIOBASE+0x50C)
#define GPIO_DIRSET (GPIOBASE+0x518)

#define UART_BASE       0x40002000
#define UART_STARTTX    (UART_BASE+0x008)
#define UART_ENABLE     (UART_BASE+0x500)
#define UART_PSELTXD    (UART_BASE+0x50C)
#define UART_TXD        (UART_BASE+0x51C)
#define UART_BAUDRATE   (UART_BASE+0x524)
#define UART_CONFIG     (UART_BASE+0x56C)

int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;
    
    PUT32(GPIO_DIRSET,1<<24);
    PUT32(UART_BAUDRATE,0x01D7E000);
    PUT32(UART_PSELTXD,24);
    PUT32(UART_ENABLE,4);
    PUT32(UART_STARTTX,1);

    for(rb=0;;rb++)
    {
        PUT32(UART_TXD,0x30+(rb&7));
        for(ra=0;ra<0x200;ra++) dummy(ra);
    }
    return(0);
}
