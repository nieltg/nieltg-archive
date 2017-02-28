/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#pragma once

#include <algorithm>

/**
 * @brief Mengurutkan data menggunakan algoritma insertion.
 * @param  _first Penunjuk pertama pada data
 * @param  _last Penunjuk terakhir pada data
 */
template
	<class RandomAccessIterator,
	 class Compare = std::less<typename RandomAccessIterator::value_type>>
void sort_insert
	(RandomAccessIterator _first, RandomAccessIterator _last,
	 Compare _func = std::less<typename RandomAccessIterator::value_type> ())
{
	for (RandomAccessIterator it = _first; it != _last; ++it)
	{
		RandomAccessIterator j = it;

		while (j != _first)
		{
			const RandomAccessIterator k = j--;

			if (_func (*j, *k))
				j = _first;
			else
				std::swap (*j, *k);
		}
	}
}
