/**
 * Tugas Besar 1 IF2230 Operating System
 */

#ifndef __ANIM_H__
#define __ANIM_H__ 1

#include "vga.h"

extern int anim_is_enabled;

void anim_init (void);
void anim_next (void);

int anim_is_idle (void);

void anim_render (void);

#endif
