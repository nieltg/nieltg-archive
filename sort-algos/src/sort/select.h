/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#pragma once

#include <algorithm>

/**
 * @brief Mengurutkan data menggunakan algoritma selection.
 * @param  _first Penunjuk pertama pada data
 * @param  _last Penunjuk terakhir pada data
 * @param  _func Fungsi komparasi
 */
template
	<class RandomAccessIterator,
	 class Compare = std::less<typename RandomAccessIterator::value_type>>
void sort_select
	(RandomAccessIterator _first, RandomAccessIterator _last,
	 Compare _func = std::less<typename RandomAccessIterator::value_type> ())
{
	for (RandomAccessIterator it = _first; it != _last; ++it)
	{
		RandomAccessIterator t = it;

		for (RandomAccessIterator j = (t + 1); j != _last; ++j)
		{
			if (_func (*j, *t))
				t = j;
		}

		std::swap (*it, *t);
	}
}
