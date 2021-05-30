void PUT32(unsigned int, unsigned int);
void dummy(unsigned int);

#define GPIOBASE 0x50000000
#define GPIO_OUTSET (GPIOBASE + 0x508)
#define GPIO_OUTCLR (GPIOBASE + 0x50C)
#define GPIO_DIRSET (GPIOBASE + 0x518)

unsigned char grid[5][5][2] = {
	{{13, 4},{14, 7},{13, 5},{14, 8},{13, 6}},
	{{15, 7},{15, 8},{15, 9},{15,10},{15,11}},
	{{14, 5},{13,12},{14, 6},{15,12},{14, 4}},
	{{13,11},{13,10},{13, 9},{13, 8},{13, 7}},
	{{15, 6},{14,10},{15, 4},{14, 9},{15, 5}}
};

unsigned char image[5][5] = {
	{0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0}
};

// Stupid timer
void delay() {
	for (unsigned int ra = 0; ra < 20; ra++);
}

void pixel(unsigned int x, unsigned int y) {
	PUT32(GPIO_OUTSET, 1 << grid[x][y][0]);
	PUT32(GPIO_OUTCLR, 1 << grid[x][y][1]);
	delay();
	PUT32(GPIO_OUTCLR, 1 << grid[x][y][0]);
	PUT32(GPIO_OUTSET, 1 << grid[x][y][1]);
}

void start() {
	PUT32(GPIO_DIRSET, 0xFFF0);
	PUT32(GPIO_OUTCLR, 0xE000);
	PUT32(GPIO_OUTSET, 0x1FF0);

	// Plot a pixel, sleep, clear, repeat,
	// like a CRT. Kinda stupid, but works.
	while (1) {
		for (unsigned int x = 0; x < 5; x++) {
			for (unsigned int y = 0; y < 5; y++) {
				if (image[x][y]) {
					pixel(x, y);
				}
			}
		}
	}
}
