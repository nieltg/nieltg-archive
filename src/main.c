/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "anim.h"
#include "payload.h"
#include "vga.h"

void busy_wait (void)
{
	unsigned i, j;

	for (i = 0; i < 32767; i++)
		for (j = 0; j < 40; j++);
}

int kernel_main (void)
{
	vga_cursor_hide ();

	vga_screen_write (0, 0, payload_bitmap);

	anim_init ();
	anim_render ();

	while (1)
	{
		busy_wait ();

		anim_next ();
		anim_render ();
	}

	return 0;
}
