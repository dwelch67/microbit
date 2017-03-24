
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

int notmain ( void )
{
    unsigned int ra;
    PUT32(GPIO_DIRSET,(1<<ROW1)|(1<<COL9));
    PUT32(GPIO_OUTCLR,1<<COL9);
    while(1)
    {
        PUT32(GPIO_OUTCLR,1<<ROW1);
        for(ra=0;ra<200000;ra++) dummy(ra);
        PUT32(GPIO_OUTSET,1<<ROW1);
        for(ra=0;ra<200000;ra++) dummy(ra);
    }
    return(0);
}
