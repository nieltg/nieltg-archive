/**
 * Tugas Besar 1 IF2230 Operating System
 */

#ifndef __VGA_H__
#define __VGA_H__ 1

#include <stddef.h>

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

#define SCREEN_ROW   (25)
#define SCREEN_COL   (80)
#define SCREEN_SIZE  (SCREEN_ROW * SCREEN_COL)

#define SCREEN_MEM_MAX  (SCREEN_SIZE * 2)

void vga_cursor_hide (void);
void vga_cursor_set_location (size_t r, size_t c);

void vga_screen_set_all (size_t r, size_t c, char ch, char col);
void vga_screen_set_color (size_t r, size_t c, char col);

void vga_screen_write (size_t r, size_t c, char* str);

#endif
