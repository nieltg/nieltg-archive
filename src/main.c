/**
 * Tugas OS
 */

#define COLOR_BLACK         (0)
#define COLOR_BLUE          (1)
#define COLOR_GREEN         (2)
#define COLOR_CYAN          (3)
#define COLOR_RED           (4)
#define COLOR_MAGENTA       (5)
#define COLOR_BROWN         (6)
#define COLOR_LIGHT_GREY    (7)
#define COLOR_DARK_GREY     (8)
#define COLOR_LIGHT_BLUE    (9)
#define COLOR_LIGHT_GREEN   (10)
#define COLOR_LIGHT_CYAN    (11)
#define COLOR_LIGHT_RED     (12)
#define COLOR_LIGHT_MAGENTA (13)
#define COLOR_LIGHT_BROWN   (14)
#define COLOR_WHITE         (15)

#define MAX_SCREEN  (2 * 80 * 25)

int cursor = 0;

void print (int color, char* str)
{
	while (*str)
	{
		cursor %= MAX_SCREEN;
		
		putInMemory (0xB000, 0x8000 + cursor++, *str++);
		putInMemory (0xB000, 0x8000 + cursor++, color);
	}
}

int kernel_main (void)
{
	print (COLOR_WHITE, "Hello World! ");
	
	return 0;
}
