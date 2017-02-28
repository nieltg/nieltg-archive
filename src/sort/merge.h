/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#pragma once

#include <algorithm>
#include <vector>

/**
 * @brief Mengurutkan data menggunakan algoritma merge-sort.
 * @param  _first Penunjuk pertama pada data
 * @param  _last Penunjuk terakhir pada data
 */
template
	<class RandomAccessIterator,
	 class Compare = std::less<typename RandomAccessIterator::value_type>>
void sort_merge
	(RandomAccessIterator _first, RandomAccessIterator _last,
	 Compare _func = std::less<typename RandomAccessIterator::value_type> ())
{
	const size_t dist = std::distance (_first, _last);

	if (dist > 1)
	{
		const size_t h = dist / 2;

		const RandomAccessIterator src_mid = _first + h;

		sort_merge (_first, src_mid, _func);
		sort_merge (src_mid, _last, _func);

		// Merge

		using T = typename RandomAccessIterator::value_type;

		std::vector<T> vec (_first, _last);

		const typename std::vector<T>::iterator mid = vec.begin () + h;

		typename std::vector<T>::iterator pri = vec.begin ();
		typename std::vector<T>::iterator sec = mid;
		typename std::vector<T>::iterator dst = _first;

		while ((pri != mid) && (sec != vec.end ()))
		{
			if (_func (*sec, *pri))
				*(dst++) = *(sec++);
			else
				*(dst++) = *(pri++);
		}

		while (pri != mid)
			*(dst++) = *(pri++);

		while (sec != vec.end ())
			*(dst++) = *(sec++);
	}
}
