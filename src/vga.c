/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "vga.h"

#define SCREEN_OFFSET(r, c)      (c + (r * SCREEN_COL))
#define SCREEN_MEM_OFFSET(r, c)  (2 * SCREEN_OFFSET (r, c))

void vga_cursor_hide (void)
{
	/*
	 * http://forum.osdev.org/viewtopic.php?f=1&t=15669
	 * http://osdever.net/FreeVGA/vga/crtcreg.htm
	 */

	outb (0x3D4, 0x0A);
	outb (0x3D5, 0x20);
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

void vga_screen_write_all (size_t r, size_t c, char* str, char col)
{
	size_t i = SCREEN_MEM_OFFSET (r, c);

	while (*str)
	{
		putInMemory (0xB000, 0x8000 + i++, *str++);
		putInMemory (0xB000, 0x8000 + i++, col);
	}
}
