
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define GPIOBASE 0x50000000
#define GPIO_OUTSET (GPIOBASE+0x508)
#define GPIO_OUTCLR (GPIOBASE+0x50C)
#define GPIO_DIRSET (GPIOBASE+0x518)

//unsigned int rgrid[5][5]=
//{
//{11,24,12,25,13},
//{34,35,36,37,38},
//{22,19,23,39,21},
//{18,17,16,15,14},
//{33,27,31,26,32},
//};

const unsigned char grid[5][5][2]=
{
  {{13, 4},{14, 7},{13, 5},{14, 8},{13, 6},},
  {{15, 7},{15, 8},{15, 9},{15,10},{15,11},},
  {{14, 5},{13,12},{14, 6},{15,12},{14, 4},},
  {{13,11},{13,10},{13, 9},{13, 8},{13, 7},},
  {{15, 6},{14,10},{15, 4},{14, 9},{15, 5},},
};


static void delay ( void )
{
    unsigned int ra;
    for(ra=0;ra<200000;ra++) dummy(ra);
}

int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    PUT32(GPIO_DIRSET,0xFFF0);
    PUT32(GPIO_OUTCLR,0xE000);
    PUT32(GPIO_OUTSET,0x1FF0);

    while(1)
    {
        for(ra=0;ra<5;ra++)
        {
            for(rb=0;rb<5;rb++)
            {
                PUT32(GPIO_OUTSET,1<<grid[ra][rb][0]);
                PUT32(GPIO_OUTCLR,1<<grid[ra][rb][1]);
                delay();
                PUT32(GPIO_OUTCLR,1<<grid[ra][rb][0]);
                PUT32(GPIO_OUTSET,1<<grid[ra][rb][1]);
            }
        }
    }
    return(0);
}
