/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "prng.h"

#include "anim.h"

#define TRAIL_MIN (15)
#define TRAIL_MAX (30)
#define TRAIL_DELTA (TRAIL_MAX - TRAIL_MIN)

#define DROPS_MAX  (SCREEN_COL * SCREEN_ROW / 8)

char _anim_buf[SCREEN_ROW][SCREEN_COL];

typedef struct
{
	unsigned r, c;
	unsigned speed, len;
}
drop_t;

drop_t _anim_drop[DROPS_MAX];

void anim_init (void)
{
	int i;

	for (i = 0; i < DROPS_MAX; i++)
	{
		_anim_drop[i].r = prng_gen_range (0, 500);
		_anim_drop[i].c = prng_gen_range (0, 500);

		_anim_drop[i].speed = 5 + prng_gen_range (0, 20);

		_anim_drop[i].len = TRAIL_MIN + prng_gen_range(0, TRAIL_DELTA);
	}
}

void anim_next (void)
{
	int i;

	for (i = 0; i < DROPS_MAX; i++)
	{
		_anim_drop[i].r += _anim_drop[i].speed;

		if (_anim_drop[i].r > 500)
		{
			_anim_drop[i].r -= 500;
			_anim_drop[i].c = prng_gen_range (0, 500);
		}
	}
}

void anim_render (void)
{
	int i, j;

	for (i = 0; i < SCREEN_ROW; i++)
		for (j = 0; j < SCREEN_COL; j++)
			_anim_buf[i][j] = COLOR_DARK_GREY;

	for (i = 0; i < DROPS_MAX; i++)
	{
		unsigned r, c;

		r = _anim_drop[i].r * (SCREEN_ROW + TRAIL_MAX) / 500;
		c = _anim_drop[i].c * (SCREEN_COL) / 500;

		for (j = 0; j < _anim_drop[i].len; j++)
		{
			if (r >= j)
			{
				if (j < 2)
					_anim_buf[r - j][c] = COLOR_LIGHT_GREEN;
				else
				if (j < _anim_drop[i].len / 4)
					_anim_buf[r - j][c] = COLOR_WHITE;
				else
				if (j < _anim_drop[i].len * 4 / 5)
					_anim_buf[r - j][c] = COLOR_GREEN;
				else
					_anim_buf[r - j][c] = COLOR_LIGHT_GREY;
			}
		}
	}

	for (i = 0; i < SCREEN_ROW; i++)
		for (j = 0; j < SCREEN_COL; j++)
			vga_screen_set_color (i, j, _anim_buf[i][j]);
}
