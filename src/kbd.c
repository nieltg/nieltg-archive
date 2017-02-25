/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "anim.h"

#include "kbd.h"

void _kbd_irq_handler (void)
{
	char ch = inb (0x60);

	if (ch < 0x80)
		anim_is_enabled = !anim_is_enabled;

	outb (0x20, 0x61);
}

void kbd_init (void)
{
#asm
	cli
#endasm

	/*
	 * http://inglorion.net/documents/tutorials/x86ostut/keyboard
	 * http://wiki.osdev.org/Interrupt_Vector_Table
	 */

	outb (0x43, 00110100b);

	outb (0x40, 0xFF);
	outb (0x40, 0xFF);

#asm
	push    ds
	push    *0x0
	pop     ds
	mov     [0x24], #_kbd_init_irq
	mov     [0x26], cs
	sti
	pop     ds
	jmp     _kbd_init_end
_kbd_init_irq:
	cli
	pusha
	call    __kbd_irq_handler
	popa
	sti
	iret
_kbd_init_end:
#endasm
}
