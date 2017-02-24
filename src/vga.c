/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "vga.h"

#define SCREEN_OFFSET(r, c)      (c + (r * SCREEN_COL))
#define SCREEN_MEM_OFFSET(r, c)  (2 * SCREEN_OFFSET (r, c))

void vga_cursor_hide (void)
{
	/* TODO: implement vga_cursor_hide */
}

void vga_screen_set_all (size_t r, size_t c, char ch, char col)
{
	size_t i = SCREEN_MEM_OFFSET (r, c);

	putInMemory (0xB000, 0x8000 + i, ch);
	putInMemory (0xB000, 0x8001 + i, col);
}

void vga_screen_set_color (size_t r, size_t c, char col)
{
	size_t i = SCREEN_MEM_OFFSET (r, c);

	putInMemory (0xB000, 0x8001 + i, col);
}

void vga_screen_write (size_t r, size_t c, char* str)
{
	size_t i = SCREEN_MEM_OFFSET (r, c);

	while (*str)
	{
		putInMemory (0xB000, 0x8000 + i, *str++);
		i += 2;
	}
}
