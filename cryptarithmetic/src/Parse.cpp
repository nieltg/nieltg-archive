/*
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Wed Jan 19 2017
 * Topik     : Bruteforce
 * Deskripsi : Cryptarithmetic
 */

#include <iomanip>

#include "Parse.h"

Parse::Token Parse::next (void) throw (std::underflow_error)
{
	std::string buf;
	
	if (in >> std::setw (Parse::MAX_LENGTH) >> buf)
	{
		bool sum = false;
		
		// Process '+' character
		
		if (buf == "+")
			return next ();
		else
		if (buf.back () == '+')
			buf.pop_back ();
		
		// Process sum-token
		
		if (buf.find_first_not_of ('-') == std::string::npos)
		{
			// Read value
			if (!(in >> std::setw (Parse::MAX_LENGTH) >> buf))
				throw std::underflow_error ("value is missing");
			
			sum = true;
		}
		
		Parse::Type type = (sum) ? Type::SUM : Type::ADDEND;
		Parse::Token tok (type, buf);
		
		return tok;
	}
	else
	{
		Parse::Token tok (Type::END, "");
		return tok;
	}
}
