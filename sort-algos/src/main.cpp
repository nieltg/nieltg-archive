/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#include <unistd.h>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

#include <sort/select.h>
#include <sort/insert.h>
#include <sort/merge.h>
#include <sort/quick.h>
#include <ui/print.h>

template
	<typename Sort, typename Compare, typename T>
void unit_test
	(std::vector<T> data, Sort sort_func, Compare comp_func)
{
	clock_t cl = clock ();
	sort_func (data.begin (), data.end (), comp_func);
	uint32_t d = (clock () - cl) / (CLOCKS_PER_SEC / 1000);

	if (std::is_sorted (data.begin (), data.end (), comp_func))
		std::cout << "ok";
	else
		std::cout << "fail";

	std::cout << " in " << d << " ms" << std::endl;

	pretty_print (std::cout, data.begin (), data.end ());
}

int main (int argc, char** argv)
{
	if (argc != 1)
	{
		std::cerr << "Usage: " << argv[0] << " < FILE" << std::endl;

		return EXIT_FAILURE;
	}

	// Read

	std::cout << "Read: " << std::flush;

	std::vector<int_fast32_t> src;

	int_fast32_t buf;

	while (std::cin >> buf)
		src.push_back (buf);

	std::cout << src.size () << " data(s)" << std::endl;

	// Quick

	std::cout << "Quick-sort: " << std::flush;

	unit_test
		(src, sort_quick<std::vector<int_fast32_t>::iterator,
		 std::less<int_fast32_t>>, std::less<int_fast32_t> ());

	std::cout << std::endl;

	// Merge

	std::cout << "Merge-sort: " << std::flush;

	unit_test
		(src, sort_merge<std::vector<int_fast32_t>::iterator,
		 std::less<int_fast32_t>>, std::less<int_fast32_t> ());

	std::cout << std::endl;

	// Insert

	std::cout << "Insert-sort: " << std::flush;

	unit_test
		(src, sort_insert<std::vector<int_fast32_t>::iterator,
		 std::less<int_fast32_t>>, std::less<int_fast32_t> ());

	std::cout << std::endl;

	// Select

	std::cout << "Select-sort: " << std::flush;

	unit_test
		(src, sort_select<std::vector<int_fast32_t>::iterator,
		 std::less<int_fast32_t>>, std::less<int_fast32_t> ());
}
