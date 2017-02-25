/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "reboot.h"

void reboot (void)
{
	/*
	 * https://en.wikipedia.org/wiki/Reset_vector
	 */

#asm
	jmp     *0xFFFF:0
#endasm
}
