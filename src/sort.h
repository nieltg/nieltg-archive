/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#pragma once

#include <vector>

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

/**
 * @brief Mengurutkan data menggunakan algoritma selection.
 * @param  _first Penunjuk pertama pada data
 * @param  _last Penunjuk terakhir pada data
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
