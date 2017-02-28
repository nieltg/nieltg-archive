/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include <ui/print.h>

int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " COUNT" << std::endl;

		return EXIT_FAILURE;
	}

	int len = atoi (argv[1]);

	if (len < 0)
	{
		std::cerr << argv[0] << ": Length must not negative" << std::endl;

		return EXIT_FAILURE;
	}

	// Generator

	std::vector<int> data;

	for (size_t i = 1; i <= len; i++)
		data.push_back (i);

	std::random_device rd;
	std::mt19937 prng (rd ());

	std::shuffle (data.begin (), data.end (), prng);

	// Pretty-print

	pretty_print (std::cout, data.begin (), data.end ());

	return EXIT_SUCCESS;
}
