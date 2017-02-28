/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#pragma once

#include <algorithm>

/**
 * @brief Mengurutkan data menggunakan algoritma quick-sort.
 * @param  _first Penunjuk pertama pada data
 * @param  _last Penunjuk terakhir pada data
 */
template
	<class RandomAccessIterator,
	 class Compare = std::less<typename RandomAccessIterator::value_type>>
void sort_quick
	(RandomAccessIterator _first, RandomAccessIterator _last,
	 Compare _func = std::less<typename RandomAccessIterator::value_type> ())
{
	const size_t dist = std::distance (_first, _last);

	if (dist > 1)
	{
		const size_t h = dist / 2;

		const RandomAccessIterator p = _first + h;
		std::swap (*p, *_first);

		RandomAccessIterator dst = _first + 1;

		for (RandomAccessIterator it = dst; it != _last; ++it)
		{
			if (_func (*it, *_first))
				std::swap (*(dst++), *it);
		}

		std::swap (*_first, *(--dst));

		// Recurse

		sort_quick (_first, dst, _func);
		sort_quick (dst + 1, _last, _func);
	}
}
