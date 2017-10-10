
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
#define UART_STOPTX     (UART_BASE+0x00C)
#define UART_TXREADY    (UART_BASE+0x11C)
#define UART_ENABLE     (UART_BASE+0x500)
#define UART_PSELTXD    (UART_BASE+0x50C)
#define UART_TXD        (UART_BASE+0x51C)
#define UART_BAUDRATE   (UART_BASE+0x524)
#define UART_CONFIG     (UART_BASE+0x56C)

static void uart_init ( void )
{
    PUT32(GPIO_DIRSET,1<<24);
    PUT32(UART_BAUDRATE,0x01D7E000); //115200
    //PUT32(UART_BAUDRATE,0x00EBF000); //57600
    PUT32(UART_PSELTXD,24);
    PUT32(UART_ENABLE,4);
    PUT32(UART_STARTTX,1);
    //PUT32(UART_TXD,0x00); //force txready
}
static void uart_send ( unsigned int x )
{
    PUT32(UART_TXD,x);
    while(GET32(UART_TXREADY)==0) continue;
    PUT32(UART_TXREADY,0);
}
static void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}

static void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}

int notmain ( void )
{
    unsigned int ra;

    uart_init();
    hexstring(0x12345678);

    //for(ra=0;;ra++) hexstring(ra);
    for(ra=0x30;;ra++)
    {
        ra&=0x37; uart_send(ra);
    }

    return(0);
}
