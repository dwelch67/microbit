
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define GPIOBASE 0x50000000
#define GPIO_OUTSET (GPIOBASE+0x508)
#define GPIO_OUTCLR (GPIOBASE+0x50C)
#define GPIO_DIRSET (GPIOBASE+0x518)

#define ROW3 15
#define ROW2 14
#define ROW1 13
#define COL9 12
#define COL8 11
#define COL7 10
#define COL6  9
#define COL5  8
#define COL4  7
#define COL3  6
#define COL2  5
#define COL1  4

#define TIMER0_BASE         0x40008000
#define TIMER0_START        (TIMER0_BASE+0x000)
#define TIMER0_CAPTURE0     (TIMER0_BASE+0x040)
#define TIMER0_MODE         (TIMER0_BASE+0x504)
#define TIMER0_BITMODE      (TIMER0_BASE+0x508)
#define TIMER0_CC0          (TIMER0_BASE+0x540)
#define TIMER0_PRESCALER    (TIMER0_BASE+0x510)

int notmain ( void )
{
    unsigned int ra;

    PUT32(GPIO_DIRSET,(1<<ROW1)|(1<<COL9));
    PUT32(GPIO_OUTCLR,1<<COL9);

    PUT32(TIMER0_MODE,0);
    PUT32(TIMER0_BITMODE,3);
    PUT32(TIMER0_PRESCALER,0);
    //PUT32(TIMER0_PRESCALER,4);
    PUT32(TIMER0_START,1);

    while(1)
    {
        PUT32(GPIO_OUTSET,1<<ROW1);
        while(1)
        {
            PUT32(TIMER0_CAPTURE0,1);
            ra=GET32(TIMER0_CC0);
            if((ra&0x01000000)!=0) break;
        }
        PUT32(GPIO_OUTCLR,1<<ROW1);
        while(1)
        {
            PUT32(TIMER0_CAPTURE0,1);
            ra=GET32(TIMER0_CC0);
            if((ra&0x01000000)==0) break;
        }
    }

    return(0);
}
