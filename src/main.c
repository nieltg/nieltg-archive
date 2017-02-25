/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "anim.h"
#include "payload.h"
#include "timer.h"
#include "vga.h"

int kernel_main (void)
{
	vga_cursor_hide ();

	vga_screen_write_all (0, 0, payload_bitmap, COLOR_BLACK);

	anim_init ();
	anim_render ();

	timer_init ();
	kbd_init ();

#asm
_kernel_main_loop:
	hlt
	jmp     _kernel_main_loop
#endasm

	return 0;
}
