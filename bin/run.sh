#!/bin/sh

mkdir -p out

echo "Sort using Divide & Conquer"
echo "By: 13515071 Daniel Pintara"
echo

echo "Compiling... "

make
make bin/test/gen

echo "done."
echo

unit_test()
{
	echo "Generating $1 data... "

	src="out/src-$1.txt"
	log="out/log-$1.txt"

	bin/test/gen $1 > "${src}"

	echo "Benchmarking... "

	cat "${src}" | bin/main | tee "${log}" | grep sort

	echo "done."
	echo
}

unit_test 1000
unit_test 5000
unit_test 10000
unit_test 50000
unit_test 100000
unit_test 500000
unit_test 1000000

