/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "prng.h"

unsigned prng_seed = 0xFF;

/*
 * http://stackoverflow.com/questions/19083566/
 * what-are-the-better-pseudo-random-number-generator-than-the-lcg-for-lottery-sc
 */

unsigned _prng_temper (unsigned x)
{
	x ^= x >> 5;
	x ^= x << 3 & 0x9258;
	x ^= x << 7 & 0xEC00;
	x ^= x >> 9;

	return x;
}

unsigned prng_gen (void)
{
	prng_seed = 0x5F47 * prng_seed + 1;

	return _prng_temper (prng_seed);
}

unsigned prng_gen_range (unsigned a, unsigned b)
{
	unsigned d = b - a;

	return a + (prng_gen () % d);
}
