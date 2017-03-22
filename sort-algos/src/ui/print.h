/*
 * Tugas Kecil 2 IF2211 Strategi Algoritma
 */

#pragma once

#include <iomanip>
#include <ostream>

template
	<class ForwardIterator>
void pretty_print
	(std::ostream& _s, ForwardIterator _first, ForwardIterator _last)
{
	constexpr uint32_t sep = 1;
	constexpr uint32_t col = 80;

	using T = typename ForwardIterator::value_type;

	if (_first == _last)
	{
		_s << "(no data)" << std::endl;

		return;
	}

	T val = *std::max_element (_first, _last);

	// Count padding

	uint32_t pad = sep;

	if (val)
	{
		while (val)
		{
			pad++;
			val /= 10;
		}
	}
	else
		pad++;

	uint32_t cnt = col / pad;

	// Print numbers

	uint32_t i = 0;

	for (ForwardIterator it = _first; it != _last; ++it)
	{
		if (++i > cnt)
		{
			_s << std::endl;
			i = 1;
		}

		_s << std::setw (pad) << *it;
	}

	_s << std::endl;
}
